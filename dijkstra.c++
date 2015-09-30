#include <cassert>      // assert
#include <iostream>     // std::endl, std::istream, std::ostream
#include <sstream>      // std::istringstream
#include <string>       // std::getline, std::string
#include <algorithm>    // std::reverse
#include <forward_list> // std::forward_list
#include <vector>       // std::vector

#include <cstdint>

// Graphs are stored in two classes.  There is a vector of GraphVertex objects.
// Each GraphVertex object contains a linked list of Edge objects.

// An Edge is described as a vertex and a weight/distance.  This representation is
// odd because I only store one vertex; the GraphVertex object holds the other vertex.
// That's not exactly true, though.  The index into the vector of GraphVertex objects
// is actually the starting vertex.
//
// A better representation of a graph might be a std::pair with the two vertices.
class Edge {
public:
    Edge():
        vertex_(INT32_MAX),
        distance_(0)
    {}

    Edge(int32_t v, int32_t d) :
        vertex_(v),
        distance_(d)
    {}

    int32_t getVertex() { return vertex_; }
    int32_t getDistance() { return distance_; }

private:
    int32_t vertex_;
    int32_t distance_;
};

class GraphVertex {
public:
    GraphVertex() :
        edge_()
    {}

    void addEdge(const int32_t & v, const int32_t & d) {
        edge_.emplace_after(edge_.before_begin(), v, d);
    }

    std::forward_list<Edge> getEdge() const { return edge_; }

private:
    std::forward_list<Edge> edge_;
};

// The solve() function creates an array of Node objects; this is the space in
// which the Dijkstra algorithm is executed.
class Node {
public:
    Node() :
        nextVertex_(INT32_MAX),
        distance_(INT32_MAX),
        visited_(false)
    {}

    int32_t getNextVertex() const { return nextVertex_; }
    void setNextVertex(const int32_t v) { nextVertex_ = v; }

    int32_t getDistance() const { return distance_; }
    void setDistance(const int32_t d) { distance_ = d; }

    bool getVisited() const { return visited_; }
    void setVisited(const bool v) { visited_ = v; }

private:
    int32_t nextVertex_;
    int32_t distance_;
    bool visited_;
};

// Read in the data and populate the graph.
//
// Note: I was getting too confused thinking about vectors being zero-based arrays
// while our graph starts with vertex '1'.  For this reason, I ignore graph[0] and
// just start things off with graph[1].
void populate_graph(std::vector<GraphVertex> & graph,
                    uint32_t & destination_vertex) {
    // Input
    // The first line contains two integers n and m (2 <= n <= 10^5, 0 <= m <= 10^5),
    // where n is the number of vertices and m is the number of edges. Following m
    // lines contain one edge each in form ai, bi and wi (1< = ai, bi <= n,
    // 1 <= wi <= 10^6), where ai, bi are edge endpoints and wi is the length of the edge.
    uint32_t m, a, b, w;
    // Read in "n" and "m"
    std::string s;
    std::getline(std::cin, s);
    std::istringstream sin(s);
    sin >> destination_vertex >> m;
    assert((2<=destination_vertex) && (destination_vertex <= 100000));
    assert((0<=m) && (m <= 100000));
    // Resize the GraphVertex vector to hold all of the edges.  Note that the size
    // of the vector is twice the number of edges due to the way I store the data.
    // For ever edge from 'a' to 'b' I have to store not only that edge but also
    // the edge from 'b' to 'a'.
    graph.resize((2*m)+1);

    // Read in a, b, w for each edge
    for (uint32_t edge_count=0; edge_count<m; edge_count++) {
        std::getline(std::cin, s);
        std::istringstream edge(s);
        edge >> a >> b >> w;
        assert(1<=a);
        assert(b<=destination_vertex);
        assert((1<=w) && (w<=1000000));
        graph[a].addEdge(b, w);
        graph[b].addEdge(a, w);
    }

    return;
}

// Print out the edges
void dump_graph(std::vector<GraphVertex> & graph,
                const uint32_t destination_vertex) {
    uint32_t n = 0;
    uint32_t m = 0;
    for (auto g : graph) {
        for (auto e : g.getEdge()) {
            ++m;
        }
    }

    std::cout << destination_vertex << " " << m << std::endl;

    for (auto g : graph) {
        for (auto e : g.getEdge()) {
            std::cout << n << " " << e.getVertex() << " " <<
                e.getDistance() << std::endl;
        }
        ++n;
    }
}

// Find the shortest path from vertex '1' to the destination vertex
//
// Note: See note above about zero-based vs. one-based.  I make my vector of
// Node object one larger than the number of vertices, and I ignore Node[0].
void solve(std::vector<GraphVertex> & graph, std::vector<int32_t> & solution,
           const uint32_t destination_vertex) {
    std::vector<Node> nodes(destination_vertex+1);
    // Initialze the first row of the solution
    nodes[1].setNextVertex(1);
    nodes[1].setDistance(0);
    nodes[1].setVisited(true);
    // Fill in all of the vertices reachable from vertex 1
    int32_t next_vertex = 1;
    bool done = false;
    while (!done) {
        int nkn1 = 1;
        for (auto & e : graph[next_vertex].getEdge()) {
            int32_t v = e.getVertex(); // This edge goes from 'next_vertex' to 'v'
            if (nodes[v].getVisited()) {
                continue;
            }
            int32_t d = e.getDistance();
            if (nodes[next_vertex].getDistance() != INT32_MAX) {
                d += nodes[next_vertex].getDistance();
            }
            if (d < nodes[v].getDistance()) {
                nodes[v].setNextVertex(next_vertex);
                if (nodes[next_vertex].getDistance() == INT32_MAX) {
                    nodes[v].setDistance(d);
                } else {
                    nodes[v].setDistance(d+nodes[next_vertex].getDistance());
                }
            }
        }

        // Find the least expensive edge
        int32_t cost = INT32_MAX;
        for (uint32_t j=1; j<destination_vertex+1; j++) {
            if (nodes[j].getVisited()) {
                continue;
            }
            if (nodes[j].getDistance() < cost) {
                next_vertex = j;
                cost = nodes[j].getDistance();
            }
        }
        nodes[next_vertex].setVisited(true);
        done = (cost==INT32_MAX);
        int nkn2=1;
    }

    // If no cheapest node then destination_vertex not reachable
    if (next_vertex == -1) {
        return;
    }

    // Did we find a path to the destination vertex?
    if (nodes[destination_vertex].getVisited()) {
        solution[0] = destination_vertex;
        next_vertex = nodes[destination_vertex].getNextVertex();
        do {
            solution.emplace_back(next_vertex);
            if (next_vertex == 1) {
                break;
            } else {
                next_vertex = nodes[next_vertex].getNextVertex();
            }
        } while (true);
    }

    std::reverse(solution.begin(), solution.end());
    return;
}

int main() {
    Node n;
    Edge e;
    std::vector<GraphVertex> graph;
    uint32_t destination_vertex;

    populate_graph(graph, destination_vertex);
#ifdef DEBUG
    dump_graph(graph, destination_vertex);
#endif

    std::vector<int32_t> solution(1, -1);
    solve(graph, solution, destination_vertex);
    if (solution.size()==-1) {
        std::cout << -1;
    } else {
        for (auto s : solution) {
            std::cout << s << " ";
        }
    }
    std::cout << std::endl;

    return(0);
}
