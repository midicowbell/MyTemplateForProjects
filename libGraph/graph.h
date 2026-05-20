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
struct EdgeInput {
	T from;
	T to;
	int weight = 1;
};
template<typename T>
class AdjListGraph {
private:
	int count_vertices;
	std::vector<Vertex<T>> vertices; 
	bool isOriented;
	bool isWeighted;
public:
	AdjListGraph(int n, bool oriented, bool weighted, const std::vector<EdgeInput<T>>& _data) {
		count_vertices = n;
		isOriented = oriented;
		isWeighted = weighted;
		vertices.resize(n);

		for (int i = 0; i < n; i++) {
			vertices[i].data = (T)i;
		}

		// Пробегаемся по нашей красивой структуре
		for (const auto& edge : _data) {
			int w = isWeighted ? edge.weight : 1;

			int u_ind = (int)edge.from;
			int v_ind = (int)edge.to;

			if (u_ind >= count_vertices || v_ind >= count_vertices) continue;

			// прямая связь
			Edge<T> new_edge;
			new_edge.to = edge.to;
			new_edge.weight = w;
			vertices[u_ind].neighbors.push_back(new_edge);

			// обратная связь для неориентированного графа
			if (!isOriented) {
				Edge<T> reserve_edge;
				reserve_edge.to = edge.from;
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

		auto it = vertices[u_ind].neighbors.begin();
		while (it != vertices[u_ind].neighbors.end()) {
			if (it->to == v) {
				it = vertices[u_ind].neighbors.erase(it);
			}
			else {
				++it;
			}
		}
		if (!isOriented) {
			auto it_rev = vertices[v_ind].neighbors.begin();
			while (it_rev != vertices[v_ind].neighbors.end()) {
				if (it_rev->to == u) {
					it_rev = vertices[v_ind].neighbors.erase(it_rev);
				}
				else {
					++it_rev;
				}
			}
		}
	}
	void delete_vertex(T v_to_delete) {
		int del_idx = (int)v_to_delete;
		if (del_idx < 0 || del_idx >= (int)vertices.size()) return;

		for (int i = 0; i < (int)vertices.size(); i++) {
			if (i == del_idx) continue; // соседей удаляемой вершины не трогаем

			// сдвигаем data, если индекс вершины больше удаляемого
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
		vertices.erase(vertices.begin() + del_idx);
		count_vertices = (int)vertices.size();
	}
	void djikrstra(T start, T end) {
		int start_idx = (int)start;
		int end_idx = (int)end;

		if (start_idx >= count_vertices || end_idx >= count_vertices || start_idx < 0 || end_idx < 0) {
			std::cerr << "Ошибка: таких вершин не существует\n";
			return;
		}
		const int INF = 1e9 + 7;
		std::vector<int> dist(count_vertices, INF);
		std::vector<int> parent(count_vertices, -1);
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

		dist[start_idx] = 0;
		pq.push({ 0, start_idx });

		while (!pq.empty()) {
			int d = pq.top().first;
			int v = pq.top().second;
			pq.pop();
			if (d > dist[v]) continue;
			for (const auto& edge : vertices[v].neighbors) {
				int u = (int)edge.to;
				int weight = edge.weight;

				if (dist[v] + weight < dist[u]) {
					dist[u] = dist[v] + weight;
					parent[u] = v;
					pq.push({ dist[u], u });
				}
			}
		}

		if (dist[end_idx] == INF) {
			std::cout << "Пути от " << start_idx << " до " << end_idx << " не существует.\n";
			return;
		}

		std::vector<int> path;
		for (int v = end_idx; v != -1; v = parent[v]) {
			path.push_back(v);
		}
		std::reverse(path.begin(), path.end());
		std::cout << "Кратчайшее расстояние от " << start_idx << " до " << end_idx << " равно: " << dist[end_idx] << "\n";
		std::cout << "Путь: ";
		for (size_t i = 0; i < path.size(); i++) {
			std::cout << path[i];
			if (i != path.size() - 1) std::cout << " -> ";
		}
		std::cout << "\n";
	}
};