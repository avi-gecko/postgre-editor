#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <stack>


class Command
{
public:
    virtual void execute() = 0;

    void forward();
    void back();

    static void run();

    virtual ~Command() {};

private:
    static std::stack<Command*> _commands;
};


#endif
