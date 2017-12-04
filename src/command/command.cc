#include "src/command/command.h"

namespace command {

Command::Command()
    : type_(Type::NILL),
      addressing_type_(AddressingType::IMMEDIATE),
      value_(0) {}

Command::Command(Type type, AddressingType addressing_type, int value)
    : type_(type),
      addressing_type_(addressing_type),
      value_(value) {}

}  // namespace command
