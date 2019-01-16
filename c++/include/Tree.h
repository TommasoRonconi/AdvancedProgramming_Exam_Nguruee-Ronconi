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


#ifdef __TREE__
#define __TREE__
#include <iostream>

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
   *  @struct Node Tree.h "include/Tree.h"
   *
   *  @brief The class Node
   *
   *  This custom-type is used to handle objects of type <EM> Node
   *  </EM>. It is templated on two types T and U for the  
   *  <EM> key </EM> and <EM> value </EM> of the tree, respectively.
   *  The templated scheme is deduced from the owner class Tree.
   */
  struct Node {
    T key;
    U val;
    std::unique_ptr<Node> parent;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    /* Node(const T& v, Node* n) : val{v}, next{n} {} */
    /* ~Node() = default; */
  };

  ///@}


  /**
   *  @name Private variables of the class
   */
  ///@{

  /// The root node of the BST
  std::unique_ptr<Node> root;

  /// The head of the BST
  std::unique_ptr<Node> head;

  /// The tail of the BST
  std::unique_ptr<Node> tail;

  ///@}

 public:

  /**
   *  @name Friends of the class Tree
   */
  ///@{

  /// operator<< overload
  template < class ot, class ou >
    friend std::ostream& operator<<(std::ostream&, const Tree< ot, ou >&);

  /// operator[] overload, constant version
  template < class ot, class ou >
    friend ou& operator[] ( const ot& key ) const;

  /// operator[] overload, non-constant version
  template < class ot, class ou >
    friend ou& operator[] ( const ot& key );

  ///@}

  /**
   *  @name Constructors/Destructor
   */
  ///@{
  
  Tree() = default;
  
  ~Tree() = default;

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

  void insert ( Node * new, const bool substitute );

  void clear ();

  void balance ();

  ConstIterator find ( const T key );

  ///@}
  
};


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


// ===========================================================================


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