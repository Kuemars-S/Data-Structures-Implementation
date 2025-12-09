#include <iostream>

class LinkedList {
private:
    struct node {
        int data;
        node* next;
    };

    node* head;
    node* tail;
    int size;
public:
    LinkedList(): head(nullptr), tail(nullptr), size(0) {};

    void insert_last(const int value) {
        const auto newNode = new node();
        newNode->data = value;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    void insert_first(const int value) {
        const auto newNode = new node();
        newNode->data = value;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void remove_first() {
        if (head == nullptr) {
            std::cout << "Cannot remove from empty list" << std::endl;
            return;
        }
        auto temp = head;
        head = head->next;
        delete temp;
        size--;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void remove_last() {
        if (head == nullptr) {
            std::cout << "Cannot remove from empty list" << std::endl;
            return;
        }

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size--;
            return;
        }
        auto current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
        size--;
    }

    void search(const int value) const {
        auto current = head;
        while (current->next != nullptr) {
            if (current->data == value) {
                std::cout << value << " was Found!\n";
                return;
            }
            current = current->next;
        }
        std::cout << value << " was Not Found!\n";
    }

    void display() const {
        if (head == nullptr) {
            std::cout << "Empty List\n";
            return;
        }
        auto current = head;
        while (current != nullptr) {
            std::cout << current->data;
            if (current->next != nullptr) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << "\n";
    }

    void insert_at_index(int value, int index) {
        if (index < 0 || index > size) {
            std::cout << "Invalid Index\n";
            return;
        }
        auto newNode = new node();
        newNode->data = value;
        newNode->next = nullptr;

        if (index == 0) {
            newNode->next = head;
            head = newNode;
        }
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            auto current = head;
            for (int i = 0; i < index - 1; i++) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
            if (newNode->next == nullptr) {
                tail = newNode;
            }
        }
        size++;
    }

    void remove_element(int value) {
        if (head == nullptr) {
            tail = nullptr;
            return;
        }

        if (head->data == value) {
            auto temp = head;
            head = head->next;
            delete temp;
            size--;

            if (head == nullptr) {
                tail = nullptr;
            }
            return;
        }

        auto current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                auto temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;

                if (current->next == nullptr) {
                    tail = current;
                }
                return;
            }
            current = current->next;
        }
    }

    [[nodiscard]] int getSize() const {
        return size;
    }

    ~LinkedList() {
        auto current = head;
        while (current != nullptr) {
            const auto temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;

    while (true) {
        std::string type;
        std::cin >> type;
        if (type == "insert") {
            int value;
            std::cin >> value;
            list.insert_first(value);
            continue;
        }
        else if (type == "display") {
            list.display();
            continue;
        }
        else if (type == "remove") {
            int value;
            std::cin >> value;
            list.remove_element(value);
            continue;
        }
        else if (type == "size") {
            std::cout << list.getSize() << std::endl;
        }
        else if (type == "exit") {
            return 0;
        }
    }
}