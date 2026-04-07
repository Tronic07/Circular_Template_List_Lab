//
// Created by Christopher Vaughn on 10/24/25.
//

#ifndef CIRCULARTEMPLATEDLIST_LINKEDLIST_H
#define CIRCULARTEMPLATEDLIST_LINKEDLIST_H

#include <iostream>

// ===============================
//      Templated Node
// ===============================
template <typename T>
struct Node {
    T data;            // T will be Media*
    Node<T>* next;

    Node(T d) : data(d), next(nullptr) {}
};

// ===============================
//   Templated Circular LinkedList
// ===============================
template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* current;

public:
    // Constructor
    LinkedList() : head(nullptr), tail(nullptr), current(nullptr) {}

    // Destructor (circular-safe)
    ~LinkedList() {
        if (!head) return;

        Node<T>* temp = head;

        do {
            Node<T>* nextNode = temp->next;
            delete temp->data;   // delete Media*
            delete temp;
            temp = nextNode;
        } while (temp != head);

        head = tail = current = nullptr;

        std::cout << "\n[Playlist cleanup complete. All memory deallocated.]\n";
    }

    // ===============================
    //          INSERT (Circular)
    // ===============================
    void insert(T item) {
        Node<T>* newNode = new Node<T>(item);

        if (!head) {
            head = tail = current = newNode;
            newNode->next = head;   // circular link
            return;
        }

        tail->next = newNode;       // append
        tail = newNode;
        tail->next = head;          // maintain circularity
    }

    // ===============================
    //        DISPLAY (Circular)
    // ===============================
    void displayList() const {
        if (!head) {
            std::cout << "\n[Playlist is empty.]\n";
            return;
        }

        std::cout << "\n--- Current Playlist ---\n";

        Node<T>* temp = head;
        int index = 1;

        do {
            std::cout << index++ << ". " << temp->data->toString() << "\n";
            temp = temp->next;
        } while (temp != head);

        std::cout << "------------------------\n";
    }

    // ===============================
    //       PLAY CURRENT ITEM
    // ===============================
    void playCurrent() const {
        if (!current) {
            std::cout << "[Playlist is empty. Nothing to play.]\n";
            return;
        }
        current->data->play();
    }

    // ===============================
    //       PLAY NEXT (Circular)
    // ===============================
    void playNext() {
        if (!current) {
            std::cout << "[Playlist is empty.]\n";
            return;
        }

        current = current->next;   // circular by design
        current->data->play();
    }
};

#endif // CIRCULARTEMPLATEDLIST_LINKEDLIST_H