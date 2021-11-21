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
Примечание: сериализация подразумевает сохранение и восстановление полной структуры списка, включая взаимное соотношение его элементов между собой.

3) Реализуйте функцию расчета усредненных нормалей для вершин меша, заданного индексированными треугольниками. 
```cpp
//
// Calculate smooth (average) per-vertex normals
//
// [out] normals - output per-vertex normals
// [in] verts - input per-vertex positions
// [in] faces - triangles (triplets of vertex indices)
// [in] nverts - total number of vertices (# of elements in verts and normals arrays)
// [in] nfaces - total number of faces (# of elements in faces array)
//
void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces);
```
