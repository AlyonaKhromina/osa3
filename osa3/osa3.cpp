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

class character {
private:
    string name;
    Marks marks;
public:
    character(string name, Marks marks) {
        this->name = name; this->marks = marks;
    }
    character() { name = ""; }

    character get_person() {
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
    character p;
    pers4list * next;
};

class List {
private:
    pers4list* first;
public:
    List() {
        first = nullptr;
    }

    void add_back(character p) {
        pers4list* p4l = new pers4list;
        p4l->p = p;
        p4l->next = nullptr;
        if (first == nullptr) {
            first = p4l;
        }
    }

    void add_front(character p) {
        pers4list* p4l = new pers4list;
        p4l->p = p;
        p4l->next = first;
        first = p4l;
    }

    bool addAfter(character p, int index) {
        pers4list* current = first;
        for (; index > 0 && current != nullptr; index--) {
            current = current->next;
        }
        if (current == nullptr) { return false; }
        pers4list* p4lNew = new pers4list;
        p4lNew->p = p;
        p4lNew->next = current->next;
        current->next = p4lNew;
        return true;
    }

    bool remove_back() {
        pers4list* p4l;
        p4l = first;
        while (p4l->next != nullptr) {
            p4l = p4l->next;
        }
        if (p4l != nullptr) {
            p4l->next = nullptr;
        }
        else {
            first = nullptr;
        }
        return true;
    }

    bool remove_front() {
        pers4list* p4l;
        if (first == nullptr) {
            return false;
        }
        p4l = first->next;
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

    character getItem(int index) {
        pers4list* current = first;
        for (; index > 0; index--) {
            current = current->next;
        }
        if (current == nullptr) {
            character p;
            return p;
        }
        return current->p;
    }
};

character persCreator() {
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
            character p(name, marks);
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

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int counter, temp;
    List data;
    while (1) {
        switch (temp) {
        case 1:
            data.add_back(persCreator());
            break;
        case 2:
            data.add_front(persCreator());
            break;
        case 3:
            data.remove_back();
            break;
        case 4:
            data.remove_back();
            break;
        case 5:
            data.remove_front();
            break;
        case 6:
        {
            character p;
            for (int i = 0; data.getItem(i).get_name() != ""; i++) {
                cout << data.getItem(i).get_name() << ", Ср. Оценка: "
                    << data.getItem(i).get_mark().get_average() << endl;
                printV(data.getItem(i).get_person().get_mark().get_mark());
            }
        }
        break;
        case 7:
        {
            counter += 1;
            char yes_or_not;
            vector<int> v;
            cout << "Введите имя: ";
            string name;
            cin >> name;
            v = data.searchByName(name);
            character p;
            for (vector<int>::iterator iterator = v.begin(); iterator != v.end(); iterator++) {
                p = data.getItem(*iterator);
                cout << p.get_name() << ", Ср. Оценка: " << p.get_mark().get_average() << endl;
                cout << "Вставить новый элемент? (y/n)";
                cin >> yes_or_not;
                if (yes_or_not == 'y') {
                    data.addAfter(persCreator(), *iterator);
                }
            }
        }
        break;
        case 8:
            return 0;
        }
    }
}
