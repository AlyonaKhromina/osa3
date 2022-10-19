#include<vector>
#include<iostream>
#include<list>
#include<iterator>
#include<string>
#include<iterator>
#include<Windows.h>

using namespace std;

class Marks {
private:
    vector<int> marks;

public:
    void addMark(int mark) {
        marks.push_back(mark);
    }

    vector<int> getMarks() {
        return marks;
    }
    
    float getAvg() {
        float sum = 0;
        for (int i = 0; i < marks.size(); i++) {
            sum += marks[i];
        }
        return sum / marks.size();
    }

    int getValue() {
        return marks.size();
    }
};

class Person {
private:
    string name;
    Marks marks;
public:
    Person(string name, Marks marks) {
        this->name = name; this->marks = marks;
    }
    Person() {}

    Person getP() {
        return *this;
    }

    string getName() {
        return name;
    }

    Marks getMarks() {
        return marks;
    }
};

struct pers4list { 
    Person p; 
    pers4list* before; 
    pers4list* next; 

    pers4list* searchByName(string name) {
        pers4list* current = this;
        for (; current != nullptr; current = current->next) {
            if (current->p.getName() == name) {
                return current;
            }
        }
        return nullptr;
    }
};

class List {
private:
    pers4list *first, *last;
public:
    List() {
        first = nullptr;
        last = nullptr;
    }

    void addBack(Person p) {
        pers4list* p4l = new pers4list;
        p4l->p = p;
        p4l->before = last;
        p4l->next = nullptr;
        if (last != nullptr) {
            last->next = p4l;
        }
        last = p4l;
        if (first == nullptr) {
            first = p4l;
        }
    }

    void addFront(Person p) {
        pers4list* p4l =  new pers4list;
        p4l->p = p;
        p4l->before = nullptr;
        p4l->next = first;
        if (first != nullptr) {
            first->before = p4l;
        }
        first = p4l;
        if (last == nullptr) {
            last = p4l;
        }
    }

    bool addAfter(Person p, pers4list* p4l) {
        if (p4l == nullptr) { return false; }
        pers4list* p4lNew = new pers4list;
        p4lNew->p = p;
        p4lNew->next = p4l->next;
        p4lNew->before = p4l;
        p4l->next = p4lNew;
    }

    bool delBack() {
        pers4list* p4l;
        if (last == nullptr) {
            return false;
        }
        p4l = last->before;
        if (p4l != nullptr) {
            p4l->next = nullptr;
        }
        else {
            first = nullptr;
        }
        delete(last);
        last = p4l;
        return true;
    }

    bool delFront() {
        pers4list* p4l;
        if (first == nullptr) {
            return false;
        }
        p4l = first->next;
        if (p4l != nullptr) {
            p4l->before = nullptr;                   
        }
        else {
            last = nullptr;
        }
        delete(first);
        first = p4l;
        return true;
    }

    pers4list* searchByName(string name) {
        pers4list* current = first;
        for (; current != nullptr; current = current->next) {
            if (current->p.getName() == name) {
                return current;
            }
        }
        return nullptr;
    }

    pers4list* getItem(int index) {
        pers4list* current = first;
        for (; index > 0 && current != nullptr; index--) {
            current = current->next;
        } 
        return current;
    }
};

Person persCreator() {
    Marks marks;
    int mark;
    while (1) {
        string name;
        cout << "Введите оценку: ";
        cin >> mark;
        if (mark == 0) {
            cout << "Введите имя: ";
            cin >> name;
            Person p(name, marks);
            pers4list p4l;
            p4l.p = p;
            return (p);
        }
        marks.addMark(mark);
    }
}

void printV(vector<Person> v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i].getName() << endl << v[i].getMarks().getAvg() << endl;
        for (int q = 0; q < v[i].getMarks().getMarks().size(); q++) {
            std::cout << v[i].getMarks().getMarks()[q] << " ";
        }
        std::cout << endl << endl;
    }
}

void printP(pers4list v) {
    std::cout << v.p.getName() << endl << v.p.getMarks().getAvg() << endl;
        for (int q = 0; q < v.p.getMarks().getMarks().size(); q++) {
            std::cout << v.p.getMarks().getMarks()[q] << " ";
        }
        std::cout << endl << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int worknum;
    List data;
    while (1) {
        cin >> worknum;
        switch (worknum) {
        case 1:
            data.addBack(persCreator());
            break;
        case 2:
            data.addFront(persCreator());
            break;
        case 3:
            data.delBack();
            break;
        case 4:
            data.delFront();
            break;
        case 5:
            for (pers4list* p4l = data.getItem(0); p4l != nullptr; p4l = p4l->next) {
                cout << p4l->p.getName() << ", Ср. Оценка: " << p4l->p.getMarks().getAvg() << endl;
            }
            break;
        case 6:
        {
            string name;
            char yn;
            cout << "Введите имя: ";
            cin >> name;
            pers4list* p4l = data.searchByName(name);
            while (p4l != nullptr) {
                cout << p4l->p.getName() << ", Ср. Оценка: " << p4l->p.getMarks().getAvg() << endl;
                cout << "Вставить новый элемент? (y/n)";
                cin >> yn;
                if (yn == 'y') {
                    data.addAfter(persCreator(), p4l);
                }
                p4l = p4l->next;
                if (p4l != nullptr) {
                    p4l = p4l->searchByName(name);
                }
            }
        }
        }
    }
}