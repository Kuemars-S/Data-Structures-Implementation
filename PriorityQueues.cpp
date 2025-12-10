#include <iostream>
#include <functional>
#include <stdexcept>

template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
private:
    struct Node {
        T data;
        Node* next;
    };

    Node* head;
    size_t currentSize;
    Compare comp;

public:
    PriorityQueue(): head(nullptr), currentSize(0), comp() {}

    explicit PriorityQueue(const Compare& compare): head(nullptr), currentSize(0), comp(compare) {}

    ~PriorityQueue() {
        while (head != nullptr) {
            const Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    [[nodiscard]] size_t size() const {
        return currentSize;
    }

    [[nodiscard]] bool empty() const {
        return head == nullptr;
    }

    void push(const T& value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr || comp(head->data, value)) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && comp(value, current->next->data)) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        currentSize++;
    }

    [[nodiscard]] const T& top() const {
        if (head == nullptr) {
            throw std::out_of_range("Priority queue is empty");
        }
        return head->data;
    }

    void pop() {
        if (head == nullptr) {
            throw std::out_of_range("Priority queue is empty");
        }
        const Node* temp = head;
        head = head->next;
        delete temp;
        currentSize--;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
};

int main() {
    PriorityQueue<int> pq;

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::string type;
        std::cin >> type;

        if (type == "push") {
            int value;
            std::cin >> value;
            pq.push(value);
        }
        else if (type == "pop") {
            if (!pq.empty()) {
                pq.pop();
            }
        }
        else if (type == "top") {
            if (!pq.empty()) {
                std::cout << pq.top() << "\n";
            }
        }
        else if (type == "display") {
            pq.print();
        }
        else if (type == "size") {
            std::cout << pq.size() << "\n";
        }
    }

    return 0;
}