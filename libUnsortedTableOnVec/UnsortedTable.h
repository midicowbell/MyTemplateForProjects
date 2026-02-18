#pragma once
#include "../libTvector/tvector.h"
#include "../libITable/itable.h"
template <typename Tkey, typename Tvalue>
class UnsortedTableOnVec : public Itable<Tkey, Tvalue> {
private:
	Tvector<std::pair<Tkey, Tvalue>> _rows;
public:
	~UnsortedTableOnVec() = default;
	UnsortedTableOnVec() {};
	bool is_empty() const noexcept override;
	void insert(const Tkey& key, const Tvalue& value);
	void replace(const Tkey& key, const Tvalue& value);
	Tvalue& find(const Tkey& key) const;
	void erase(const Tkey& key);
	ostream& print(ostream& os) const noexcept;
	bool is_empty() const noexcept;
	bool consist(const Tkey& key) const noexcept;

};