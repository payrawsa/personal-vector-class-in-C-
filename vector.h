#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>     // std::cout
#include <algorithm>    // std::max

namespace ubcse {

    template<typename Item_Type>
    class vector {
    private:
        /* Data fields */

        /** Initial capacity of the array */
        static const size_t INITIAL_CAPACITY; // size_t is equivalent to unsigned integers
        // it starts from 0 .

        /** The current capacity of the array */
        size_t current_capacity;

        /** The current number of items in the array */
        size_t num_items;

        /** The array to contain data .
         * we acquire it in the heap with new command
         */
        Item_Type* data_array;

    public:

        /*** Constructors and assignment operators  ***/

        vector<Item_Type>() {
            num_items = 0;
            current_capacity = INITIAL_CAPACITY;
            data_array = new Item_Type[current_capacity];

        }

        vector<Item_Type>(size_t n, const Item_Type &value) {

            num_items = n;
            current_capacity = std::max(num_items, INITIAL_CAPACITY);

            data_array = new Item_Type[current_capacity];

            for (int i = 0; i < num_items; i++) {
                data_array[i] = value;

            }


        }

        vector<Item_Type>(Item_Type& start, Item_Type& end) {
            Item_Type* pointer;
            Item_Type* pointer2;
            pointer = &start;
            pointer2 = &end;
            int counter = 0;
            for (pointer = &start; pointer != pointer2 + 1; pointer++) {
                counter++;
            }
            pointer = &start;
            num_items = counter;
            current_capacity = num_items;
            data_array = new Item_Type[current_capacity];
            int counters = 0;
            for (pointer; pointer != pointer2 + 1; pointer++) {
                data_array[counters] = *pointer;
                counters++;
            }

        }

        vector<Item_Type>(const vector<Item_Type>&other, int start, int end) {

            int total = end - start + 1;
            num_items = total;
            data_array = new Item_Type[num_items];

            for (int i = 0; i < total; i++) {
                data_array[i] = other.data_array[i];

            }
        }
            vector(const vector<Item_Type>&other) {

                num_items = other.size();
                Item_Type* other1 = new Item_Type[std::max(num_items, INITIAL_CAPACITY)];
                for (int i = 0; i < num_items; i++) {
                    other1[i] = other.data_array[i];

                }

                data_array = new Item_Type[num_items];
                for (int i = 0; i < num_items; i++) {
                    data_array[i] = other1[i];
                }

            }

            ~vector() {
//               delete[] data_array;


            }


            // Copy assignment.
            vector<Item_Type>& operator=(const vector<Item_Type>&other);
            vector<Item_Type>& operator+(const vector<Item_Type>&other);


            // Get reference to element at index.
            Item_Type & at(const int index);

            // Get reference to element at index using [] op
            Item_Type& operator[](const int& index);

            // Get the number of elements stored.
            size_t size() const;

            // Return if the vector is storing values.
            bool empty() const;

            // reserve space for vector.
            void reserve(size_t newSize);

            // Resize size of storage for vector.
            void resize(const size_t & newSize);

            // Insert copy of value at index.
            void insert(const int& index, const Item_Type & value);

            // Insert copy of value at end of vector.
            void push_back(const Item_Type & value);

            // Erase element at index.
            void erase(int index);


            // print array
            void print();

            // concatanate two vectors.
            void concat(const vector<Item_Type>&other);

            // reduce current capacity to num_items.
            void shrink_to_fit();

        }; //end of class vector

        template <typename Item_Type>
        const size_t vector<Item_Type>::INITIAL_CAPACITY = 10;

        /** Implementation: assignment operator
         *
         */
        template <typename Item_Type>
        vector<Item_Type>& vector<Item_Type>::operator=(const vector<Item_Type>& other) {

            // This operator is used to copy the state of the
            // other object into this instance of the object.
            if (this != &other) {
                if (current_capacity != other.current_capacity) {
                    // We need to reallocate storage size.
                    delete[] data_array;
                    // In case memory allocation fails,
                    // we update state of this object first.
                    // Allocate new space.
                    data_array = new Item_Type[other.current_capacity];

                    // Set appropriate size of stored values.
                    current_capacity = other.current_capacity;
                }

                // Copy memory over.
                std::copy(other.data_array, other.data_array + other.num_items, data_array);
                num_items = other.num_items;

            }

            return *this;
        }


        // Get reference to element at index.

        template <typename Item_Type>
        Item_Type& vector<Item_Type>::at(const int index) {
            if (index >= current_capacity || index < 0) {
                throw;
            }
            return data_array[index];
        }

        // Get reference to element at index.

        template <typename Item_Type>
        Item_Type& vector<Item_Type>::operator[](const int& index) {
            return this->at(index);
        }

        // Get the size of the vector.

        template <typename Item_Type>
        size_t vector<Item_Type>::size() const {
            return num_items;
        }

        // Return if the vector is storing values.

        template <typename Item_Type>
        bool vector<Item_Type>::empty() const {
            return num_items == 0;
        }

        // Reserve storage.

        template <typename Item_Type>
        void vector<Item_Type>::reserve(size_t newSize) {
            if (current_capacity >= newSize) {
                return;
            }
            Item_Type* temp = new Item_Type[newSize];
            std::copy(data_array, data_array + num_items, temp);
            std::swap(data_array, temp);
            delete[] temp;
            current_capacity = newSize;
        }

        // Resize vector.

        template <typename Item_Type>
        void vector<Item_Type>::resize(const size_t& newSize) {
            if (current_capacity >= newSize) {
                num_items = newSize > 0 ? newSize : 0;
            } else {
                this->reserve(newSize);
                num_items = newSize;
            }
        }

        // Insert copy of value at index.

        template <typename Item_Type>
        void vector<Item_Type>::insert(const int& index, const Item_Type& value) {
            if (index < 0 || index > num_items) {
                throw;
            }

            // if we have maxed the size, double the capacity
            size_t init = 1;
            if (num_items >= current_capacity) {
                this->reserve(std::max(init, current_capacity * 2));
            }

            // shift elements right to make room for value.
            for (int i = num_items - 1; i >= index; --i) {
                data_array[i + 1] = data_array[i];
            }

            data_array[index] = value;
            num_items++;
        }

        // Insert value at end of storage.

        template <typename Item_Type>
        void vector<Item_Type>::push_back(const Item_Type& value) {
            this->insert(num_items, value);
        }

        // Erase element at index.

        template <typename Item_Type>
        void vector<Item_Type>::erase(int index) {
            if (index < 0 || index >= num_items) {
                throw;
            }

            // shift elements left to cover gap.
            for (int i = index + 1; i < num_items; ++i) {
                data_array[i - 1] = data_array[i];
            }
            num_items--;
        }

        template <typename Item_Type>
        void vector<Item_Type>::print() {

            for (int i = 0; i < num_items; ++i) {
                std::cout << data_array[i] << " ";
            }
            std::cout << "" << std::endl;


        }

        template <typename Item_Type>
        void vector<Item_Type>::concat(const vector<Item_Type>&other) {

            int one = other.size();
            int two = num_items;
            for (int i = 0; i < one; i++) {

                data_array[i + two] = other.data_array[i];
                num_items += 1;
            }

        }

        template <typename Item_Type>
        vector<Item_Type>& vector<Item_Type>::operator+(const vector<Item_Type>& other) {

            int one = this->size();
            int two = other.size();

            for (int i = 0; i < two; i++) {

                this->data_array[i + one] = other.data_array[i];
                num_items += 1;

            }

            return *this;
        }

        template <typename Item_Type>
        void vector<Item_Type>::shrink_to_fit() {


            current_capacity = num_items;
            data_array = new Item_Type[num_items];

        }

    }

#endif /* VECTOR_H_ */

