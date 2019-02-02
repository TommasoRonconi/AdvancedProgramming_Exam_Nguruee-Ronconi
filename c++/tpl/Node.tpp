/**
 *  @file tpl/Node.tpp
 *
 *  @brief Definition of templated functions of struct Node
 *
 *  This file defines the interface of the templated functions of the struct Node
 *  It is included at the end of the header file include/Node.h.
 *  Implementing the definition of the structure member functions in a separate
 *  file allows us to maintain an ordered structure, while using this strategy
 *  instead of declaring each possible setting of the templated types keeps the
 *  generality of the class.
 *
 *  @author Herbert Nguruwe, Tommaso Ronconi
 *
 *  @author hknguruwe@gmail.com, tronconi@sissa.it
 */


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
