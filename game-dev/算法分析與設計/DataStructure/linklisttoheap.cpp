#include <iostream>

struct Node {
    int data;
    Node* next;
};

class MinHeap {
    Node* head;

public:
    MinHeap() : head(nullptr) {}

    void insert(int data) {
        Node* node = new Node;
        node->data = data;
        node->next = nullptr;

        if (head == nullptr || data < head->data) {
            node->next = head;
            head = node;
        }
        else {
            Node* current = head;
            while (current->next != nullptr && current->next->data < data) {
                current = current->next;
            }
            node->next = current->next;
            current->next = node;
        }
    }

    int getMin() {
        if (head != nullptr) {
            return head->data;
        }
        return -1;
    }

    void deleteMin() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void printHeap() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};


int main() {
    MinHeap h;
    h.insert(1);
    std::cout << "Min: " << h.getMin() << std::endl;
    h.printHeap();
    h.insert(1);
    h.insert(114);
    h.insert(5);
    h.insert(14);
    h.insert(45);

    std::cout << "Heap: ";
    h.printHeap();

    std::cout << "Min: " << h.getMin() << std::endl;

    h.deleteMin();
    std::cout << "Heap after deleting min: ";
    h.printHeap();

    return 0;
}
