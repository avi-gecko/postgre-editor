#include "qt/headers/mainwindow.h"
#include "ui_mainwindow.h"

#include "qt/headers/connectdialog.h"
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent, PostgreModel* model)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _model(model)
{
    ui->setupUi(this);

    QSettings settings("MGSU", "Database");
    settings.beginGroup("MainWindowGeometry");
        const auto geometry = settings.value("geometry", QByteArray()).toByteArray();
        if (geometry.isEmpty())
            setGeometry(200, 200, 400, 400);
        else
            restoreGeometry(geometry);
    settings.endGroup();

    qDebug() << "Enter window size: " << size();
    qDebug() << "Enter window position: " << pos().rx() << ' ' << pos().rx();

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

    connect(ui->actionAuthor,
            &QAction::triggered,
            this,
            &MainWindow::author_command);

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
    qDebug() << "add_command inserted row: " << inserted_row;
    if (!inserted_row)
    {
        QMessageBox::critical(this,
                              tr("Error insert row!"),
                              tr("Cannot insert row.\n"));
        return;
    }

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

void MainWindow::author_command()
{
    QMessageBox::information(this,
                             tr("Author"),
                             tr("Created by Alexey Ilin ICTMS 3-5"));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("MGSU", "Database");
    settings.beginGroup("MainWindowGeometry");
        settings.setValue("geometry", saveGeometry());
    settings.endGroup();

    qDebug() << "Exit window size: " << size();
    qDebug() << "Exit window position: " << pos().rx() << ' ' << pos().rx();

    event->accept();

}



