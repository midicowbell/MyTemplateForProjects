#pragma once

#include "../libHeap/heap.h"
template<typename Pr, typename Val>
class QueueOnHeap {
private:
	MinHeap<std::pair<Pr, Val>> heap;
public:
	QueueOnHeap() = default;
	std::pair<Pr, Val> pop() {
		if (heap.empty()) {
			throw std::out_of_range("Heap is empty");
		}
		return heap.pop();

	}
	void push(const Pr& pr, const Val& val) {
		std::pair<Pr, Val> pairr = std::make_pair(pr, val);
		heap.add(pairr);
	}
	bool empty() const {
		return heap.empty();
	}
	 
};