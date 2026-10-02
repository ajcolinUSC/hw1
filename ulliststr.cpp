#include "ulliststr.h"
#include <cstddef>
#include <stdexcept>

ULListStr::ULListStr() {
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr() { clear(); }

bool ULListStr::empty() const { return size_ == 0; }

size_t ULListStr::size() const { return size_; }

void ULListStr::push_front(const std::string &val) {
  if (head_ == NULL) {
    Item *n = new Item();
    head_ = n;
    tail_ = n;

    n->first = ARRSIZE;
    n->last = ARRSIZE;
    n->first = n->first - 1;
    n->val[n->first] = val;
    size_ = size_ + 1;
    return;
  }

  if (head_->first != 0) {
    head_->first--;
    head_->val[head_->first] = val;
    size_++;
  } else {
    Item *n = new Item();
    n->first = ARRSIZE;
    n->last = ARRSIZE;
    n->first--;
    n->val[n->first] = val;
    n->next = head_;
    head_->prev = n;
    head_ = n;
    size_++;
  }
}

void ULListStr::pop_back() {
  if (size_ == 0) {
    return;
  }
  tail_->last = tail_->last - 1;

  tail_->val[tail_->last] = "";
  size_--;

  if (tail_->first == tail_->last) {
    Item *temp = tail_;
    if (tail_->prev == NULL) {
      // that was the only node
      head_ = NULL;
      tail_ = NULL;
    } else {
      tail_ = tail_->prev;
      tail_->next = NULL;
    }
    delete temp;
  }
}

void ULListStr::push_back(const std::string &val) {
  if (tail_ == NULL) {
    Item *n = new Item();
    n->first = 0;
    n->last = 0;
    n->val[n->last] = val;
    n->last++;
    head_ = n;
    tail_ = n;
    size_++;
    return;
  }
  if (tail_->last < ARRSIZE) {
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
    return;
  }

  Item *n = new Item();
  n->first = 0;
  n->last = 0;
  n->val[0] = val;
  n->last = 1;
  n->prev = tail_;
  tail_->next = n;
  tail_ = n;
  size_++;
}

std::string const &ULListStr::front() const { return head_->val[head_->first]; }

void ULListStr::pop_front() {
  if (size_ == 0) {
    return;
  }
  head_->val[head_->first] = "";
  head_->first++;
  size_--;
  if (head_->first == head_->last) {
    Item *temp = head_;
    if (head_->next == NULL) {
      head_ = NULL;
      tail_ = NULL;
    } else {
      head_ = head_->next;
      head_->prev = NULL;
    }
    delete temp;
  }
}

std::string const &ULListStr::back() const {
  return tail_->val[tail_->last - 1];
}

std::string *ULListStr::getValAtLoc(size_t loc) const {
  if (loc >= size_) {
    return NULL;
  }
  Item *cur = head_;
  size_t left = loc;
  while (cur != NULL) {
    size_t num = cur->last - cur->first;
    if (left < num) {
      return &(cur->val[cur->first + left]);
    }
    left = left - num;
    cur = cur->next;
  }
  return NULL;
}

void ULListStr::set(size_t loc, const std::string &val) {
  std::string *ptr = getValAtLoc(loc);
  if (ptr == NULL) {
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string &ULListStr::get(size_t loc) {
  std::string *ptr = getValAtLoc(loc);
  if (ptr == NULL) {
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const &ULListStr::get(size_t loc) const {
  std::string *ptr = getValAtLoc(loc);
  if (ptr == NULL) {
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear() {
  while (head_ != NULL) {
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
