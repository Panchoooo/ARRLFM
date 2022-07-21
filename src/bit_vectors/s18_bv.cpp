/*#include "s18_bv.h"

S18BV::S18BV (bit_vector input) {
  vector_size = input.size();
}

S18BV::~S18BV (void) {
  delete b_rank;
  delete b_select;
}

int S18BV::operator[](size_t i) {
  return i < vector_size ? B[i] : 0;
}

int S18BV::access (size_t i) {
  return i < vector_size ? B[i] : 0;
}

int S18BV::rank (size_t i) {
  return (*b_rank)(i);
}

int S18BV::select (size_t i) {
  return i < vector_size ? (*b_select)(i) : 0;
}

int S18BV::size () {
  return size_in_bytes(*b_rank) + size_in_bytes(*b_select) + size_in_bytes(B);
}*/