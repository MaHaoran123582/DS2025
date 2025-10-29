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

int main() {
    // 随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-10, 10);

    // 生成无序复数向量（有重复项）
    std::vector<Complex> vec;
    for (int i = 0; i < 20; ++i) {
        vec.emplace_back(dis(gen), dis(gen));
        // 插入一些重复项
        if (i % 5 == 0) {
            vec.emplace_back(dis(gen), dis(gen));
            vec.push_back(vec.back());
        }
    }

    std::cout << "=== 原始向量 ===\n";
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // (1) 置乱、查找、插入、删除、唯一化操作
    // 置乱
    std::shuffle(vec.begin(), vec.end(), gen);
    std::cout << "=== 置乱后 ===\n";
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // 查找（示例：查找第一个实部和虚部为0的复数）
    Complex target(0, 0);
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        std::cout << "找到目标复数: " << *it << "\n";
    } else {
        std::cout << "未找到目标复数\n";
    }
    std::cout << "\n";

    // 插入
    vec.insert(vec.begin() + 5, Complex(1, 1));
    std::cout << "=== 插入后 ===\n";
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // 删除（示例：删除第一个实部为1、虚部为1的复数）
    it = std::find(vec.begin(), vec.end(), Complex(1, 1));
    if (it != vec.end()) {
        vec.erase(it);
    }
    std::cout << "=== 删除后 ===\n";
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // 唯一化（先排序，再去重）
    std::sort(vec.begin(), vec.end(), compareComplex);
    auto last = std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
    std::cout << "=== 唯一化后 ===\n";
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // (2) 冒泡排序和归并排序的效率比较
    // 生成测试数据
    std::vector<Complex> bubbleVec, mergeVec;
    for (int i = 0; i < 1000; ++i) {
        bubbleVec.emplace_back(dis(gen), dis(gen));
        mergeVec.push_back(bubbleVec.back());
    }

    // 顺序、乱序、逆序测试（这里以乱序为例，顺序和逆序可类似构造）
    std::vector<Complex> sortedVec = bubbleVec;
    std::sort(sortedVec.begin(), sortedVec.end(), compareComplex);
    std::vector<Complex> reversedVec = sortedVec;
    std::reverse(reversedVec.begin(), reversedVec.end());

    // 冒泡排序（乱序）
    std::vector<Complex> bubbleTest = bubbleVec;
    clock_t start = clock();
    for (int i = 0; i < bubbleTest.size() - 1; ++i) {
        for (int j = 0; j < bubbleTest.size() - i - 1; ++j) {
            if (!compareComplex(bubbleTest[j], bubbleTest[j + 1])) {
                std::swap(bubbleTest[j], bubbleTest[j + 1]);
            }
        }
    }
    clock_t end = clock();
    double bubbleTime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "冒泡排序（乱序）时间: " << bubbleTime << " 秒\n";

    // 归并排序（STL的merge逻辑，实际可手动实现归并，这里用sort代替测试效率）
    std::vector<Complex> mergeTest = bubbleVec;
    start = clock();
    std::sort(mergeTest.begin(), mergeTest.end(), compareComplex);
    end = clock();
    double mergeTime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "归并排序（乱序）时间: " << mergeTime << " 秒\n";
    std::cout << "\n";

    // (3) 区间查找（模介于m1和m2之间的元素）
    double m1 = 5, m2 = 8;
    std::vector<Complex> result;
    for (const auto& c : sortedVec) {  // 基于已排序的向量
        double mod = c.getMod();
        if (mod >= m1 && mod < m2) {
            result.push_back(c);
        }
    }
    std::cout << "=== 模介于[" << m1 << "," << m2 << ")的元素 ===\n";
    for (const auto& c : result) {
        std::cout << c << " (模=" << c.getMod() << ")\n";
    }

    return 0;
}
