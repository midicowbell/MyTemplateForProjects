#pragma once
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <ostream>
template <typename Tkey, typename Tvalue>
class Itable {
public:
	virtual void insert(const Tkey& key, const Tvalue& value) = 0;
	virtual void replace(const Tkey& key, const Tvalue& value) = 0;
	virtual Tvalue& find(const Tkey& key) = 0;
	virtual void erase(const Tkey& key) = 0;
	virtual std::ostream& print(std::ostream& os) const noexcept = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual bool consist(const Tkey& key) const noexcept = 0;
};