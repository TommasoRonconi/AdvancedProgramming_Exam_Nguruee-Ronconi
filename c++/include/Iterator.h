#ifndef __ITERATOR__
#define __ITERATOR__

#include <memory>
#include <Node.h>

template < class T, class U >
class Iterator {
  
  using Node = struct Node<T, U>;
  
  std::unique_ptr<Node> current;
  
public:
  
  Iterator( std::unique_ptr<Node> n ) : current{ n } {}

  U& operator*() const { return current->value(); }

  std::unique_ptr<Node> &operator->() const {
    
    return current.get();
    
  }
  
  Iterator& operator++() {

    if ( current->right() )
      current = current->right->leftmost();
    else
      current = current->parent();
      
    return *this;
    
  }
  
  Iterator operator++(int){
    
    Iterator it{*this};
    
    ++(*this);
    
    return it;
    
  }
  
  bool operator==(const Iterator& other) { return current == other.current; }
  
  bool operator!=(const Iterator& other) { return !(*this == other); }
  
};


/* // =========================================================================== */


template < class T, class U >
  class ConstIterator : public Iterator<T, U> {
    
 public:
    using parent = Iterator<T, U>;
    // using parent::Iterator<T, U>;
    const U& operator*() const { return parent::operator*(); }
    // using parent::operator==;
    // using parent::operator!=;
};

#endif //__ITERATOR__