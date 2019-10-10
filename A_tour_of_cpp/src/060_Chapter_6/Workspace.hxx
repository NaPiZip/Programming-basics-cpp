// Copyright 2019, Nawin

template<typename T>
section_6_2::Vector<T>::Vector(int sz) : element_{ new T[sz] }, sz_{sz} {
  for (auto idx = 0; idx != sz_; ++idx) {
    element_[idx] = 0;
  }
}

template<typename T>
section_6_2::Vector<T>::Vector(std::initializer_list<T> list) :
  element_{ new T[list.size()] },
  sz_{ static_cast<int>(list.size()) } {
  int idx = 0;
  for (auto item : list) {
    element_[idx++] = item;
  }
}

template<typename T>
section_6_2::Vector<T>::Vector(const Vector<T>& v) :
  element_{ new T[v.sz_] },
  sz_{ v.sz_ } {
  for (auto idx = 0; idx != sz_; ++idx) {
    element_[idx] = v.element_[idx];
  }
}

template<typename T>
T& section_6_2::Vector<T>::operator[](int i) {
  return element_[i];
}

template<typename T>
const T& section_6_2::Vector<T>::operator[](int i) const {
  return element_[i];
}

template<typename T>
void section_6_2::Vector<T>::push_back(T val) {
  T* new_data = new T[sz_ + 1];
  for (auto idx = 0; idx != sz_; ++idx)
  {
    new_data[idx] = element_[idx];
  }
  delete[] element_;
  element_ = new_data;
  element_[sz_++] = val;
}

template<typename T>
T* section_6_2::Vector<T>::begin() {
  return size() ? &(*this)[0] : nullptr;
}

template<typename T>
T* section_6_2::Vector<T>::end() {
  return size() ? &(*this)[0]+size() : nullptr;
}

template<typename T>
int section_6_2::Vector<T>::size() const {
  return sz_;
}

template<typename T>
template<typename Iter>
section_6_2::Vector2<T>::Vector2(Iter b, Iter e) : Vector<T>(0){
  // @TODO ask in Slack how this works
}