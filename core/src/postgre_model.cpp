#include "../headers/postgre_model.hpp"
#include <QSqlDatabase>
#include <QDebug>


PostgreModel::PostgreModel(const char *main_table, const QList<std::pair<int, QSqlRelation> >& relations)
    :_main_table(main_table),
     _relations(relations)
{

}

bool PostgreModel::init(const char *from)
{
    QString parse_from = from;
    qDebug() << parse_from;

    QList init_data = parse_from.split(u';');
    qDebug() << init_data;

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName(init_data[0]);
    db.setDatabaseName(init_data[1]);
    db.setUserName(init_data[2]);
    db.setPassword(init_data[3]);
    bool ok = db.open();
    if (!ok)
    {
        return ok;
    }

    _model = new QSqlRelationalTableModel(nullptr, db);
    _model->setTable(_main_table);

    for (auto& relation : _relations)
    {
        _model->setRelation(relation.first, relation.second);
    }

    qDebug() << _model->select();
    return ok;
}

void PostgreModel::add(const char *what, const char *to, const char *table)
{

}

void PostgreModel::edit(const char *what, const char *to, const char *table)
{

}

void PostgreModel::remove(const char *what, const char *table)
{

}

const char *PostgreModel::get(const char *what, const char *table)
{

}
