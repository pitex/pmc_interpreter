#ifndef COM_GITHUB_PITEX_PMC_INTERPRETER_COMMAND_ADDRESSING_TYPE_H_
#define COM_GITHUB_PITEX_PMC_INTERPRETER_COMMAND_ADDRESSING_TYPE_H_

#include <map>

namespace command {

enum AddressingType {
  IMMEDIATE,
  DIRECT,
  INDIRECT,
  INDEX,
};

const std::map<AddressingType, char> kAddressingToCharacter = {
  {AddressingType::IMMEDIATE, '.'},
  {AddressingType::DIRECT, '@'},
  {AddressingType::INDIRECT, '*'},
  {AddressingType::INDEX, '+'},
};

const std::map<char, AddressingType> kCharacterToAddressing = {
  {'.', AddressingType::IMMEDIATE},
  {'@', AddressingType::DIRECT},
  {'*', AddressingType::INDIRECT},
  {'+', AddressingType::INDEX},
};

}  // namespace command

#endif  // COM_GITHUB_PITEX_PMC_INTERPRETER_COMMAND_ADDRESSING_TYPE_H_