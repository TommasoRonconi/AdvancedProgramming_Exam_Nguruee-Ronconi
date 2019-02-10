#include <Tree.h>
#include <memory>
#include <map>
#include <chrono>
#include <fstream>
// #include <thread>

/// used for performance measures
typedef std::chrono::high_resolution_clock Clock;

/// this function inserts a set of key-values inside an empty Tree
void fill_me ( Tree< int, double > &T ) {

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

  return;
  
}

/// this function runs some tests to check basic usage of the Tree
void make_some_tests () {

  Tree< int, double > T {};
  fill_me( T );
  
  std::cout << "\n!! --- Ordered tree before balance --- !!\n" << std::endl;
  std::cout << T << std::endl;

  T.balance();
  std::cout << "\n!! --- Ordered tree after balance --- !!\n" << std::endl;
  std::cout << T << std::endl;
  
  Tree< int, double >::Iterator it = T.top();
  std::cout << "\n!! ---- Check if they correspond ---- !!\n" << std::endl;
  std::cout << "Checking position in Tree:\n\t should be 5:\t" << it->left->right->left->key() << std::endl;
  std::cout << "Checking T.find(2):\n\t should be 7.3:\t" << T.find( 2 )->value() << std::endl;
  std::cout << "Checking T[2]:\n\t should be 7.3:\t" << T[2] << std::endl;
  T[2] = 1.1;
  std::cout << "Checking assignment T[2]=1.1:\n\t should be 1.1:\t" << T[2] << std::endl;
  std::cout << "Checking T[16]:\n\t should be default value:\t" << T[16] << std::endl;
  std::cout << "Checking assignment T[17] (with const Tree):\n\t should not be there and throw exception.\t";
  const auto T2 = T;
  try{
    std::cout << T2[17] << std::endl;
  } catch (const Tree<int,double>::key_not_found& s) {
    std::cerr << s.message << std::endl;
  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n";
    return;
  }
  

  T.clear();
  if ( ! T.top().operator->() )
    std::cout << "\n!! --------- Done all clear --------- !!\n" << std::endl;

  return;

}

/// this function reads from stdin a set of couples (key, value) and allocates a Tree and an std::map
/// it measures the time spent by the find() algorithm of each of the two.
/// time spent by Tree::find() is measured before and after having balanced it
void compare_with_map () {

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

  // read a bunch of keys from a file and store in a int vector
  std::string file_in = "input/bunch_of_random_keys.dat";
  std::ifstream fin { file_in.c_str() };
  std::vector< int > ran_keys;
  while (fin >> key)
    ran_keys.push_back( key );

  // find some values within the Tree:
  // (measuring performance)
  auto myT_time_start = Clock::now();
  for ( auto kk: ran_keys ) myT.find( kk );
  auto myT_time_end = Clock::now();
  double myT_time = std::chrono::duration_cast<std::chrono::nanoseconds>(myT_time_end - myT_time_start).count();
  std::cout << myT_time << "\t";

  // find some values within the Tree:
  // (measuring performance)
  myT.balance();
  myT_time_start = Clock::now();
  for ( auto kk: ran_keys ) myT.find( kk );
  myT_time_end = Clock::now();
  myT_time = std::chrono::duration_cast<std::chrono::nanoseconds>(myT_time_end - myT_time_start).count();
  std::cout << myT_time << "\t";

  // find same values within the map:
  // (measuring performance)
  auto myM_time_start = Clock::now();
  for ( auto kk: ran_keys ) myM.find( kk );
  auto myM_time_end = Clock::now();
  double myM_time = std::chrono::duration_cast<std::chrono::nanoseconds>(myM_time_end - myM_time_start).count();
  std::cout << myM_time << std::endl;

  myT.clear();

  return;
  
}

/// this function measures the time spent by the balance algorithm
void balance_tree () {

  // allocate an object of class Tree
  Tree< int, double > myT;

  // insert elements into the two allocated objects
  // (pairs 'key-value' are read from stdin)
  int key;
  double value;
  while ( std::cin >> key >> value )
    myT.insert( key, value );
  
  auto myT_time_start = Clock::now();
  myT.balance();
  auto myT_time_end = Clock::now();
  double myT_time = std::chrono::duration_cast<std::chrono::nanoseconds>(myT_time_end - myT_time_start).count();
  std::cout << myT_time << std::endl;

  myT.clear();

  return;
  
}

int main() {

  // fill balance and print
#ifdef DEFAULT
  Tree< int, double > T {};
  fill_me( T );
  T.balance();
  std::cout << T << std::endl;
  
  // std::vector<Node<int, double>*> nodes;
  // Tree< int, double >::Iterator it = T.begin();
  // for ( ; it != T.end(); ++it )
  //   nodes.push_back( new Node<int, double> { it->key(), it->value() } );
  
  // for ( std::vector< Node<int, double>* >::iterator it = nodes.begin(); it != nodes.end(); ++it )
  //   delete ( *it );
  
  T.clear();
#endif
  
  // run some tests:
#ifdef TEST
  make_some_tests();
#endif

  // test balance time
#ifdef TEST_BALANCE
  balance_tree();
#endif

  // test performance (requires to insert elements from stdin)
#ifdef PERFORMANCE
  compare_with_map();
#endif
  
  return 0;
  
}
