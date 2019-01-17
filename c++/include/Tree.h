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
#include <utility>
#include <memory>
#include <BST_utility.h>



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

  /**
   *  @name Custom-types owned by the class Tree
   */
  ///@{

  /**
   *  @class Node Tree.h "include/Tree.h"
   *
   *  @brief The class Node
   *
   *  This custom-type is used to handle objects of type <EM> Node
   *  </EM>. It is templated on two types T and U for the  
   *  <EM> key </EM> and <EM> value </EM> of the tree, respectively.
   *  The templated scheme is deduced from the owner class Tree.
   */
  struct Node : public std::pair< T, U > {

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

    Node ( T key, U value, std::unique_ptr<Node> par )
      : std::pair< T, U >{ key, value }, parent{par} {}
    /* Node(const T& v, Node* n) : val{v}, next{n} {} */

    ~Node() = default;

  ///@}

  /**
   *  @name Public functions of the struct Node
   */
  ///@{


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


    /**
     *  @brief set the pointer corresponding to bst::direction
     *  
     *  @param dir the direction to set
     *  
     *  @param new_child pointer to the new child
     *
     *  @return none
     */
    void set_at_direction ( bst::direction dir, std::unique_ptr<Node> new_child ) {
      
      if ( dir == bst::direction::left ) left = new_child;
      else return right = new_child;
      
    }

    

  ///@}
    
  };

  ///@}


  /**
   *  @name Private variables of the class
   */
  ///@{

  /// The root node of the BST
  std::unique_ptr<Node> root = nullptr;

  /// The head of the BST
  std::unique_ptr<Node> head = nullptr;

  /// The tail of the BST
  std::unique_ptr<Node> tail = nullptr;

  ///@}

  /**
   *  @name Private functions of the class
   */
  ///@{
  void m_insert(std::unique_ptr<Node> &newnode, const bool substitute);
  ///@}

public:

  /**
   *  @name Friends of the class Tree
   */
  ///@{

  /// operator<< overload
  template < class ot, class ou >
    friend std::ostream& operator<< ( std::ostream&, const Tree< ot, ou >& );

  /// operator[] overload, constant version
  template < class ot, class ou >
    ou& operator[] ( const ot& key ) const;

  /// operator[] overload, non-constant version
  template < class ot, class ou >
    ou& operator[] ( const ot& key );

  ///@}

  /**
   *  @name Constructors/Destructor
   */
  ///@{
  
  Tree() = default;

  /////////////////////////
  /// Copy semantics:

  Tree( const Tree & t );

  Tree& operator= (const Tree& t);
  /// end of copy semantics
  /////////////////////////

  /////////////////////////
  // move semantics

  // move ctor
  Tree(Tree&& v) noexcept = default/*: _size{std::move(v._size)}, elem{std::move(v.elem)} */;

  // move assignment
  Tree& operator=(Tree&& v) noexcept = default;/*  { */
  /*   std::cout << "move assignment\n"; */
  /*   _size = std::move(v._size); */
  /*   elem = std::move(v.elem); */
  /*   return *this; */
  /* } */

  // end move semantics
  /////////////////////////
  
  ~Tree() noexcept = default;

  ///@}

  /**
   *  @name Iterators declaration
   */
  ///@{

  class Iterator;
  class ConstIterator;
  Iterator begin() { return Iterator{ head.get() }; }
  Iterator end() { return Iterator{ tail.get() }; }
  Iterator top() { return Iterator{ root.get() }; }

  ConstIterator cbegin() const { return ConstIterator{ head.get() }; }
  ConstIterator cend() const { return ConstIterator{ tail.get() }; }
  ConstIterator ctop() const { return ConstIterator{ root.get() }; }

  ///@}

  /**
   *  @name Public functions of the class Tree
   */
  ///@{


  void insert (const T key, const U value, const bool substitute );

  void clear ();

  void balance ();

  ConstIterator find ( const T key );

  ///@}
  
};

template < class T, class U >
  std::ostream& operator<< (std::ostream& os, const Tree< T,U >& t) {
  
  /* for (const auto& x : l) */
  /*   os << x << " "; */
  
  return os;
}

/* template <typename T> */
/* void Tree<T>::push_back(const T& t) { */
/*   auto tmp = head.get(); */
/*   while (tmp->next != nullptr) {  // equivalent while(tmp->next) */
/*     tmp = tmp->next.get(); */
/*   } */
/*   tmp->next.reset(new Node{t, nullptr}); */
/* } */

// ===========================================================================


template < class T, class U >
  class Tree<T, U>::Iterator {
  using Node = Tree<T, U>::Node;

  Node* current;

 public:
  Iterator(Node* n) : current{n} {}
  T& operator*() const { return current->val; }
  Iterator& operator++() {
    current = current->next.get();
    return *this;
  }
  // Iterator operator++(int){
  //   Iterator it{*this};
  //   ++(*this);
  //   return it;
  // }
  bool operator==(const Iterator& other) { return current == other.current; }
  bool operator!=(const Iterator& other) { return !(*this == other); }
};


/* // =========================================================================== */


template < class T, class U >
  class Tree<T, U>::ConstIterator : public Tree<T, U>::Iterator {
 public:
    using parent = Tree<T, U>::Iterator;
  using parent::Iterator;
  const T& operator*() const { return parent::operator*(); }
  // using parent::operator==;
  // using parent::operator!=;
};




#endif
