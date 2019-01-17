/**
 *  @file include/BST_utility.h
 *
 *  @brief Header containing declaration of some helper functions and types
 *
 *  This file declares some helper functions and custom-types
 *
 *  @author Herbert Nguruwe, Tommaso Ronconi
 *
 *  @author hknguruwe@gmail.com, tronconi@sissa.it
 */
#ifndef __BST_UTILITY__
#define __BST_UTILITY__

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

  /**
   * @enum direction
   * @brief Direction is used to decide where to add the node. Its either right or left
   */
  enum class direction{left, right};

  /**
   *  @brief get the pointer corresponding to bst::direction
   *  
   *  @param dir the direction to take
   *
   *  @return pointer to child in the given direction
   */
  template<class T> 
    direction which_direction(const T keychild, const T keyparent)
    {
      if (keychild > keyparent) return direction::right;
      else return direction::left;
    }

}

#endif //__BST_UTILITY__
