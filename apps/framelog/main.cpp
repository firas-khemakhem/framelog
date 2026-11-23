#include <framelog/version.hpp>

#include <iostream>
#include <string_view>

namespace {

constexpr std::string_view kProgram{"framelog"};

void print_help(std::ostream& out) {
  out << "FrameLog " << flog::version() << "\n\n"
      << "Usage: framelog <command> [options]\n\n"
      << "Options:\n"
      << "  -h, --help       Show this help and exit\n"
      << "  -V, --version    Show the version and exit\n\n"
      << "Product commands (inspect, filter, stats, gen) arrive in v0.1.0.\n"
      << "Status: M0 foundation.\n";
}

}  // namespace

int main(int argc, char* argv[]) {
  if (argc == 1) {
    print_help(std::cerr);
    return 1;
  }

  const std::string_view argument{argv[1]};

  if (argument == "--help" || argument == "-h") {
    print_help(std::cout);
    return 0;
  }

  if (argument == "--version" || argument == "-V") {
    std::cout << kProgram << " " << flog::version() << "\n";
    return 0;
  }

  std::cerr << kProgram << ": unknown argument '" << argument << "'\n\n";
  print_help(std::cerr);
  return 1;
}
