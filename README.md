# zuu_string_view

[![C++11](https://img.shields.io/badge/C++-11-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B11)

`zuu_string_view` is a lightweight, non-owning `string_view` implementation that brings C++17 `std::string_view` features to **C++11**. It holds only a pointer to the start of the character data and its length, without copying or allocating new memory. 

Designed for high-performance applications, `zuu_string_view` uses a zero-copy approach and features **SWAR (SIMD Within A Register)** bit-parallel optimizations, allowing you to read, search, and process text sources significantly faster than standard implementations in many scenarios.

## Key Features

* **C++11 Compatible:** Enjoy `string_view` semantics in older codebases without upgrading your compiler standard.
* **Blazing Fast Searches:** Outperforms `std::string_view` in most search operations (see benchmarks).
* **SWAR Optimized:** Uses bitwise operations for parallel character processing.
* **Zero-Copy & Non-Owning:** No memory allocation overhead.
* **Drop-in Replacement:** API design closely mirrors `std::string_view`.

## Benchmarks

*Tested on 12x 2096 MHz CPU using Google Benchmark (Fair runtime test avoiding compiler constant folding).*

| API / Function | `zuu::string_view` (Ours) | `std::string_view` | Speedup / Status |
| :--- | :--- | :--- | :--- |
| **`find_first_of`** | **6.11 ns** | 15.7 ns | ~2.5x Faster |
| **`find` (Substring)** | **11.1 ns** | 14.1 ns | ~1.3x Faster |
| **`rfind` (Substring)** | **11.4 ns** | 16.7 ns | ~1.4x Faster |
| **`find` (Char)** | **1.56 ns** | 2.24 ns | ~1.4x Faster |
| **`find_last_of`** | **11.0 ns** | 14.7 ns | ~1.3x Faster |
| **`rfind` (Char)** | **2.39 ns** | 2.50 ns | Tie / Slightly Faster |
| `find_first_not_of` | 6.22 ns | **5.01 ns** | *~20% Slower* |
| `find_last_not_of` | 6.82 ns | **5.00 ns** | *~26% Slower* |

*Note: `zuu_string_view` heavily accelerates positive searches (`find`, `find_first_of`) via SWAR. Negative searches (`not_of`) perform well but are slightly edged out by native compiler intrinsics in GCC/Clang.*

## Quick Usage

```cpp
#include <iostream>
#include <zuu/string_view.hpp>

int main() {
    const char* raw_text = "Hello World! Welcome to zuu_string_view.";
    
    // Create a non-owning view (zero copy)
    zuu::string_view view(raw_text);

    // Blazing fast SWAR-optimized search
    auto pos = view.find_first_of("Ww");
    
    if (pos != zuu::string_view::npos) {
        std::cout << "Found at index: " << pos << "\\n";
        
        // Fast substring extraction (zero copy)
        zuu::string_view sub = view.substr(pos, 5); 
        std::cout << "Substring: " << sub.data() << "\\n";
    }

    return 0;
}
```

## Integration (CMake)

You can easily integrate `zuu_string_view` into your project via CMake:

```cmake
# Add the library directory
add_subdirectory(path/to/zuu_string_view)

# Link against your target
target_link_libraries(your_executable PRIVATE zuu_string_view::internal)
```