#include <cstdint>
#include <iostream>
#include <algorithm>
#include <forward_list>
#include <iterator>
#include <numeric>
#include <map>
#include <vector>

template <class Iterator>
class IndexedIterator {
public:
	IndexedIterator(Iterator it, size_t index) : start(it), current(it), null(index) {}
	uint64_t index() const {
		return null + std::distance(start, current);
	}

	bool operator != (const Iterator& it) {
		return current != it;
	}
	bool operator != (const IndexedIterator& it) {
		return current != it.current;
	}
	
	IndexedIterator<Iterator>& operator ++ () {
		++current;
		return *this;
	}
	IndexedIterator<Iterator>& operator -- () {
		--current;
		return *this;
	}
	IndexedIterator<Iterator> operator ++ (int) {
		IndexedIterator<Iterator> tmp = *this;
		++current;
		return tmp;
	}
	IndexedIterator<Iterator> operator -- (int) {
		IndexedIterator<Iterator> tmp = *this;
		--current;
		return tmp;
	}
	
	IndexedIterator<Iterator> operator + (int64_t step) {
		IndexedIterator copy = *this;
		copy.current += step;
		return copy;
	}
	int64_t operator - (const IndexedIterator& it) {
		return current - it.current;
	}

	typename Iterator::value_type operator * () {
		return *current;
	}
	typename Iterator::value_type operator * () const {
		return *current;
	}
	Iterator operator -> () {
		return current;
	}
	Iterator operator -> () const {
		return current;
	}
	
	using difference_type = typename Iterator::difference_type;
	using value_type = typename Iterator::value_type;
	using pointer = typename Iterator::pointer;
	using reference = typename Iterator::reference;
	using iterator_category = typename Iterator::iterator_category;

private:
	Iterator start;
	Iterator current;
	uint64_t null;
};

template <class It>
IndexedIterator<It> CreateIndexedIterator(It iterator, size_t index = 0) {
    return IndexedIterator<It>(iterator, index);
}

