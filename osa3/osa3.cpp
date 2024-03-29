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
    void add_mark(int mark) {
        marks.push_back(mark);
    }

    vector<int> get_mark() {
        return marks;
    }

    float get_average() {
        float sum = 0;
        for (int i = 0; i < marks.size(); i++) {
            sum += marks[i];
        }
        return sum / marks.size();
    }

    int get_value_of_marks() {
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
    Person() { name = ""; }

    Person get_person() {
        return *this;
    }

    string get_name() {
        return name;
    }

    Marks get_mark() {
        return marks;
    }
};

struct pers4list {
    Person p;
    pers4list *prev, *next;
};

class List {
private:
    pers4list* first, * last;
public:
    List() {
        first = nullptr;
        last = nullptr;
    }

    void add_back(Person p) {
        pers4list* p4l = new pers4list;
        p4l->p = p;
        p4l->prev = last;
        p4l->next = nullptr;
        if (last != nullptr) {
            last->next = p4l;
        }
        last = p4l;
        if (first == nullptr) {
            first = p4l;
        }
    }

    void add_front(Person p) {
        pers4list* p4l = new pers4list;
        p4l->p = p;
        p4l->prev = nullptr;
        p4l->next = first;
        if (first != nullptr) {
            first->prev = p4l;
        }
        first = p4l;
        if (last == nullptr) {
            last = p4l;
        }
    }

    bool addAfter(Person p, int index) {
        pers4list* current = first;
        for (; index > 0 && current != nullptr; index--) {
            current = current->next;
        }
        if (current == nullptr) { return false; }
        pers4list* p4lNew = new pers4list;
        p4lNew->p = p;
        p4lNew->next = current->next;
        p4lNew->prev = current;
        current->next = p4lNew;
        return true;
    }

    bool remove_back() {
        pers4list* p4l;
        if (last == nullptr) {
            return false;
        }
        p4l = last->prev;
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

    bool remove_front() {
        pers4list* p4l;
        if (first == nullptr) {
            return false;
        }
        p4l = first->next;
        if (p4l != nullptr) {
            p4l->prev = nullptr;
        }
        else {
            last = nullptr;
        }
        delete(first);
        first = p4l;
        return true;
    }

    vector<int> searchByName(string name) {
        vector<int> v;
        pers4list* current = first;
        for (int i = 0; current != nullptr; i++) {
            if (current->p.get_name() == name) {
                v.push_back(i);
            }
            current = current->next;
        }
        return v;
    }

    Person getItem(int index) {
        pers4list* current = first;
        for (; index > 0 ; index--) {
            current = current->next;
        }
        if (current == nullptr) {
            Person p;
            return p;
        }
        return current->p;
    }
};

Person persCreator() {
    Marks marks;
    int mark;
    while (1) {
        string name;
        cout << "Введите оценку (0 для прекращения ввода оценок): ";
        cin >> mark;
        if (mark == 0) {
            cout << "Введите имя: ";
            cin >> name;
            cout << endl;
            Person p(name, marks);
            pers4list p4l;
            p4l.p = p;
            return (p);
        }
        marks.add_mark(mark);
    }
}

void printV(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl << endl;
}

int main(int count, char** params)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int counter;
    List data;
    for (counter = 1; counter < count; counter++) {
        if (string(params[counter]) == "add") {
            counter += 1;
            if (string(params[counter]) == "back") {
                data.add_back(persCreator());
            }
            else if (string(params[counter]) == "front") {
                data.add_front(persCreator());
            }
            else {
                cout << "Неверный выбор места добавления элемента.";
            }
        }
        else if (string(params[counter]) == "remove") {
            counter += 1;
            if (string(params[counter]) == "back") {
                data.remove_back();
            }
            else if (string(params[counter]) == "front") {
                data.remove_front();
            }
            else {
                cout << "Неверный выбор удаления добавления элемента.";
            }
        }
        else if (string(params[counter]) == "show") {
            Person p;
            for (int i = 0; data.getItem(i).get_name() != ""; i++) {
                cout << data.getItem(i).get_name() << ", Ср. Оценка: "
                    << data.getItem(i).get_mark().get_average() << endl;
                printV(data.getItem(i).get_mark().get_mark());
            }
        }
        else if (string(params[counter]) == "search") {
            counter += 1;
            char yn;
            vector<int> v;
            v = data.searchByName(string(params[counter]));
            Person p;
            for (vector<int>::iterator iterator = v.begin(); iterator != v.end(); iterator++) {
                p = data.getItem(*iterator);
                cout << p.get_name() << ", Ср. Оценка: " << p.get_mark().get_average() << endl;
                cout << "Вставить новый элемент? (y/n)";
                cin >> yn;
                if (yn == 'y') {
                    data.addAfter(persCreator(), *iterator);
                }
            }
        }
    }
    return 0;
}
