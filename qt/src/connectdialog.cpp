#include "qt/headers/connectdialog.h"
#include "ui_connectdialog.h"

#include <QMessageBox>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFile>

ConnectDialog::ConnectDialog(QWidget *parent, PostgreModel* model, QTableView* view) :
    QDialog(parent),
    ui(new Ui::ConnectDialog),
    _model(model),
    _view(view)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }

}

void ConnectDialog::dropEvent(QDropEvent *e)
{
    QFile file_connection(e->mimeData()->urls()[0].toLocalFile());
    if (!file_connection.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file_connection);
    QString connection_data = in.readLine();
    qDebug() << connection_data;
    if (!_model->is_initialized())
    {
        ConnectDialog::_connect_to_db(connection_data.toLocal8Bit().data());
        accept();
    }

    QMessageBox::critical(this,
                          tr("Error!"),
                          tr("Database is already opened."));
    reject();
}

void ConnectDialog::on_buttonBox_accepted()
{
    if (!_model->is_initialized())
    {
        QString connection_data = ui->serverEdit->text() + ';' +
                       ui->databaseEdit->text() + ';' +
                       ui->userEdit->text() + ';' +
                       ui->passwordEdit->text();
        qDebug() << connection_data;
        ConnectDialog::_connect_to_db(connection_data.toLocal8Bit().data());
        accept();
    }

    QMessageBox::critical(this,
                          tr("Error!"),
                          tr("Database is already opened."));
    reject();
}


void ConnectDialog::on_buttonBox_rejected()
{
    reject();
}

void ConnectDialog::_connect_to_db(const char* data)
{
    if (!_model->init(data))
    {
        QMessageBox::critical(this,
                              tr("Error!"),
                              tr("Can't connect to database.\n"));
        return;
    }
    _model->bind(_view);
    _view->hideColumn(0);
    _view->resizeColumnsToContents();
    _view->setSortingEnabled(true);
    _view->show();
}

