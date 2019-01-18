#include <Tree.h>


// ===========================================================================
/**
   *  @brief get the pointer corresponding 
   *  
   *  @param dir the direction to take
   *
   *  @return pointer to child in the given direction
   */

void Tree::insert ( const int k, const int v, bool sub ){

  if (root)

    root->insert( k, v, sub );

  else{
  
    root.reset( new Node{ k, v } );

  }

}




// ===========================================================================
