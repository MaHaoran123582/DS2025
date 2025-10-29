#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <cmath>

class Complex {
private:
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    double getReal() const { return real; }
    double getImag() const { return imag; }
    double getMod() const { return std::sqrt(real * real + imag * imag); }
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
        return os;
    }
};

bool compareComplex(const Complex& c1, const Complex& c2) {
    double mod1 = c1.getMod(), mod2 = c2.getMod();
    return mod1 != mod2 ? mod1 < mod2 : c1.getReal() < c2.getReal();
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-10, 10);

    std::vector<Complex> vec;
    for (int i = 0; i < 20; ++i) {
        vec.emplace_back(dis(gen), dis(gen));
        if (i % 5 == 0) { vec.push_back(vec.back()); }
    }

    // (1) 置乱、查找、插入、删除、唯一化
    std::shuffle(vec.begin(), vec.end(), gen);
    Complex target(0, 0);
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) std::cout << "找到: " << *it << "\n";
    vec.insert(vec.begin() + 5, Complex(1, 1));
    it = std::find(vec.begin(), vec.end(), Complex(1, 1));
    if (it != vec.end()) vec.erase(it);
    std::sort(vec.begin(), vec.end(), compareComplex);
    auto last = std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());

    // (2) 冒泡与归并排序效率对比
    std::vector<Complex> bubbleVec, mergeVec;
    for (int i = 0; i < 1000; ++i) {
        bubbleVec.emplace_back(dis(gen), dis(gen));
        mergeVec.push_back(bubbleVec.back());
    }

    clock_t start = clock();
    for (size_t i = 0; i < bubbleVec.size() - 1; ++i)
        for (size_t j = 0; j < bubbleVec.size() - i - 1; ++j)
            if (!compareComplex(bubbleVec[j], bubbleVec[j + 1]))
                std::swap(bubbleVec[j], bubbleVec[j + 1]);
    clock_t end = clock();
    std::cout << "冒泡排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";

    start = clock();
    std::sort(mergeVec.begin(), mergeVec.end(), compareComplex);
    end = clock();
    std::cout << "归并排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";

    // (3) 区间查找
    double m1 = 5, m2 = 8;
    std::vector<Complex> result;
    for (const auto& c : mergeVec) {
        double mod = c.getMod();
        if (mod >= m1 && mod < m2) result.push_back(c);
    }
    std::cout << "模在[" << m1 << "," << m2 << ")的元素: \n";
    for (const auto& c : result) std::cout << c << " (模=" << c.getMod() << ")\n";

    return 0;

}
