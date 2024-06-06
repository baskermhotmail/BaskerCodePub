#pragma once
template <typename T> class List;
template <typename T> class ListIter;
#include <iostream>
using namespace std;
///
// All template definitions must be in header files. So no .cpp file for List
///
template <typename T> class ListImpl { // Implementation class
  ListImpl<T>* prev;
  ListImpl<T>* next;
  T value;
 ListImpl(const T& actualValue, ListImpl* prevImpl = nullptr, ListImpl* nextImpl = nullptr):value(actualValue),prev(prevImpl),next(nextImpl)
    {}
  ListImpl(const ListImpl& ref)=delete;
  ListImpl( ListImpl&& ref)=delete;
  ListImpl& operator= (const ListImpl& ref) =delete;
  ListImpl& operator= (ListImpl&& ref) =delete;
  ~ListImpl() {};
  friend List<T>;
  friend ListIter<T>;
};

template <typename T> class List {
  friend ListIter<T>;
  unsigned size_=0;
  ListImpl<T>* listImpl_ = nullptr;
  ListImpl<T>* frontImpl_=nullptr;
  ListImpl<T>* backImpl_=nullptr;
  List(const List& ref)=delete;
  List( List&& ref)=delete;
  List& operator= (const List& ref) =delete;
  List& operator= (List&& ref) =delete;
public:
  List(){}// Default constructor
  ~List() {clear();} // Destructor
  void push_back(const T& value) // Add to the end
  {
    ListImpl<T>* currentBack = backImpl_;
    if(listImpl_) {
      backImpl_->next = new ListImpl<T>(value,currentBack);
      backImpl_ = backImpl_->next;
    } else {
      listImpl_ = new ListImpl<T>(value);
      frontImpl_ = listImpl_;
      backImpl_ = listImpl_;
    }
    size_++;
  }
  void push_front(const T& value) { // Add to the front
    ListImpl<T>* currentFront = frontImpl_;
    if(listImpl_) {
      frontImpl_->prev = new ListImpl<T>(value,0,currentFront);
      frontImpl_ = frontImpl_->prev;
      listImpl_ = frontImpl_;
    } else {
      listImpl_ = new ListImpl<T>(value);
      frontImpl_ = listImpl_;
      backImpl_ = listImpl_;
    }
    size_++;
  }
  void pop_back(){ // remove last elem    
    if( backImpl_) {
      if( backImpl_->prev){
	ListImpl<T>* tmpImpl = backImpl_->prev;
	delete backImpl_;
	backImpl_ = tmpImpl;
	backImpl_->next = nullptr;
	size_--;
      } else if(size_ == 1) {
	delete listImpl_;
	frontImpl_ = backImpl_ = listImpl_ =nullptr;
	size_ =0;
      } else { // empty list. Do nothing.
      }
    }    
  }
  void pop_front(){ // remove first elem
    
    if( frontImpl_) {
      if( frontImpl_->next){
	ListImpl<T>* tmpImpl = frontImpl_->next;
	delete frontImpl_;
	frontImpl_ = tmpImpl;
	frontImpl_->prev = nullptr;
	listImpl_= frontImpl_;
	size_--;
      } else if(size_ == 1) {
	delete listImpl_;
	frontImpl_ = backImpl_ = listImpl_ =nullptr;
	size_ =0;
      } else { // empty list. Do nothing.
      }
    }    

  }
  const T& back()const{ // Last elem value
    return backImpl_->value;
  }
  const T& front()const{ // First elem value
    return frontImpl_->value;
  }
  void print(const char separator= ' ',std::ostream& out = std::cout)const{
    // Printing function with a single character separator 
    ListImpl<T> *implPtr= listImpl_;
    if(!implPtr){
      out << endl;
      return;
    }
    out << implPtr->value ;
    implPtr = implPtr->next;
    while(implPtr) {
      out << separator <<implPtr->value ;
      implPtr = implPtr->next;
    }
    out << std::endl;
  }
  void print(const char* separator,std::ostream &out = std::cout)const{
      // Printing function with a string separator 
    ListImpl<T> *implPtr= listImpl_;
    if(!implPtr){
      out << endl;
      return;
    }
    out << implPtr->value ;
    implPtr = implPtr->next;
    while(implPtr) {
      out << separator <<implPtr->value ;
      implPtr = implPtr->next;
    }
    out << std::endl;
  }
  void remove(const T& t);// Remove the first element matching the value
  void remove_all(const T& t); // Remove all elements matcching the value
  unsigned size()const {return size_;} // Returns size
  bool empty() const {return size_ == 0;} // Checks emptiness
  void clear() { // Clears out all entries.
    ListImpl<T>* impl= listImpl_;
    size_ = 0;
    frontImpl_ = backImpl_ = listImpl_ = nullptr;
    while(impl) {
      ListImpl<T> *next = impl->next;
      delete impl;
      impl = next;
    }
  }
};
//Utility class iterator
template <typename T> class ListIter {
  friend List<T>;
  static void remove(List<T>& list, const T& t);
  static void remove_all(List<T>& list, const T& t);
    ListIter(const ListIter& ref)=delete;
  ListIter( ListIter&& ref)=delete;
  ListIter& operator= (const ListIter& ref) =delete;
  ListIter& operator= (ListIter&& ref) =delete;
  ListIter()=delete;
  // Just static methods. No constructors
};

  template <typename T>  void List<T>::remove(const T& t)
  {
    ListIter<T>::remove(*this,t);
  }


  template <typename T> void List<T>::remove_all(const T& t)
  {
    ListIter<T>::remove_all(*this,t);
  }
  template <typename T>  void ListIter<T>::remove_all(List<T>& list, const  T& t)
  {
    ListImpl<T> *impl = list.listImpl_;
    while(impl) {
      if(impl->value == t) {
	if(impl == list.frontImpl_) {
	  list.pop_front();
          impl = list.frontImpl_;continue;	  
	} else if(impl == list.backImpl_) {
	  list.pop_back(); return;
	} else { // It's in the middle
	  ListImpl<T>* prev = impl->prev;
	  ListImpl<T>* next = impl->next;
	  prev->next = next;
	  next->prev = prev;
	  delete impl;
	  impl = prev;
	  list.size_--;
	}
      }
      impl = impl->next;
    }
  }

  template <typename T> void ListIter<T>::remove(List<T>& list, const  T& t)
  {
    ListImpl<T> *impl = list.listImpl_;
    while(impl) {
      if(impl->value == t) {
	if(impl == list.frontImpl_) {
	  list.pop_front(); return;
	} else if(impl == list.backImpl_) {
	  list.pop_back(); return;
	} else {
	  ListImpl<T>* prev = impl-> prev;
	  ListImpl<T>* next = impl->next;
	  prev->next = next;
	  next->prev = prev;
	  list.size_--;
	  delete impl;
	  return;
	}
      }
      impl = impl->next; 
    }
  }
