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
std::unique_ptr<Node> get_direction(bst::direction dir)
{
    if (dir == bst::direction::left) return left
    else return right;
}
