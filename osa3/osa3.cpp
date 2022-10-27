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
    void add_mark(int mark) { // добавляет оценку в конец
        marks.push_back(mark);
    }

    vector<int> get_mark() { // возвращает вектор оценок
        return marks;
    }

    float get_average() { // возвращает среднее значение
        float sum = 0;
        for (int i = 0; i < marks.size(); i++) {
            sum += marks[i];
        }
        return sum / marks.size();
    }

    int get_value_of_marks() { // возвращает количество оценок
        return marks.size();
    }
};

class character {
private:
    string name;
    Marks marks;
public:
    character(string name, Marks marks) {  // конструктор
        this->name = name; this->marks = marks; 
    }
    character() { name = ""; } // конструктор по умолчанию (создаётся пустое имя для проверки в ... где то )

    character get_person() { // возвращает себя
        return *this;
    }

    string get_name() { // возврашает имя
        return name;
    }

    Marks get_mark() { //возвращает оценки (объект типа mark!!!)
        return marks;
    }
};

struct pers4list { // структура, с которой работает список
    character p; // все данные
    pers4list * next; // указатель на следующий элемент
};

class List {
private:
    pers4list* first; // переименуй на хедер
public:
    List() {
        first = nullptr; // надо будет для проверки и в принципе с этим работать круто он классный, ахуенный обалденный
    }

    void add_back(character p) {
        pers4list* p4l = new pers4list; // p4l переименуй, создали элемент
        p4l->p = p; // записали данные
        p4l->next = nullptr; // уверенно сделали следующий элемент нулптром
        if (first == nullptr) { // проверели первый ли это элемент в списке
            first = p4l; 
        }
    }

    void add_front(character p) {
        pers4list* p4l = new pers4list; // уверенно создали 
        p4l->p = p; // записали данные
        p4l->next = first; // следующий элемент для нашего нового элемента - это первый элемент
        first = p4l; // теперь новый элемент - первый элемент
    }

    bool addAfter(character p, int index) { //добавляет по после найденного
        pers4list* current = first;
        for (; index > 0 && current != nullptr; index--) { // бежим по списку 
            current = current->next;
        }
        if (current == nullptr) { return false; } // проверяем куда пришли
        pers4list* p4lNew = new pers4list;
        p4lNew->p = p; // записываем данные в новый элемент
        p4lNew->next = current->next; // указатель на следующий у нового равен указателю старого 
        current->next = p4lNew; // указатель старого указывает теперь на новый элемент
        return true;
    }

    bool remove_back() { // удаляем с конца
        pers4list* p4l; // создали новый УКАЗАТЕЛЬ!!!
        p4l = first; // p4l находится в нулевой точке (указывает на первый элемент)
        while (p4l->next != nullptr) { // бежим по списку
            p4l = p4l->next;
        }
        if (p4l != nullptr) { // в случае, если список не пустой
            p4l->next = nullptr; // удаляем последний элемент
        }
        else {
            first = nullptr; 
        }
        return true;
    }

    bool remove_front() { 
        pers4list* p4l;
        if (first == nullptr) { // проверка на пустой список
            return false;
        }
        p4l = first->next;
        delete(first);
        first = p4l;
        return true;
    }

    vector<int> searchByName(string name) { // поиск элемента
        vector<int> v;
        pers4list* current = first; // создаём указатель на первый элемент
        for (int i = 0; current != nullptr; i++) {
            if (current->p.get_name() == name) { // ищет имя с совпадением, записывает номер элемента в вектор
                v.push_back(i);
            }
            current = current->next; // сдвигаем каррент
        }
        return v; // возвращаем вектор с номерами элементов
    }

    character getItem(int index) { // нахождение элемента по индексу
        pers4list* current = first;
        for (; index > 0; index--) { // бежим по списку до нашего индекса
            current = current->next;
        }
        if (current == nullptr) { //проверяем не пустой ли элемент мы нашли
            character p; // если да, то возвращается p c именем ""
            return p;
        }
        return current->p; // возвращаем данные каррента, то есть объект типа character
    }
};

character persCreator() { // создаёт новую персону
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
            character p(name, marks); //создаём объект с помощью коструктора
            //pers4list p4l;
            //p4l.p = p;
            return (p);
        }
        marks.add_mark(mark); // добавление оценки в вектор
    }
}

void printV(vector<int> v) { // выводит интовый вектор оценок
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl << endl;
}      

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int temp;
    List data;
    while (1) {
        cout << "Введите номер работы: ";
        cin >> temp;
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
