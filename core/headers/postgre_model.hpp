#ifndef POSTGRE_MODEL_HPP
#define POSTGRE_MODEL_HPP

#include <QSqlRelationalTableModel>
#include <QAbstractItemView>
#include <QSqlError>


class PostgreModel
{
public:
    PostgreModel(const char* main_table,
                 const QList<std::pair<int, QSqlRelation>>& relations,
                 const QList<QString>& column_names);

    bool init(const char* from);
    int add();
    bool remove(const char* what);
    void bind(QAbstractItemView * gui);
    bool is_initialized();
    void close();
    bool apply();
    void decline();
    QModelIndex index(int row);
    void update_column_names();
    QString column_name(int column);
    void filter(QString filter);


    ~PostgreModel() {delete _model;}

private:
    QSqlRelationalTableModel* _model;
    const char* _main_table;
    const QList<std::pair<int, QSqlRelation>>& _relations;
    const QList<QString>& _column_names;
    QList<QString> _header;
    PostgreModel() = delete;
    bool _is_init;

};


#endif
