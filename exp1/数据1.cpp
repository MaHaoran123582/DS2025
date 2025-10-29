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

int main() {
    // �����������
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-10, 10);

    // �������������������ظ��
    std::vector<Complex> vec;
    for (int i = 0; i < 20; ++i) {
        vec.emplace_back(dis(gen), dis(gen));
        // ����һЩ�ظ���
        if (i % 5 == 0) {
            vec.emplace_back(dis(gen), dis(gen));
            vec.push_back(vec.back());
        }
    }

    std::cout << "=== ԭʼ���� ===\n";
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // (1) ���ҡ����ҡ����롢ɾ����Ψһ������
    // ����
    std::shuffle(vec.begin(), vec.end(), gen);
    std::cout << "=== ���Һ� ===\n";
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // ���ң�ʾ�������ҵ�һ��ʵ�����鲿Ϊ0�ĸ�����
    Complex target(0, 0);
    auto it = std::find(vec.begin(), vec.end(), target);
    if (it != vec.end()) {
        std::cout << "�ҵ�Ŀ�긴��: " << *it << "\n";
    } else {
        std::cout << "δ�ҵ�Ŀ�긴��\n";
    }
    std::cout << "\n";

    // ����
    vec.insert(vec.begin() + 5, Complex(1, 1));
    std::cout << "=== ����� ===\n";
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // ɾ����ʾ����ɾ����һ��ʵ��Ϊ1���鲿Ϊ1�ĸ�����
    it = std::find(vec.begin(), vec.end(), Complex(1, 1));
    if (it != vec.end()) {
        vec.erase(it);
    }
    std::cout << "=== ɾ���� ===\n";
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // Ψһ������������ȥ�أ�
    std::sort(vec.begin(), vec.end(), compareComplex);
    auto last = std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
    std::cout << "=== Ψһ���� ===\n";
    for (const auto& c : vec) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // (2) ð������͹鲢�����Ч�ʱȽ�
    // ���ɲ�������
    std::vector<Complex> bubbleVec, mergeVec;
    for (int i = 0; i < 1000; ++i) {
        bubbleVec.emplace_back(dis(gen), dis(gen));
        mergeVec.push_back(bubbleVec.back());
    }

    // ˳������������ԣ�����������Ϊ����˳�����������ƹ��죩
    std::vector<Complex> sortedVec = bubbleVec;
    std::sort(sortedVec.begin(), sortedVec.end(), compareComplex);
    std::vector<Complex> reversedVec = sortedVec;
    std::reverse(reversedVec.begin(), reversedVec.end());

    // ð����������
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
    std::cout << "ð����������ʱ��: " << bubbleTime << " ��\n";

    // �鲢����STL��merge�߼���ʵ�ʿ��ֶ�ʵ�ֹ鲢��������sort�������Ч�ʣ�
    std::vector<Complex> mergeTest = bubbleVec;
    start = clock();
    std::sort(mergeTest.begin(), mergeTest.end(), compareComplex);
    end = clock();
    double mergeTime = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "�鲢��������ʱ��: " << mergeTime << " ��\n";
    std::cout << "\n";

    // (3) ������ң�ģ����m1��m2֮���Ԫ�أ�
    double m1 = 5, m2 = 8;
    std::vector<Complex> result;
    for (const auto& c : sortedVec) {  // ���������������
        double mod = c.getMod();
        if (mod >= m1 && mod < m2) {
            result.push_back(c);
        }
    }
    std::cout << "=== ģ����[" << m1 << "," << m2 << ")��Ԫ�� ===\n";
    for (const auto& c : result) {
        std::cout << c << " (ģ=" << c.getMod() << ")\n";
    }

    return 0;
}
