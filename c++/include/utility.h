/**
 *  @file include/Tree.h
 *
 *  @brief The class Tree
 *
 *  This file defines the interface of the class Tree
 *
 *  @author Herbert Nguruwe, Tommaso Ronconi
 *
 *  @author hknguruwe@gmail.com, tronconi@sissa.it
 */
#include<iostream>
#include<memory>
/**                                                                               
   *  @brief The namespace of the functions and classes used to handle 
   *  <B> catalogues of astronomical sources </B>   
   *                                                       
   *  The \e catalogue namespace contains all the functions and                                      
   *  classes used to handle catalogues of astronomical sources                                          
*/

namespace bst{

enum class direction{left, right};

direction  which_direction(int key_child, int key_parent){
    return (key_child > key_parent) ? direction::right : direction::left;
 }

}


