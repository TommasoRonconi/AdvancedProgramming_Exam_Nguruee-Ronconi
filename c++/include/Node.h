#ifndef __NODE__
#define __NODE__

#include <memory>
#include <utility>
#include <BST_utility.h>

template< class T, class U >
struct Node {

  /// Content of the node
  std::pair< T, U > content;
    
  /// Pointer to parent Node
  std::unique_ptr<Node> parent = nullptr;

  /// Pointer to left Node
  std::unique_ptr<Node> left = nullptr;

  /// Pointer to right Node
  std::unique_ptr<Node> right = nullptr;

  /**
   *  @name Constructors/Destructor
   */
  ///@{

  Node () : content{ std::make_pair<T, U>() }, parent{ nullptr } {}

  Node ( T key, U value, std::unique_ptr<Node> par = nullptr )
    : content{ std::make_pair<T,U>( key, value ) }, parent{par} {}
  /* Node(const T& v, Node* n) : val{v}, next{n} {} */

  ~Node() = default;

  ///@}

  /**
   *  @name Public functions of the struct Node
   */
  ///@{

  T key() { return content.first; }

  U value() { return content.second; }


  /**
   *  @brief get the pointer corresponding to bst::direction
   *  
   *  @param dir the direction to take
   *
   *  @return pointer to child in the given direction
   */
  std::unique_ptr<Node> get_direction ( bst::direction dir ) {
      
    if ( dir == bst::direction::left ) return left;
    else return right;
      
  }    

  ///@}
    
}; // end of class Node

#endif //__NODE__
