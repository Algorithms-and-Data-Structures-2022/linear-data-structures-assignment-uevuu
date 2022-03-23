#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }

    capacity_ = capacity;

    data_ = new int[capacity_]{};
  }

  DynamicArray::~DynamicArray() {
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
    data_ = nullptr;
  }

  void DynamicArray::Add(int value) {
    // Write your code here ...
    if (size_ + 1 > capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }
    data_[size_] = value;
    size_ += 1;
  }

  bool DynamicArray::Insert(int index, int value) {
    // Write your code here ...
    if (index >= 0 and index <= size_) {
      if (size_ == capacity_) {
        Resize(capacity_ + kCapacityGrowthCoefficient);
      }
      int* arr = new int[capacity_]{};
      for (int i = 0; i < index; i++) {
        arr[i] = data_[i];
      }
      arr[index] = value;
      for (int i = index; i < size_; i++) {
        arr[i + 1] = data_[i];
      }
      data_ = arr;
      size_ += 1;
      return true;
    }
    return false;
  }

  bool DynamicArray::Set(int index, int new_value) {
    // Write your code here ...
    if (index < size_ and index >= 0) {
      data_[index] = new_value;
      return true;
    }
    return false;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    // Write your code here ...
    if (index >= 0 and index < size_) {
      int del_item = data_[index];
      for (int i = index; i < size_; i++) {
        data_[i] = data_[i + 1];
      }
      size_ -= 1;
      return del_item;
    }
    return std::nullopt;
  }

  void DynamicArray::Clear() {
    data_ = nullptr;
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if (index >= 0 and index < size_) {
      return data_[index];
    }
    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    // Write your code here ...
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    // Write your code here ...
    if (new_capacity > capacity_) {
      int* arr = new int[new_capacity]{};
      for (int i = 0; i < capacity_; i++) {
        arr[i] = data_[i];
      }
      data_ = arr;
      capacity_ = new_capacity;
      return true;
    }
    return false;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment