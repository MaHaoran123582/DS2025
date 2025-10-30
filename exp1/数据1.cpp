#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <cmath>

// �����ඨ��
class Complex {
private:
    double real;   // ʵ��
    double imag;   // �鲿
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // ��ȡʵ�����鲿
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // ����ʵ�����鲿
    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }

    // ���㸴����ģ
    double getMod() const { return std::sqrt(real * real + imag * imag); }

    // ����==��������ж����������Ƿ�ʵ�����鲿����ͬ
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    // ����<<������������������
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
        return os;
    }
};

// �ȽϺ������Ȱ�ģ����ģ��ͬʱ��ʵ������
bool compareComplex(const Complex& c1, const Complex& c2) {
    double mod1 = c1.getMod();
    double mod2 = c2.getMod();
    if (mod1 != mod2) {
        return mod1 < mod2;
    } else {
        return c1.getReal() < c2.getReal();
    }
}

