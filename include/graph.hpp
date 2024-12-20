#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <vector>
#include <unordered_map>
#include <list>
#include <tuple>

/* Feel free to add more standard library headers */
#include <optional>

// A vertex is typed as `vertex_t`. An edge is typed as `edge_t`,
// which is associated with a source vertex, a destination vertex, and
// its weight. A list of edges is typed as `edges_t`, which is a
// vector of `edge_t`.

using vertex_t = std::size_t;
using edge_weight_t = double;
using edge_t = std::tuple<vertex_t,
                          vertex_t,
                          edge_weight_t>;
using edges_t = std::vector<edge_t>;

enum class GraphType {
UNDIRECTED,
DIRECTED
};

/*
 * We do not enforce a specific design constraints other than the
 * consturtor. You may introduce your own changes as you
 * want---implementing your own member functions or variables. You
 * will still need to ensure that your constructor works properly,
 * such that we can run the test for grading. The provided test will
 * check if the constructor is correctly designed.
 */
class Graph {
    public:
        Graph() = delete;
        Graph(const Graph&) = delete;
        Graph(Graph&&) = delete;

        /* We assume that if num_vertices is n, a graph contains n vertices
           from 0 to n-1. */
        Graph(size_t num_vertices,
              const edges_t& edges,
              GraphType Type) {
            // TODO: Implement the constructor
            this->num_vertices = num_vertices;
            this->type = Type;
            this->edges = edges;
        }
        // TODO(optional): Define helper functions, e.g., out_deges(v)

        size_t get_num_vertices();
        GraphType get_type();

        int in_deg_num(vertex_t v);
        int out_deg_num(vertex_t v);

        std::optional<std::vector<vertex_t>> in_deges(vertex_t v);
        std::optional<std::vector<vertex_t>> out_deges(vertex_t v);
        std::optional<std::vector<std::pair<vertex_t, edge_weight_t>>> get_connected_edges(vertex_t v);
		
    private:
        // TODO: Roll out your own data structures
        size_t num_vertices;
        GraphType type;
        edges_t edges;
};

size_t Graph::get_num_vertices() {
    return this->num_vertices;
}

GraphType Graph::get_type() {
    return this->type;
}

int Graph::in_deg_num(vertex_t v) {
    int count = 0;
    for(int i = 0; i < this->edges.size(); i++) {
        if(v == std::get<1>(this->edges[i]))
            count++;
    }
    return count;
}

int Graph::out_deg_num(vertex_t v) {
    int count = 0;
    for(int i = 0; i < this->edges.size(); i++) {
        if(v == std::get<0>(this->edges[i]))
            count++;
    }
    return count;
}

std::optional<std::vector<vertex_t>> Graph::in_deges(vertex_t v) {
    std::vector<vertex_t> in_deges;
    for(int i = 0; i < this->edges.size(); i++) {
        if(v == std::get<1>(this->edges[i])) {
            in_deges.push_back(std::get<0>(this->edges[i]));
        }
    }
    if(in_deges.size() == 0) {
        return std::nullopt;
    } else {
        return in_deges;
    }
}

std::optional<std::vector<vertex_t>> Graph::out_deges(vertex_t v) {
    std::vector<vertex_t> out_deges;
    for(int i = 0; i < this->edges.size(); i++) {
        if(v == std::get<0>(this->edges[i])) {
            out_deges.push_back(std::get<1>(this->edges[i]));
        }
    }
    if(out_deges.size() == 0) {
        return std::nullopt;
    } else {
        return out_deges;
    }
}

std::optional<std::vector<std::pair<vertex_t, edge_weight_t>>> Graph::get_connected_edges(vertex_t v) {
    std::vector<std::pair<vertex_t, edge_weight_t>> connected_edges;
    for(auto edge : this->edges) {
        std::optional<vertex_t> neighbor;
        if(v == std::get<0>(edge)) {
            neighbor = std::get<1>(edge);
        }else if (v == std::get<1>(edge) && this->type == GraphType::UNDIRECTED) {
            neighbor = std::get<0>(edge);
        }else {
            neighbor = std::nullopt;
        }
        if(neighbor && (v != neighbor.value())) {
            connected_edges.push_back(std::make_pair(neighbor.value(), std::get<2>(edge)));
        }
    }
    if(connected_edges.size() == 0)
        return std::nullopt;
    else
        return connected_edges;
}

#endif // __GRAPH_H_
