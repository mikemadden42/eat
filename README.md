# eat
Simple program to allocate memory

## Build

```sh
make
```

or with CMake:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build
```

## Usage

```sh
eat SIZE
```

`SIZE` is a whole number of gigabytes. `eat` allocates that much memory in
1 MB blocks, writes zeros to every block so the pages are actually used,
then frees it and exits. It exits 1 if the argument is invalid or the
allocation fails.

```sh
$ eat 2
Allocating 2 GB...
Freeing 2 GB...
```

## Note on Linux

Linux overcommits memory by default, so asking for more memory than the
system has usually doesn't fail with `bad_alloc`. Instead, the OOM killer
ends the process while the blocks are being written.
