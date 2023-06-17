template <class T>
void TransformIf(T* begin, T* end, bool (*p)(const T&), void (*f)(T&)) {
    std::vector<T> copyP;
    std::vector<uint64_t> iP;    
    for (T* it = begin; it <= end; ++it) {
        bool isCopyThrows = false;
        try {
            if (p(*it)) {
            	try {
            		copyP.push_back(*it);
                	iP.push_back(it - begin);
            	} catch (...) {
            		isCopyThrows = true;
            	}
                f(*it);
            }
        } catch (...) {
            if (isCopyThrows)
                throw;
            for (uint64_t i = 0; i < iP.size(); ++i)
                *(begin + iP[i]) = copyP[i];
            throw;
        }
    }
}
