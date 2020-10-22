#include<bitset>
#include<cassert>
#include<chrono>
#include<cmath>
#include<cstddef>
#include<cstdlib>
#include<ctime>
#include<cctype>
#include<filesystem>
#include<fstream>
#include<functional>
#include<iomanip>
#include<ios>
#include<iostream>
#include<iterator>
#include<locale>
#include<map>
#include<mutex>
#include<numeric>
#include<optional>
#include<random>
#include<set>
#include<sstream>
#include<string>
#include<string_view>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>


#include <sqlite3.h>

//https://tociyuki.hatenablog.jp/entry/20141218/1418914334
namespace sqlite3pp {
class statement {
private:
    std::shared_ptr<struct sqlite3_stmt> mstmt;
public:
    statement (sqlite3_stmt* pstmt) : mstmt (pstmt, sqlite3_finalize) { }
    int reset () { return sqlite3_reset (mstmt.get ()); }
    int bind (int n, int v) { return sqlite3_bind_int (mstmt.get (), n, v); }
    int bind (int n, double v) { return sqlite3_bind_double (mstmt.get (), n, v); }
    int bind (int n, std::string s) {
        return sqlite3_bind_text (mstmt.get (), n, s.c_str (), (int)s.size (), SQLITE_TRANSIENT);
    }
    int step () { return sqlite3_step (mstmt.get ()); }
    int column_int (int n) { return sqlite3_column_int (mstmt.get (), n); }
    double column_double (int n) { return sqlite3_column_double (mstmt.get (), n); }
    std::string column_string (int n)
    {
        return std::string((char const*)sqlite3_column_text (mstmt.get (), n),
            sqlite3_column_bytes (mstmt.get (), n));
    }
};

class connection {
private:
    std::shared_ptr<struct sqlite3> mdb;
    int mstatus;
public:
    connection (std::string s)
    {
        sqlite3* db;
        mstatus = sqlite3_open (s.c_str (), &db);
        mdb = std::shared_ptr<struct sqlite3>(db, sqlite3_close);
    }
    statement prepare (std::string s)
    {
        sqlite3_stmt* stmt;
        mstatus = sqlite3_prepare_v2 (mdb.get (), s.c_str (), s.size (), &stmt, 0);
        return statement (stmt);
    }
    int status () { return mstatus; }
    std::string errmsg () { return std::string (sqlite3_errmsg (mdb.get ())); }
    sqlite3_int64 last_insert_rowid () { return sqlite3_last_insert_rowid (mdb.get ()); }
    int execute (std::string s)
    {
        sqlite3_stmt* stmt;
        mstatus = sqlite3_prepare_v2 (mdb.get (), s.c_str (), s.size (), &stmt, 0);
        if (SQLITE_OK == mstatus)
            mstatus = sqlite3_step (stmt);
        if (SQLITE_DONE != mstatus && SQLITE_ROW != mstatus)
            std::cerr << "sqlite3_execute: " << errmsg () << ": " << s << std::endl; /* 2014年12月19日修正 stmt -> s */
        sqlite3_finalize (stmt);
        return mstatus;
    }
};
}


 
void read_database(std::string const& filename)
{
    sqlite3pp::connection data(filename);

    if (data.status() != SQLITE_OK) std::cerr << "sqlite3 error" << std::endl;

    auto st = data.prepare("SELECT rowid, title, year, length FROM movies");
    st.reset();
    while (st.step() == SQLITE_ROW)
    {
        std::string id = st.column_string(0);
        std::cout << "-" << std::endl;
        std::cout << " id : " << id << std::endl;
        std::cout << " title : " << st.column_string (1) << std::endl;
        std::cout << " year  : " << st.column_string (2) << std::endl;
        std::cout << " length: " << st.column_string (3) << std::endl;
        auto stdi = data.prepare(
            "SELECT * FROM (SELECT name FROM persons WHERE rowid = (SELECT personid FROM directors WHERE movieid ="+ id 
            +" ) )");
        std::cout << " directors: \n";
        while (stdi.step() == SQLITE_ROW)
        {
            std::cout << "    " << stdi.column_string(0) << std::endl;
        }
        auto stw = data.prepare(
            "SELECT * FROM (SELECT name FROM persons WHERE rowid = (SELECT personid FROM writers WHERE movieid ="+ id 
            +" ) )");
        std::cout << " writers: \n";
        while (stw.step() == SQLITE_ROW)
        {
            std::cout << "    " << stw.column_string(0) << std::endl;
        }
        std::cout << " cast: \n";
        auto stc = data.prepare(
            "SELECT role, name FROM (SELECT role, name, movieid FROM (SELECT role, name, movieid FROM casting INNER JOIN persons ON casting.personid = persons.rowid) WHERE movieid = "+ id 
            +" )");
        while (stc.step() == SQLITE_ROW)
        {
            std::cout << "    " << "role: " << stc.column_string(0) << " name: " << stc.column_string(1) << std::endl;
        }
    }
}

int main() 
{
    read_database("pr85.db");
}
