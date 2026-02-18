#include "UnsortedTable.h"
template <typename Tkey, typename Tvalue>
bool UnsortedTableOnVec<Tkey, Tvalue>::is_empty() const noexcept {
	return _rows.empty();
}
template <typename Tkey, typename Tvalue>
void UnsortedTableOnVec<Tkey, Tvalue>::insert(const Tkey& key, const Tvalue& value) {
	_rows.push_back({ key, value })
}