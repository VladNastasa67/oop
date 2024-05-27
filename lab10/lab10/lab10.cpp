#include <iostream>
#include <exception>

using namespace std;

// Exception classes
class OutOfBoundsException : public exception {
    virtual const char* what() const throw() {
        return "Indexul este inafara domeniului!";
    }
};

class CapacityExceededException : public exception {
    virtual const char* what() const throw() {
        return "Capacitatea a fost depasita!";
    }
};

// Compare class remains abstract
class Compare {
public:
    virtual int CompareElements(void* e1, void* e2) = 0;
};

template<class T>
class ArrayIterator {
private:
    T** List;
    int Current;
    int Size;
public:
    ArrayIterator(T** list, int size, int current = 0) : List(list), Size(size), Current(current) {}

    ArrayIterator& operator++() {
        if (Current < Size) ++Current;
        return *this;
    }

    ArrayIterator& operator--() {
        if (Current > 0) --Current;
        return *this;
    }

    bool operator=(ArrayIterator<T>& other) {
        return List == other.List && Current == other.Current;
    }

    bool operator!=(ArrayIterator<T>& other) {
        return !(*this == other);
    }

    T* GetElement() {
        if (Current < Size)
            return List[Current];
        return nullptr;
    }
};

template<class T>
class Array {
private:
    T** List;
    int Capacity;
    int Size;
public:
    Array() : List(nullptr), Capacity(0), Size(0) {}

    ~Array() {
        for (int i = 0; i < Size; ++i) {
            delete List[i];
        }
        delete[] List;
    }

    Array(int capacity) : Capacity(capacity), Size(0) {
        List = new T * [Capacity];
    }

    Array(const Array<T>& otherArray) : Capacity(otherArray.Capacity), Size(otherArray.Size) {
        List = new T * [Capacity];
        for (int i = 0; i < Size; ++i) {
            List[i] = new T(*otherArray.List[i]);
        }
    }

    T& operator[](int index) {
        if (index < 0 || index >= Size)
            throw OutOfBoundsException();
        return *List[index];
    }

    const Array<T>& operator+=(const T& newElem) {
        if (Size >= Capacity)
            throw CapacityExceededException();
        List[Size++] = new T(newElem);
        return *this;
    }

    const Array<T>& Insert(int index, const T& newElem) {
        if (index < 0 || index > Size)
            throw OutOfBoundsException();
        if (Size >= Capacity)
            throw CapacityExceededException();
        for (int i = Size; i > index; --i) {
            List[i] = List[i - 1];
        }
        List[index] = new T(newElem);
        ++Size;
        return *this;
    }

    const Array<T>& Insert(int index, const Array<T> otherArray) {
        if (index < 0 || index > Size)
            throw OutOfBoundsException();
        if (Size + otherArray.Size > Capacity)
            throw CapacityExceededException();
        for (int i = Size - 1; i >= index; --i) {
            List[i + otherArray.Size] = List[i];
        }
        for (int i = 0; i < otherArray.Size; ++i) {
            List[index + i] = new T(*otherArray.List[i]);
        }
        Size += otherArray.Size;
        return *this;
    }

    const Array<T>& Delete(int index) {
        if (index < 0 || index >= Size)
            throw OutOfBoundsException();
        delete List[index];
        for (int i = index; i < Size - 1; ++i) {
            List[i] = List[i + 1];
        }
        --Size;
        return *this;
    }

    bool operator=(const Array<T>& otherArray) {
        if (this != &otherArray) {
            for (int i = 0; i < Size; ++i) {
                delete List[i];
            }
            delete[] List;
            Capacity = otherArray.Capacity;
            Size = otherArray.Size;
            List = new T * [Capacity];
            for (int i = 0; i < Size; ++i) {
                List[i] = new T(*otherArray.List[i]);
            }
        }
        return true;
    }

    void Sort() {
        // Implement sort logic here
    }

    void Sort(int(*compare)(const T&, const T&)) {
        // Implement sort logic here using the compare function
    }

    void Sort(Compare* comparator) {
        // Implement sort logic here using the comparator object
    }

    int BinarySearch(const T& elem) {
        // Implement binary search logic here
        return -1; // Placeholder return value
    }

    int BinarySearch(const T& elem, int(*compare)(const T&, const T&)) {
        // Implement binary search logic here using the compare function
        return -1; // Placeholder return value
    }

    int BinarySearch(const T& elem, Compare* comparator) {
        // Implement binary search logic here using the comparator object
        return -1; // Placeholder return value
    }

    int Find(const T& elem) {
        // Implement find logic here
        return -1; // Placeholder return value
    }

    int Find(const T& elem, int(*compare)(const T&, const T&)) {
        // Implement find logic here using the compare function
        return -1; // Placeholder return value
    }

    int Find(const T& elem, Compare* comparator) {
        // Implement find logic here using the comparator object
        return -1; // Placeholder return value
    }

    int GetSize() {
        return Size;
    }

    int GetCapacity() {
        return Capacity;
    }

    ArrayIterator<T> GetBeginIterator() {
        return ArrayIterator<T>(List, Size, 0);
    }

    ArrayIterator<T> GetEndIterator() {
        return ArrayIterator<T>(List, Size, Size);
    }
};

int main() {
    try {
        Array<int> arr(5);
        arr += 10;
        arr += 20;
        arr += 30;
        arr.Insert(1, 15);
        arr.Delete(0);

        for (int i = 0; i < arr.GetSize(); i++) {
            cout << arr[i] << endl;
        }

        // Uncommenting the following line will throw an exception
        // arr[5] = 100;

    }
    catch (exception& e) {
        cout << "Exceptie: " << e.what() << endl;
    }
    return 0;
}
