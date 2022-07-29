#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sys/stat.h>

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
  char* tipo = argv[2];

  char *lectura_path = "/data/pizzachili/Resultados/"; /* CARPETA QUE CONTIENE TEXTOS */



  /* Baselines */
   // char *nasap1 = "ARRLFM_AP";
  //char *nasap1 = "ARRLFM_RLMN";
  //char *nasap1 = "ARRLFM_RUNS";

  /* ARRLMNS */
  // wt INT
   char *nasap1 = "ARRLFM_SD_INT";
 //  char *nasap1 = "ARRLFM_PEF_INT";
 // char *nasap1 = "ARRLFM_S18_INT";

  // wt AP
   // char *nasap1 = "ARRLFM_SD_AP";
 //  char *nasap1 = "ARRLFM_PEF_AP";
  // char *nasap1 = "ARRLFM_PEFv_AP";
///   char *nasap1 = "ARRLFM_S18_AP";

  // wt RLMN INT
  // char *nasap1 = "ARRLFM_SD_RLMN";
  // char *nasap1 = "ARRLFM_PEF_RLMN";
   //char *nasap1 = "ARRLFM_S18H-32_RLMN";

  // wt RLMN AP
  // char *nasap1 = "ARRLFM_SD_RLMN_AP";
  // char *nasap1 = "ARRLFM_PEF_RLMN_AP";
 // char *nasap1 = "ARRLFM_PEFv_RLMN_AP";
  //char *nasap1 = "ARRLFM_S18_RLMN_AP";

  // rl RUNS ap
   //char *nasap1 = "ARRLFM_SD_RUNS_AP";
  //char *nasap1 = "ARRLFM_PEF_RUNS_AP";
   //char *nasap1 = "ARRLFM_S18_RUNS_AP";

  // rl RUNS rlmn
   // char *nasap1 = "ARRLFM_SD_RUNS_RLMN";
  // char *nasap1 = "ARRLFM_PEF_RUNS_RLMN";
   //char *nasap1 = "ARRLFM_PEFv_RUNS_RLMN";
  //char *nasap1 = "ARRLFM_S18_RUNS_RLMN";


  strcpy(path_asap1,path_output);
  strcat(path_asap1,nasap1); 
  strcat(path_asap1,separate2); 
  strcat(path_asap1,nasap1); 

  strcpy(path_asapfolder,path_output);
  strcat(path_asapfolder,nasap1); 
  cout << path_bin << "\n";
  fs::create_directories(path_asapfolder); // Crear carpeta si no existe

  //Baseline< wt_ap<>  >  TWA(path_bin,bwt,civ); 
  //Baseline< wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>   >  >  TWA(path_bin,bwt,civ); 
  //Baseline< rl_runs< 64,wt_ap<> >  >  TWA(path_bin,bwt,civ); 
 
  // wt INT
   Arrlfm< Asap< SDBV, uint64_t ,wt_int<>> >  TWA(path_bin,bwt,civ,0);  
  //Arrlfm< Asap< pef_vector_opt_vigna< rank_support_v5<1>, select_support_mcl<1>, 1024 >, uint64_t ,wt_int<>> >  TWA(path_bin,bwt,civ,0);  
 //  Arrlfm< Asap< BVTtipo2<sdsl::s18::vector<32>, sdsl::s18::rank_support<1,32> , sdsl::s18::select_support<1,32>> , uint64_t ,wt_int<>> >  TWA(path_bin,bwt,civ,0);  
  
  // wt AP
 //Arrlfm< Asap< SDBV, uint64_t ,wt_ap<>> >  TWA(path_bin,bwt,civ,0);  
 //Arrlfm< Asap< pef_vector_opt_vigna< rank_support_v5<1>, select_support_mcl<1>, 1024 >, uint64_t ,wt_ap<>> >  TWA(path_bin,bwt,civ,0);  
   // Arrlfm< Asap< BVTtipo2<sdsl::s18::vector<32>, sdsl::s18::rank_support<1,32> , sdsl::s18::select_support<1,32>>, uint64_t ,wt_ap<>> >  TWA(path_bin,bwt,civ,0);  
  
  // wt RLMN INT
 //  Arrlfm< Asap< SDBV, uint64_t ,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>   >  > > TWA(path_bin,bwt,civ,0);  
  //  Arrlfm< Asap<pef_vector_opt_vigna< rank_support_v5<1>, select_support_mcl<1>, 1024 >, uint64_t ,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>   >  > > TWA(path_bin,bwt,civ,0);  
   //Arrlfm< Asap< BVTtipo2<sdsl::s18::vector<32>, sdsl::s18::rank_support<1,32> , sdsl::s18::select_support<1,32>>, uint64_t ,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>   >  > > TWA(path_bin,bwt,civ,0);  
  
  // wt RLMN AP
   //Arrlfm< Asap< SDBV, uint64_t ,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_ap<>   >  > > TWA(path_bin,bwt,civ,0);  
   //Arrlfm< Asap<pef_vector_opt_vigna< rank_support_v5<1>, select_support_mcl<1>, 1024 >, uint64_t ,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_ap<>   >  > > TWA(path_bin,bwt,civ,0);  
 //Arrlfm< Asap< BVTtipo2<sdsl::s18::vector<32>, sdsl::s18::rank_support<1,32> , sdsl::s18::select_support<1,32>>, uint64_t ,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_ap<>   >  > > TWA(path_bin,bwt,civ,0);  
  
  // rl RUNS AP
  //  Arrlfm< Asap< SDBV, uint64_t ,rl_runs< 64,wt_ap<> > > >  TWA(path_bin,bwt,civ,0);  
  //Arrlfm< Asap< pef_vector_opt_vigna< rank_support_v5<1>, select_support_mcl<1>, 1024 >, uint64_t ,rl_runs< 64,wt_ap<> > > >  TWA(path_bin,bwt,civ,0);  
  //Arrlfm< Asap< BVTtipo2<sdsl::s18::vector<32>, sdsl::s18::rank_support<1,32> , sdsl::s18::select_support<1,32>>, uint64_t ,rl_runs< 64,wt_ap<> > > >  TWA(path_bin,bwt,civ,0);  


  // rl RUNS rlmn ap
  //Arrlfm< Asap< SDBV, uint64_t ,rl_runs< 64,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>  > > > >  TWA(path_bin,bwt,civ,0);  
  // Arrlfm< Asap< pef_vector_opt_vigna< rank_support_v5<1>, select_support_mcl<1>, 1024 >, uint64_t ,rl_runs< 64,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>  > > > >  TWA(path_bin,bwt,civ,0);  
   //Arrlfm< Asap< BVTtipo2<sdsl::s18::vector<32>, sdsl::s18::rank_support<1,32> , sdsl::s18::select_support<1,32>>, uint64_t ,rl_runs< 64,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>  > > > >  TWA(path_bin,bwt,civ,0);  




  return 0;

}

