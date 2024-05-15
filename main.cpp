#include "qt/headers/mainwindow.h"
#include "core/headers/postgre_model.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QTest>
#include <QObject>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "cw-vesupplier_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    const std::pair product_relation = {2, QSqlRelation("products", "id", "product_name")};
    const QList<std::pair<int, QSqlRelation>>& realtions = {product_relation};
    const QList<QString> column_names = {QObject::tr("Supplier"),
                                         QObject::tr("Equipment"),
                                         QObject::tr("Equipment"),
                                         QObject::tr("Price"),
                                         QObject::tr("Stock"),
                                         QObject::tr("Email")};
    MainWindow w(nullptr, new PostgreModel("suppliers", realtions, column_names));
    w.show();
    return a.exec();
}

