#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sys/stat.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <sdsl/vectors.hpp>
#include <sdsl/wavelet_trees.hpp>

#include <sdsl/rl_runs.hpp> // Runlenght | Jose Fuentes
#include <sdsl/wt_rlmn.hpp> // Original de la sdsl Navarro 

#include "../PEF/pef_vector_opt.hpp" // Elias-Fano | Gabriel
#include "../PEF/pef_vector_opt_vigna.hpp" // Elias-Fano | Gabriel
#include "../PEF/pef_vector_unif.hpp"

#include "../s18_vector-master/s18/head/constants.hpp" // s18_vector | Manuel Weitzman
#include "../s18_vector-master/s18/head/s18_vector.hpp" // s18_vector | Manuel Weitzman



#include "../csa/Csa.h" // Elias-Fano | Gabriel

#include "../bitvectors/BVTtipo1.hpp" // Estructuras para poder utilizar rank y select con bitvector sin *
#include "../bitvectors/BVTtipo2.hpp" // Estructuras para poder utilizar rank y select con bitvector con *

#include "Baseline.h" // ASAP | Sepulveda
#include "Asap.h" // ASAP | Sepulveda
#include "bit_vectors.h"
#include "m_wt/m_wt.h"

#include "Arrlfm.h" // ARRL-FM-index

#include <sdsl/suffix_arrays.hpp> // CSA nativo
#include <algorithm>

#include <bits/stdc++.h>
#include <cstdlib>
//#include <filesystem>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using namespace std;
using namespace sdsl;



int main(int argc, char *argv[]) {

  char* file = argv[1];

  //char *lectura_path = "/data/pizzachili/Resultados/"; /* CARPETA QUE CONTIENE TEXTOS */
  char *lectura_path = "/root/data/"; /* CARPETA QUE CONTIENE TEXTOS */
  char path_asap1[100];           
  char path_asapfolder[100];           
  clock_t begin, end;
  double cpu_time_used;

  int largo_patroncito = 4;
  FILE *fichero;
  unsigned int i, x1, x2, x3, x4, x5, x6 , x7, x8, x9, x10 , x11, x12, x13, x14 , x15, x16;
  uint32_t cantidad_patrones = 49000;
  char *largo, path_out_patron ;
  char* lectura_patron;

  int_vector<> civ = int_vector<>();
  int_vector<> bwt = int_vector<>();
  int_vector<> t0 = int_vector<>();

  char *separate = "_";
  char *separate2 = "/";
  char *bwt_path = "/BWT";
  char *c_path = "/C";
  char *bin_path = "/binario.bin";
  char *t0_path = "/T0";
  char *out_path = "/Patrones/";
  char *csa_rl_runs = "/csa_rl_runs";
  char *csa_wt_rlmn = "/csa_wt_rlmn";

  char path_bwt[100];   
  strcpy(path_bwt,lectura_path); 
  strcat(path_bwt,file); 
  strcat(path_bwt,bwt_path); 
  load_from_file(bwt, path_bwt);
 
  char path_c[100];   
  strcpy(path_c,lectura_path); 
  strcat(path_c,file); 
  strcat(path_c,c_path); 
  load_from_file(civ, path_c);
  
  char path_t0[100];   
  strcpy(path_t0,lectura_path); 
  strcat(path_t0,file); 
  strcat(path_t0,t0_path); 
  load_from_file(t0, path_t0);

  char path_bin[100];   
  strcpy(path_bin,lectura_path); 
  strcat(path_bin,file); 
  strcat(path_bin,bin_path); 

  char path_csa_rl_runs[100];   
  strcpy(path_csa_rl_runs,lectura_path); 
  strcat(path_csa_rl_runs,file); 
  strcat(path_csa_rl_runs,csa_rl_runs); 

  char path_csa_wt_rlmn[100];   
  strcpy(path_csa_wt_rlmn,lectura_path); 
  strcat(path_csa_wt_rlmn,file); 
  strcat(path_csa_wt_rlmn,csa_wt_rlmn); 

  char path_output[100];   
  strcpy(path_output,lectura_path); 
  strcat(path_output,file); 
  strcat(path_output,out_path); 


  char *nasap1 = "ARRLFM_SD_INT";
  strcpy(path_asap1,path_output);
  strcat(path_asap1,nasap1); 
  strcat(path_asap1,separate2); 
  strcat(path_asap1,nasap1); 
  strcpy(path_asapfolder,path_output);
  strcat(path_asapfolder,nasap1); 
  cout << path_bin << "\n";
  //fs::create_directories(path_asapfolder); // Crear carpeta si no existe
  Arrlfm< Asap< SDBV, uint64_t ,wt_int<>> >  TWA(path_bin,bwt,civ,0);  
    


  return 0;

}

