#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator
{

public:
    Calculator(int a = 0, int b = 0) : mA(a), mB(b) {}

    int GetA() const {return mA;}
    int GetB() const {return mB;}
    void SetA(int a) {mA = a;}
    void SetB(int b) {mB = b;}

    int Sum() const {return mA + mB;}
    int Diff() const {return mA - mB;}
    int Mult() const {return mA * mB;}
    int Div() const {return mA / mB;}

private:
    int mA, mB;
};

#endif // CALCULATOR_H
