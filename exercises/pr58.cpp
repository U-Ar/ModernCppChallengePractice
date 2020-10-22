#include<array>
#include<cassert>
#include<chrono>
#include<cmath>
#include<cstdlib>
#include<ctime>
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
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

int ctoi(char const c)
{
    return c - 'A';
}
char itoc(int const i)
{
    return i + 'A';
}

int main() 
{
    int V, E;
    std::cin >> V >> E;
    std::vector<int> d(V,100000);
    std::vector<bool> used(V,false);
    std::vector<int> ansc(V,-1);
    std::vector<std::vector<int> > G(V,std::vector<int>(V,100000));
    char a,b;
    int e;
    for (int i = 0; i < E; i++)
    {
        std::cin >> a >> b >> e;
        G[ctoi(a)][ctoi(b)] = G[ctoi(b)][ctoi(a)] = e;
    }
    std::cin >> a;
    int start = ctoi(a);

    d[start] = 0;
    while (true) {
        int v = -1;
        for (int u = 0; u < V; u++)
        {
            if (!used[u] && (v==-1 || d[u] < d[v])) v = u;
        }

        if (v == -1) break;
        used[v] = true;

        for (int u = 0; u < V; u++)
        {
            if (d[v]+G[v][u] < d[u])
            {
                ansc[u] = v;
                d[u] = d[v]+G[v][u];
            }
        }
    }

    for (int u = 0; u < V; u++)
    {
        std::cout << itoc(start) << " -> " << itoc(u) << " : "
        << std::setw(7) << std::setfill(' ') << std::left 
        << d[u];
        std::string tmp;
        tmp += itoc(u);
        int v = u;
        while (v != start)
        {
            v = ansc[v];
            tmp = " -> " + tmp;
            tmp = itoc(v) + tmp;
        }

        std::cout << tmp << std::endl;
    }

    


}

