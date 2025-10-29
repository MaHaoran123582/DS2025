#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <unordered_map>

template <typename T>
class Stack {
private:
    std::stack<T> stk;
public:
    void push(const T& val) { stk.push(val); }
    void pop() { if (!stk.empty()) stk.pop(); }
    T top() const { return stk.top(); }
    bool empty() const { return stk.empty(); }
};

class Calculator {
private:
    std::unordered_map<char, int> priority = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 0}, {')', 0}};

    double calculate(double a, double b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': return b ? a / b : throw std::runtime_error("����Ϊ0");
            default: throw std::runtime_error("��Ч�����");
        }
    }

public:
    double calculateExpression(const std::string& expr) {
        Stack<double> numStk;
        Stack<char> opStk;

        for (size_t i = 0; i < expr.size(); ++i) {
            char c = expr[i];
            if (c == ' ') continue;

            if (std::isdigit(c) || c == '.') {
                std::string numStr;
                while (i < expr.size() && (std::isdigit(expr[i]) || expr[i] == '.'))
                    numStr += expr[i++];
                i--;
                numStk.push(std::stod(numStr));
            } else if (c == '(') {
                opStk.push(c);
            } else if (c == ')') {
                while (!opStk.empty() && opStk.top() != '(') {
                    char op = opStk.top(); opStk.pop();
                    double b = numStk.top(); numStk.pop();
                    double a = numStk.top(); numStk.pop();
                    numStk.push(calculate(a, b, op));
                }
                if (!opStk.empty() && opStk.top() == '(') opStk.pop();
            } else if (priority.count(c)) {
                while (!opStk.empty() && priority[opStk.top()] >= priority[c]) {
                    char op = opStk.top(); opStk.pop();
                    double b = numStk.top(); numStk.pop();
                    double a = numStk.top(); numStk.pop();
                    numStk.push(calculate(a, b, op));
                }
                opStk.push(c);
            } else {
                throw std::runtime_error("��Ч�ַ�: " + std::string(1, c));
            }
        }

        while (!opStk.empty()) {
            char op = opStk.top(); opStk.pop();
            double b = numStk.top(); numStk.pop();
            double a = numStk.top(); numStk.pop();
            numStk.push(calculate(a, b, op));
        }

        if (numStk.empty() || numStk.size() > 1)
            throw std::runtime_error("����ʽ��Ч");
        return numStk.top();
    }

    // ѡ����֧�����Ǻ���������
    double calculateAdvanced(const std::string& expr) {
        std::string mod = expr;
        size_t pos = mod.find("sin(");
        while (pos != std::string::npos) {
            size_t end = mod.find(")", pos + 4);
            if (end == std::string::npos) throw std::runtime_error("���Ų�ƥ��");
            double num = std::stod(mod.substr(pos + 4, end - pos - 4));
            mod.replace(pos, end - pos + 1, std::to_string(std::sin(num)));
            pos = mod.find("sin(", pos);
        }

        pos = mod.find("cos(");
        while (pos != std::string::npos) {
            size_t end = mod.find(")", pos + 4);
            if (end == std::string::npos) throw std::runtime_error("���Ų�ƥ��");
            double num = std::stod(mod.substr(pos + 4, end - pos - 4));
            mod.replace(pos, end - pos + 1, std::to_string(std::cos(num)));
            pos = mod.find("cos(", pos);
        }

        pos = mod.find("log(");
        while (pos != std::string::npos) {
            size_t end = mod.find(")", pos + 4);
            if (end == std::string::npos) throw std::runtime_error("���Ų�ƥ��");
            double num = std::stod(mod.substr(pos + 4, end - pos - 4));
            if (num <= 0) throw std::runtime_error("����������Ч");
            mod.replace(pos, end - pos + 1, std::to_string(std::log(num)));
            pos = mod.find("log(", pos);
        }

        return calculateExpression(mod);
    }
};

int main() {
    Calculator calc;
    try {
        std::cout << "3+4*2 = " << calc.calculateExpression("3+4*2") << "\n";
        std::cout << "3*(4+2)-10/2 = " << calc.calculateExpression("3*(4+2)-10/2") << "\n";
        std::cout << "sin(0.5)+cos(0.5)*2 = " << calc.calculateAdvanced("sin(0.5)+cos(0.5)*2") << "\n";
    } catch (const std::exception& e) {
        std::cout << "����: " << e.what() << "\n";
    }
    return 0;
}
