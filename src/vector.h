#ifndef VectorClass
#define VectorClass


#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#define SWAP(type, a, b) type tmp ## a = a; a = b; b = tmp ## a;

// This class implements missing vector from STL
template <class VectorType> class Vector
{
    VectorType *begin;
    VectorType *storage;
    int head;

public:
    VectorType OB;

    // We can save a few re-sizings if we know how large the array is likely to grow to be
    Vector(int initialSize = 0)
    {
        begin = new VectorType[initialSize]; //points to the beginning of the new array
        head = initialSize - 1;
        storage = begin + initialSize; //points to the element one outside of the array (such that end - begin = capacity)
    }

    Vector(Vector &obj)
    {
        begin = new VectorType[0]; // Points to the beginning of the new array, it's zero but this line keeps malloc from seg faulting should we delete begin before resizing it
        head = -1;
        storage = begin; //points to the element one outside of the array (such that end - begin = capacity)

        *this = obj;
    }

    // If there's anything in the vector then delete the array, if there's no array then doing will will cause seg faults
    virtual ~Vector() { delete[] begin; }

    Vector &operator=(Vector &obj)
    {
        // Reallocate the underlying buffer to the same size as the
        Resize(obj.Size());

        for(int i = 0; i < obj.Size(); i++)
            (*this)[i] = obj[i];

        head = obj.head;

        return *this;
    }

    // Swaps the underlying array and characteristics of this vector with another of the same type, very quickly
    void Swap(Vector &obj)
    {
        SWAP(int, head, obj.head);
        SWAP(VectorType*, begin, obj.begin);
        SWAP(VectorType*, storage, obj.storage);
    }

    // Checks the entire Vector to see whether a matching item exists. Bear in mind that the VectorType might need to implement
    // equality operator (operator==) for this to work properly.
    bool Contains(VectorType element)
    {
        for(int i = 0; i < Size(); i++)
            if(operator [](i) == element)
                return true;

        return false;
    }

    int Find(VectorType element)
    {
        for(int i = 0; i < Size(); i++)
            if(operator [](i) == element)
                return i;

        return -1;
    }

    void PushBack(VectorType element) { PushBack(&element, 1); }

    void PushBack(const VectorType *elements, int len)
    {
        // If the length plus this's size is greater than the capacity, reallocate to that size.
        if(len + Size() > Capacity())
            ReAllocate(MAX(Size() + len, Size() * 2));

        int append = MIN(storage - begin - head - 1, len), prepend = len - append;

        // memcpy the data starting at the head all the way up to the last element *(storage - 1)
        memcpy((begin + head + 1), elements, sizeof(VectorType) * append);

        // If there's still data to copy memcpy whatever remains, starting at the first element *(begin) until the end of data. The first step will have ensured
        // that we don't crash into the tail during this process.
        memcpy(begin,(elements + append), sizeof(VectorType) * prepend);

        // Re-recalculate head and size.
        head += len;
    }

    void Erase(unsigned int position) { Erase(position, position + 1); }

    // Erase an arbitrary section of the vector from first up to last minus one. Like the stl counterpart, this is pretty labour intensive so go easy on it.
    void Erase(int first, int last)
    {
        // For this we'll set the value of the array at first to the value of the array at last plus one. We'll do that all the way up to toIndex
        for(int i = 0; i < (Size() - first); i++)
        {
            // If by trying to fill in the next element with the ones ahead of it we'll be running off the end of the vector, stop.
            if((i + last) > (Size() - 1))
                break;

            begin[first + i] = begin[last + i];
        }

        // Adjust the head to reflect the new size
        head -= last - first;
    }

    // Remove the most recent element in the array
    void PopBack()
    {
        if(Size() > 0)
            head--;
    }

    // Empty the vector, or to be precise - forget the fact that there was ever anything in there.
    void Clear() { head = -1; }

    // Returns a bool indicating whether or not there are any elements in the array
    bool Empty() { return head == -1; }

    // Returns the oldest element in the array (the one added before any other)
    VectorType const &Back() { return *begin; }

    // Returns the newest element in the array (the one added after every other)
    VectorType const &Front() { return begin[head]; }

    // Returns the nth element in the vector
    VectorType &operator[](int n)
    {
        if(n < Size())
            return begin[n];
        else
            return OB;  // out of bounds
    }

    // Returns a pointer such that the vector's data is laid out between ret to ret + size
    VectorType *Data() { return begin; }

    // Recreates the vector to hold len elements, all being copies of val
    void Assign(int len, const VectorType &val)
    {
        delete[] begin;

        // Allocate an array the same size as the one passed in
        begin = new VectorType[len];
        storage = begin + len;

        // Refresh the head and tail, assuming the array is in order, which it really has to be
        head = len - 1;

        for(int i = 0 ; i < Size(); i++)
            begin[i] = val;
    }

    // Recreates the vector using an external array
    void Assign(VectorType *array, int len)
    {
        delete[] begin;

        // Allocate an array the same size as the one passed in
        begin = new VectorType[len];
        storage = begin + len;

        // Refresh the head and tail, assuming the array is in order, which it really has to be
        head = len - 1;

        // Copy over the memory
        memcpy(begin, array, sizeof(VectorType) * len);
    }

    // Returns the number of elements that the vector will support before needing resizing
    int Capacity() { return (storage - begin); }

    // Returns the number of elements in vector
    int Size() { return head + 1; }

    // Requests that the capacity of the allocated storage space for the elements
    // of the vector be at least enough to hold size elements.
    void Reserve(unsigned int size)
    {
        if(size > Capacity())
            ReAllocate(size);
    }

    // Resizes the vector
    void Resize(unsigned int size)
    {
        // If necessary, resize the underlying array to fit the new size
        if(size > Capacity())
            ReAllocate(size);

        // Now revise the head and size (tail needn't change) to reflect the new size
        head = size - 1;
    }

private:

    void ReAllocate(unsigned int size)
    {
        // Just in case we're re-allocating less room than we had before, make sure that we don't overrun the buffer by trying to write more elements than
        // are now possible for this vector to hold.
        if(Size() > (int)size)
            head = size - 1;

        // Allocate an array twice the size of that of the old
        VectorType *_begin = new VectorType[size];
        VectorType *_storage = _begin + size;

        int _head = Size() - 1;

        // Copy across all the old array's data and rearrange it!
        for(int i = 0; i < Size(); i++)
            _begin[i] = (*this)[i];

        // Free the old memory
        delete[] begin;

        // Redirect the old array to point to the new one
        begin = _begin;
        storage = _storage;
        head = _head;
    }
};

#endif