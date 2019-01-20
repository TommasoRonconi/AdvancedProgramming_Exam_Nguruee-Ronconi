


// ===========================================================================


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

  Tree< T, U > T_new {};
  
  kernel_balance( T_new, begin(), 0.5 * size, end() );

  root->clear();
  *this = std::move( T_new );
  
}

// ===========================================================================


template < class T, class U >
void Tree< T, U >::kernel_balance( Tree& T_new, Iterator startpoint, size_t steps, Iterator endpoint ) {

  Iterator it = startpoint;
  size_t ii = 0;

  if ( steps > 0 ) {

    for ( ; ii < steps; ++ii, ++it );
    
    T_new.insert( it->key(), it->value(), true );
    
    kernel_balance ( T_new, startpoint, steps/2, it );
    if ( (++it).operator->() ) kernel_balance ( T_new, it, steps/2, endpoint );
    
  }
  else {
    while ( it != endpoint ) {
      
      T_new.insert( it->key(), it->value(), true );
      ++it;

    } 
  }
  
  
}


// ===========================================================================
