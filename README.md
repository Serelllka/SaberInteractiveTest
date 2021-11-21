# SaberInteractiveTest
Задачи:
1) Напишите функцию, которая принимает на вход знаковое целое число и печатает его двоичное представление, не используя библиотечных классов и функций.
2) Реализуйте функции сериализации и десериализации двусвязного списка в бинарном формате в файл.
```cpp
struct ListNode {
     ListNode *      prev;
     ListNode *      next;
     ListNode *      rand; // указатель на произвольный элемент данного списка либо NULL
     std::string     data;
};

class List {
public:
     void Serialize   (FILE * file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
     void Deserialize (FILE * file);  // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

private:
     ListNode *      head;
     ListNode *      tail;
     int       count;
};

```
