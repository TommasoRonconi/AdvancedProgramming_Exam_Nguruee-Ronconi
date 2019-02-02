

// ===========================================================================


// template< class T, class U >
// void Node< T, U >::insert ( const T key, const U value, const bool substitute ) {
      
//   if ( substitute && key == content.first ) content.second = value;
      
//   if( key < content.first ) {
//     if( left ) 
//       left->insert( key, value, substitute );
//     else
//       left.reset( new Node { key, value, this } );
//   }

//   if ( key > content.first ) {
//     if ( right ) 
//       right->insert( key, value, substitute );
//     else 
//       right.reset( new Node{ key, value, parent } );	
//   }
      
// }


// ===========================================================================


template< class T, class U >
Node< T, U > * Node< T, U >::insert ( const T key, const U value, const bool substitute ) {

  Node * n = nullptr;
  if ( substitute && key == content.first ) {
    content.second = value;
    n = this;
  }
      
  if( key < content.first ) {
    if( left ) 
      n = left->insert( key, value, substitute );
    else {
      left.reset( new Node { key, value, this } );
      n = left.get();
    }
  }

  if ( key > content.first ) {
    if ( right ) 
      n = right->insert( key, value, substitute );
    else {
      right.reset( new Node{ key, value, parent } );
      n = right.get();
    }
  }

  return n;
      
}


// ===========================================================================


template< class T, class U >
Node< T, U > * Node< T, U >::find ( const T key ) {
  
  if ( key == content.first ) 
    return this;

  if ( ( left ) && ( key < content.first ) ) 
    return left->find( key );

  if ( ( right ) && ( key > content.first ) ) 
    return right->find( key );

  return nullptr;

}


// ===========================================================================
