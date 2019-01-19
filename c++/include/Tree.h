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
  
  /// copy-constructor
  // Tree( const Tree & t );

  // /// copy-assignment overload
  // Tree& operator= (const Tree& t);

  
  // /// move ctor
  // Tree ( Tree< T, U >&& t ) noexcept
  //   : root{ t.root },
  //     head{ t.head },
  //     tail{ t.tail } {}
  //   // : root{ std::move( t.root ) },
  //   //   head{ std::move( t.head ) },
  //   //   tail{ std::move( t.tail ) } {}

  // /// move assignment
  // Tree& operator=( Tree< T, U >&& t ) noexcept  {
    
  //   root = std::move(t.root);
  //   head = t.head;
  //   tail = t.tail;
  //   // head = std::move(t.head);
  //   // tail = std::move(t.tail);
    
  //   return *this;
  // }
  
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


  void insert ( const T key, const U value, const bool substitute ) {

    if ( root ) {
      root->insert( key, value, substitute );
      if ( key < tail->key() ) tail = tail->left.get();
      if ( key > head->key() ) head = head->right.get();
    }
    else {
      root.reset( new Node{ key, value } );
      tail = root.get();
      head = root.get();
    }

  }

  void clear () {

    root->clear();
    root.reset();
    
  }

  void balance ();

  Iterator find ( const T key, Iterator it ) {

    if ( key == it->key() )
      return it;

    if ( key < it->key() && ( it->left ) )
      return find( key, Iterator( it->left.get() ) );

    if ( key < it->key() && !( it->left ))
      return end();

    if ( key > it->key() && (it->right))
      return find( key, Iterator( it->right.get() ) );

    if ( key > it->key() && !(it->right))
      return end();

    return end();
    
  }

 
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
  
  
}; // end of class Tree

template < class ot, class ou >
  std::ostream& operator<< (std::ostream& os, Tree< ot, ou >& t) {
  
  Iterator< ot, ou > it = t.begin();
  Iterator< ot, ou > stop { t.head };
  while ( it != stop ) {
    os << it->key() << ":\t" << it->value() << "\n";
    ++it;
  }

  os << it->key() << ":\t" << it->value();

  return os;
  
}

// ===========================================================================


template < class T, class U >
void Tree< T, U >::balance() {

  size_t size = 0;

  Iterator it = begin();

  while ( it != end() ) { ++size; ++it; }
  std::cout << "check " << size << std::endl;

  Tree< T, U > T_new {};
  
  kernel_balance( T_new, begin(), 0.5 * size, end() );

  /* here calls the recursive function */

  // last step:
  // ( with the hope that the new tree's nodes do not go
  //   out of scope when exiting balance() function )
  root->clear();
  // auto temp = T_new.top().operator->() ;
  // root.reset( temp );
  // root.reset( T_new.top().operator->() );
  // tail = std::move( T_new.end().operator->() );
  *this = std::move( T_new );
  
}

// ===========================================================================


template < class T, class U >
void Tree< T, U >::kernel_balance( Tree& T_new, Iterator startpoint, size_t steps, Iterator endpoint ) {

  Iterator it = startpoint;
  size_t ii = 0;


  if ( steps/2 > 2 ) {

    for ( ; ii < steps; ++ii, ++it );
    std::cout << "inserted: " << it->key() << "  " << it->value() << std::endl;
    T_new.insert( it->key(), it->value(), true );
    
    kernel_balance ( T_new, startpoint, ( steps/2 - 1), it );
    kernel_balance ( T_new, ++it, steps/2, endpoint );
    
  }
  else {
    while ( it != endpoint ) {
      
      std::cout << "inserted: " << it->key() << "  " << it->value() << std::endl;
      T_new.insert( it->key(), it->value(), true );
      ++it;

    } 
  }
  
  
}


// ===========================================================================


#endif //__TREE__
