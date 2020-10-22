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
#include<set>
#include<sstream>
#include<string>
#include<thread>
#include<type_traits>
#include<utility>
#include<vector>

//隣接リスト式グラフ表現
template<typename Vertex = int, typename Weight = double>
class graph 
{
public:
    using vertex_type = Vertex;
    using weight_type = Weight;
    using neighbor_type = std::pair<Vertex, Weight>;
    using neighbor_list_type = std::vector<neighbor_type>;

    void add_edge(Vertex const source, Vertex const target, 
                  Weight const weight, bool const bidirectional = true)
    {
        adjacency_list[source].push_back(std::make_pair(target,weight));
        if (bidirectional)
        adjacency_list[target].push_back(std::make_pair(source,weight));
    }
    constexpr size_t vertex_count() const { return adjacency_list.size(); }
    std::vector<Vertex> vertices() const 
    {
        std::vector<Vertex> v {};
        for (auto const& p : adjacency_list)
        {
            v.push_back(p.first);
        }
        return v;
    }
    neighbor_list_type const & neighbors(Vertex const & v) const 
    {
        auto pos = adjacency_list.find(v);
        if (pos == adjacency_list.end()) throw std::runtime_error("vertex not found");
        return pos->second;
    }
    constexpr static Weight Infinity = std::numeric_limits<Weight>::infinity();
private:
    std::map<vertex_type, neighbor_list_type> adjacency_list;
};

template<typename Vertex, typename Weight>
void shortest_path(graph<Vertex, Weight> const & g,
                    Vertex const source,
                    std::map<Vertex, Weight>& min_distance,
                    std::map<Vertex, Vertex>& previous)
{
    auto const vertices = g.vertices();

    min_distance.clear();
    for (auto const & v : vertices)
    {
        min_distance[v] = graph<Vertex, Weight>::Infinity;
    }
    min_distance[source] = 0;

    previous.clear();

    std::set<std::pair<Weight, Vertex>> vertex_queue;
    vertex_queue.insert(std::make_pair(min_distance[source],source));

    while (!vertex_queue.empty())
    {
        auto dist = vertex_queue.begin()->first;
        auto u = vertex_queue.begin()->second;

        vertex_queue.erase(std::begin(vertex_queue));

        auto const & neighbors = g.neighbors(u);
        for (auto const& [v, w] : neighbors)
        {
            auto dist_via_u = dist+w;
            if (dist_via_u < min_distance[v])
            {
                vertex_queue.erase(std::make_pair(min_distance[v],v));

                min_distance[v] = dist_via_u;
                previous[v] = u;
                vertex_queue.insert(std::make_pair(min_distance[v],v));
            }
        }
    }
}

template<typename Vertex>
void build_path(std::map<Vertex, Vertex> const& prev, Vertex const v,
                std::vector<Vertex> & result)
{
    result.push_back(v);

    auto pos = prev.find(v);
    if (pos == std::end(prev)) return;

    build_path(prev, pos->second, result);
}

template<typename Vertex>
std::vector<Vertex> build_path(std::map<Vertex, Vertex> const& prev, Vertex const v)
{
    std::vector<Vertex> result;
    build_path(prev, v, result);
    std::reverse(std::begin(result), std::end(result));
    return result;
}

template<typename Vertex>
void print_path(std::vector<Vertex> const & path)
{
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << path[i];
        if (i < path.size()-1) std::cout << " -> ";
    }
}


int main()
{
    graph<char, double> g;
    g.add_edge('A','B',7);
    g.add_edge('A','C',9);
    g.add_edge('A','F',14);
    g.add_edge('B','C',10);
    g.add_edge('B','D',15);
    g.add_edge('C','D',11);
    g.add_edge('C','F',2);
    g.add_edge('D','E',6);
    g.add_edge('E','F',9);

    char source = 'A';
    std::map<char, double> min_distance;
    std::map<char, char> previous;
    shortest_path(g,source,min_distance, previous);

    for (auto const & [vertex, weight] : min_distance)
    {
        std::cout << source << " -> " << vertex << " : "
        << weight << '\t';

        print_path(build_path(previous,vertex));
        std::cout << std::endl;
    }
}