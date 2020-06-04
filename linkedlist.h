#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>
#include "NodeIterator.h"
#include <type_traits>
#include <utility>

template <class T>
class LinkedList {
private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int size = 0;
public:
    typedef NodeIterator<T> iterator;
    void insertBefore(T valueToBeInserted,  T valueToBeFound);
    void insertAfter(T valueToBeInserted,  T valueToBeFound);
    int getSize();
    Node<T>* getHead();
    Node<T>* getTail();
    int findAll(T value);
    void empty();
    void insertHead(T value);
    void push(T value);
    void insertTail(T value);
    void remove(T value);
    void removeNode(Node<T>* nodeToBeRemoved);
    Node<T>* search(T value);
    void print();
    bool isLastElement(Node<T>* lastElement);
    NodeIterator<T> begin();
    NodeIterator<T> end();
    T &operator[](int i) {
             if( i > size ) {
                return getHead()->value;
             }

             int counter = 0;
             Node<T> *temp;

             temp = head;
             while (temp != nullptr) {
                 counter += 1;
                 if (counter == i) {
                     break;
                 }
                 temp = temp->next;
             }
             return temp->value;
    }
};

template<class T>
NodeIterator<T> LinkedList<T>::end() {
    NodeIterator<T> temp;
    return temp;
}

template<class T>
NodeIterator<T> LinkedList<T>::begin() {
    NodeIterator<T> temp(head);
    return temp;
}


template <class T>
Node<T>* LinkedList<T>::search(T value) {
    Node<T> *temp;
    temp = head;
        while (temp != nullptr) {
            if (value == temp->value) {
                return temp;
            } else {
                temp = temp->next;
            }
        }
        return nullptr;


}

template<class T>
void LinkedList<T>::remove(T value) {
    Node<T> *findNode;
    findNode = search(value);
    if (findNode != nullptr) {

        //If Head Removal
        if (findNode == head && findNode != tail) {
            findNode->next->prev = nullptr;
            head = findNode->next;
        } else if (findNode == tail && findNode != head) {
            findNode->prev->next = nullptr;
            tail = findNode->prev;
        } else if (findNode != tail && findNode != head) {
            findNode->prev->next = findNode->next;
            findNode->next->prev = findNode->prev;
        } else if (findNode == tail && findNode == head) {
            head = nullptr;
            tail = nullptr;
        }
        size -= 1;
        delete findNode;

    }
}

template<class T>
void LinkedList<T>::insertTail(T value) {

    Node<T> *temp = new Node<T>;
    temp->value = value;
    temp->next = nullptr;

    if (tail == nullptr) {
        temp->prev = nullptr;
        head = temp;
        tail = temp;
    } else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    size += 1;
}

template<class T>
void LinkedList<T>::insertHead(T value) {
    Node<T> *temp = new Node<T>;
    temp->value = value;
    temp->prev = nullptr;

    if (head == nullptr && tail == nullptr) {
        temp->next = nullptr;
        head = temp;
        tail = temp;
    } else {
        temp->next = head;
        head->prev = temp;
        head = temp;
    }
    size += 1;

}
template <class T>
void LinkedList<T>::print() {
    Node<T> *temp;
    temp = head;
    while (temp != nullptr) {
        std::cout << "| Previous: " << temp->prev << " Value: " << temp->value << " Current: " << temp << " Next: "
                  << temp->next << "| " << std::endl;

        temp = temp->next;
    }
}


template<class T>
void LinkedList<T>::push(T value) {
    Node<T>* temp = new Node<T>;
    temp->value = value;

    if (head == 0 && tail == 0) {
        temp->prev = nullptr;
        temp->next = nullptr;

        head = temp;
        tail = temp;

    } else {
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
        tail->next = nullptr;
    }
    size += 1;
}

template<class T>
void LinkedList<T>::insertBefore(T valueToBeInserted, T valueToBeFound) {
    Node<T> *temp;
    temp = search(valueToBeFound);

    if (temp != nullptr) {
        Node<T> *newTemp = new Node<T>;
        newTemp->value = valueToBeInserted;
        newTemp->next = temp;
        newTemp->prev = temp->prev;
        temp->prev->next = newTemp;
        temp->prev = newTemp;

    }
    size += 1;

}

template<class T>
Node<T> *LinkedList<T>::getHead() {
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getTail() {
    return tail;
};
template<class T>
int LinkedList<T>::getSize() {
    int counter = 0;
    Node<T> *temp;

    temp = head;
    while (temp != nullptr) {
        counter += 1;
        temp = temp->next;
    }
    return counter;
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *nodeToBeRemoved) {
    if (nodeToBeRemoved) {
        //If Head Removal
        if (nodeToBeRemoved == head && nodeToBeRemoved != tail) {
            nodeToBeRemoved->next->prev = nullptr;
            head = nodeToBeRemoved->next;
        } else if (nodeToBeRemoved == tail && nodeToBeRemoved != head) {
            nodeToBeRemoved->prev->next = nullptr;
            tail = nodeToBeRemoved->prev;
        } else if (nodeToBeRemoved != tail && nodeToBeRemoved != head) {
            nodeToBeRemoved->prev->next = nodeToBeRemoved->next;
            nodeToBeRemoved->next->prev = nodeToBeRemoved->prev;
        } else if (nodeToBeRemoved == tail && nodeToBeRemoved == head) {
            head = nullptr;
            tail = nullptr;
        }
        delete nodeToBeRemoved;
    }
}

template<class T>
bool LinkedList<T>::isLastElement(Node<T> *lastElement) {
    return lastElement == tail;
}

template<class T>
void LinkedList<T>::insertAfter(T valueToBeInserted, T valueToBeFound) {
    Node<T> *temp;
    temp = search(valueToBeFound);

    if (temp != nullptr) {
        Node<T> *newTemp = new Node<T>;
        newTemp->value = valueToBeInserted;
        if (temp->next != nullptr) {
            temp->next->prev = newTemp;
        };
        newTemp->next = temp->next;
        temp->next = newTemp;
        newTemp->prev = temp;
    }
    size += 1;
};


#endif // LINKEDLIST_H
