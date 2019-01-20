

// ===========================================================================


template< class T, class U >
void Node< T, U >::insert ( const T key, const U value, const bool substitute ) {
      
  if ( substitute && key == content.first ) content.second = value;
      
  if( key < content.first ) {
    if( left ) 
      left->insert( key, value, substitute );
    else
      left.reset( new Node { key, value, this } );
  }

  if ( key > content.first ) {
    if ( right ) 
      right->insert( key, value, substitute );
    else 
      right.reset( new Node{ key, value, parent } );	
  }
      
}


// ===========================================================================
