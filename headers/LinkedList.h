#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdarg>

template <typename T> class LinkedList
{
    struct Node
    {
        Node()
        {
            next = nullptr;
        }
        Node(T value)
        {
            this->value = value;
            next = nullptr;
        }
        
        T value;
        Node* next;
    };
    public:
    LinkedList();
    ~LinkedList();
    void add(T val);
    // template <typename... Args>
    // void addAll(const std::initializer_list<T>& list);
    void removeAfter(Node* node);
    bool isEmpty();
    void clear();
    template <typename Function>
    void forEach(Function func);
    template <typename Function>
    void forEachAndRemoveIf(Function func);
    void sort(int(*compare)(T, T));

    private:
    Node* head;
    Node* tail;
};

template <typename T>
LinkedList<T>::LinkedList()
{
    head = new Node();
    tail = head;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    clear();
    delete head;
    // delete tail;
}

template <typename T>
void LinkedList<T>::add(T val)
{
    Node* newNode = new Node(val);
    
    tail->next = newNode;
    tail = newNode;
}

template <typename T>
void LinkedList<T>::removeAfter(Node* prev)
{
    Node* nodeToRemove = prev->next;
    prev->next = nodeToRemove->next;

    if(nodeToRemove == tail) tail = prev;
    delete nodeToRemove;
}
template <typename T>
bool LinkedList<T>::isEmpty()
{
    return (head->next == nullptr);
}


template <typename T>
void LinkedList<T>::clear()
{
    while(!isEmpty())
    {
        removeAfter(head);
    }
}

template <typename T>
template <typename Function>
void LinkedList<T>::forEach(Function func)
{
    Node* currNode = head;
    while(currNode->next != nullptr)
    {
        func(currNode->next->value);
        currNode = currNode->next;
    }
}

template <typename T>
template <typename Function>
void LinkedList<T>::forEachAndRemoveIf(Function func)
{
    Node* currNode = head;
    while(currNode->next != nullptr)
    {
        if(func(currNode->next->value)) removeAfter(currNode);
        else currNode = currNode->next;
    }
}
// template <typename T>
// void LinkedList<T>::getFirstElement()
// {
//     return head->next;
// }

#endif