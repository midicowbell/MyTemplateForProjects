#pragma once
#include <iostream>
#define STEP_CAPACITY 15

int calculate_capacity(size_t size) {
	return (size + STEP_CAPACITY) / STEP_CAPACITY * STEP_CAPACITY;
}

template <class T>
class Tvector {
protected:
	size_t _size;
	size_t _capacity;
	T* _data;
public:
	Tvector() : _size(0), _capacity(0), _data(nullptr) {}
	
	Tvector(size_t size) : _size(size), _data(nullptr) {
		_capacity = calculate_capacity(_size);
		if (_capacity > 0) {
			_data = new T[_capacity]();
		}
	}
	
	Tvector(const Tvector& other) : _size(other._size), _capacity(other._capacity), _data(nullptr) {
		if (_capacity > 0) {
			_data = new T[_capacity];
			for (size_t i = 0; i < _size; i++) {
				_data[i] = other._data[i];
			}
		}
	}
	
	Tvector(const T* arr, size_t n) : _size(n), _capacity(calculate_capacity(_size)), _data(nullptr) {
		if (n > 0) {
			if (arr == nullptr) {
				throw std::logic_error("arr is empty, but n > 0, wayd");
			}
			_data = new T[_capacity];
			for (size_t i = 0; i < _size; i++) {
				_data[i] = arr[i];
			}
		}
	}
	
	Tvector(std::initializer_list<T> data) {
		_size = data.size();
		_capacity = calculate_capacity(_size);
		_data = new T[_capacity];
		for (size_t i = 0; i < _size; i++) {
			_data[i] = *(data.begin() + i);
		}
	}
	
	void push_back(T val) {
		if (_size == _capacity) {
			reserve(calculate_capacity(_size + 1));
		}
		_data[_size] = val;
		_size++;
	}
	
	void push_front(T val) {
		if (_size == _capacity) {
			reserve(calculate_capacity(_size + 1));
		}
		for (size_t i = _size; i > 0; i--) {
			_data[i] = _data[i - 1];
		}
		_data[0] = val;
		_size++;
	}
	
	void print() {
		if (_data != nullptr) {
			std::cout << "[";
			for (size_t i = 0; i < _size; i++) {
				if (i > 0) {
					std::cout << ", ";
				}
				std::cout << _data[i];
			}
			std::cout << "]\n";
		}
	}

	void resize(size_t new_size) {
		if (new_size > _capacity) {
			reserve(calculate_capacity(new_size));
		}
		_size = new_size;
	}

	void reserve(size_t new_capacity) {
		if (new_capacity <= _capacity) {
			return;
		}

		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < _size; i++) {
			new_data[i] = _data[i];
		}
		delete[] _data;
		_data = new_data;
		_capacity = new_capacity;
	}
	
	void shrink_to_fit() {
		if (_capacity == _size) return;
		T* new_data = nullptr;
		if (_size > 0) {
			new_data = new T[_size];
			for (size_t i = 0; i < _size; i++) {
				new_data[i] = _data[i];
			}
		}

		delete[] _data;
		_data = new_data;
		_capacity = _size;
	}

	void insert(size_t pos, const T& val) {
		if (pos > _size) throw std::out_of_range("Index out of range");
		if (_size == _capacity) {
			reserve(calculate_capacity(_size + 1));
		}
		for (size_t i = _size; i > pos; i--) {
			_data[i] = _data[i - 1];
		}
		_data[pos] = val;
		++_size;
	}

	void pop(size_t pos) {
		if (pos >= _size) throw std::out_of_range("Index out of range");
		for (size_t i = pos; i < _size - 1; i++) {
			_data[i] = _data[i + 1];
		}
		--_size;
	}

	void erase(size_t pos, size_t length = 1) {
		if (pos >= _size) throw std::out_of_range("Index out of range");
		if (pos + length > _size) length = _size - pos;
		
		for (size_t i = pos; i < _size - length; i++) {
			_data[i] = _data[i + length];
		}
		_size = _size - length;
	}

	bool empty() const noexcept {
		return _size == 0;
	}

	void pop_back() {
		if (_size > 0) { --_size; }
	}

	size_t find_first(const T& val) const {
		for (size_t i = 0; i < _size; i++) {
			if (_data[i] == val) { return i; }
		}
		throw std::logic_error("Val not in data");
	}
	
	size_t find_last(const T& val) const {
		for (size_t i = _size; i > 0; i--) {
			if (_data[i - 1] == val) { return i - 1; }
		}
		throw std::logic_error("Val not in data");
	}

	Tvector<size_t> find_all(const T& val) const {
		Tvector<size_t> indices;
		for (size_t i = 0; i < _size; i++) {
			if (_data[i] == val) {
				indices.push_back(i);
			}
		}
		return indices;
	}

	friend std::ostream& operator <<(std::ostream& os, const Tvector<T>& other) {
		os << "[";
		for (size_t i = 0; i < other.size(); i++) {
			if (i > 0) {
				os << ", ";
			}
			os << other[i];
		}
		os << "]";
		return os;
	}

	friend std::istream& operator >> (std::istream& is, Tvector<T>& vec) {	
		size_t count;
		std::cout << "Enter number of elements: ";
		is >> count;

		vec.resize(count);

		std::cout << "Enter the elements:\n";
		for (size_t i = 0; i < vec.size(); i++) {
			is >> vec[i];
		}
		return is;
	}

	Tvector<T>& operator=(const Tvector<T>& other) noexcept {
		if (this == &other) {
			return *this;
		}
		delete[] _data;
		_size = other._size;
		_capacity = other._capacity;
		if (_capacity > 0) {
			_data = new T[_capacity];
			for (size_t i = 0; i < _size; i++) {
				_data[i] = other._data[i];
			}
		}
		else {
			_data = nullptr;
		}
		return *this;
	}
	
	// ??????????: ?????? ????????? ?????????? size_t
	inline T& operator[](size_t indx) noexcept {
		return _data[indx];
	}
	
	inline const T& operator[](size_t indx) const noexcept {
		return _data[indx];
	}
	
	inline size_t size() const noexcept {
		return _size;
	}
	
	inline size_t capacity() const noexcept {
		return _capacity;
	}
	
	inline T* data() const noexcept {
		return _data;
	}
		
	~Tvector() {
		delete[] _data;
	}
};