#include <QtTest>
#include <QCoreApplication>

#include "../core/headers/postgre_model.hpp"
#include <QSqlRelation>
#include <QTableView>

class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();
    ~UnitTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_init_db();
    void test_remove_to_db();

};

UnitTest::UnitTest()
{


}

UnitTest::~UnitTest()
{


}

void UnitTest::initTestCase()
{

}

void UnitTest::cleanupTestCase()
{
}

void UnitTest::test_init_db()
{
    const std::pair product_relation = {2, QSqlRelation("products", "id", "product_name")};
    const QList<std::pair<int, QSqlRelation>>& realtions = {product_relation};
    PostgreModel* model = new PostgreModel("suppliers", realtions);
    QVERIFY(model->init("192.168.56.2;db;alexey;123"));
    delete model;
}

void UnitTest::test_remove_to_db()
{
    const std::pair product_relation = {2, QSqlRelation("products", "id", "product_name")};
    const QList<std::pair<int, QSqlRelation>>& realtions = {product_relation};
    PostgreModel* model = new PostgreModel("suppliers", realtions);
    model->init("192.168.56.2;db;alexey;123");
    //QVERIFY(model->remove("2", ""));
    delete model;
}





QTEST_MAIN(UnitTest)

#include "tst_unittest.moc"
