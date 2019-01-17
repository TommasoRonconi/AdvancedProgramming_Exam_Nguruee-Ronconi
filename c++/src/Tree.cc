#include <Tree.h>
// #include <iostream>
// #include<memory>
// #include <BST_utility.h>


// ===========================================================================

template< class T, class U >
void Tree< T, U >::m_insert(std::unique_ptr<Tree< T, U >::Node> newnode, Tree::Iterator it, const bool substitute){
  
  bst::direction dir = bst::which_direction( newnode->key(), it->key() );
     
     if (it->get_direction(dir))
       m_insert(newnode, Iterator(it->get_direction(dir)), substitute);
     else
       it->new_node(newnode, dir);
     
 
}


// ===========================================================================


template <class T, class U>
void Tree< T, U >::insert(const T key, const U value, const bool substitute)
{
    Node newnode { key, value };
    
    if (root) 
      m_insert(&newnode, top(), substitute);
    else 
      root = newnode;
    

}


// ===========================================================================
