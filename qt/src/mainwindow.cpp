#include "qt/headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "core/headers/qt_commands.hpp"
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

}

MainWindow::~MainWindow()
{
    delete ui;
    delete _model;
}

void MainWindow::init_command()
{
    qDebug() << "Initialization database...";
    ConnectDialog w(nullptr, _model);
    w.exec();
    _model->bind(ui->tableView);
    ui->tableView->show();
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
                              tr("Error select!"),
                              tr("Error!"));
}

void MainWindow::decline_transaction()
{
    _model->descline();
    qDebug() << "Descline transaction";
}

void MainWindow::add_command()
{

}

void MainWindow::add_directory_command()
{

}

void MainWindow::edit_command()
{

}

void MainWindow::edit_directory_command()
{

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
            _model->remove(buf, "");
        }
    }
}

void MainWindow::delete_directory_command()
{

}

void MainWindow::get_command()
{

}

void MainWindow::get_directory()
{

}

void MainWindow::handle_command()
{

}


