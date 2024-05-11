#include "connectdialog.h"
#include "ui_connectdialog.h"

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

        _model->init(from.toLocal8Bit().data());
    }
}

