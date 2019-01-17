#include <Tree.h>
// #include <iostream>
// #include<memory>
// #include <BST_utility.h>


// ===========================================================================

// copy ctor
// template< class T, class U >
// Tree< T, U >::Tree ( const Tree& t ) : root{t.root}, head{t.head}, tail{t.tail} {

// }


// ===========================================================================

template< class T, class U >
void Tree< T, U >::m_insert(std::unique_ptr<Node> newnode, Tree::Iterator it, const bool substitute){
  
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
