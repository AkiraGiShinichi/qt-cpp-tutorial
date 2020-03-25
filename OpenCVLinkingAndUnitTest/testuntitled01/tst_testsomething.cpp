#include <QtTest>
#include "Calculator.h"
#include "calculator2.h"

// add necessary includes here

class testsomething : public QObject
{
    Q_OBJECT

public:
    testsomething();
    ~testsomething();

private slots:
    void test_case1();

    void init();

    void testConstructor();
    void testSum();
    void testSum2();

private:
    const int A0 = 0;
    const int B0 = 0;

private:
    Calculator mCalc;
    Calculator2 mCalc2;

};

void testsomething::init()
{
    mCalc.SetA(A0);
    mCalc.SetB(B0);
}

void testsomething::testConstructor()
{
    Calculator c1;
    QVERIFY(c1.GetA() == 0);
    QVERIFY(c1.GetB() == 0);

    const int A = 10;
    const int B = 2;
    Calculator c2(A, B);
    QVERIFY2(c2.GetA() == 10, "first operand doesn't match");
    QVERIFY2(c2.GetB() == B, "second operand doesn't match");
}

void testsomething::testSum()
{
    QCOMPARE(mCalc.Sum(), A0 + B0);

    const int A = 10;
    const int B = 2;
    mCalc.SetA(A);
    mCalc.SetB(B);
    QCOMPARE(mCalc.Sum(), A + B);
}

void testsomething::testSum2()
{
    const int A = 7;
    const int B = 6;
    mCalc2.SetA(A);
    mCalc2.SetB(B);
    QCOMPARE(mCalc2.Sum(), A + B);
}

testsomething::testsomething()
{

}

testsomething::~testsomething()
{

}

void testsomething::test_case1()
{

}

QTEST_APPLESS_MAIN(testsomething)

#include "tst_testsomething.moc"
