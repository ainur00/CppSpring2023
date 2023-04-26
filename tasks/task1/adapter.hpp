#include "some_library.hpp"

class Adapter {
    public:
        std::string name_;
        int value_;
};

inline void SetValue(SomeLibrary::ValueHolder& valueHolder, int value) {
    reinterpret_cast<Adapter&>(valueHolder).value_ = value;
}
