#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <list>

template <typename T> // Последовательный контейнер
class My_vector {
private:
    T* data;
    size_t capacity;
    size_t S;

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity]; // Выделяем новую память
        for (size_t i = 0; i < S; ++i) 
        {
            newData[i] = data[i]; // Копируем существующие элементы
        }

        delete[] data; // Освобождаем старую память
        data = newData;// Указываем на новую память
        capacity = newCapacity; // Обновляем текущий размер
    }

public:

    My_vector(size_t initialCapacity = 10) //Начальный размер контейнера
        : capacity(initialCapacity), S(0) 
        {
        data = new T[capacity]; // Выделяем память для массива data
        }

    ~My_vector() // Деструктор
    {
        delete[] data;
    }

    void push_back(const T& value) 
    {
        if (S >= capacity) 
        {
            resize(static_cast<size_t>(capacity * 1.5)); // Если не хватает памяти увеличиваем память
        }

        data[S++] = value; // Добавляем элемент увеличивая размер
    }

    void insert(size_t index, const T& value) 
    {
        if (index > S) throw std::out_of_range("Error in insert");

        if (S >= capacity) 
        {
            resize(static_cast<size_t>(capacity * 1.5));
        }

        for (size_t i = S; i > index; --i) 
        {
            data[i] = data[i - 1]; // Cдвигаем элементы вправо, начиная с конца массива до позиции вставки
        }

        data[index] = value;

        S++;
    }

    void erase(size_t index)
    {
        if (index >= S) throw std::out_of_range("Error in erase");

        for (size_t i = index; i < S - 1; ++i) 
        {
            data[i] = data[i + 1];
        }

        S--;
    }

    size_t size() const 
    {
        return S;
    }

    T& operator[](size_t index) 
    {
        if (index >= S) throw std::out_of_range("Error in []");

        return data[index]; // Возвращаем элемент по индексу
    }

    void print() const 
    {
        for (size_t i = 0; i < S; ++i) 
        {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

template <typename T> // Списоковый контейнер двусвязный
class Double_list {
private:
    struct Node 
    {
        T data; // Данные
        Node* next; // Указатель на следующий узел
        Node* prev; // Указатель на предыдущий узел
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {} // Инициализация узла
    };

    Node* head; // Голова
    Node* tail; // Хвост
    size_t S; // Количество узлов

public:

    Double_list() : head(nullptr), tail(nullptr), S(0) {}

    ~Double_list() // Деструктор
    {
        while (head) {
            Node* temp = head;
            head = head->next; // Переходит к следующему узлу и удаляет
            delete temp;
        }
    }

    void push_back(const T& value) 
    {
        Node* newNode = new Node(value); // Создание нового узла

        if (!head) // Если список пуст
        { 
            head = tail = newNode;
        } 
        else 
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode; // Новый узел == новый хвост
        }
        S++;
    }

    void insert(size_t index, const T& value) {

        if (index > S) std::cout << "ошибка";
        
        Node* newNode = new Node(value);
        
        if (index == 0) // Если индекс равен 0, вставляет новый узел в начало списка
        { 
            newNode->next = head;
            if (head) head->prev = newNode; // Если список не пустой
            head = newNode;
            if (!tail) tail = newNode; // Если список пустой
        } 

        else if (index == S) //Если индекс равен размеру списка, вызывает push_back
        { 
            push_back(value);
            return;
        } 

        else 
        {
            Node* current = head;
            for (size_t i = 0; i < index; ++i) // Находим узел по индексу
            {
                current = current->next;
            }

            newNode->prev = current->prev;
            newNode->next = current;

            if (current->prev) current->prev->next = newNode;
            
            current->prev = newNode;

            if (index == 0) head = newNode; // Если вставляем в начало
        }
        
        S++;
    }

    void erase(size_t index) {
        if (index >= S) throw std::out_of_range("ошибка");
        
        Node* current = head;
        for (size_t i = 0; i < index; ++i) 
        {
            current = current->next; // Находит узел по индексу
        }
        
        if (current->prev) current->prev->next = current->next; //Обновляет указатели next и prev у соседних узлов, чтобы исключить текущий узел из списка
        if (current->next) current->next->prev = current->prev;

        if (current == head) head = current->next; // Если удаляем голову
        if (current == tail) tail = current->prev; // Если удаляем хвост

        delete current;
        S--;
    }

    size_t size() const 
    {
        return S;
    }

    T& operator[](size_t index) 
    {
        if (index >= S) std::cout <<"Error in []";
        
        Node* current = head;

        for (size_t i = 0; i < index; ++i) 
        {
            current = current->next;
        }
        
        return current->data;
    }

    void print() const 
    {
        Node* current = head;
        while (current) 
        {
            std::cout << current->data << " ";
            current = current->next; //Проходит по всем узлам, начиная с head, и выводит их данные
        }
        std::cout << std::endl;
    }
};

template <typename T> // Списоковый контейнер односвязный
class Solo_list {
private:
    struct Node 
    {
        T data; // Данные
        Node* next; // Указатель на следующий узел

        Node(T value) : data(value), next(nullptr) {} 
    };

    Node* head; // Голова
    size_t S; // Размер списка

public:

    Solo_list() : head(nullptr), S(0) {}

    ~Solo_list() // Деструктор
    {
        while (head) 
        {
            erase(0); // Удаляем все узлы
        }
    }

    void push_back(T value) 
    {
        Node* newNode = new Node(value); 
        if (!head) 
        {
            head = newNode; // Если список пуст, новый узел становится головой
        } 
        else 
        {
            Node* current = head;
            while (current->next) 
            {
                current = current->next; // Находим последний узел
            }
            current->next = newNode; // Добавляем новый узел в конец списка
        }
        S++;
    }

    void insert(size_t index, T value) 
    {
        if (index > S) throw std::out_of_range("Error in insert");
        
        Node* newNode = new Node(value);

        if (index == 0) 
        {
            newNode->next = head; 
            head = newNode;
        } 
        else 
        {
            Node* current = head;
            for (size_t i = 0; i < index - 1; ++i) 
            {
                current = current->next; // Находим узел перед индексом
            }
            newNode->next = current->next; // Устанавливаем указатель нового узла
            current->next = newNode; // Вставляем новый узел
        }
        S++;
    }

    void erase(size_t index) 
    {
        if (index >= S) throw std::out_of_range("Error in erase");

        Node* toDelete = nullptr;
        if (index == 0) 
        {
            toDelete = head; // Удаление головы
            head = head->next; // Обновляем голову
        } 
        else 
        {
            Node* current = head;
            for (size_t i = 0; i < index - 1; ++i) 
            {
                current = current->next; // Находим узел перед удаляемым
            }
            toDelete = current->next; // Узел для удаления
            current->next = toDelete->next; // Обновляем указатель
        }
        delete toDelete;
        S--;
    }

    size_t size() const 
    {
        return S;
    }

    T& operator[](size_t index) 
    {
        if (index >= S) throw std::out_of_range("Error in []");

        Node* current = head;

        for (size_t i = 0; i < index; ++i) 
        {
            current = current->next; 
        }
        return current->data; // Возвращаем ссылку на данные узла
    }

    void print() const
    {
        Node* current = head;
        while (current) 
        {
            std::cout << current->data << " "; // Выводим данные узла
            current = current->next; // Переходим к следующему узлу
        }
        std::cout << std::endl;
    }
};

template <typename T> // Вектор итератор метод get()
class VectorIteratorGet {
private:
    typename std::vector<T>::iterator it;
public:
    // Конструктор принимает итератор std::vector<T>
    VectorIteratorGet(typename std::vector<T>::iterator iterator) : it(iterator) {}
    T& operator*() 
    {
        return *it;
    }
    // Метод для получения значения (возвращает ссылку на элемент)
    T& get() 
    {
        return *it;
    }
    VectorIteratorGet& operator++() 
    {
        ++it; // Инкремент
        return *this; 
    }
    bool operator!=(const VectorIteratorGet& other) const // Сравнение двух операторов
    {
        return it != other.it;
    } 
};

template <typename T> // Вектор итератор методы begin() и end()
class VectorIteratorBE {
private:
    std::vector<T> data;
public:
    VectorIteratorBE(const std::initializer_list<T>& elements) : data(elements) {}
    VectorIteratorBE<T> begin() 
    {
        return VectorIteratorBE<T>(data.begin());
    }
    VectorIteratorBE<T> end() 
    {
        return VectorIteratorBE<T>(data.end());
    }
};

template <typename T> // Лист итератор метод get()
class ListIteratorGet {
private:
    typename std::list<T>::iterator it;
public:
    ListIteratorGet(typename std::list<T>::iterator iterator) : it(iterator) {}

    T& operator*() 
    {
        return *it;
    }
    // Метод для получения значения
    T& get() 
    {
        return *it;
    }
    ListIteratorGet& operator++()
     {
        ++it;
        return *this;
    }
    ListIteratorGet& operator--() 
    {
        --it;
        return *this; //декремент
    }
    bool operator!=(const ListIteratorGet& other) const 
    {
        return it != other.it;
    }
};

template <typename T> // Лист итератор методы begin() и end()
class ListIteratorBE {
private:
    std::list<T> data;
public:
    ListIteratorBE(const std::initializer_list<T>& elements) : data(elements) {}
    ListIteratorBE<T> begin() 
    {
        return ListIteratorBE<T>(data.begin());
    }
    ListIteratorBE<T> end() 
    {
        return ListIteratorBE<T>(data.end());
    }
};