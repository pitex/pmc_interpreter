#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "src/processor/processor.h"

struct Arguments {
  std::string cmd_file;
  std::string input_file;
  std::map<std::string, bool> params;

  int ParseArguments(const int& argc, char *argv[]);
};

int Arguments::ParseArguments(const int& argc, char *argv[]) {
  int it = 1;
  int files = 0;
  Arguments arguments;

  while (it < argc) {
    std::string arg(argv[it]);

    if (arg.substr(0, 2) == "--") {
      arguments.params[arg] = true;
    } else if (arg[0] == '-') {
    } else {
      switch (files) {
        case 0: {
          arguments.cmd_file = arg;
          break;
        }
        case 1:
          arguments.input_file = arg;
          break;
        default:
          return -1;
      }
      ++files;
    }
  }

  if (files < 2) {
    return -1;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  Arguments arguments;
  if (arguments.ParseArguments(argc, argv) < 0) {
    std::cout << "USAGE: pmc_interpreter <cmd_file, input_file>";
  }

  std::ifstream cmd_file(arguments.cmd_file);
  std::ifstream input_file(arguments.input_file);

  processor::Processor proc = processor::Processor(cmd_file, input_file);

  return proc.RunPMC();
}
