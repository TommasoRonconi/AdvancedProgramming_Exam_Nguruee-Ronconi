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
    Iterator< ot, ou > stop { t.head };
    while ( it != stop ) {
      os << it->key() << ":\t" << it->value() << "\n";
      ++it;
    }

    os << it->key() << ":\t" << it->value();
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
Iterator< T, U > Tree< T, U >::find ( const T key, Iterator it ) {

  if ( key == it->key() )
    return it;

  if ( key < it->key() && ( it->left ) )
    return find( key, Iterator( it->left.get() ) );

  if ( key > it->key() && (it->right))
    return find( key, Iterator( it->right.get() ) );

  return end();
    
}


// ===========================================================================


template < class T, class U >
void Tree< T, U >::insert ( const T key, const U value, const bool substitute ) {

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


// ===========================================================================


template < class T, class U >
void Tree< T, U >::balance() {

  size_t size = 0;

  Iterator it = begin();

  while ( it != end() ) { ++size; ++it; }

  Tree< T, U > T_new;
  
  kernel_balance( T_new, begin(), 0.5 * size, end() );

  this->clear();
  // root->clear();
  *this = std::move( T_new );
  
}

// ===========================================================================


template < class T, class U >
void Tree< T, U >::kernel_balance( Tree& T_new, Iterator startpoint, size_t steps, Iterator endpoint ) {

  Iterator it = startpoint;
  size_t ii = 0;

  if ( steps > 0 ) {

    for ( ; ii < steps && it != endpoint; ++ii, ++it );
    
    if ( it.operator->() )
      T_new.insert( it->key(), it->value(), true );
    else T_new.insert( startpoint->key(), startpoint->value(), true );
    
    kernel_balance ( T_new, startpoint, steps/2, it );
    if ( ++it != endpoint ) kernel_balance ( T_new, it, steps/2, endpoint );
    
  }
  else {
    while ( it != endpoint && it.operator->() ) {

      T_new.insert( it->key(), it->value(), true );
      ++it;

    } 
  }
  
  
}


// ===========================================================================