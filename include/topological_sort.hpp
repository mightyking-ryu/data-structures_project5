#ifndef __TOPOLOGICAL_SORT_H_
#define __TOPOLOGICAL_SORT_H_

#include <vector>
#include "graph.hpp"
/* Feel free to add more standard library headers */
#include <deque>

/* Return _a_ valid topologically sorted sequence of vertex descriptors */
std::vector<vertex_t> topological_sort(Graph& g) {
	std::vector<vertex_t> sorted;
	std::deque<vertex_t> queue;
	size_t num_vertices = g.get_num_vertices();
	int *in_deg_list = new int[num_vertices];
	for(vertex_t i = 0; i < num_vertices; i++) {
		in_deg_list[i] = g.in_deg_num(i);
	}
	while(sorted.size() < num_vertices) {
		for(vertex_t i = 0; i < num_vertices; i++) {
			if(in_deg_list[i] == 0) {
				queue.push_back(i);
				in_deg_list[i] = -1;
			}
		}
		if(queue.size() == 0) {
			break;
		} else {
			vertex_t v = queue.front();
			sorted.push_back(v);
			queue.pop_front();
			std::optional<std::vector<vertex_t>> out_deges_opt = g.out_deges(v);
			if(out_deges_opt) {
				for(int i = 0; i < out_deges_opt.value().size(); i++) {
					in_deg_list[out_deges_opt.value()[i]] -= 1;
				}
			}
		}
	}
	delete [] in_deg_list;
	return sorted;
}

#endif // __TOPOLOGICAL_SORT_H_
