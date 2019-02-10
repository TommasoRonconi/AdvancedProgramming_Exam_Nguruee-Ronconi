/**
 *  @file tpl/Tree.tpp
 *
 *  @brief Definition of templated functions of class Tree
 *
 *  This file defines the interface of the templated functions of the class Tree
 *  It is included at the end of the header file include/Tree.h.
 *  Implementing the definition of the class member functions in a separate
 *  file allows us to maintain an ordered structure, while using this strategy
 *  instead of declaring each possible setting of the templated types keeps the
 *  generality of the class.
 *
 *  @author Herbert Nguruwe, Tommaso Ronconi
 *
 *  @author hknguruwe@gmail.com, tronconi@sissa.it
 */



// ===========================================================================


template < class ot, class ou >
std::ostream& operator<< (std::ostream& os, Tree< ot, ou >& t) {
  
  Iterator< ot, ou > it = t.begin();
  
  if ( it.operator->() ) {
    Iterator< ot, ou > stop = t.end();
    while ( it != stop ) {
      os << it->key() << ":\t" << it->value() << "\n";
      ++it;
    }

  }
  else os << "Empty Tree!";

  return os;
  
}


// ===========================================================================


template < class T, class U >
Tree< T, U >::Tree ( const Tree & T_other ) {

  // Lambda-function making recursive new insertions
  // from top to bottom of hierarchy, starting from some ConstIterator
  std::function< void ( ConstIterator ) > deep_copy =
    [ this, &deep_copy ] ( ConstIterator it ) {
    
    insert( it->key(), it->value() );
    
    if ( it->left )
      deep_copy( ConstIterator{ it->left.get() } );
    if ( it->right )
      deep_copy( ConstIterator{ it->right.get() } );
    
    return;
    
  };

  deep_copy( ConstIterator{ T_other.root.get() } );

}


// ===========================================================================


template < class T, class U >
typename Tree< T, U >::Iterator Tree< T, U >::insert ( const T key, const U value, const bool substitute ) {

  if ( root ) {
    Iterator it { root->insert( key, value, substitute ) };
    if ( key < tail->key() ) tail = tail->left.get();
    return it;
  }
  else {
    root.reset( new Node{ key, value } );
    tail = root.get();
    return Iterator { root.get() };
  }

}


// ===========================================================================


template < class T, class U >
void Tree< T, U >::balance() {

  std::vector<Node*> nodes;
  Iterator it = begin();
  for ( ; it != end(); ++it )
    nodes.push_back( new Node { it->key(), it->value() } );
  clear();
  //this->root.reset();

  if ( nodes.size() > 0 ) {
    //root.release();
    root.reset( nodes[ 0.5 * nodes.size() ] );
    // std::cout << root->key() << std::endl;
    kernel_balance( Iterator { root.get() }, nodes );
  }
  // else {
  //   root.release();
  //   root.reset( nullptr );
  // }
  
  // for ( typename std::vector< Node* >::iterator it = nodes.begin(); it != nodes.end(); ++it )
  //   delete ( *it );
  tail = root->leftmost();
 
}

// ===========================================================================


template < class T, class U >
void Tree< T, U >::kernel_balance( Iterator here, const std::vector<Node*>& nodes ) {

  auto begin = nodes.begin();
  auto last = nodes.begin() + nodes.size();
  
  // std::cout << here->key() << std::endl;
  
  std::vector< Node* > left_half { begin, begin + 0.5 * nodes.size() };
  if ( left_half.size() > 0 ) {
    // here->left.release();
    here->left.reset( left_half[ 0.5 * left_half.size() ] );
    // std::cout << here->left->key() << std::endl;
    here->left->parent = here.operator->();
    kernel_balance( Iterator{ here->left.get() }, left_half );
  }
  // else {
  //   // here->left.release();
  //   here->left.reset( nullptr );
  // }

  std::vector< Node* > right_half { last - 0.5 * nodes.size(), last };
  if ( right_half.size() > 0 ) {
    // here->right.release();
    here->right.reset( right_half[ 0.5 * right_half.size() ] );
    // std::cout << here->right->key() << std::endl;
    here->right->parent = here->parent;
    kernel_balance( Iterator{ here->right.get() }, right_half );
  }
  // else {
  //   // here->right.release();
  //   here->right.reset( nullptr );
  // }

  return;
  
}

// ===========================================================================
