#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "core/headers/postgre_model.hpp"
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, PostgreModel* model = nullptr);
    ~MainWindow();

    void init_command();
    void close_command();

    void apply_transaction();
    void decline_transaction();

    void add_command();
    void delete_command();

    void sorting_command();

    void author_command();

    void set_filter_command();
    void unset_filter_command();

    void closeEvent(QCloseEvent *event) override;


private:
    Ui::MainWindow *ui;
    PostgreModel* _model;
    QTranslator _translator;
    QList<QAction*> _languages;
};
#endif // MAINWINDOW_H
