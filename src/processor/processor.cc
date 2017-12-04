#include "src/processor/processor.h"

#include <fstream>
#include <string>

#include "src/command/addressing_type.h"
#include "src/command/type.h"

namespace processor {

const int kMaxCycles = 1000000000;

Processor::Processor(std::ifstream& cmd_file, std::ifstream& infile) {
  int command_number;
  cmd_file >> command_number;

  for (int i = 0; i < command_number; ++i) {
    ReadCommand(cmd_file);
  }

  int input_length;
  infile >> input_length;
  for (int i = 0; i < input_length; ++i) {
    ReadInput(infile);
  }
}

void Processor::ReadCommand(std::ifstream& cmd_file) {
  std::string memory_str, type;
  char addressing_type;
  int value, memory;

  cmd_file >> memory_str >> type;
  memory = atoi(memory_str.substr(0, memory_str.length() - 1).c_str());

  if (command::kStringToType.find(type) == command::kStringToType.end()) {
    memory_[memory] =
        command::Command(command::Type::VALUE, command::AddressingType::IMMEDIATE, atoi(type.c_str()));
    return;
  }

  cmd_file >> addressing_type >> value;

  memory_[memory] =
      command::Command(
          command::kStringToType.find(type)->second,
          command::kCharacterToAddressing.find(addressing_type)->second,
          value);
}

void Processor::ReadInput(std::ifstream& infile) {
  std::string memory;
  int value;

  infile >> memory >> value;

  memory_[atoi(memory.substr(0, memory.length() - 1).c_str())] =
      command::Command(command::Type::VALUE, command::AddressingType::IMMEDIATE, value);
}

ErrorCode Processor::RunPMC() {
  ErrorCode return_value;
  int counter = 0;

  while ((return_value = RunCommand(++cache_[CacheType::PC])) > 0) {
    ++counter;
    if (counter > kMaxCycles) {
      return ErrorCode::TIME_LIMIT_EXCEEDED;
    }
  }

  return return_value;
}

#define COUNT_OPERAND(a, v) ErrorCode e = CountOperand(a, v); if(e <= 0) { return e; }

ErrorCode Processor::RunCommand(const int& memory) {
  command::Command current_command = memory_[memory];

  switch (current_command.type()) {
    case (command::Type::LOAD): {
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      cache_[CacheType::AC] = cache_[CacheType::OP];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::STORE): {
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      memory_[CacheType::OP].set_value(cache_[CacheType::AC]);
      return ErrorCode::CONTINUE;
    }
    case (command::Type::JUMP): {
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      cache_[CacheType::PC] = cache_[CacheType::OP];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::JNEG): {
      if (cache_[CacheType::AC] >= 0) {
        return ErrorCode::CONTINUE;
      }
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      cache_[CacheType::PC] = cache_[CacheType::OP];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::JZERO): {
      if (cache_[CacheType::AC] != 0) {
        return ErrorCode::CONTINUE;
      }
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      cache_[CacheType::PC] = cache_[CacheType::OP];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::STOP): {
      return ErrorCode::COMPLETED;
    }
    case (command::Type::NILL): {
      ++cache_[CacheType::PC];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::ADD): {
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      cache_[CacheType::AC] += cache_[CacheType::OP];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::SUB): {
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      cache_[CacheType::AC] -= cache_[CacheType::OP];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::AND): {
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      cache_[CacheType::AC] &= cache_[CacheType::OP];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::OR): {
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      cache_[CacheType::AC] |= cache_[CacheType::OP];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::NOT): {
      cache_[CacheType::AC] = ~cache_[CacheType::AC];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::SHL): {
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      cache_[CacheType::AC] <<= cache_[CacheType::OP];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::SHR): {
      COUNT_OPERAND(current_command.addressing_type(), current_command.value())
      cache_[CacheType::AC] >>= cache_[CacheType::OP];
      return ErrorCode::CONTINUE;
    }
    case (command::Type::VALUE): {
      return ErrorCode::NO_COMMAND_TO_RUN;
    }
    default: {
      return ErrorCode::UNKNOWN_COMMAND_TYPE;
    }
  }
}

#undef COUNT_OPERAND

ErrorCode Processor::CountOperand(const command::AddressingType& addressing_type, const int& value) {
  switch (addressing_type) {
    case (command::AddressingType::IMMEDIATE): {
      cache_[CacheType::OP] = value;
      return ErrorCode::CONTINUE;
    }
    case (command::AddressingType::DIRECT): {
      cache_[CacheType::OP] = memory_[value].value();
      return ErrorCode::CONTINUE;
    }
    case (command::AddressingType::INDIRECT): {
      cache_[CacheType::OP] = memory_[memory_[value].value()].value();
      return ErrorCode::CONTINUE;
    }
    case (command::AddressingType::INDEX): {
      cache_[CacheType::OP] = memory_[cache_[CacheType::AC] + value].value();
      return ErrorCode::CONTINUE;
    }
    default: {
      return ErrorCode::UNKNOWN_ADDRESSING_TYPE;
    }
  }
}

}  // namespace processor
