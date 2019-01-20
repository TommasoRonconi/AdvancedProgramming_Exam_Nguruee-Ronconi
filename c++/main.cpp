#include <Tree.h>
#include <memory>

void make_some_tests () {

  Tree< int, double > T {};
  
  bool sub = true;
  T.insert( 2, 7.3, sub );
  T.insert( 3, 6.2, sub );
  T.insert( 1, 8.4, sub );
  T.insert( 6, 12., sub );
  T.insert( 4, 5.1, sub );
  T.insert( 5, 9.5, sub );
  T.insert( 7, 1.1, sub );
  T.insert( 8, 9.5, sub );
  T.insert( 9, 1.1, sub );
  T.insert( 10, 9.5, sub );
  T.insert( 11, 1.1, sub );
  T.insert( 12, 9.5, sub );
  T.insert( 13, 1.1, sub );
  T.insert( 14, 9.5, sub );
  T.insert( 15, 1.1, sub );

  std::cout << "\n!! --- Ordered tree before balance --- !!\n" << std::endl;
  std::cout << T << std::endl;

  T.balance();
  std::cout << "\n!! --- Ordered tree after balance --- !!\n" << std::endl;
  std::cout << T << std::endl;
  
  Tree< int, double >::Iterator it = T.top();
  std::cout << "\n!! ---- Check if they correspond ---- !!\n" << std::endl;
  std::cout << "should be 5: " << it->left->right->left->key() << std::endl;
  std::cout << "should be 9: " << it->right->left->left->key() << std::endl;
  std::cout << "should be 7.3: " << T.find( 2, it )->value() << std::endl;
  std::cout << "should be 9.5: " << T.find( 5, it )->value() << std::endl;

  T.clear();
  if ( ! T.top().operator->() )
    std::cout << "\n!! --------- Done all clear --------- !!\n" << std::endl;

  return;

}

int main( ) {

  // uncomment to make some tests:
  // make_some_tests();

  int key;
  double value;
  bool substitute = true;
  Tree< int, double > T {};

  while ( std::cin >> key >> value )
    T.insert( key, value, substitute );

  std::cout << T << std::endl;
  Tree< int, double >::Iterator it = T.top();

  T.clear();
  
  return 0;
  
}
