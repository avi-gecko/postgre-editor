#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "headers/view_interface.hpp"
#include "core/headers/postgre_model.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public ViewInterface
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, PostgreModel* model = nullptr);
    ~MainWindow();

    void init_command() override;
    void close_command();
    void apply_transaction();
    void decline_transaction();

    void add_command() override;
    void add_directory_command() override;

    void edit_command() override;
    void edit_directory_command() override;

    void delete_command() override;
    void delete_directory_command() override;

    void get_command() override;
    void get_directory() override;

    void handle_command() override;

private slots:

private:
    Ui::MainWindow *ui;
    PostgreModel* _model;
};
#endif // MAINWINDOW_H
