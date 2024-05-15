#include "core/headers/qt_commands.hpp"
#include <QMessageBox>


InitCommand::InitCommand(ModelInterface *model, QWidget *parent, const char *from)
    :_model(model),
     _parent(parent),
     _from(from)
{

}

void InitCommand::execute()
{
    if (!_model->init(_from))
    {
        QMessageBox::critical(_parent,
                              tr("Error!"),
                              tr("Can't connect to database."));
    };
}
