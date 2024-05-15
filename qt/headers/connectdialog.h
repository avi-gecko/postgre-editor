#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include <QTableView>
#include "core/headers/postgre_model.hpp"

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = nullptr, PostgreModel* model = nullptr, QTableView* view = nullptr);
    ~ConnectDialog();

    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void _connect_to_db(const char* data);
    Ui::ConnectDialog *ui;
    PostgreModel* _model;
    QTableView* _view;
};

#endif // CONNECTDIALOG_H
