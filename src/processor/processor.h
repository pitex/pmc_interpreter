#ifndef COM_GITHUB_PITEX_PMC_INTERPRETER_PROCESSOR_PROCESSOR_H_
#define COM_GITHUB_PITEX_PMC_INTERPRETER_PROCESSOR_PROCESSOR_H_

#include <fstream>
#include <map>

#include "src/command/command.h"
#include "src/command/addressing_type.h"
#include "src/processor/cache_type.h"
#include "src/processor/error_code.h"

namespace processor {

class Processor {
 public:
  Processor(std::ifstream& cmd_file, std::ifstream& infile);

  ErrorCode RunPMC();
  void PrintState();

  void set_line_by_line(bool line_by_line) { line_by_line_ = line_by_line; }
  void set_verbose(bool verbose) { verbose_ = verbose; }
 private:
  void ReadCommand(std::ifstream&);
  void ReadInput(std::ifstream&);
  ErrorCode RunCommand(const int&);
  ErrorCode CountOperand(const command::AddressingType&, const int&);

  command::Command memory_[512] = {};
  bool line_by_line_ = false;
  bool verbose_ = false;
  int cache_[CacheType::CACHE_TYPE_LENGTH] = {};
  std::map<int, bool> used_memory_;
};

}  // namespace processor

#endif  // COM_GITHUB_PITEX_PMC_INTERPRETER_PROCESSOR_PROCESSOR_H_
