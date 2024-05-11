#include "qt/headers/mainwindow.h"
#include "core/headers/postgre_model.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QTest>

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
    MainWindow w(nullptr, new PostgreModel("suppliers", realtions));
    w.show();
    return a.exec();
}

