#ifndef BVTtipo2_H
#define BVTtipo2_H
#include <sdsl/bit_vectors.hpp>
using namespace std;
using namespace sdsl;

template< class BV =  sdsl::s18::vector<> , class RBV = sdsl::s18::rank_support<> , class SBV = sdsl::s18::select_support<> >
class BVTtipo2 {
  BV *B;
  RBV *b_rank;
  SBV *b_select;
  size_t vector_size;
public:
  BVTtipo2() {;}
  ~BVTtipo2() {;}
  BVTtipo2<BV,RBV,SBV> ( bit_vector input ) {
      vector_size = input.size();
      B = new BV(input);
      b_rank = new RBV(*B);  
      b_select = new SBV(*B);  
  }
  int operator[](size_t i) {
    return i < vector_size ? B[i] : 0;
  }
  int rank (size_t i) {
    return (*b_rank)(i);
  }
  int access (size_t i) {
    return  (*B)[i];
  }
  int select (size_t i) {
    return (*b_select)(i);
  }
  int size () {
    return  size_in_bytes(*B);
  }
};
#endif