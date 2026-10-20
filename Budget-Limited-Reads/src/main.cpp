#include <cstdlib>
#include <iostream>
#include <string>

// Planned CLI:
//   blr --mode {rr|lessbusy|fixed|budget} --trace <csv> --file-a <path> --file-b <path>
//       [--delay-us N] [--permits N] [--threshold N] [--no-threshold]
//       [--max-outstanding N] [--out-prefix <path>]

int main(int argc, char** argv) {
  std::string mode;
  for (int i = 1; i + 1 < argc; ++i) {
    if (std::string(argv[i]) == "--mode") mode = argv[i + 1];
  }
  std::cerr << "blr: not implemented (mode='" << mode << "')\n";
  return EXIT_FAILURE;
}
