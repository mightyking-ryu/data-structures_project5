#ifndef __PRIM_MINIMUM_SPANNING_TREE_H_
#define __PRIM_MINIMUM_SPANNING_TREE_H_

#include <optional>
#include <vector>
/* Feel free to add more standard library headers */

/* Returns the vector of edges in the MST, or std::nullopt if MST does
 * not exist */

struct prim_tuple {
	bool visited = false;
	std::optional<edge_weight_t> distance = std::nullopt;
	std::optional<vertex_t> parent = std::nullopt;
};

std::optional<edges_t>
prim_minimum_spanning_tree(Graph& g, vertex_t src) {
	edges_t mst;
	size_t num_vertices = g.get_num_vertices();
	prim_tuple *table = new prim_tuple[num_vertices];
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
					if(table[neighbor].distance && table[neighbor].distance <= con_edge.second) {
						continue;
					} else {
						table[neighbor].distance = con_edge.second;
						table[neighbor].parent = next_src;
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
			mst.push_back(std::make_tuple(next_src, next_next_src, table[next_next_src].distance.value()));
			next_src = next_next_src;
		}

	} while(!is_end);

	delete [] table;

	if(mst.size() == num_vertices - 1)
		return mst;
	else
		return std::nullopt;
}
#endif // __PRIM_MINIMUM_SPANNING_TREE_H_