
#include "../headers/postgre_model.hpp"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRelationalDelegate>
#include <QCoreApplication>

class PostgreModel;

/**
 * @class QSqlRelationalTableModelDebug
 * @brief Класс, наследующий QSqlRelationalTableModel для отладки.
 */
class QSqlRelationalTableModelDebug: public QSqlRelationalTableModel
{
public:
    /**
     * @brief Конструктор класса QSqlRelationalTableModelDebug.
     * @param parent Родительский объект.
     * @param db База данных.
     */
    QSqlRelationalTableModelDebug(QObject *parent = nullptr,
              const QSqlDatabase &db = QSqlDatabase()) {
        QSqlRelationalTableModel(parent, db);
    }
    /**
     * @brief Метод для получения дополнительных данных из модели.
     * @param parent Родительский индекс модели.
     */
    void fetchMore(const QModelIndex &parent = QModelIndex())
    {
        qDebug() << "Fetch more!";
        QSqlQueryModel::fetchMore(parent);
    }
    /**
     * @brief Метод для проверки, можно ли получить больше данных из модели.
     * @param parent Родительский индекс модели.
     * @return Возвращает true, если можно получить больше данных, иначе false.
     */
    bool canFetchMore(const QModelIndex &parent = QModelIndex())
    {
        qDebug() << "Can fetch more!";
        return QSqlQueryModel::canFetchMore(parent);
    }

};


/**
 * @brief Конструктор класса PostgreModel.
 * @param main_table Главная таблица базы данных.
 * @param relations Список отношений между таблицами.
 * @param column_names Список имен столбцов.
 * @param validators Валидаторы для проверки данных.
 */
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

/**
 * @brief Инициализация модели.
 * @param from Строка с данными для подключения к базе данных.
 * @return Возвращает true, если подключение к базе данных успешно.
 */
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
    for (auto& relation : _relations)
    {
        _header[relation.first] = relation.second.displayColumn();
    }


    qDebug() << _header;

    update_column_names();

    _model->select();

    qDebug() << "QuerySize: " << db.driver()->hasFeature(QSqlDriver::QuerySize);
    _is_init = true;
    return ok;
}

/**
 * @brief Добавление новой строки в модель.
 * @return Возвращает индекс добавленной строки.
 */
int PostgreModel::add()
{
    int row = _model->rowCount();
    qDebug() << "Inserted row: " << row;
    _model->insertRow(row);
    return row;
}

/**
 * @brief Удаление строки из модели.
 * @param what Индекс строки для удаления.
 * @return Возвращает true, если удаление прошло успешно.
 */
bool PostgreModel::remove(const char *what)
{
    unsigned int row_index = QString(what).toUInt();
    return _model->removeRow(row_index);
}

/*!
 * \brief Привязка модели к view
 * \param gui view для привязки
 */
void PostgreModel::bind(QAbstractItemView *gui)
{
    gui->setItemDelegate(new QSqlRelationalDelegateValidation(gui, _validators));
    gui->setModel(_model);
}

/*!
 * \brief Проверка на инициализацию
 * \return true если инициализирована, иначе false
 */
bool PostgreModel::is_initialized()
{
    return _is_init;
}

/*!
 * \brief Закрытие подключения к базе данных
 */
void PostgreModel::close()
{
    delete _model;
    _is_init = false;
}

/*!
 * \brief Применение транзакции
 * \return true если успешно приминена транзакция, иначе false
 */
bool PostgreModel::apply()
{
    return _model->submitAll();
}

/*!
 * \brief Отмена транзакции
 */
void PostgreModel::decline()
{
    _model->revertAll();
}

/*!
 * \brief Возвращение индекса из модели
 * \param row Индекс строки
 * \return Объект модели
 */
QModelIndex PostgreModel::index(int row)
{
    return _model->index(row, 1);
}

/*!
 * \brief Перевод полей таблицы
 */
void PostgreModel::update_column_names()
{
    int column_index = 1;
    for (auto& column_name: _column_names)
    {
        _model->setHeaderData(column_index++, Qt::Horizontal, QCoreApplication::translate("QObject", column_name.toLocal8Bit().data()));
    }
}

/*!
 * \brief Доступ к названием полей
 * \param column Индекс поля
 * \return Название поля
 */
QString PostgreModel::column_name(int column)
{
    return _header[column];
}

/**
 * @brief Фильтрация модели.
 * @param filter Строка фильтра.
 */
void PostgreModel::filter(QString filter)
{
    _model->setFilter(filter);
}

