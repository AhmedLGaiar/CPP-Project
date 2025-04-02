#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <cstring> // For memcpy
#include <functional> // For comparison functions
#include <vector> // For sorting
#include <algorithm> // For sorting

template <typename T>
class LinkedList
{
private:
    class Node
    {
    public:
        Node* Next;
        Node* Prev;
        T* data;

        Node() : Next(nullptr), Prev(nullptr), data(nullptr) {}

        Node(T* _data) : Next(nullptr), Prev(nullptr), data(nullptr)
        {
            if (_data != nullptr)
            {
                data = new T(*_data);
            }
        }

        Node(T& _data) : Next(nullptr), Prev(nullptr), data(nullptr)
        {
            data = new T(_data);
        }

        ~Node()
        {
            if (data != nullptr)
            {
                delete data;
                data = nullptr;
            }
        }
    };

    Node* Head;
    Node* Tail;
    int Count;

public:
    LinkedList() : Head(nullptr), Tail(nullptr), Count(0) {}

    ~LinkedList()
    {
        Node* current = Head;
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->Next;
            delete temp;
        }
        Head = nullptr;
        Tail = nullptr;
        Count = 0;
    }

    void Add(T data)
    {
        Node* newNode = new Node(data);

        if (Head == nullptr)
        {
            Head = newNode;
            Tail = newNode;
        }
        else
        {
            newNode->Prev = Tail;
            Tail->Next = newNode;
            Tail = newNode;
        }
        Count++;
    }

    Node* Search(const T& data) const
    {
        Node* current = Head;
        while (current != nullptr)
        {
            if (*(current->data) == data)
            {
                return current;
            }
            current = current->Next;
        }
        return nullptr;
    }

    // Search with custom comparator
    Node* SearchBy(std::function<bool(const T&)> comparator)
    {
        Node* current = Head;
        while (current != nullptr)
        {
            if (comparator(*(current->data)))
            {
                return current;
            }
            current = current->Next;
        }
        return nullptr;
    }

    void SortBy(std::function<bool(const T&, const T&)> comparator) {
        if (Count <= 1) return;

        // Copy elements to vector
        std::vector<T> elements;
        Node* current = Head;
        while (current != nullptr) {
            elements.push_back(*(current->data));
            current = current->Next;
        }

        // Sort the vector
        std::sort(elements.begin(), elements.end(), comparator);

        // Copy back to linked list
        current = Head;
        for (const T& item : elements) {
            *(current->data) = item;
            current = current->Next;
        }
    }

    bool Delete(const T& data)
    {
        Node* nodeToDelete = Search(data);
        if (nodeToDelete == nullptr)
        {
            return false;
        }

        if (nodeToDelete == Head)
        {
            Head = nodeToDelete->Next;
            if (Head != nullptr)
            {
                Head->Prev = nullptr;
            }
            else
            {
                Tail = nullptr;
            }
        }
        else if (nodeToDelete == Tail)
        {
            Tail = nodeToDelete->Prev;
            if (Tail != nullptr)
            {
                Tail->Next = nullptr;
            }
            else
            {
                Head = nullptr;
            }
        }
        else
        {
            nodeToDelete->Prev->Next = nodeToDelete->Next;
            nodeToDelete->Next->Prev = nodeToDelete->Prev;
        }

        delete nodeToDelete;
        Count--;
        return true;
    }

    void Display() const
    {
        Node* current = Head;
        while (current != nullptr)
        {
            std::cout << *(current->data) << std::endl;
            current = current->Next;
        }
    }

    int Size() const
    {
        return Count;
    }

    class Iterator
    {
    private:
        Node* pNode;

    public:
        Iterator(Node* _pNode) : pNode(_pNode) {}

        T& operator*() const
        {
            return *(pNode->data);
        }

        Iterator& operator++()  // prefix increment
        {
            pNode = pNode->Next;
            return *this;
        }

        Iterator operator++(int)  // postfix increment
        {
            Iterator temp = *this;
            pNode = pNode->Next;
            return temp;
        }

        bool operator==(const Iterator& other) const
        {
            return pNode == other.pNode;
        }

        bool operator!=(const Iterator& other) const
        {
            return pNode != other.pNode;
        }

        T* operator->() const
        {
            return pNode->data;
        }
    };

    Iterator begin() const
    {
        return Iterator(Head);
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }
};

#endif // LINKEDLIST_H