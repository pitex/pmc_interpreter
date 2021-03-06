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
  int files = 0;

  for (int i = 1; i < argc; ++i) {
    std::string arg(argv[i]);

    if (arg.substr(0, 2) == "--") {
      params[arg.substr(2, arg.length() - 2)] = true;
    } else if (arg[0] == '-') {
    } else {
      switch (files) {
        case 0: {
          cmd_file = arg;
          break;
        }
        case 1:
          input_file = arg;
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
    std::cout << "USAGE: pmc_interpreter [options] <cmd_file, input_file>" << std::endl;
    std::cout << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "  --line_by_line  " << "Waits for enter key after every command. Highly recommended to use together with --verbose." << std::endl;
    std::cout << "  --verbose       " << "Prints additional information." << std::endl;
  }

  std::ifstream cmd_file(arguments.cmd_file);
  std::ifstream input_file(arguments.input_file);

  processor::Processor proc = processor::Processor(cmd_file, input_file);
  proc.set_verbose(arguments.params["verbose"]);
  proc.set_line_by_line(arguments.params["line_by_line"]);

  int error_code = proc.RunPMC();
  proc.PrintState();

  return error_code;
}
