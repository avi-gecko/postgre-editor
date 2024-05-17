#include "qt/headers/connectdialog.h"
#include "ui_connectdialog.h"

#include <QMessageBox>
#include <QDragEnterEvent>
#include <QPushButton>
#include <QMimeData>
#include <QFile>

/**
 * @brief Конструктор класса ConnectDialog.
 * @param parent Родительский виджет.
 * @param model Модель данных PostgreModel.
 * @param view Представление данных QTableView.
 */
ConnectDialog::ConnectDialog(QWidget *parent, PostgreModel* model, QTableView* view) :
    QDialog(parent),
    ui(new Ui::ConnectDialog),
    _model(model),
    _view(view)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Connect"));
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    setAcceptDrops(true);
}

/**
 * @brief Деструктор класса ConnectDialog.
 */
ConnectDialog::~ConnectDialog()
{
    delete ui;
}

/**
 * @brief Обработчик события входа перетаскивания.
 * @param e Событие перетаскивания.
 */
void ConnectDialog::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
}

/**
 * @brief Обработчик события отпускания перетаскивания.
 * @param e Событие отпускания перетаскивания.
 */
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
        return;
    }

    QMessageBox::critical(this,
                          tr("Error!"),
                          tr("Database is already opened."));
    reject();
}

/**
 * @brief Обработчик события принятия диалогового окна.
 */
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
        return;
    }

    QMessageBox::critical(this,
                          tr("Error!"),
                          tr("Database is already opened."));
    reject();
}

/**
 * @brief Обработчик события отклонения диалогового окна.
 */
void ConnectDialog::on_buttonBox_rejected()
{
    reject();
}

/**
 * @brief Метод подключения к базе данных.
 * @param data Данные для подключения.
 */
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
