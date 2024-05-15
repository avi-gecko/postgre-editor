#include "qt/headers/connectdialog.h"
#include "ui_connectdialog.h"
#include "core/headers/qt_commands.hpp"
#include <QMessageBox>

ConnectDialog::ConnectDialog(QWidget *parent, PostgreModel* model) :
    QDialog(parent),
    ui(new Ui::ConnectDialog),
    _model(model)
{
    ui->setupUi(this);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_buttonBox_accepted()
{
    if (!_model->is_initialized())
    {
        QString from = ui->serverEdit->text() + ';' +
                       ui->databaseEdit->text() + ';' +
                       ui->userEdit->text() + ';' +
                       ui->passwordEdit->text();
        qDebug() << from;
        InitCommand command(_model, this, from.toLocal8Bit().data());
        command.execute();
    }
    else
    {
        QMessageBox::critical(this,
                              tr("Error!"),
                              tr("Database is already opened."));
    }
}


void ConnectDialog::on_buttonBox_rejected()
{
    this->close();
}

