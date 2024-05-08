#include "qt/headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "core/headers/init_command.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_command()
{

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

