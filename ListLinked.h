#include <ostream>
#include "List.h"
#include "Node.h"
#include <stdexcept>

template <typename T>
class ListLinked : public List<T> {

private:
    Node<T>* first;
    int n;

public:
    ListLinked() : first(nullptr), n(0) {}

    ~ListLinked() {
        Node<T>* aux;
        while (first != nullptr) {
            aux = first->next;
            delete first;
            first = aux;
        }
    }

    T operator[](int pos){
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición fuera de rango");
        }
        Node<T>* aux = first;
        for (int i = 0; i < pos; ++i) {
            aux = aux->next;
        }
        return aux->data;
    }

    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
        Node<T>* aux = list.first;
        while (aux != nullptr) {
            out << aux->data << " ";
            aux = aux->next;
        }
        return out;
    }
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("posicion invalida");
        }

        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            prev->next = new Node<T>(e, prev->next);
        }
        ++n;
    }

    void append(T e) override {
        insert(n, e);
    }

    void prepend(T e) override {
        insert(0, e);
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("posicion invalida");
        }

        Node<T>* toDelete;
        T value;

        if (pos == 0) {
            toDelete = first;
            value = first->data;
            first = first->next;
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            toDelete = prev->next;
            value = toDelete->data;
            prev->next = toDelete->next;
        }

        delete toDelete;
        --n;
        return value;
    }

    T get(int pos) const override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("posicion invalida");
        }

        Node<T>* aux = first;
        for (int i = 0; i < pos; ++i) {
            aux = aux->next;
        }
        return aux->data;
    }

    int search(T e) const override {
        Node<T>* aux = first;
        int i = 0;
        while (aux != nullptr) {
            if (aux->data == e) {
                return i;
            }
            aux = aux->next;
            ++i;
        }
        return -1;
    }

    bool empty() const override {
        return n == 0;
    }

    int size() const override {
        return n;
    }
};
