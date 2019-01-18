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
  Node * parent = nullptr;

  /// Pointer to left Node
  std::unique_ptr<Node> left = nullptr;

  /// Pointer to right Node
  std::unique_ptr<Node> right = nullptr;

  /**
   *  @name Constructors/Destructor
   */
  ///@{

  /// default constructor
  Node () : content{ std::pair<T, U>{} }, parent{ nullptr } {}

  /// constructor that takes a key and a value as the input
  Node ( T key, U value )
    : content{ std::pair<T,U>( key, value ) } {}
  /* Node(const T& v, Node* n) : val{v}, next{n} {} */

  // ==================== copy/move ===================
  // /// copy-constructor
  // Node( const Node & n ) : content{ n.content } {}

  // /// copy-assignment overload ( just copies the content of node into a new Node with left, right, parent all pointing to nullptr )
  // Node& operator= ( const Node& n ) {
    
  //   return Node{ n.key(), n.value() };
    
  // }

  /// move-constructor
  // Node( Node && n ) noexcept
  //   : content{std::move(n.content)},
  //     parent{std::move(n.parent)},
  //     left{std::move(n.left)},
  //     right{std::move(n.right)} {}

  // /// move assignment
  // Node& operator=(Node&& n) noexcept  {

  //   content = std::move(n.content);
  //   parent = std::move(n.parent);
  //   left = std::move(n.left);
  //   right = std::move(n.right);
    
  //   return *this;
    
  // }
  // ==================================================
  

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
      
    if ( dir == bst::direction::left ) return std::move( left );
    else return std::move( right );
      
  }    


  /**
   *  @brief 
   *
   *  @param newnode reference to unique_ptr to Node
   *  
   *  @param dir the direction to take
   *
   *  @return 
   */
  void new_node ( std::unique_ptr<Node> & newnode, bst::direction dir ) {

    std::unique_ptr<Node> tmp = std::move( parent );
    if ( dir == bst::direction::left ) {
      left = std::move( newnode );
      newnode->parent = std::unique_ptr<Node>( this );
    }
    else {
      right = std::move( newnode );
      // newnode->parent = std::unique_ptr<Node>( parent.get() );
      // newnode->parent->operator=( * std::move(parent) );
      // newnode->parent = nullptr;
      // newnode->parent = std::move( parent );
      newnode->parent = std::make_unique< Node > ( *parent.get() );
      std::cout << "check\n";
    }
      
  }    

  ///@}
    
}; // end of class Node

#endif //__NODE__
