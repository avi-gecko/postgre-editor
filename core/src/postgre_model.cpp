#include "../headers/postgre_model.hpp"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include <QCoreApplication>



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



PostgreModel::PostgreModel(const char *main_table,
                           const QList<std::pair<int, QSqlRelation> >& relations,
                           const QList<QString>& column_names,
                           QMap<int, std::pair<QValidator*, QString>>* validators)
    :_main_table(main_table),
     _relations(relations),
     _column_names(column_names),
     _is_init(false),
     _validators(validators)
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

    for (int i = 0; i != _model->columnCount(); ++i)
    {
        _header.append(_model->headerData(i, Qt::Horizontal).toString());
    }

    update_column_names();

    _model->select();

    qDebug() << db.driver()->hasFeature(QSqlDriver::QuerySize);
    _is_init = true;
    return ok;
}

int PostgreModel::add()
{
    int row = _model->rowCount();
    qDebug() << "Inserted row: " << row;
    _model->insertRow(row);
    return row;
}

bool PostgreModel::remove(const char *what)
{
    unsigned int row_index = QString(what).toUInt();
    return _model->removeRow(row_index);
}

void PostgreModel::bind(QAbstractItemView *gui)
{
    gui->setItemDelegate(new QSqlRelationalDelegateValidation(gui, _validators));
    gui->setModel(_model);
}

bool PostgreModel::is_initialized()
{
    return _is_init;
}

void PostgreModel::close()
{
    delete _model;
    _is_init = false;
}

bool PostgreModel::apply()
{
    return _model->submitAll();
}

void PostgreModel::decline()
{
    _model->revertAll();
}

QModelIndex PostgreModel::index(int row)
{
    return _model->index(row, 1);
}

void PostgreModel::update_column_names()
{
    int column_index = 1;
    for (auto& column_name: _column_names)
    {
        _model->setHeaderData(column_index++, Qt::Horizontal, QCoreApplication::translate("QObject", column_name.toLocal8Bit().data()));
    }
}

QString PostgreModel::column_name(int column)
{
    return _header[column];
}

void PostgreModel::filter(QString filter)
{
    _model->setFilter(filter);
}

