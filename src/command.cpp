#include "command.hpp"

std::stack<Command*> Command::_commands;

void Command::forward()
{
  _commands.push(this);
}

void Command::back()
{
  _commands.pop();
}

void Command::run()
{
  while (!_commands.empty())
  {
      Command* command = _commands.top();
      command->execute();
      delete command;
      _commands.pop();
  }
}
