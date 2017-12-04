#ifndef COM_GITHUB_PITEX_PMC_INTERPRETER_COMMAND_COMMAND_H_
#define COM_GITHUB_PITEX_PMC_INTERPRETER_COMMAND_COMMAND_H_

#include "src/command/addressing_type.h"
#include "src/command/type.h"

namespace command {

class Command {
 public:
  Command();
  Command(Type, AddressingType, int);

  Type type() const { return type_; }
  AddressingType addressing_type() const { return addressing_type_; }
  void set_value(int value) { value_ = value; }
  int value() const { return value_; }

 private:
  Type type_;
  AddressingType addressing_type_;
  int value_;
};

}  // namespace command

#endif  // COM_GITHUB_PITEX_PMC_INTERPRETER_COMMAND_COMMAND_H_
