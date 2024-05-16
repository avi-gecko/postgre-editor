#include "qt/headers/mainwindow.h"
#include "core/headers/postgre_model.hpp"

#include <QApplication>
#include <QTest>
#include <QObject>
#include <QValidator>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const std::pair product_relation = {2, QSqlRelation("products", "id", "product_name")};
    const QList<std::pair<int, QSqlRelation>>& realtions = {product_relation};
    const QList<QString> column_names = {QObject::tr("Supplier"),
                                         QObject::tr("Equipment"),
                                         QObject::tr("Price"),
                                         QObject::tr("Stock"),
                                         QObject::tr("Email")};

    QRegularExpressionValidator* email_validator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$"));
    const std::pair email_validator_binded = {email_validator, QString("mailname@host.domain")};

    QMap<int, std::pair<QValidator*, QString>>* validators = new QMap<int, std::pair<QValidator*, QString>>;
    (*validators)[5] = email_validator_binded;

    MainWindow w(nullptr, new PostgreModel("suppliers", realtions, column_names, validators));
    w.show();
    return a.exec();
}

