
#include <iostream>
using namespace std;

class Point {

    protected:
    bool isStart() const {
        cout << "Point is in start" << endl;
        return x == 0 && y == 0;
    }

private:
    int x;
    int y;

public:
    // Конструктор без параметров
    Point() : x(0), y(0) {
        cout << "Point(): created\n";
    }

    // Конструктор с параметрами
    Point(int x, int y) : x(x), y(y) {
        cout << "Point(int, int): created\n";
    }

    // Конструктор копирования
    Point(const Point& other)
        : x(other.x), y(other.y) {
        cout << "Point(copy): created\n";
    }

    // Деструктор
    ~Point() {
        cout << "~Point(): destroyed\n";
    }

    // Изменение координат
    void move(int dx, int dy) {
        x += dx;
        y += dy;

        cout << "Point::move()\n";
    }

    // Вывод координат
    void print() const {
        cout << "Point: (" << x << ", " << y << ")\n";
    }
};



class ColoredPoint : public Point {

private:
    string color;

public:
    // Конструктор без параметров
    ColoredPoint() : Point(), color("white") {
        cout << "ColoredPoint: default constructor" << endl;
    }

    // Конструктор с параметрами
    ColoredPoint(int x, int y, string color)
        : Point(x, y), color(color) {
        cout << "ColoredPoint: parameterized constructor" << endl;
    }

    // Конструктор копирования
    ColoredPoint(const ColoredPoint& other)
        : Point(other), color(other.color) {
        cout << "ColoredPoint: copy constructor" << endl;
    }

    void setColor(string newColor) {
        color = newColor;
        cout << "ColoredPoint: setColor()" << endl;
    }

    // Деструктор
    ~ColoredPoint() {
        cout << "ColoredPoint: destructor" << endl;
    }

    // Скрываем метод print() базового класса
    void print() const {
        cout << "ColoredPoint: print()" << endl;

        // Вызываем реализацию родителя
        Point::print();

        cout << "Color: " << color << endl;

        // Обращаемся к protected методу родителя
        cout << "Is start point: "
                << (isStart() ? "yes" : "no") << endl;
    }
};




class PointPair {

private:
    Point first;    // Объект хранится напрямую
    Point* second;  // Указатель на объект

public:
    // Конструктор без параметров
    PointPair() : first() {
        second = new Point();
        cout << "PointPair: default constructor" << endl;
    }

    // Конструктор с параметрами
    PointPair(int x1, int y1, int x2, int y2)
        : first(x1, y1) {
        second = new Point(x2, y2);
        cout << "PointPair: parameterized constructor" << endl;
    }

    // Конструктор копирования
    PointPair(const PointPair& other)
        : first(other.first) {
        second = new Point(*other.second);
        cout << "PointPair: copy constructor" << endl;
    }

    // Деструктор
    ~PointPair() {
        cout << "PointPair: destructor" << endl;
        delete second;
    }

    // Запрещаем присваивание, пока не реализовали его
    PointPair& operator=(const PointPair&) = delete;

    // Вывод двух точек
    void print() const {
        cout << "First point: ";
        first.print();

        cout << "Second point: ";
        second->print();
    }

    // Изменение второй точки
    void moveSecond(int dx, int dy) {
        second->move(dx, dy);
    }
};



int main() {
    cout << "Static objects \n";

    Point p1;
    Point p2(10, 20);
    Point p3(p2);

    p1.print();
    p2.print();
    p3.print();

    p2.move(5, 5);
    p2.print();

    cout << "\nDynamic objects\n";

    Point* p4 = new Point(30, 40);
    p4->print();

    delete p4;

    ColoredPoint c1;
    ColoredPoint c2(10, 20, "red");
    ColoredPoint c3(c2);

    // Проверяем методы
    c2.print();

    // Вызываем унаследованный метод
    c3.move(5, 5);
    c3.print();

    // Указатель на базовый класс
    Point* ptr = &c2;
    ptr->print();

    cout << "\n--- Default constructor ---\n";
    PointPair pair1;

    cout << "\n--- Parameterized constructor ---\n";
    PointPair pair2(10, 20, 30, 40);
    pair2.print();

    cout << "\n--- Copy constructor ---\n";
    PointPair pair3(pair2);

    cout << "\n--- Changing original ---\n";
    pair2.moveSecond(5, 5);

    cout << "\nOriginal:\n";
    pair2.print();

    cout << "\nCopy:\n";
    pair3.print();

    cout << "\n--- End of composition scope ---\n";

    cout << "\n=== Object copying ===" << endl;

    {
        Point a(10, 20);

        // Создаём новый объект через конструктор копирования
        Point b = a;

        cout << "\nBefore changing:\n";
        a.print();
        b.print();

        // Изменяем только первый объект
        a.move(5, 5);

        cout << "\nAfter changing a:\n";
        a.print();
        b.print();

        // Присваиваем значения одного объекта другому
        b = a;

        cout << "\nAfter assignment b = a:\n";
        a.print();
        b.print();

        // Проверяем независимость после присваивания
        b.move(10, 10);

        cout << "\nAfter changing b:\n";
        a.print();
        b.print();
    }

    
    cout << "\n=== Pointer copying ===" << endl;

    {
        // Создаём динамический объект
        Point* a = new Point(10, 20);

        // Копируем адрес, а не сам объект
        Point* b = a;

        cout << "\nBefore changing:\n";
        a->print();
        b->print();

        // Изменяем объект через первый указатель
        a->move(5, 5);

        cout << "\nAfter changing through a:\n";
        a->print();
        b->print();

        // Изменяем объект через второй указатель
        b->move(10, 10);

        cout << "\nAfter changing through b:\n";
        a->print();
        b->print();

        // Оба указателя указывают на один объект
        cout << "\nAddresses:\n";
        cout << "a = " << a << endl;
        cout << "b = " << b << endl;

        // Удаляем объект только один раз
        delete a;

        a = nullptr;
        b = nullptr;
    }

    {
        Point p1(10, 20);
        ColoredPoint p2(30, 40, "red");

        // Указатель на обычный Point
        Point* ptr1 = &p1;

        // Указатель на Point хранит адрес ColoredPoint
        Point* ptr2 = &p2;

        cout << "\n=== Calling methods ===\n";

        ptr1->print();
        ptr2->print();

        // Вызов метода через сам объект-наследник
        p2.print();

        // Метод, который есть только у ColoredPoint
        p2.setColor("blue");
        p2.print();

        // Ошибка компиляции, если раскомментировать:
        // ptr2->setColor("green");
    }

    
    cout << "\n=== Object slicing ===" << endl;

    {
        ColoredPoint original(10, 20, "red");

        // Копируем наследника в объект базового класса
        Point copy = original;

        cout << "\nOriginal:\n";
        original.print();

        cout << "\nCopy:\n";
        copy.print();

        // Изменяем координаты исходного объекта
        original.move(5, 5);

        cout << "\nAfter changing original:\n";
        original.print();
        copy.print();
    }

    
    cout << "\n=== Dynamic inheritance ===" << endl;

    {
        // Создаём базовый объект
        Point* base = new Point(10, 20);

        // Создаём объект наследника
        ColoredPoint* derived =
            new ColoredPoint(30, 40, "green");

        // Указатель на базовый класс
        Point* basePtr = derived;

        cout << "\n=== Methods ===\n";

        base->print();
        basePtr->print();
        derived->print();

        cout << "\n=== Deleting objects ===\n";

        delete base;
        delete derived;
    }


    return 0;
}
