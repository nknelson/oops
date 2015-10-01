#include <cassert>      // assert
#include <iostream>     // std::endl, std::istream, std::ostream
#include <sstream>      // std::istringstream
#include <string>       // std::getline, std::string
#include <algorithm>    // std::reverse
#include <forward_list> // std::forward_list
#include <vector>       // std::vector
#include <deque>
#include <map>

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

   uint32_t getVertex() { return vertex_; }
    int32_t getDistance() { return distance_; }

private:
   uint32_t vertex_;
    int32_t distance_;
};

class GraphVertex {
public:
    GraphVertex() :
        edge_()
    {}

    void addEdge(const uint32_t & v, const int32_t & d) {
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
        prevVertex_(INT32_MAX),
        distance_(INT32_MAX),
        marked_(false)
    {}

   uint32_t getPrevVertex() const { return prevVertex_; }
    void setPrevVertex(const uint32_t v) { prevVertex_ = v; }

    int32_t getDistance() const { return distance_; }
    void setDistance(const int32_t d) { distance_ = d; }

    bool getMarked() const { return marked_; }
    void setMarked(const bool v) { marked_ = v; }

private:
    uint32_t prevVertex_;
    int32_t distance_;
    bool marked_;
};

// Read in the data and populate the graph.
//
// Note: I was getting too confused thinking about vectors being zero-based arrays
// while our graph starts with vertex '1'.  For this reason, I ignore graph[0] and
// just start things off with graph[1].
void populate_graph(std::vector<GraphVertex> & graph,
                    uint32_t & destination_vertex)
{
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
    // assert((2<=destination_vertex) && (destination_vertex <= 100000));
    // assert((0<=m) && (m <= 100000));
    // Resize the GraphVertex vector to match the number of vertices (plus one)
    graph.resize(destination_vertex+1);

    // Read in a, b, w for each edge
    for (uint32_t edge_count=0; edge_count<m; edge_count++) {
        std::getline(std::cin, s);
        std::istringstream edge(s);
        edge >> a >> b >> w;
        // assert(1<=a);
        // assert(b<=destination_vertex);
        // assert((1<=w) && (w<=1000000));
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
// Node objects one larger than the number of vertices, and I ignore Node[0].
void solve(std::vector<GraphVertex> & graph,
	   std::deque<int32_t> & solution,
           const uint32_t destination_vertex)
{
  std::map<uint32_t, Node> unmarked_nodes;
  std::map<uint32_t, uint32_t> marked_nodes;
    
    // Initialze the first row of the solution
    unmarked_nodes[1].setPrevVertex(1);
    unmarked_nodes[1].setDistance(0);
    uint32_t marked_vertex = 1;
    bool done = false;
    while (!done) {
      marked_nodes[marked_vertex] = unmarked_nodes[marked_vertex].getPrevVertex();

      if (marked_vertex == destination_vertex) {
	done = true;
	break;
      }
      
      int32_t marked_dist = unmarked_nodes[marked_vertex].getDistance();
      unmarked_nodes.erase(marked_vertex);
      
	for (auto & e : graph[marked_vertex].getEdge()) {
           uint32_t v = e.getVertex(); // This edge goes from 'curr_vertex' to 'v'
	   if (marked_nodes.find(v) != marked_nodes.end()) {
	     // Already marked
	     continue;
	   }
	   // v is in unmarked_nodes
	   int32_t d = e.getDistance();
	   d += marked_dist;
	   if (unmarked_nodes.find(v) == unmarked_nodes.end()) {
	     // First time node is visited, create entry
	     unmarked_nodes[v].setPrevVertex(marked_vertex);
	     unmarked_nodes[v].setDistance(d);
	   }
	   else if (d < unmarked_nodes[v].getDistance()) {
	     unmarked_nodes[v].setPrevVertex(marked_vertex);
	     unmarked_nodes[v].setDistance(d);
	   }
	}
	
	// Find the least expensive edge
	int32_t least_cost = INT32_MAX;
	for (auto & it : unmarked_nodes) {
	  if (it.second.getDistance() < least_cost) {
	    marked_vertex = it.first;
	    least_cost = it.second.getDistance();
	  }
	}
	
	if (least_cost==INT32_MAX) {
	  done = true;
	}
	
        int nkn2=1; // this is just here so that I can put a bkpt at the bottom of the while loop
    }
    
    // If no cheapest node then destination_vertex not reachable
    if (marked_vertex == 1) {
      return;
    }
    
    // Did we find a path to the destination vertex?
    if (marked_nodes.find(destination_vertex) != marked_nodes.end()) {
      solution.push_front(destination_vertex);
      // Previous vertex is always a marked node
      uint32_t prev_vertex = marked_nodes[destination_vertex];
      do {
	solution.push_front(prev_vertex);
	if (prev_vertex == 1) {
	  break;
	} else {
	  prev_vertex = marked_nodes[prev_vertex];
	}
      } while (true);
    }
    
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

    std::deque<int32_t> solution;
    solve(graph, solution, destination_vertex);
    if (solution.size() == 0) {
        std::cout << -1;
    } else {
        for (auto s : solution) {
            std::cout << s << " ";
        }
    }
    std::cout << std::endl;

    return(0);
}
