#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <cmath>

// 复数类定义
class Complex {
private:
    double real;   // 实部
    double imag;   // 虚部
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 获取实部和虚部
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // 设置实部和虚部
    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }

    // 计算复数的模
    double getMod() const { return std::sqrt(real * real + imag * imag); }

    // 重载==运算符，判断两个复数是否实部和虚部都相同
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    // 重载<<运算符，用于输出复数
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
        return os;
    }
};

// 比较函数：先按模排序，模相同时按实部排序
bool compareComplex(const Complex& c1, const Complex& c2) {
    double mod1 = c1.getMod();
    double mod2 = c2.getMod();
    if (mod1 != mod2) {
        return mod1 < mod2;
    } else {
        return c1.getReal() < c2.getReal();
    }
}

