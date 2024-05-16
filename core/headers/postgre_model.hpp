#ifndef POSTGRE_MODEL_HPP
#define POSTGRE_MODEL_HPP

#include <QSqlRelationalTableModel>
#include <QLineEdit>
#include <QSqlRelationalDelegate>
#include <QAbstractItemView>
#include <QSqlError>

class QSqlRelationalDelegateValidation;
class PostgreModel
{
public:
    PostgreModel(const char* main_table,
                 const QList<std::pair<int, QSqlRelation>>& relations,
                 const QList<QString>& column_names,
                 QMap<int, std::pair<QValidator*, QString>>* validators);

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


    ~PostgreModel() {delete _model; delete _validators;}

private:
    QSqlRelationalTableModel* _model;
    const char* _main_table;
    const QList<std::pair<int, QSqlRelation>>& _relations;
    const QList<QString>& _column_names;
    QMap<int, std::pair<QValidator*, QString>>* _validators;
    QList<QString> _header;
    PostgreModel() = delete;
    bool _is_init;

};

class QSqlRelationalDelegateValidation: public QSqlRelationalDelegate
{
public:
    QSqlRelationalDelegateValidation(QObject* parent = 0, QMap<int, std::pair<QValidator*, QString>>* validators = nullptr):
        QSqlRelationalDelegate(parent),
        _validators(validators)
    {}
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
    {
        QWidget* editor = QSqlRelationalDelegate::createEditor(parent, option, index);
        QLineEdit* line_edit = qobject_cast<QLineEdit*>(editor);
        if (!line_edit)
            return editor;
        if (_validators->contains(index.column()))
        {
            line_edit->setValidator((*_validators)[index.column()].first);
            line_edit->setPlaceholderText((*_validators)[index.column()].second);
        }
        return line_edit;
    }
private:
    QMap<int, std::pair<QValidator*, QString>>* _validators;
};


#endif
