#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>

// 复数类定义
class Complex {
private:
    double real;   // 实部
    double imag;   // 虚部

public:
    // 构造函数
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // 获取实部和虚部
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // 计算复数的模
    double getModulus() const {
        return std::sqrt(real * real + imag * imag);
    }

    // 重载==运算符（实部和虚部均相等才认为相等）
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    // 重载!=运算符
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // 重载<运算符（用于排序：先比较模，模相等则比较实部）
    bool operator<(const Complex& other) const {
        double mod1 = getModulus();
        double mod2 = other.getModulus();
        if (mod1 != mod2) {
            return mod1 < mod2;
        } else {
            return real < other.real;
        }
    }

    // 重载>运算符
    bool operator>(const Complex& other) const {
        return other < *this;
    }

    // 输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
        return os;
    }
};

// 生成随机复数向量（包含重复元素）
std::vector<Complex> generateRandomComplexVector(int size) {
    std::vector<Complex> vec;
    for (int i = 0; i < size; ++i) {
        double real = rand() % 20 - 10;  // 实部范围：[-10, 10)
        double imag = rand() % 20 - 10;  // 虚部范围：[-10, 10)
        vec.push_back(Complex(real, imag));
        // 每3个元素添加一个重复项
        if (i % 3 == 0) {
            vec.push_back(Complex(real, imag));
        }
    }
    return vec;
}

// 查找复数（返回第一个匹配元素的索引，未找到返回-1）
int findComplex(const std::vector<Complex>& vec, const Complex& target) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// 删除向量中所有匹配的复数
void deleteComplex(std::vector<Complex>& vec, const Complex& target) {
    auto it = vec.begin();
    while (it != vec.end()) {
        if (*it == target) {
            it = vec.erase(it);  // erase返回下一个迭代器
        } else {
            ++it;
        }
    }
}

// 向量唯一化（去除重复元素）
void uniqueComplex(std::vector<Complex>& vec) {
    std::sort(vec.begin(), vec.end());  // 先排序
    auto last = std::unique(vec.begin(), vec.end());  // 移动重复元素到末尾
    vec.erase(last, vec.end());  // 删除重复元素
}

// 起泡排序实现
void bubbleSort(std::vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// 区间查找（返回模在[m1, m2)范围内的元素）
std::vector<Complex> findInRange(const std::vector<Complex>& vec, double m1, double m2) {
    std::vector<Complex> result;
    for (const auto& c : vec) {
        double mod = c.getModulus();
        if (mod >= m1 && mod < m2) {
            result.push_back(c);
        }
    }
    return result;
}

int main() {
    // 初始化随机数种子
    srand(static_cast<unsigned>(time(nullptr)));

    // 1. 生成并展示原始向量
    std::vector<Complex> vec = generateRandomComplexVector(10);
    std::cout << "=== 原始向量 ===" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n向量大小: " << vec.size() << "\n" << std::endl;

    // 2. 置乱向量
    std::random_shuffle(vec.begin(), vec.end());
    std::cout << "=== 置乱后向量 ===" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n" << std::endl;

    // 3. 查找操作
    Complex target(3, 5);  // 要查找的目标复数
    int index = findComplex(vec, target);
    if (index != -1) {
        std::cout << "找到复数 " << target << "，索引为: " << index << std::endl;
    } else {
        std::cout << "未找到复数 " << target << std::endl;
    }
    std::cout << std::endl;

    // 4. 插入操作
    Complex insertVal(7, 8);  // 要插入的复数
    vec.insert(vec.begin() + 2, insertVal);  // 在索引2处插入
    std::cout << "=== 插入 " << insertVal << " 后向量 ===" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n向量大小: " << vec.size() << "\n" << std::endl;

    // 5. 删除操作
    std::cout << "=== 删除 " << target << " 后向量 ===" << std::endl;
    deleteComplex(vec, target);
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n向量大小: " << vec.size() << "\n" << std::endl;

    // 6. 唯一化操作
    uniqueComplex(vec);
    std::cout << "=== 唯一化后向量 ===" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n向量大小: " << vec.size() << "\n" << std::endl;

    // 7. 排序效率对比（起泡排序 vs 归并排序）
    std::vector<Complex> bubbleVec = generateRandomComplexVector(1000);  // 用于起泡排序的向量
    std::vector<Complex> mergeVec = bubbleVec;  // 用于归并排序的向量（副本）

    // 起泡排序计时
    clock_t startBubble = clock();
    bubbleSort(bubbleVec);
    clock_t endBubble = clock();
    double bubbleTime = static_cast<double>(endBubble - startBubble) / CLOCKS_PER_SEC;

    // 归并排序计时（使用STL的sort，其底层包含归并排序逻辑）
    clock_t startMerge = clock();
    std::sort(mergeVec.begin(), mergeVec.end());
    clock_t endMerge = clock();
    double mergeTime = static_cast<double>(endMerge - startMerge) / CLOCKS_PER_SEC;

    std::cout << "=== 排序效率对比 ===" << std::endl;
    std::cout << "起泡排序时间: " << bubbleTime << " 秒" << std::endl;
    std::cout << "归并排序时间: " << mergeTime << " 秒" << std::endl;
    std::cout << "归并排序比起泡排序快约 " << bubbleTime / mergeTime << " 倍" << "\n" << std::endl;

    // 8. 区间查找（模在[m1, m2)范围内的元素）
    double m1 = 3.0, m2 = 7.0;
    std::vector<Complex> rangeResult = findInRange(mergeVec, m1, m2);
    std::cout << "=== 模在 [" << m1 << ", " << m2 << ") 范围内的元素 ===" << std::endl;
    for (const auto& c : rangeResult) {
        std::cout << c << " (模: " << c.getModulus() << ")" << std::endl;
    }

    return 0;
}

