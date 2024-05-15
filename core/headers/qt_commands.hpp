#ifndef QT_COMMANDS_H
#define QT_COMMANDS_H

#include "../headers/command.hpp"
#include "../headers/model_interface.hpp"

#include <QWidget>
#include <QObject>

class InitCommand: public Command, public QObject
{
public:
    InitCommand(ModelInterface* model, QWidget* parent, const char* from);
    void execute() override;
private:
    ModelInterface* _model;
    QWidget* _parent;
    const char* _from;

    InitCommand() = delete;

};

#endif // QT_COMMANDS_H
