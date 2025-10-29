#include <iostream>
using namespace std;


class A {
protected:
    int i;
public:
   
    A(int val) : i(val) {}

    void display() {
        cout << "i: " << i << endl;
    }
};

class A1 : virtual public A {
protected:
    int j;
public:
    A1(int val1, int val2) : A(val1), j(val2) {}
};

class A2 : virtual public A {
protected:
    int k;
public:
    A2(int val1, int val3) : A(val1), k(val3) {}
};

class A3 : public A1, public A2 {
public:
    A3(int val1, int val2, int val3) : A(val1), A1(val1, val2), A2(val1, val3) {}
    void disp() {
        display();
        cout << "j: " << j << endl;
        cout << "k: " << k << endl;
    }
};

int main() {
    int A, B, C;
    cout << "请输入 3 个整数: ";
    cin >> A >> B >> C;
    A3 obj(A, B, C) ; 
    obj.disp();
    return 0;
}    
