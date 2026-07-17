#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

template<typename T>
class LinkedList {
private:
    struct Node {
        T     data;
        Node* next;

        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList()
    {
        Node* current = head;
        while (current)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    LinkedList(const LinkedList& other) = delete;
    LinkedList& operator=(const LinkedList& other) = delete;

    void addToEnd(const T& value)
    {
        Node* node = new Node(value);
        if (!head)
        {
            head = node;
        }
        else
        {
            tail->next = node;
        }
        tail = node;
    }

    // Removes the first element equal to value. Returns false if not found.
    bool remove(const T& value)
    {
        Node* previous = nullptr;
        for (Node* current = head; current; previous = current, current = current->next)
        {
            if (current->data == value)
            {
                if (previous)
                {
                    previous->next = current->next;
                }
                else
                {
                    head = current->next;
                }
                if (current == tail)
                {
                    tail = previous;
                }
                delete current;
                return true;
            }
        }
        return false;
    }

    bool isEmpty() const
    {
        return head == nullptr;
    }

    void print() const
    {
        for (const Node* current = head; current; current = current->next)
        {
            std::cout << current->data;
            if (current->next)
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

    class ConstIterator {
    private:
        const Node* current;

    public:
        explicit ConstIterator(const Node* node) : current(node) {}

        const T& operator*() const { return current->data; }

        ConstIterator& operator++()
        {
            current = current->next;
            return *this;
        }

        bool operator!=(const ConstIterator& other) const
        {
            return current != other.current;
        }
    };

    ConstIterator begin() const { return ConstIterator(head); }
    ConstIterator end()   const { return ConstIterator(nullptr); }
};

#endif // LINKED_LIST_H
