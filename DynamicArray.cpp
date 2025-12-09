#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t currentSize;
    size_t currentCapacity;
public:
    DynamicArray(): data(nullptr), currentSize(0), currentCapacity(0) {}

    ~DynamicArray() {
        delete[] data;
    }

    [[nodiscard]] size_t size() const {
        return currentSize;
    }

    void reserve(const size_t newCapacity) {
        if (newCapacity <= currentCapacity) return;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < currentSize; ++i) {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
        currentCapacity = newCapacity;
    }

    void resize(const size_t newSize) {
        if (newSize > currentCapacity) {
            reserve(newSize);
        }
        if (newSize > currentSize) {
            for (size_t i = currentSize; i < newSize; ++i) {
                data[i] = T();
            }
        }
        currentSize = newSize;
    }

    T& operator[](size_t index) {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& at(size_t index) {
        if (index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& front() {
        if (currentSize == 0) {
            throw std::out_of_range("Array is empty");
        }
        return data[0];
    }

    T& back() {
        if (currentSize == 0) {
            throw std::out_of_range("Array is empty");
        }
        return data[currentSize - 1];
    }

    void expand() {
        const size_t newCapacity = (currentCapacity == 0) ? 1 : currentCapacity * 2;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < currentSize; ++i) {
            newData[i] = std::move(data[i]);
        }
        delete[] data;
        data = newData;
        currentCapacity = newCapacity;
    }

    void push_back(const T& value) {
        if (currentSize == currentCapacity) {
            expand();
        }
        data[currentSize++] = value;
    }

    void pop_back() {
        if (currentSize == 0) {
            throw std::out_of_range("Array is empty");
        }
        --currentSize;
    }

    void insert(size_t index, const T& value) {
        if (currentSize == currentCapacity) {
            expand();
        }
        if (index > currentSize) {
            throw std::out_of_range("Given index out of range");
        }
        for (size_t i = currentSize; i > index; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[index] = value;
        ++currentSize;
    }

    void erase(size_t index) {
        if (index >= currentSize) {
            throw std::out_of_range("Given index out of range");
        }
        for (size_t i = index; i < currentSize - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --currentSize;
    }

    [[nodiscard]] const T* begin() const {
        return data;
    }

    [[nodiscard]] const T* end() const {
        return data + currentSize;
    }

    void print() const {
        for (auto it = begin(); it != end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    DynamicArray<int> arr;

    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);

    arr.insert(2, 99);
    arr.erase(0);
    arr.pop_back();

    arr.print();

    return 0;
}