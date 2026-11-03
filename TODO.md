# TODO

## Bugs (`eat.cc`)

- [x] **Negative numbers wrap to a huge size** (`eat.cc:11`). `strtol` returns a `long`, and it's stored in a `size_t`, so `eat -1` prints `Allocating 18446744073709551615 GB...` and then hits `bad_alloc`.
- [x] **A failed allocation exits with 0** (`eat.cc:35-37`). After the `catch`, `main` ends without a `return`, so `./eat -1` exits 0. Add `return 1;` after the error message.
- [x] **Bad input is accepted.** `eat 5abc` allocates 5 GB, `eat 1x` allocates 1 GB, and `99999999999999999999` becomes `9223372036854775807 GB`. Pass an `endptr` and check `*endptr == '\0'` and `errno == ERANGE`.
- [x] **`eat 0` gives the wrong error.** It says "Cannot convert argument to number: 0", but 0 is a valid number. Give it its own message ("size must be > 0").
- [x] **`size_gb * 1024` can overflow** (`eat.cc:21`) for large values, so the program would allocate less than it reports. Check `size_gb > SIZE_MAX / (1024ULL * 1024 * 1024)` before multiplying.

Suggested parsing fix:

```cpp
errno = 0;
char *end = nullptr;
long long v = std::strtoll(argv[1], &end, 10);
if (errno == ERANGE || end == argv[1] || *end != '\0' || v <= 0) {
    std::cerr << "Invalid size: " << argv[1] << '\n';
    return 1;
}
```

## Smaller code issues

- [ ] **The allocation could be optimized away.** C++14 and later let the compiler remove an unused `new`/`memset`/`delete` sequence. Make the memory observable, e.g. read a byte from each block into a `volatile` sink.
- [ ] **The memory is freed straight away.** Add a `--hold`/sleep option or "press Enter to free" for memory pressure testing.
- [x] Usage and conversion errors go to `std::cout`; send them to `std::cerr`. Use `return 1` instead of `exit(1)` inside `main`.
- [x] Initialize `size_gb` when declaring it, and remove the `else` after `exit`.

## Build and CI

- [ ] **Makefile:** use `CXX`/`CXXFLAGS` instead of `CC`/`CFLAGS`; use `$<` instead of `$@.cc`; make `clean` `rm -f` and `.PHONY`.
- [ ] **`.gitignore`:** add the built `eat` binary.
- [ ] **CMakeLists.txt:** replace `set(CMAKE_CXX_FLAGS ...)` with `target_compile_options(eat PRIVATE -Wall -Wextra -pedantic)`; add `set(CMAKE_CXX_STANDARD_REQUIRED ON)`.
- [x] **CI tests:** `ctest` now runs a 1 GB smoke test and `WILL_FAIL` tests for invalid input.
- [ ] **CI:** update `actions/checkout@v3` and remove the template comments.

## Docs

- [ ] **README:** explain usage, that sizes are in GB, and that on Linux overcommit means the OOM killer usually ends the process instead of `bad_alloc`.
