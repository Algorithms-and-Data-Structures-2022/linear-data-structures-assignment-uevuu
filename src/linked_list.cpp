#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    // Write your code here ...
    Node* new_node = new Node(value);
    if (size_ == 0) {
      front_ = new_node;
    } else {
      back_->next = new_node;
    }
    back_ = new_node;
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index >= 0 and index <= size_) {
      Node* node = new Node(value);
      if (index == 0) {
        node->next = front_;
        front_ = node;
        if (size_ == 0) {
          back_ = front_;
        }
        size_ += 1;
        return true;
      }
      if (index == size_) {
        back_->next = node;
        back_ = node;
        size_ += 1;
        return true;
      } else {
        Node* curr_node = front_;
        for (int i = 0; i < index - 1; i++) {
          curr_node = curr_node->next;
        }
        node->next = curr_node->next;
        curr_node->next = node;
        size_ += 1;
        return true;
      }
    }
    return false;
  }

  bool LinkedList::Set(int index, int new_value) {
    Node* now_node = front_;
    for (int i = 0; i != size_; i++) {
      if (index == i) {
        now_node->value = new_value;
        return true;
      }
      now_node = now_node->next;
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index < size_ and index >= 0) {
      Node* del_node = front_;
      size_ -= 1;
      if (index == 0) {
        front_ = front_->next;
        return del_node->value;
      }
      for (int i = 0; i < index - 1; i++) {
        del_node = del_node->next;
      }
      int del_value = del_node->next->value;
      del_node->next = del_node->next->next;
      return del_value;
    }
    return std::nullopt;
  }

  void LinkedList::Clear() {
    for (Node* curr = front_; curr != nullptr; /* */) {
      Node* node_to_remove = curr;
      curr = curr->next;
      delete node_to_remove;
    }
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    Node* now_node = front_;
    for (int i = 0; i != size_; i++) {
      if (index == i) {
        return now_node->value;
      }
      now_node = now_node->next;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* now_node = front_;
    for (int i = 0; i != size_; i++) {
      if (now_node->value == value) {
        return i;
      }
      now_node = now_node->next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node* now_node = front_;
    for (int i = 0; i != size_; i++) {
      if (now_node->value == value) {
        return true;
      }
      now_node = now_node->next;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr) {
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr) {
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    // Write your code here ...
    Node* now_node = front_;
    for (int i = 0; i != size_; i++) {
      if (index == i) {
        return now_node;
      }
      now_node = now_node->next;
    }
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment