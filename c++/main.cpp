#include <Tree.h>
#include <memory>
#include <map>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

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

  // uncomment to run some tests:
  // make_some_tests();

  // allocate an object of class Tree
  Tree< int, double > myT;

  // allocate an object of class std::map
  std::map< int, double > myM;

  // insert elements into the two allocated objects
  // (pairs 'key-value' are read from stdin)
  int key;
  double value;
  while ( std::cin >> key >> value ) {
    myT.insert( key, value );
    myM.insert( std::pair< int, double >( key, value ) );
  }
  std::cout << myT << std::endl;
  std::cout << "ROOT: " << myT.top()->key() << std::endl;  

  // find some values within the Tree:
  // (measuring performance)
  auto myT_time_start = Clock::now();
  myT.find( 42, myT.top() );  // not present
  myT.find( 145, myT.top() ); // present (close to root)
  myT.find( 304, myT.top() ); // present
  myT.find( 322, myT.top() ); // present (head)
  myT.find( 1, myT.top() );   // not present
  myT.find( 6, myT.top() );   // present
  auto myT_time_end = Clock::now();
  double myT_time = std::chrono::duration_cast<std::chrono::nanoseconds>(myT_time_end - myT_time_start).count();
  std::cout << "Time spent (Tree): " << myT_time << std::endl;

  // find some values within the Tree:
  // (measuring performance)
  myT.balance();
  myT_time_start = Clock::now();
  myT.find( 42, myT.top() );  // not present
  myT.find( 145, myT.top() ); // present (close to root)
  myT.find( 304, myT.top() ); // present
  myT.find( 322, myT.top() ); // present (head)
  myT.find( 1, myT.top() );   // not present
  myT.find( 6, myT.top() );   // present
  myT_time_end = Clock::now();
  myT_time = std::chrono::duration_cast<std::chrono::nanoseconds>(myT_time_end - myT_time_start).count();
  std::cout << "Time spent (balanced Tree): " << myT_time << std::endl;

  // find same values within the map:
  // (measuring performance)
  auto myM_time_start = Clock::now();
  myT.find( 42, myT.top() );  // not present
  myT.find( 145, myT.top() ); // present (close to root)
  myT.find( 304, myT.top() ); // present
  myT.find( 322, myT.top() ); // present (head)
  myT.find( 1, myT.top() );   // not present
  myT.find( 6, myT.top() );   // present
  auto myM_time_end = Clock::now();
  double myM_time = std::chrono::duration_cast<std::chrono::nanoseconds>(myM_time_end - myM_time_start).count();
  std::cout << "Time spent (std::map): " << myM_time << std::endl;

  
  Tree< int, double >::Iterator it = myT.top();

  myT.clear();
  
  return 0;
  
}
