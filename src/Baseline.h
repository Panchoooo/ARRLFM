#ifndef BASELINE
#define BASELINE

#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <sdsl/vectors.hpp>
#include <sdsl/wavelet_trees.hpp>
#include "bit_vectors.h"
#include "m_wt/m_wt.h"


#include <iostream>
#include <ctime>
#include <sdsl/rl_runs.hpp>
#include <sdsl/wavelet_trees.hpp>

#include "../PEF/pef_vector_opt.hpp"
#include "../PEF/pef_vector_unif.hpp"

#include "Asap.h"
#include "bit_vectors.h"
#include "m_wt/m_wt.h"




using namespace std;
using namespace sdsl;


template<class Estructura = wt_int<> >
class Baseline{

private:
  int_vector<> sa; // suffix array
  int_vector<> t; // texto de simbolos

  unordered_map<uint32_t, string > S2W; // Symbol to Word
  unordered_map<string, uint32_t> W2S; // Word to Symbol


public:
  Estructura* AWT; // ASAP
  int_vector<> C; // arreglo C

  int_vector<> t0; // texto de simbolos sin 0 final
  int_vector<> BWT; // barrows wheeler

  ~Baseline<Estructura> (void);
  Baseline<Estructura> ( char*,int_vector<>,int_vector<>);


  
};

#include "Baseline.cpp"
#endif