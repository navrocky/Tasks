#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "task.h"

class AsynctaskTest : public QObject
{
    Q_OBJECT

public:
    AsynctaskTest();

private Q_SLOTS:
    void testCase1();
};

AsynctaskTest::AsynctaskTest()
{
}

void AsynctaskTest::testCase1()
{
//    auto task = Delay::start(2000);

//    Delay::start(1000)->continue_with([](){
//       qDebug() << "finished";
//    });


//    task->wait();

    tasks::task<void> t;


    tasks::task<int> t2;
    int v = t2.result();

    QVERIFY2(true, "Failure");
}

QTEST_MAIN(AsynctaskTest)

#include "tst_asynctasktest.moc"
