#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <list>
template<typename T>
struct Edge {
	T to;
	int weight;
};
template<typename T>
struct Vertex {
	T data;
	std::list<Edge<T>> neighbors;
};
template<typename T>
class AdjListGraph {
private:
	int count_vertices;
	bool isOriented;
	bool isWeighted;
	std::vector<Vertex<T>> vertices; 
public:
	AdjListGraph(int n, bool oriented, bool weighted, std::vector<std::pair<T, T>> _data) {
		count_vertices = n;
		isOriented = oriented;
		isWeighted = weighted;
		vertices.resize(n);
		for (int i = 0; i < n; i++) {
			vertices[i].data = (T)i;
		}
		for (const auto& p : _data) {
			int u_ind = (int)p.first;
			int v_ind = (int)p.second;

			if (u_ind >= count_vertices || v_ind >= count_vertices) continue;

			int w = 1;

			// прямая связь
			Edge<T> new_edge;
			new_edge.to = p.second;
			new_edge.weight = w;
			vertices[u_ind].neighbors.push_back(new_edge);

			// обратная связь
			if (!isOriented) {
				Edge<T> reserve_edge;
				reserve_edge.to = p.first;
				reserve_edge.weight = w;
				vertices[v_ind].neighbors.push_back(reserve_edge);
			}
		}
	}
	void add_edge(T u, T v, int weight = 1) {
		int u_ind = (int)u;
		int v_ind = (int)v;
		if (u_ind >= count_vertices || v_ind >= count_vertices) return;

		int w;
		if (this->isWeighted) {
			w = weight;
		}
		else {
			w = 1;
		}
		Edge<T> new_edge;
		new_edge.to = v;
		new_edge.weight = w;
		vertices[u_ind].neighbors.push_back(new_edge);
		if (!this->isOriented) {
			Edge<T> reserve_edge;
			reserve_edge.to = u;
			reserve_edge.weight = w;
			vertices[v_ind].neighbors.push_back(reserve_edge);
		}
	}
	void delete_edge(T u, T v) {
		int u_ind = (int)u;
		int v_ind = (int)v;
		if (u_ind >= count_vertices || v_ind >= count_vertices) return;
		while ()
		vertices[u_ind].neighbors.remove[v];
		if (!isOriented) {
			vertices[v_ind].neighbors.remove[u];
		}

	}
	void delete_vertex(T v_to_delete) {
		int del_idx = (int)v_to_delete;
		if (del_idx >= count_vertices) return;

		vertices.erase(vertices.begin() + del_idx);
		count_vertices--;
		for (int i = 0; i < count_vertices; i++) {

			if ((int)vertices[i].data > del_idx) {
				vertices[i].data = (T)((int)vertices[i].data - 1);
			}
			auto it = vertices[i].neighbors.begin();
			while (it != vertices[i].neighbors.end()) {

				if ((int)it->to == del_idx) {
					it = vertices[i].neighbors.erase(it);
				}
				else {
					if ((int)it->to > del_idx) {
						it->to = (T)((int)it->to - 1);
					}
					++it;
				}
			}
		}
	}
	void djikrstra(T start, T end) {
		int start = int(start);
		int end = int(end);
		if (start >= count_vertices || end >= count_vertices) {
			throw std::logic_error("Таких вериш не сущесвуют\n");
			return;
		}
		const int INF = 1e9 + 7;
		std::vector<int> ans(count_vertices, INF);
		std::vector<int> pr(count_vertices, INF);
		std::priority_queue<std::pair<int, int>, std::vector<pair<int, int>>, std::greater<pair<int, int>>> q;
		q.push({ 0, start });
		while (!q.empty()) {
			std::pair<int, int> c = q.top();
			q.pop();
			int dst = c.first;
			int v = c.second;
			if (ans[v] < dst) {
				continue;
			}
			auto it = vertices[v].neighbors.begin();
			while (it != vertices[v].neighbors.end()) {
				int u = (int)it->to;
				int len_vu = it->weight;
				int n_dst = dst + len_vu; // текущий пробег(сколько прошли + новая дорога)
				if (n_dst < ans[u]) {
					ans[i] = n_dst;
					pr[u] = v;
					q.push({n_dst, u})
				}
				++it;
			}
		}
		if (ans[end] == INF) { return; }
		std::vector<int> path;
		int cur = end;
		path.push_back(cur);
		while (pr[cur] != -1) {
			cur = pr[cur];
			path.push_back(cur);
		}
		std::reverse(path.begin(), path.end());
		std::cout << "Кратчайший пусть от " << start << "до " << end << " раввен:" << ans[end] << "\n";
		for (size_t i = 0; i < path.size(); i++) {
			std::cout << path[i];
			if (i != path.size() - 1) std::cout << " -> ";
		}
		std::cout << "\n";
	}
};