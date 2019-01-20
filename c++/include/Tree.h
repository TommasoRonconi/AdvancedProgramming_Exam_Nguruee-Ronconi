/**
 *  @file include/Tree.h
 *
 *  @brief The class Tree
 *
 *  This file defines the interface of the class Tree
 *
 *  @author Herbert Nguruwe, Tommaso Ronconi
 *
 *  @author hknguruwe@gmail.com, tronconi@sissa.it
 */


#ifndef __TREE__
#define __TREE__
#include <iostream>
#include <memory>
#include <Node.h>
#include <Iterator.h>


/**
 *  @class Tree Tree.h "include/Tree.h"
 *
 *  @brief The class Tree
 *
 *  This class is used to handle objects of type <EM> Tree
 *  </EM>. It is templated on two types T and U for the  
 *  <EM> key </EM> and <EM> value </EM> of the tree, respectively.
 */
template < class T, class U >
class Tree {

  using Node = struct Node< T, U >;
  
  /**
   *  @name Custom-types owned by the class Tree
   */
  ///@{

  // /**
  //  *  @class Node Tree.h "include/Tree.h"
  //  *
  //  *  @brief The class Node
  //  *
  //  *  This custom-type is used to handle objects of type <EM> Node
  //  *  </EM>. It is templated on two types T and U for the  
  //  *  <EM> key </EM> and <EM> value </EM> of the tree, respectively.
  //  *  The templated scheme is deduced from the owner class Tree.
  //  */
  // struct Node;

  ///@}


  /**
   *  @name Private variables of the class
   */
  ///@{

  /// The root node of the BST
  std::unique_ptr<Node> root = nullptr;

  /// The head of the BST
  Node * head = nullptr;

  /// The tail of the BST
  Node * tail = nullptr;

  void kernel_balance ( Tree& Tnew, Iterator< T, U > startpoint, size_t steps, Iterator< T, U > endpoint ); 

  ///@}
  
public:
  using Iterator = class Iterator< T, U >;
  using ConstIterator = class ConstIterator< T, U >;

  /**
   *  @name Friends of the class Tree
   */
  ///@{

  /// operator<< overload
  template < class ot, class ou >
    friend std::ostream& operator<< ( std::ostream&, Tree< ot, ou >& );

  /// operator[] overload, constant version
  // template < class ot, class ou >
  //   ou& operator[] ( const ot& key ) const;

  // /// operator[] overload, non-constant version
  // template < class ot, class ou >
  //   ou& operator[] ( const ot& key );

  ///@}

  /**
   *  @name Constructors/Destructor
   */
  ///@{


  /// default constructor
  Tree() = default;
  // Tree () { std::cout << "default ctor\n"; }

  // default copy semantic is fine
  Tree(const Tree&) = default;
  Tree& operator=(const Tree&) = default;

  // move semantic is fine as well
  Tree(Tree&&) = default;
  Tree& operator=(Tree&&) = default;
  
  ~Tree() noexcept = default;
  // ~Tree() noexcept { std::cout << "default dtor\n"; };

  ///@}

  /**
   *  @name Iterators declaration
   */
  ///@{

  // class Iterator;
  // class ConstIterator;
  Iterator begin() { return Iterator{ tail }; }
  Iterator end() { return Iterator{ nullptr }; }
  Iterator top() { return Iterator{ root.get() }; }

  ConstIterator cbegin() const { return ConstIterator{ tail }; }
  ConstIterator cend() const { return ConstIterator{ nullptr }; }
  ConstIterator ctop() const { return ConstIterator{ root.get() }; }

  ///@}

  /**
   *  @name Public functions of the class Tree
   */
  ///@{


  void insert ( const T key, const U value, const bool substitute );

  void clear () {

    root->clear();
    root.reset();
    
  }

  void balance ();

  Iterator find ( const T key, Iterator it );
 
  U& operator[]( const T key ) {

    Iterator n = find(key, top());
    if (n == end())
      insert(key,U{}, false);
    return n->value();
  }

  const U& operator[]( const T key ) const {
    return this->operator[]( key );
  }

  ///@}
  
  
}; // end of class Tree declaration


#include <Tree.tpp>

#endif //__TREE__
