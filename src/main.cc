#include <cstdio>
#include <fstream>

#include "src/processor/processor.h"

int main() {
  std::ifstream file("file.txt");
  processor::Processor proc = processor::Processor(file, file);
  return 0;
}
