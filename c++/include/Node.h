/**
 *  @file include/Node.h
 *
 *  @brief The class Node
 *
 *  This file defines the interface of the class Node
 *
 *  @author Herbert Nguruwe, Tommaso Ronconi
 *
 *  @author hknguruwe@gmail.com, tronconi@sissa.it
 */


#ifndef __NODE__
#define __NODE__

#include <memory>
#include <utility>


/**
 *  @class Node Node.h "include/Node.h"
 *
 *  @brief The class Node
 *
 *  This class is used to handle objects of type <EM> Node
 *  </EM>. It is templated on two types T and U for the  
 *  <EM> key </EM> and <EM> value </EM> retained by the Node, respectively.
 */
template< class T, class U >
struct Node {

  /// Content of the node, a std::pair templated on the key (first
  /// argument of pair) and value (second argument of std::pair) types
  std::pair< T, U > content;
    
  /// Raw pointer to parent Node
  Node * parent = nullptr;

  /// Pointer to left Node (std::unique_ptr)
  std::unique_ptr<Node> left = nullptr;

  /// Pointer to right Node (std::unique_ptr)
  std::unique_ptr<Node> right = nullptr;

  /**
   *  @name Constructors/Destructor
   */
  ///@{

  /// default constructor
  Node () : content{ std::pair<T, U>{} }, parent{ nullptr } {}

  /**
   *  @brief Constructor that builds a new Node setting the content and position wrt parent
   *
   *  @param key the key of the Node
   *
   *  @param value the value contained in the Node
   *
   *  @param par parent Node to which the Node is attached (default = nullptr)
   */
  Node ( T key, U value, Node * par = nullptr )
    : content{ std::pair<T,U>( key, value ) }, parent{ par } {}

  
  // ==================================================
  

  /// default destructor of Node
  ~Node() = default;

  ///@}

  /**
   *  @name Public functions of the struct Node
   */
  ///@{

  /// returns the key of the Node
  const T& key() const { return content.first; }

  /// returns the value of the Node
  const U& value() const { return content.second; }

  /// returns the value of the Node
  U& value() { return content.second; }

  Node * find ( const T key );

  /**
   *  @brief Recursive function to insert a new Node lower in hierarchy with respect
   *         to current Node. If Node has no childs it inserts the new one as the 
   *         correct new child, otherwise calls itself again from the right child of
   *         current Node.
   *
   *  @param key key of the new Node to be generated
   *  
   *  @param value value of the new Node to be generated
   *
   *  @param substitute whether to substitute or not the value if a Node with same 
   *                    key  exists
   *
   *  @return void
   */
  Node * insert ( const T key, const U value, const bool substitute = false );

  /**
   *  @brief Recursive function to find the leftmost Node in hierarchy from current
   *
   *  @return Raw pointer to leftmost Node, if current has no left child returns <b>this</b>
   */
  Node * leftmost () {

    if ( left )
      return left->leftmost();
    else
      return this;
   
  }

  /**
   *  @brief Recursive function for removing all nodes lower in hierarchy than current.
   *         If current has left/right child calls itself again from left/right 
   *         than resets left/right.
   *
   *  @return void
   */
  void clear () {

    // reset everything on the left
    left.reset();

    // reset everything on the right
    right.reset();
    
  }


  ///@}
    
}; // end of class Node

#include <Node.tpp>

#endif //__NODE__
