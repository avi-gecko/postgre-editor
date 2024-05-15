#include "qt/headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "qt/headers/connectdialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent, PostgreModel* model)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _model(model)
{
    ui->setupUi(this);

    connect(ui->actionConnect_to_a_database,
            &QAction::triggered,
            this,
            &MainWindow::init_command);

    connect(ui->actionClose_connection,
            &QAction::triggered,
            this,
            &MainWindow::close_command);

    connect(ui->removeButton,
            &QPushButton::clicked,
            this,
            &MainWindow::delete_command);

    connect(ui->acceptButton,
            &QPushButton::clicked,
            this,
            &MainWindow::apply_transaction);

    connect(ui->declineButton,
            &QPushButton::clicked,
            this,
            &MainWindow::decline_transaction);

    connect(ui->addButton,
            &QPushButton::clicked,
            this,
            &MainWindow::add_command);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete _model;
}

void MainWindow::init_command()
{
    qDebug() << "Initialization database...";
    ConnectDialog w(nullptr, _model, ui->tableView);
    w.exec();
}

void MainWindow::close_command()
{
    _model->close();
}

void MainWindow::apply_transaction()
{
    if (_model->apply())
    {
        ui->tableView->reset();
        qDebug() << "Applied transaction";
    }
    else
        QMessageBox::critical(this,
                              tr("Error transaction!"),
                              tr("Cannot apply transaction\n"));
}

void MainWindow::decline_transaction()
{
    _model->decline();
    qDebug() << "Descline transaction";
}

void MainWindow::add_command()
{   int inserted_row = _model->add();
    if (!inserted_row)
        QMessageBox::critical(this,
                              tr("Error insert row!"),
                              tr("Cannot insert row.\n"));

    QModelIndex insert_index = _model->index(inserted_row);
    ui->tableView->setCurrentIndex(insert_index);
    ui->tableView->edit(insert_index);
}


void MainWindow::delete_command()
{
    QModelIndexList indexList = ui->tableView->selectionModel()->selectedIndexes();
    qDebug() << "Count = " << indexList.count();
    for (QModelIndex &index : indexList)
    {
        int selectedRow = index.row();
        qDebug() << "row = " << selectedRow;
        if (selectedRow >= 0) {
            char buf[256];
            sprintf(buf, "%d", selectedRow);
            _model->remove(buf);
        }
    }
}



