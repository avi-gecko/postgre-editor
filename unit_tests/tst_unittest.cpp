#include <QtTest>
#include <QCoreApplication>

#include "../headers/model_interface.hpp"
#include "../core/headers/postgre_model.hpp"

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
    ModelInterface* model = new PostgreModel;
    QVERIFY(model->init("192.168.56.2;db;alexey;123"));
    delete model;
}

QTEST_MAIN(UnitTest)

#include "tst_unittest.moc"
