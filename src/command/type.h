#ifndef COM_GITHUB_PITEX_PMC_INTERPRETER_COMMAND_TYPE_H_
#define COM_GITHUB_PITEX_PMC_INTERPRETER_COMMAND_TYPE_H_

#include <map>
#include <string>

namespace command {

enum Type {
  LOAD = 1,
  STORE,
  JUMP,
  JNEG,
  JZERO,
  STOP,
  NILL,
  ADD,
  SUB,
  AND,
  OR,
  NOT,
  SHL,
  SHR,
  VALUE,
};

const std::map<std::string, Type> kStringToType = {
  {"LOAD", Type::LOAD},
  {"STORE", Type::STORE},
  {"JUMP", Type::JUMP},
  {"JNEG", Type::JNEG},
  {"JZERO", Type::JZERO},
  {"STOP", Type::STOP},
  {"NULL", Type::NILL},
  {"ADD", Type::ADD},
  {"SUB", Type::SUB},
  {"AND", Type::AND},
  {"OR", Type::OR},
  {"NOT", Type::NOT},
  {"SHL", Type::SHL},
  {"SHR", Type::SHR},
  {"VALUE", Type::VALUE}
};

}  // namespace command

#endif  // COM_GITHUB_PITEX_PMC_INTERPRETER_COMMAND_TYPE_H_