#ifndef ARRLFM
#define ARRLFM

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


template<class Estructura = Asap<pef_vector_unif<100, rank_support_v5<1>, select_support_mcl<1>>, uint64_t,sdsl::rl_runs<64,wt_ap<>>> >
class Arrlfm{

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

  Arrlfm<Estructura> ( char*,int_vector<>,int_vector<>,unsigned);
  Arrlfm<Estructura> ( int_vector<>,unsigned);
  Arrlfm<Estructura> ( string, unsigned);
  ~Arrlfm<Estructura> (void);

  unsigned countbyIntVector (int_vector<> patron);
  unsigned countbyString (string patron);
  unsigned countbyIntVectorSave (int_vector<> patron,char* output);
  unsigned long size ();
  unsigned long size2 ();

  void getC ();
  void getBWT ();
  void getT ();
  void getSA ();

  void saveBWT(char* output);
  string buscarPatron(int largo_patron);
  void printW2S ();

  void testing(char* file,int tipo,char* nasap1, char *lectura_path);
  
};

#include "Arrlfm.cpp"
#endif