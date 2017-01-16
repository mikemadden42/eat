#include <cstring>
#include <iostream>

#include <boost/program_options.hpp>

// Based on https://theboostcpplibraries.com/boost.program_options

using namespace boost::program_options;

int main(int argc, const char *argv[]) {
  try {
    options_description desc{"Options"};
    desc.add_options()("help,h", "Help screen")(
        "size", value<int>()->default_value(2), "Size");

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help"))
      std::cout << desc << '\n';
    else if (vm.count("size")) {
      std::cout << "Allocating " << vm["size"].as<int>() << " GB" << std::endl;
      const size_t n = vm["size"].as<int>() * 1024;
      const size_t size = 1024 * 1024;
      char **array = new char *[n];
      for (size_t a = 0; a < n; a++) {
        array[a] = new char[size];
        memset(array[a], 0, size);
      }
      for (size_t a = 0; a < n; a++)
        delete[] array[a];
      delete[] array;
      return 0;
    }
  } catch (const error &ex) {
    std::cerr << ex.what() << '\n';
  }
}
