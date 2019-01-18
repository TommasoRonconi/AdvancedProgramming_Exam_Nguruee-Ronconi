#include <Tree.h>


// ===========================================================================
/**
   *  @brief get the pointer corresponding 
   *  
   *  @param dir the direction to take
   *
   *  @return pointer to child in the given direction
   */

template< class T, class U >
void Tree< T, U >::insert ( const T key, const U value, const bool substitute ){

  if ( root )

    root->insert( key, value, substitute );

  else{
  
    root.reset( new Node{ key, value } );

  }

}




// ===========================================================================
