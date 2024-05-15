#include "qt/headers/connectdialog.h"
#include "ui_connectdialog.h"
#include <QMessageBox>

ConnectDialog::ConnectDialog(QWidget *parent, PostgreModel* model, QTableView* view) :
    QDialog(parent),
    ui(new Ui::ConnectDialog),
    _model(model),
    _view(view)
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
        if (!_model->init(from.toLocal8Bit().data()))
        {
            QMessageBox::critical(this,
                                  tr("Error!"),
                                  tr("Can't connect to database.\n"));
            return;
        }
        _model->bind(_view);
        _view->hideColumn(0);
        _view->resizeColumnsToContents();
        _view->show();
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

