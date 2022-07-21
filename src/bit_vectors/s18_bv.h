/*#ifndef S18_BIT_VECTORS
#define S18_BIT_VECTORS

#include <sdsl/bit_vectors.hpp>

#include "abstract_bv.h"

#include "../../s18_vector-master/s18/head/s18_vector.hpp" // s18_vector | Manuel Weitzman
#include "../../s18_vector-master/s18/head/constants.hpp" // s18_vector | Manuel Weitzman

using namespace sdsl;

class S18BV: public Bitvector {
  private:
    sd_vector<> B;
    size_t vector_size;
    sd_vector<>::rank_1_type *b_rank;
    sd_vector<>::select_1_type *b_select;
  public:
    S18BV (bit_vector input);
    ~S18BV (void);
    int operator[](size_t i);
    int access (size_t i);
    int rank   (size_t i);
    int select (size_t i);
    int size ();
};

#endif*/