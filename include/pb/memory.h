/**
 * This is a class that provides a growable memory structure that can store any type of data in any structure.
 * It is designed to be flexible and efficient, allowing for serialization to and from various formats such as JSON, CSV, etc.
 * The class can also handle memory mapping for large datasets.
 */


#pragma once

#include <stdexcept>
#include <cstddef> // for size_t
#include <string>
#include <algorithm> // for std::min

namespace pb {

    /**
     * MemoryGrowthPolicy: An abstract base class that defines the interface for memory growth policies.
     * This class provides a method to determine how memory should grow based on the current size,
     */
    class MemoryGrowthPolicy {
        public:
            virtual ~MemoryGrowthPolicy() = default;

            // This method should be implemented to define how memory grows
            virtual size_t grow_to_size(size_t needed_size, size_t current_size, size_t max_size) = 0;

    };

    /**
     * MemoryGrowthPolicyFixed: A policy that does not allow memory growth.
     * It throws an exception if an attempt is made to grow memory.
     */
    class MemoryGrowthPolicyFixed : public MemoryGrowthPolicy {
        public:
            virtual size_t grow_to_size(size_t needed_size, size_t current_size, size_t max_size) override {
                // Fixed policy does not allow growth
                throw std::runtime_error("Memory growth not allowed");
            }
    };

    /**
     * MemoryGrowthPolicyExponential: A policy that allows memory to grow exponentially.   
     */
    class MemoryGrowthPolicyExponential : public MemoryGrowthPolicy {
        public:
            virtual size_t grow_to_size(size_t needed_size, size_t current_size, size_t max_size) override {
                // Exponential growth policy
                return std::max(std::min(current_size * 2, max_size, SIZE_MAX), needed_size);
            }
    };

    /**
     * MemoryGrowthPolicyLinear: A policy that allows memory to grow linearly.
     * It increases the size by a fixed percentage or amount.
     */
    class MemoryGrowthPolicyLinear : public MemoryGrowthPolicy {
        public:
            virtual size_t grow_to_size(size_t needed_size, size_t current_size, size_t max_size) override {
                // Linear growth policy
                return std::max(std::min(current_size + (current_size / 2), max_size, SIZE_MAX), needed_size);
            }
    };

    /**
     * MemoryGrowthPolicyPercentage: A policy that allows memory to grow by a specified percentage.
     * It increases the size by a percentage of the current size.
     */
    class MemoryGrowthPolicyPercentage : public MemoryGrowthPolicy {
        private:
            double growth_percentage_;

        public:
            MemoryGrowthPolicyPercentage(double percentage=10) : growth_percentage_(percentage) {}

            virtual size_t grow_to_size(size_t needed_size, size_t current_size, size_t max_size) override {
                // Percentage growth policy
                return std::max(std::min(size_t(current_size * (1 + (growth_percentage_ / 100))), max_size, SIZE_MAX), needed_size);
            }
    };

    /**
     * Memory: A class that provides a growable memory structure that can store any type of data in any structure.
     * It is designed to be flexible and efficient, allowing for serialization to and from various formats such as JSON, CSV, etc.
     * The class can also handle memory mapping for large datasets.
     */
    class Memory {
        public:
            Memory(MemoryGrowthPolicy& growth_policy, size_t initial_size, size_t max_size=SIZE_MAX, bool lazy_init=false) 
            : growth_policy_(growth_policy), data_(nullptr), initial_size_(initial_size), max_size_(max_size), current_size_(0), lazy_init_(lazy_init) {
                // Constructor initializes the memory with a growth policy
            }

            virtual ~Memory() {
                
                if (data_) {
                    free(data_);
                }
            }

            void initialize(bool force_init = false) {
                if (lazy_init_ && !force_init) {
                    // Lazy initialization don't do anything yet
                } else {
                    // Eager initialization logic
                    data_ = calloc(initial_size_, 1);
                    if (!data_) {
                        throw std::runtime_error("Memory allocation failed");
                    }
                    current_size_ = initial_size_;
                }
            }

            void set_growth_policy(MemoryGrowthPolicy& growth_policy) {
                growth_policy_ = growth_policy;
            }

            void set_max_size(size_t max_size) {
                if (max_size < current_size_) {
                    throw std::runtime_error("New maximum size cannot be less than current size");
                }
                max_size_ = max_size;
            }

            size_t read(void* buffer, size_t size, size_t offset = 0) {
                if (offset + size > current_size_) {
                    throw std::out_of_range("Read exceeds current memory size");
                }
                memcpy(buffer, static_cast<char*>(data_) + offset, size);
                return size;
            }

            size_t write(const void* buffer, size_t size, size_t offset = 0) {
                
                if (offset + size > max_size_) {
                    throw std::out_of_range("Write exceeds maximum memory size");
                }

                if (offset + size > current_size_) {
                    
                    grow(offset + size);
                }
                memcpy(static_cast<char*>(data_) + offset, buffer, size);
                return size;
            }
            

        protected:
            MemoryGrowthPolicy& growth_policy_; // Reference to the growth policy
            void* data_ = nullptr;          // Pointer to the actual data
            size_t initial_size_ = 0;       // Size of the data in bytes
            size_t max_size_ = SIZE_MAX;    // Maximum size of the data in bytes
            size_t current_size_ = 0;       // Current size of the data in bytes
            bool lazy_init_ = false;  // Flag for lazy initialization

        private:            
            void grow(size_t needed_size) {
                if (needed_size > max_size_) {
                    throw std::runtime_error("Memory growth not allowed.  Allocation exceeds maximum size.");
                }
                // data_ will be nullptr if lazy initialization is used and not yet initialized
                if (data_ == nullptr) {
                    initialize(true);
                }
                else {
                    size_t required_size = growth_policy_.grow_to_size(needed_size, current_size_, max_size_);
                    if (required_size == current_size_) {
                        throw std::runtime_error("Memory growth not allowed.  Maximum size reached.");
                    }
                    void* new_data = realloc(data_, required_size);
                    if (!new_data) {    
                        throw std::runtime_error("Memory reallocation failed");
                    }
                    data_ = new_data;
                    memset(static_cast<char*>(data_) + current_size_, 0, required_size - current_size_);
                    current_size_ = required_size;
                }
                
                
                // Here you would typically reallocate memory to the new size
            }

    };


} // namespace pb