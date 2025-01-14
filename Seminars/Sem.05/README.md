# Разделна компилация. Абстракция. Копиращ конструктор и оператор за присвоявяне (=)

## Разделна компилация.

![.](https://camo.githubusercontent.com/28dc183568fa5f05a944d8ec4f3033c8ee08e4c87b6c19ae051dc55ea7979f69/68747470733a2f2f692e6962622e636f2f664436584c4a4d2f436f6d70696c6174696f6e2e706e67)

Една програма на С++ може да бъде разбита в множество изходни файлове(.cpp), които се **компилират независимо един от друг**, т.е. осъществява се **разделна компилация**. <br />
Преди самата компилация изходният файл бива подаден на препроцесора, който изпълнява всички директиви (започващи с #). <br />
Пример: при всяко срещане на #include препроцесорът го заменя със съответстващото му парче код (хедър файл, съдържащ декларации). <br />
В резултат на компилацията се получават няколко **обектни файла** (файлове с разширение **.obj**), те представляват машинен код. <br />
Изпълнимият код на програмата (файл с разширение .ехе) се получава след свързване на обектните файлове от linker-a (**Linking**). <br />
Той асоциира всички референции към имена (на променливи, функции, класове и т.н.) на един обектов файл към съответните им дефиниции, които могат да се намират и в други изходни файлове. <br />
Понякога се случва дефинициите да не се намират в никой от обектните файлове, като в този случай компилаторът претърсва стандартната C++ библиотека (libcp.lib), стандартната C библиотека (libc.lib), а също и всяка ръчно указана такава от програмиста. Ако такава дефиниция не бъде открита линкерът дава грешка. <br />
За да се възползваме максимално от разделната компилация, разделяме класовете на **.h** и **.cpp** файлове. <br />
Навсякъде където ще работим с класа, ще включваме **само .h файла.** По този начин, ако променим реализацията на някоя от функциите на класа, ще се **прекомпилира само този файл**. <br />

![enter image description here](https://i.ibb.co/N9RnMHv/sss.png)
## Абстракция

- Пример за **лоша абстракция**:
```c++
struct Triangle {
	int x1;
	int y1;
	
	int x2;
	int y2;

	int x3;
	int y3;
};

int getPer(const Triangle& t) {
	return
	    sqrt( (t.x1-t.x2)*(t.x1-t.x2) + (t.y1-t.y2)*(t.y1-t.y2) + 
	    sqrt( (t.x2-t.x3)*(t.x2-t.x3) + (t.y2-t.y3)*(t.y2-t.y3) + 
	    sqrt( (t.x3-t.x1)*(t.x3-t.x1) + (t.y3-t.y1)*(t.y3-t.y1); 
}
```
 
- Пример за **по-добра абстракция**:
 ```c++
struct Point {
	int x, y;
	double getDistTo(const Point& other) const {
		return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
	}
};

struct Triangle {
	Point p1;
	Point p2;
	Point p3;
};

int getPer(const Triangle& t) {
	return t.p1.getDistTo(t.p2) + t.p2.getDistTo(t.p3) + t.p3.getDistTo(t.p1);
}
 ```

## Копиращ конструктор и оператор =
Заедно с конструктора по подразбиране и деструктора във всеки клас се дефинират и следните член-функции:
 - Копиращ конструктор - конструктор, който приема обект от същия клас и създава новият обект като негово копие.
 - Оператор= - функция/оператор, който приема  обект от същия клас и променя данните на съществуващ обект от същия клас (обектът от който извикваме функцията).

**При липсата на дефиниран/и копиращ конструктор и/или оператор=, компилаторът автоматично създава такива по подразбиране.**
**Забележка:** Копиращият конструктор създава нов обект, а оператор= модифицира вече съществуващ такъв!

 **Относно следващия пример:** <br />
 В рамките на курса ще възприемаме, че няма да се извикват нито излишни copy constructor-и(защото връщаме по копие), нито destructor-и(в scope на функцията обектът умира, но преди това би трябвало да се копира, за да се върне по копие) в scope-a на функцията, защото се случва [RVO - return value optimization](https://en.cppreference.com/w/cpp/language/copy_elision), което ни спестява излишни копирания, тоест единствено ще се извикат constructor и destructor на съответние места индикирани с коментари.
```c++
#include <iostream>

struct Test {
    Test() {
        std::cout << "Default constructor\n";
    }

    Test(const Test& other) {
        std::cout << "Copy constructor\n";
    }

    Test& operator=(const Test& other) {
        std::cout << "operator=\n";
	    return *this;
    }

    ~Test() {
        std::cout << "Destructor\n";
    }
};

void f(Test object) {
    //do Stuff
}

void g(Test& object) {
    //do Stuff
}

int main()
{
    Test t;      //Default constructor;

    Test t2(t);  // Copy constructor
    Test t3(t2); // Copy constructor	
    t2 = t3;     // operator=
    t3 = t;      // operator=

    Test newTest = t; //Copy constructor !!!!!!!

    f(t);   // Copy constructor	
    g(t);   // nothing. We are passing it as a reference. We are not copying it!

    Test* ptr = new Test();  // Default constructor // we create a new object in the dynamic memory. The destructor must be invoked explicitly  (with delete)

    delete ptr; // Destructor	

} //Destructor Destructor Destructor Destructor
```

## **Задачи**

**Задача 1:**
Напишете клас, който е за работа със събитие. Събитието се характеризира с име (низ до 20 символа), дата, начален час и краен час.

**Задача 2:**
Напишете клас за работа с колекция от събития (най-много 20). Трябва да имате:
 - Добавяне на събитие.
 - Намиране на най-дългото събитие.
 - Приемане на дата и връщане на максималния брой събития, които може да се посетят в този ден. (за да се посетят 2 събития, те трябва да не се пресичат).
 - Премахване на събитие по име.
