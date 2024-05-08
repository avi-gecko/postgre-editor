#ifndef POSTGRE_MODEL_HPP
#define POSTGRE_MODEL_HPP

#include "../headers/model_interface.hpp"
#include <QSqlRelationalTableModel>


class PostgreModel: public ModelInterface
{
public:
    PostgreModel(const char* main_table, const QList<std::pair<int, QSqlRelation>>& relations);

    bool init(const char* from) override;
    void add(const char* what, const char* to, const char* table) override;
    void edit(const char* what, const char* to, const char* table) override;
    void remove(const char* what, const char* table) override;
    const char* get(const char* what, const char* table) override;

    ~PostgreModel() {delete _model;};
private:
    QSqlRelationalTableModel* _model;
    const char* _main_table;
    const QList<std::pair<int, QSqlRelation>>& _relations;
    PostgreModel() = delete;

};


#endif
