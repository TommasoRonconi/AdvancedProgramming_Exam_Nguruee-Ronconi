/**
 *  @file include/Iterator.h
 *
 *  @brief The classes Iterator and ConstIterator
 *
 *  This file defines the interface of the class Iterator and 
 *  of class ConstIterator
 *
 *  @author Herbert Nguruwe, Tommaso Ronconi
 *
 *  @author hknguruwe@gmail.com, tronconi@sissa.it
 */


#ifndef __ITERATOR__
#define __ITERATOR__

#include <memory>
#include <Node.h>

/**
 *  @class Iterator Iterator.h "include/Iterator.h"
 *
 *  @brief The class Iterator
 *
 *  This class is used to handle objects of type <EM> Iterator
 *  </EM>. It is templated on two types T and U for the  
 *  <EM> key </EM> and <EM> value </EM>, respectively, of the Node
 *  contained by the iterator is .
 */
template < class T, class U >
class Iterator {

  /// Type Node keyword definition
  using Node = struct Node<T, U>;

  /// Actual content of the Iterator: a pointer to some Node
  Node * current;
  
public:

  /// Default constructor
  Iterator () noexcept = default;

  /**
   *  @brief Custom constructor of iterator to some Node n
   *
   *  @param n raw pointer to the Node to which the Iterator will iterator
   *           (iterators gonna iterate..lol)
   */ 
  Iterator( Node * n ) : current{ n } {}

  /// De-reference operator overload, it returns a reference to the de-referenced object of
  /// class Node contained in the Iterator
  Node& operator*() { return *current; }

  /// Member-access operator overload, it returns the raw pointer to the object of class Node
  /// contained in the Iterator
  Node* operator->() const { return current;  }
  
  /**
   *  @brief Pre-increment operator overload, it copies into <b>*this</b> a pointer to 
   *         the next element in the Tree hierarchy.
   *
   *  @return A reference to the resulting iterator
   */
  Iterator& operator++() {

    if ( current ) {
      if ( current->right )
	current = current->right->leftmost() ;
      else
	current = current->parent;
    }
      
    return *this;
    
  }
  
  /**
   *  @brief Post-increment operator overload, implementation calls overloaded pre-increment 
   *         operator 
   *
   *  @return The resulting iterator
   */
  Iterator operator++( int ) {
    
    Iterator it{*this};
    
    ++(*this);
    
    return it;
    
  }
  
  /**
   *  @brief Logical-equality operator overload
   *
   *  @param other the r-value to be compared
   *
   *  @return bool, true if the two Iterator contain the same pointer, false if not
   */
  bool operator==(const Iterator& other) { return current == other.current; }
  
  /**
   *  @brief Logical-inequality operator overload
   *
   *  @param other the r-value to be compared
   *
   *  @return Implementation is done in terms of overloaded equality operator
   */
  bool operator!=(const Iterator& other) { return !( *this == other ); }
  
}; // end of class Iterator


// ===========================================================================


/**
 *  @class ConstIterator ConstIterator.h "include/Iterator.h"
 *
 *  @brief The class ConstIterator
 *
 *  This class is used to handle objects of type <EM> ConstIterator </EM>.
 *  It inherits from class Iterator and is templated on two types T and U for  
 *  the <EM> key </EM> and <EM> value </EM>, respectively, of the Node
 *  contained by the iterator is .
 */
template < class T, class U >
  class ConstIterator : public Iterator<T, U> {
  
  /// Type Node keyword definition
  using Node = struct Node<T, U>;
    
 public:
  
  /// 'parent' keyword definition, aliases the Iterator class 
  using parent = Iterator<T, U>;
  
  using parent::Iterator;

  /// De-reference operator overload (constant version), it returns a reference
  /// to the de-referenced object of class Node contained in the Iterator
  const Node* operator->() const { return parent::operator->();  }
  
  /// Member-access operator overload (constant version), it returns the
  /// raw pointer to the object of class Node contained in the Iterator
  const Node& operator*() const { return parent::operator*(); }
  
  using parent::operator==;
  
  using parent::operator!=;
  
}; // end of class ConstIterator

#endif //__ITERATOR__
