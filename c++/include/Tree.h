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
#include <vector>
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
  
  /// structure 'Node<T,U>' to 'Node'
  using Node = struct Node< T, U >;

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

  ///@}

  /**
   *  @name Private functions of the class
   */
  ///@{


  /**
   *  @brief Templeted private function for in-place balance a section of the Tree. 
   *         The balanced section is saved in the right level of another Tree passed 
   *         by reference to the function.
   *         The implemented algorithm recursively splits the section in 2 parts, inserts the
   *         mid-point into T_new and calls itself again once for the first half and once
   *         for the second half of the remaining Nodes between startpoint and endpoint.
   *         If the value of steps is less than 1 it inserts the leftovers and exits.
   *
   *  @param [in] startpoint Iterator to point of Tree from which to start balancing
   *
   *  @param [in] endpoint Iterator to point of Tree where to stop balancing
   *
   *  @return void
   */
  void kernel_balance ( Iterator< T, U > here, const std::vector<Node*> nodes ); 

  ///@}
  
public:

  /// class 'Iterator< T, U >' to 'Iterator'
  using Iterator = class Iterator< T, U >;

  /// class 'ConstIterator< T, U >' to 'ConstIterator'
  using ConstIterator = class ConstIterator< T, U >;

  /**
   *  @name Friends of the class Tree
   */
  ///@{

  /// operator<< overload
  template < class ot, class ou >
    friend std::ostream& operator<< ( std::ostream&, Tree< ot, ou >& );
  
  ///@}

  /**
   *  @name Constructors/Destructor
   */
  ///@{


  /// default constructor
  Tree () = default;
  
  /// Copy-constructor builds new Tree by deep-coping argument Tree 
  Tree ( const Tree & T_other );

  /// Copy-assignment operator overload, assign to existing Tree
  /// a deep copy of some other Tree
  Tree& operator= ( const Tree & T_other ) {

    this->clear();
    auto tmp = T_other;
    (*this) = std::move( tmp );

    return *this;
    
  }

  /// move-constructor
  Tree ( Tree&& T_other ) : root{ std::move( T_other.root ) },
			    tail{ std::move( T_other.tail ) },
			    head{ std::move( T_other.head ) } {}

  /// move-assignment operator
  Tree& operator= ( Tree&& T_other ) {

    root = std::move( T_other.root );
    head = std::move( T_other.head );
    tail = std::move( T_other.tail );

    return *this;

  }

  // default denstructor
  ~Tree() noexcept = default;

  ///@}

  /**
   *  @name Iterators declaration
   */
  ///@{

  /// Iterator to the tail of the tree (aka the Node with smallest key)
  Iterator begin() { return Iterator{ tail }; }

  /// Iterator to nullptr (aka the parent of the Node with the largest key)
  Iterator end() { return Iterator{ nullptr }; }

  /// Iterator to the root of the tree (aka the highest level Node)
  Iterator top() { return Iterator{ root.get() }; }

  /// ConstIterator to the tail of the tree (aka the Node with smallest key)
  ConstIterator cbegin() const { return ConstIterator{ tail }; }

  /// ConstIterator to nullptr (aka the parent of the Node with the largest key)
  ConstIterator cend() const { return ConstIterator{ nullptr }; }

  /// ConstIterator to the root of the tree (aka the highest level Node)
  ConstIterator ctop() const { return ConstIterator{ root.get() }; }

  ///@}

  /**
   *  @name Public functions of the class Tree
   */
  ///@{

  /**
   *  @brief Templeted function to insert a new Node in the Tree.
   *         If the root already exists it calls function Node::insert, otherwise
   *         it inserts root.
   *
   *  @param key the key that will identify the new Node
   *
   *  @param value the value contained by the new Node
   *
   *  @param substitute <b>true</b>: substitute the value in Node if key is present<br/>
   *                    <b>false</b>: do not substitute and exit function
   *
   *  @return void
   */
  // void insert ( const T key, const U value, const bool substitute = false );
  
  Iterator insert ( const T key, const U value, const bool substitute = false );

  /**
   *  @brief Function to remove all Nodes from Tree. 
   *         Calls function Node<T, U>::clear() of <b>root</b> Node than resets <b>root</b>.
   *
   *  @return void
   */
  void clear () {

    root.reset();
    
  }

  /**
   *  @brief Function to balance the Tree.
   *         <ol>
   *         <li> Counts the number of Nodes composing the Tree;</li>
   *         <li> Allocate new object of class Tree;</li>
   *         <li> Call to private function Tree::kernel_balance() with arguments:
   *                   <ul>
   *                   <li><EM>T_new</EM>: newly allocated Tree</li>
   *                   <li><EM>begin()</EM>: Iterator to tail of the Tree</li>
   *                   <li><EM>steps</EM>: half of the size measured in Step 1</li>
   *                   <li><EM>end()</EM>: Iterator to end of the Tree</li>
   *                   </ul></li>
   *         <li> call function clear() from root of current Tree;</li>
   *         <li> move T_new to <b>*this</b>;</li>
   *         </ol>
   *
   *  @return void
   */
  void balance ();

  /**
   *  @brief Function to find an element with given key, starting from Tree root.
   *
   *  @param key constant key value to be searched
   *
   *  @return Iterator to position in Tree where key is found, if key is not found
   *  returns Iterator to end of Tree (i.e. nullptr)
   *
   */
  Iterator find ( const T key ) { return Iterator { root->find( key ) }; }

  /**
   *  @brief Function to find an element with given key, starting from Tree root.
   *
   *  @param key constant key value to be searched
   *
   *  @return ConstIterator to position in Tree where key is found, if key is not found
   *  returns ConstIterator to end of Tree (i.e. nullptr)
   *
   */
  ConstIterator find ( const T key ) const { return ConstIterator { root->find( key ) }; }
 
  /**
   *  @brief Array subscript operator overload
   *
   *  @param key the key of the Node
   *
   *  @return it returns a reference to the value contained in the Node.
   *  it the Node does not exist it creates one and inserts the default value
   *  of the type U.
   */
  U & operator[]( const T& key ) {

    Iterator n = find( key );
    
    if ( n == end() ) {
      
      n = insert( key, U{}, false );
      // n = find( key );
      
    }
    
    return n->value();
    
  }

  struct key_not_found {
    
    std::string message;
    key_not_found( const std::string &s ) : message{s} {}
    
  };

  /**
   *  @brief Array subscript operator overload, const version
   *
   *  @param
   *
   *  @return
   *
   */
  const U & operator[]( const T key ) const {
    
    ConstIterator n = find( key );
    
    if ( n == cend() )
      throw key_not_found{ "\nI'm sorry dave, I'm afraid I can't do that\n(key " +
	  std::to_string(key) +
	  " is not present.)"};
    
    return n->value();
    
  }

  ///@}
  
  
}; // end of class Tree declaration


#include <Tree.tpp>

#endif //__TREE__
