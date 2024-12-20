#ifndef __DIJKSTRA_SHORTEST_PATHS_H_
#define __DIJKSTRA_SHORTEST_PATHS_H_

#include <unordered_map>
#include <optional>
#include <tuple>
/* Feel free to add more standard library headers */

#include "graph.hpp"

#include <iostream>


/* Given a vertex `v`, `dijkstra_shortest_path` is:
 * - `nullopt` if `v` is not reacheble from `src`.
 * - {`u`, `d`} where `u` is the predecessor of `v` and `d` is the distance
 *   from `src`
 */

struct dijkstra_tuple {
    bool visited = false;
    std::optional<edge_weight_t> distance;
    std::optional<vertex_t> previous;
};

std::unordered_map<vertex_t,
    std::optional<std::tuple<vertex_t, edge_weight_t>>>
dijkstra_shortest_path(Graph& g, vertex_t src) {
	size_t num_vertices = g.get_num_vertices();
	dijkstra_tuple *table = new dijkstra_tuple[num_vertices];
	table[src].distance = 0.0;
	bool is_end = true;;
	vertex_t next_src = src;
	do{
		table[next_src].visited = true;
		std::optional<std::vector<std::pair<vertex_t, edge_weight_t>>> connected_edges = g.get_connected_edges(next_src);
		if(connected_edges) {
			for(auto con_edge : connected_edges.value()) {
				vertex_t neighbor = con_edge.first;
				if(table[neighbor].visited == false) {
					if(table[neighbor].distance && table[neighbor].distance <= table[next_src].distance.value() + con_edge.second) {
						continue;
					} else {
						table[neighbor].distance = table[next_src].distance.value() + con_edge.second;
						table[neighbor].previous = next_src;
					}
				}
			}
		}
		is_end = true;
		vertex_t next_next_src;
		for(int i = 0; i < num_vertices; i++) {
			if(table[i].visited == false && table[i].distance) {
				next_next_src = i;
				is_end = false;
				break;
			}
		}
		if(!is_end) {
			for(int i = next_next_src + 1; i < num_vertices; i++) {
				if(table[i].visited == false && table[i].distance) {
					if(table[i].distance.value() < table[next_next_src].distance.value())
						next_next_src = i;
				}
			}
			next_src = next_next_src;
		}

	} while(!is_end);

    std::unordered_map<vertex_t, std::optional<std::tuple<vertex_t, edge_weight_t>>> path_map;

    for(int i = 0; i < num_vertices; i++) {
        if(i == src)
            continue;
        std::optional<std::tuple<vertex_t, edge_weight_t>> path;
        if(table[i].distance) {
            path = std::make_tuple(table[i].previous.value(), table[i].distance.value());
        } else {
            path = std::nullopt;
        }
        path_map[i] = path;
    }

	delete [] table;

    return path_map;
}

#endif // __DIJKSTRA_SHORTEST_PATHS_H_