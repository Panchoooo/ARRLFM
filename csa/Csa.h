#ifndef CSA
#define CSA

#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <sdsl/vectors.hpp>
#include <sdsl/wavelet_trees.hpp>
#include <sdsl/suffix_arrays.hpp>

using namespace std;
using namespace sdsl;


template<class Estructura = wt_int<> >
class Csa{
private:

public:
  csa_wt<Estructura> csa; // suffix array

  Csa<Estructura> (int_vector<>);
  Csa<Estructura> (char*);
  ~Csa<Estructura> (void);


  unsigned countbyIntVector (int_vector<> patron);

  unsigned countbyIntVectorSave (int_vector<> patron,char* output);
  unsigned countbyString (string patron);
  void saveBWT(char* output);
};

#include "Csa.cpp"
#endif