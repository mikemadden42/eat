#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " size" << std::endl;
        return 1;
    }

    errno = 0;
    char *end = nullptr;
    const long long value = std::strtoll(argv[1], &end, 10);
    if (errno == ERANGE || end == argv[1] || *end != '\0') {
        std::cerr << "Cannot convert argument to number: " << argv[1]
                  << std::endl;
        return 1;
    }
    if (value <= 0) {
        std::cerr << "Size must be greater than 0: " << argv[1] << std::endl;
        return 1;
    }

    const size_t size_gb = static_cast<size_t>(value);
    if (size_gb > SIZE_MAX / (1024ULL * 1024 * 1024)) {
        std::cerr << "Size is too large: " << argv[1] << std::endl;
        return 1;
    }

    try {
        std::cout << "Allocating " << size_gb << " GB..." << std::endl;
        const size_t n = size_gb * 1024;
        const size_t size = 1024 * 1024;
        char **array = new char *[n];
        for (size_t a = 0; a < n; a++) {
            array[a] = new char[size];
            std::memset(array[a], 0, size);
        }

        std::cout << "Freeing " << size_gb << " GB..." << std::endl;
        for (size_t a = 0; a < n; a++) {
            delete[] array[a];
        }
        delete[] array;
        return 0;
    } catch (std::bad_alloc &ba) {
        std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
        return 1;
    }
}
