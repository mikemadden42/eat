#include <cstdlib>
#include <cstring>
#include <iostream>

int main(int argc, const char *argv[]) {
    int size_gb = 0;
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " size" << std::endl;
        exit(1);
    } else {
        size_gb = atoi(argv[1]);
    }

    try {
        std::cout << "Allocating " << size_gb << " GB" << std::endl;
        const size_t n = size_gb * 1024;
        const size_t size = 1024 * 1024;
        char **array = new char *[n];
        for (size_t a = 0; a < n; a++) {
            array[a] = new char[size];
            memset(array[a], 0, size);
        }
        for (size_t a = 0; a < n; a++) delete[] array[a];
        delete[] array;
        return 0;
    } catch (std::bad_alloc &ba) {
        std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
    }
}
