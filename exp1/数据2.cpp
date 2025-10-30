#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>

// �����ඨ��
class Complex {
private:
    double real;   // ʵ��
    double imag;   // �鲿

public:
    // ���캯��
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // ��ȡʵ�����鲿
    double getReal() const { return real; }
    double getImag() const { return imag; }

    // ���㸴����ģ
    double getModulus() const {
        return std::sqrt(real * real + imag * imag);
    }

    // ����==�������ʵ�����鲿����Ȳ���Ϊ��ȣ�
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    // ����!=�����
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // ����<����������������ȱȽ�ģ��ģ�����Ƚ�ʵ����
    bool operator<(const Complex& other) const {
        double mod1 = getModulus();
        double mod2 = other.getModulus();
        if (mod1 != mod2) {
            return mod1 < mod2;
        } else {
            return real < other.real;
        }
    }

    // ����>�����
    bool operator>(const Complex& other) const {
        return other < *this;
    }

    // ������������
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << (c.imag >= 0 ? "+" : "") << c.imag << "i";
        return os;
    }
};

// ����������������������ظ�Ԫ�أ�
std::vector<Complex> generateRandomComplexVector(int size) {
    std::vector<Complex> vec;
    for (int i = 0; i < size; ++i) {
        double real = rand() % 20 - 10;  // ʵ����Χ��[-10, 10)
        double imag = rand() % 20 - 10;  // �鲿��Χ��[-10, 10)
        vec.push_back(Complex(real, imag));
        // ÿ3��Ԫ�����һ���ظ���
        if (i % 3 == 0) {
            vec.push_back(Complex(real, imag));
        }
    }
    return vec;
}

// ���Ҹ��������ص�һ��ƥ��Ԫ�ص�������δ�ҵ�����-1��
int findComplex(const std::vector<Complex>& vec, const Complex& target) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// ɾ������������ƥ��ĸ���
void deleteComplex(std::vector<Complex>& vec, const Complex& target) {
    auto it = vec.begin();
    while (it != vec.end()) {
        if (*it == target) {
            it = vec.erase(it);  // erase������һ��������
        } else {
            ++it;
        }
    }
}

// ����Ψһ����ȥ���ظ�Ԫ�أ�
void uniqueComplex(std::vector<Complex>& vec) {
    std::sort(vec.begin(), vec.end());  // ������
    auto last = std::unique(vec.begin(), vec.end());  // �ƶ��ظ�Ԫ�ص�ĩβ
    vec.erase(last, vec.end());  // ɾ���ظ�Ԫ��
}

// ��������ʵ��
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

// ������ң�����ģ��[m1, m2)��Χ�ڵ�Ԫ�أ�
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
    // ��ʼ�����������
    srand(static_cast<unsigned>(time(nullptr)));

    // 1. ���ɲ�չʾԭʼ����
    std::vector<Complex> vec = generateRandomComplexVector(10);
    std::cout << "=== ԭʼ���� ===" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n������С: " << vec.size() << "\n" << std::endl;

    // 2. ��������
    std::random_shuffle(vec.begin(), vec.end());
    std::cout << "=== ���Һ����� ===" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n" << std::endl;

    // 3. ���Ҳ���
    Complex target(3, 5);  // Ҫ���ҵ�Ŀ�긴��
    int index = findComplex(vec, target);
    if (index != -1) {
        std::cout << "�ҵ����� " << target << "������Ϊ: " << index << std::endl;
    } else {
        std::cout << "δ�ҵ����� " << target << std::endl;
    }
    std::cout << std::endl;

    // 4. �������
    Complex insertVal(7, 8);  // Ҫ����ĸ���
    vec.insert(vec.begin() + 2, insertVal);  // ������2������
    std::cout << "=== ���� " << insertVal << " ������ ===" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n������С: " << vec.size() << "\n" << std::endl;

    // 5. ɾ������
    std::cout << "=== ɾ�� " << target << " ������ ===" << std::endl;
    deleteComplex(vec, target);
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n������С: " << vec.size() << "\n" << std::endl;

    // 6. Ψһ������
    uniqueComplex(vec);
    std::cout << "=== Ψһ�������� ===" << std::endl;
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n������С: " << vec.size() << "\n" << std::endl;

    // 7. ����Ч�ʶԱȣ��������� vs �鲢����
    std::vector<Complex> bubbleVec = generateRandomComplexVector(1000);  // �����������������
    std::vector<Complex> mergeVec = bubbleVec;  // ���ڹ鲢�����������������

    // ���������ʱ
    clock_t startBubble = clock();
    bubbleSort(bubbleVec);
    clock_t endBubble = clock();
    double bubbleTime = static_cast<double>(endBubble - startBubble) / CLOCKS_PER_SEC;

    // �鲢�����ʱ��ʹ��STL��sort����ײ�����鲢�����߼���
    clock_t startMerge = clock();
    std::sort(mergeVec.begin(), mergeVec.end());
    clock_t endMerge = clock();
    double mergeTime = static_cast<double>(endMerge - startMerge) / CLOCKS_PER_SEC;

    std::cout << "=== ����Ч�ʶԱ� ===" << std::endl;
    std::cout << "��������ʱ��: " << bubbleTime << " ��" << std::endl;
    std::cout << "�鲢����ʱ��: " << mergeTime << " ��" << std::endl;
    std::cout << "�鲢��������������Լ " << bubbleTime / mergeTime << " ��" << "\n" << std::endl;

    // 8. ������ң�ģ��[m1, m2)��Χ�ڵ�Ԫ�أ�
    double m1 = 3.0, m2 = 7.0;
    std::vector<Complex> rangeResult = findInRange(mergeVec, m1, m2);
    std::cout << "=== ģ�� [" << m1 << ", " << m2 << ") ��Χ�ڵ�Ԫ�� ===" << std::endl;
    for (const auto& c : rangeResult) {
        std::cout << c << " (ģ: " << c.getModulus() << ")" << std::endl;
    }

    return 0;
}

