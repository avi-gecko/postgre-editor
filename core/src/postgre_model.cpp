#include "../headers/postgre_model.hpp"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>



class QSqlRelationalTableModelDebug: public QSqlRelationalTableModel
{
public:
    QSqlRelationalTableModelDebug(QObject *parent = nullptr,
              const QSqlDatabase &db = QSqlDatabase()) {
        QSqlRelationalTableModel(parent, db);
    }
    void fetchMore(const QModelIndex &parent = QModelIndex())
    {
        qDebug() << "Fetch more!";
        QSqlQueryModel::fetchMore(parent);
    }
    bool canFetchMore(const QModelIndex &parent = QModelIndex())
    {
        qDebug() << "Can fetch more!";
        return QSqlQueryModel::canFetchMore(parent);
    }
};



PostgreModel::PostgreModel(const char *main_table, const QList<std::pair<int, QSqlRelation> >& relations)
    :_main_table(main_table),
     _relations(relations),
     _is_init(false)
{

}

bool PostgreModel::init(const char *from)
{
    QString parse_from = from;
    qDebug() << parse_from;

    QList init_data = parse_from.split(u';');
    qDebug() << init_data;

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setConnectOptions("requiressl=1;connect_timeout=2");
    db.setHostName(init_data[0]);
    db.setDatabaseName(init_data[1]);
    db.setUserName(init_data[2]);
    db.setPassword(init_data[3]);
    bool ok = db.open();
    if (!ok)
    {
        return ok;
    }


    _model = new QSqlRelationalTableModelDebug(nullptr, db);
    _model->setTable(_main_table);
    _model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    for (auto& relation : _relations)
    {
        _model->setRelation(relation.first, relation.second);
    }


    _model->select();

    qDebug() << db.driver()->hasFeature(QSqlDriver::QuerySize);
    _is_init = true;
    return ok;
}

void PostgreModel::add(const char *what, const char *to, const char *table)
{

}

void PostgreModel::edit(const char *what, const char *to, const char *table)
{

}

bool PostgreModel::remove(const char *what, const char *table)
{
    unsigned int row_index = QString(what).toUInt();
    return _model->removeRow(row_index);
}

const char *PostgreModel::get(const char *what, const char *table)
{

}

void PostgreModel::bind(QAbstractItemView *gui)
{
    gui->setItemDelegate(new QSqlRelationalDelegate(gui));
    gui->setModel(this->_model);
}

bool PostgreModel::is_initialized()
{
    return _is_init;
}

bool PostgreModel::close()
{
    delete _model;
    _is_init = false;
}

bool PostgreModel::apply()
{
    return _model->submitAll();
}

void PostgreModel::descline()
{
    _model->revertAll();
}
