# ErrorValue

A header-only library for go-style error handling for C++ 17.

## Example

```cpp
#include <cstdio>
#include <cstdint>
#include <Result.hpp>

struct Error{
    std::int32_t code;

    inline bool ok() const noexcept {
        return code == 0;
    }
};

static Error ErrLogical{1};

template<typename _T>
using Result = ErrorValue::Result<_T,Error>;

static Result<int> DoSth(bool ok) {
    if (ok) {
        return 0;
    }
    return ErrLogical;
}

int main() {
    auto [r,err] = DoSth(true);
    if (!err.ok()) {
        std::printf("Err: %d\n",err.code);
        return 1;
    }
    return 0;
}
```
