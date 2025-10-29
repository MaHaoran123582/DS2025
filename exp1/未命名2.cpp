#include <iostream>
#include <string>
using namespace std;

class Student {
protected:
    string id;
    string name;
    int age;
public:
    Student(string sid, string sname, int sage) : id(sid), name(sname), age(sage) {}
    friend Student& operator++(Student& s);
    friend Student& operator--(Student& s);
    virtual void showInfo() const {
        cout << "ID: " << id << ", Name: " << name << ", Age: " << age << endl;
    }
};

Student& operator++(Student& s) {
    ++s.age;
    return s;
}

Student& operator--(Student& s) {
    --s.age;
    return s;
}

class Postgraduate : public Student {
private:
    string researchArea;
public:
    Postgraduate(string sid, string sname, int sage, string area) 
        : Student(sid, sname, sage), researchArea(area) {}
    
    void showInfo() const override {
        cout << "ID: " << id << ", Name: " << name 
             << ", Age: " << age << ", Research Area: " << researchArea << endl;
    }
};

template <typename T>
void show(const T& s) {
    s.showInfo();
}

int main() {
    Student s1("001", "Zhang San", 20);
    cout << "Before increment:" << endl;
    s1.showInfo();
    
    ++s1;
    cout << "After increment:" << endl;
    s1.showInfo();
    
    --s1;
    cout << "After decrement:" << endl;
    s1.showInfo();
    
    Student* ptr1 = new Student("003", "Wang Wu", 25);
    Student* ptr2 = new Postgraduate("004", "Zhao Liu", 26, "Image Processing");
    
    cout << "\nUsing dynamic polymorphism:" << endl;
    ptr1->showInfo();
    ptr2->showInfo();
    
    delete ptr1;
    delete ptr2;
    
    cout << "\nTesting template function:" << endl;
    Student s2("005", "Qian Qi", 22);
    Postgraduate pg("006", "Sun Ba", 24, "Machine Learning");
    
    show(s2);
    show(pg);
    
    return 0;
}    
