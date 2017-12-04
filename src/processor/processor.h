#ifndef COM_GITHUB_PITEX_PMC_INTERPRETER_PROCESSOR_PROCESSOR_H_
#define COM_GITHUB_PITEX_PMC_INTERPRETER_PROCESSOR_PROCESSOR_H_

#include <fstream>

#include "src/command/command.h"
#include "src/command/addressing_type.h"
#include "src/processor/cache_type.h"
#include "src/processor/error_code.h"

namespace processor {

class Processor {
 public:
  Processor(std::ifstream& cmd_file, std::ifstream& infile);

  ErrorCode RunPMC();

 private:
  void ReadCommand(std::ifstream&);
  void ReadInput(std::ifstream&);
  ErrorCode RunCommand(const int&);
  ErrorCode CountOperand(const command::AddressingType&, const int&);

  command::Command memory_[512] = {};
  int cache_[CacheType::CACHE_TYPE_LENGTH] = {};
};

}  // namespace processor

#endif  // COM_GITHUB_PITEX_PMC_INTERPRETER_PROCESSOR_PROCESSOR_H_
