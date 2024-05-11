#include "qt/headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "core/headers/init_command.hpp"
#include "qt/ui/connectdialog.h"

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


