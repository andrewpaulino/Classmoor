#ifndef NODEITERATOR_H
#define NODEITERATOR_H

#include <iterator>

template <class T>
struct Node {
    T value;
    Node* next = nullptr;
    Node* prev = nullptr;

};


template<class T>
class NodeIterator : public std::iterator<std::forward_iterator_tag, T> {
private:
    Node<T>* current;
public:
    const T& operator*();
    NodeIterator();
    NodeIterator(Node<T>* initial);
    bool operator==(const NodeIterator& other);
    friend std::ostream& operator<<(std::ostream& os, const NodeIterator<T>& dt) {
        os << "{" << std::endl;
        os << "  " <<dt.current->value.first << ": " << dt.current->value.second << std::endl;
        os << "}" << std::endl;
        return os;
    }
    bool operator!=(const NodeIterator& other);
    NodeIterator<T> operator++(int);
    NodeIterator<T> operator++();
    NodeIterator<T> operator -(int size);
    NodeIterator<T> operator +(int size);
    NodeIterator<T> operator--(int);
    NodeIterator<T> operator--();
};
template<class T>
const T& NodeIterator<T>::operator*() {
    return current->value;
}

template<class T>
NodeIterator<T> NodeIterator<T>::operator++(int) {
    Node<T>* temp = current;
    current = current->next;
    return *this;
}

template<class T>
bool NodeIterator<T>::operator==(const NodeIterator& other) {
    return current == other.current;
}

template<class T>
bool NodeIterator<T>::operator!=(const NodeIterator& other) {
    return current != other.current;
}

template<class T>
NodeIterator<T> NodeIterator<T>::operator++() {
    return current;
}

template<class T>
NodeIterator<T> NodeIterator<T>::operator--(int) {
    Node<T>* temp = current;
    current = current->prev;
    return *this;
}

template<class T>
NodeIterator<T> NodeIterator<T>::operator--() {
    return current;
}

template<class T>
NodeIterator<T>::NodeIterator() {
    current = nullptr;
}

template<class T>
NodeIterator<T>::NodeIterator(Node<T> *inital) {
    current = inital;
}

template<class T>
NodeIterator<T> NodeIterator<T>::operator-(int size) {
    Node<T>* temp = current;
    for (int i = 0; i < size; i++) {
        temp = temp->prev;
    }
    return temp;
}

template<class T>
NodeIterator<T> NodeIterator<T>::operator+(int size) {
    Node<T>* temp = current;
    for (int i = 0; i < size; i++) {
        temp = temp->next;
    }
    return temp;
}

#endif // NODEITERATOR_H
