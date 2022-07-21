#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sys/stat.h>

#include <iostream>
#include <fstream>
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
#include "../PEF/pef_vector_unif.hpp"

#include "../s18_vector-master/s18/head/s18_vector.hpp" // s18_vector | Manuel Weitzman
#include "../s18_vector-master/s18/head/constants.hpp" // s18_vector | Manuel Weitzman



#include "../csa/Csa.h" // Elias-Fano | Gabriel

#include "../bitvectors/BVTtipo1.hpp" // Estructuras para poder utilizar rank y select con bitvector sin *
#include "../bitvectors/BVTtipo2.hpp" // Estructuras para poder utilizar rank y select con bitvector con *

#include "Asap.h" // ASAP | Sepulveda
#include "bit_vectors.h"
#include "m_wt/m_wt.h"

#include "Arrlfm.h" // ARRL-FM-index

#include <sdsl/suffix_arrays.hpp> // CSA nativo
#include <algorithm>


using namespace std;
using namespace sdsl;

template <class T>
T parse(const std::string& s)
{
  T out;
  std::stringstream ss(s);
  ss >> out;
  return out;
}

int main(int argc, char *argv[]) {
  //srand (time(NULL));
  clock_t begin, end;
  double cpu_time_used;
  char* file = argv[1];
  int largo_patroncito = 4;
  FILE *fichero;
  unsigned int i, x1, x2, x3, x4, x5, x6 , x7, x8, x9, x10 , x11, x12, x13, x14 , x15, x16;
  uint32_t cantidad_patrones = 50000;
  char *largo, path_out_patron ;
  char* lectura_patron;

  int_vector<> civ = int_vector<>();
  int_vector<> bwt = int_vector<>();
  int_vector<> t0 = int_vector<>();

  char *separate = "_";
  char *lectura_path = "Lectura/";
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
  /*cout << "C:  ";
  for (long unsigned int i = 0; i < civ.size(); i++) {
      cout << civ[i] << " ";
  }
    cout << "\n\n\n\n\n";
  cout << "bwt:  ";
  for (long unsigned int i = 0; i < bwt.size(); i++) {
      cout << bwt[i] << " ";
  }  
    cout << "\n\n\n\n\n";
  cout << "T:  ";
  for (long unsigned int i = 0; i < t0.size(); i++) {
      cout << t0[i] << " ";
  }
    cout << "\n\n\n\n\n";


*/


  // Creacion estructuras ARRLFM

  char *nasap1 = "/ARRLFM1";
  char path_asap1[100];           
  strcpy(path_asap1,path_output); 
  strcat(path_asap1,nasap1); 
  cout <<  "Creacion ARRLFM 1";
  begin = clock();
 // Arrlfm< Asap< pef_vector_unif<  100, rank_support_v5<1>, select_support_mcl<1>  >, uint32_t , rl_runs< 64, wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>  > > > > TWA(path_bin,bwt,civ, 0);  
 
  //Arrlfm< Asap< SDBV, uint64_t ,rl_runs< 64,  wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<> >  > > > TWA(path_bin,bwt,civ, 0);  
 // Arrlfm< Asap< SDBV, uint64_t , wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>   > > > TWA(path_bin,bwt,civ, 0);  
 // Arrlfm< Asap< SDBV, uint64_t , rl_runs<16,wt_ap< rrr_vector<63> >>  >  > TWA(path_bin,bwt,civ, 0); 
  Arrlfm< Asap< SDBV, uint64_t , wt_int<>   >  > TWA(path_bin,bwt,civ, 0); 
 
 
  //Arrlfm< Asap< BVTtipo1<sd_vector<> , sd_vector<>::rank_1_type , sd_vector<>::select_1_type> , uint32_t , rl_runs< 64, wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>  > > > > TWA(path_bin,bwt,c, 0);  
  //Arrlfm< Asap< BVTtipo2<sdsl::s18::vector<>, sdsl::s18::rank_support<> , sdsl::s18::select_support<>> , uint32_t , wt_int<> > > TWA(path_bin,bwt,c, 0);  
  //Arrlfm< Asap< BVTtipo1<sd_vector<> , sd_vector<>::rank_1_type , sd_vector<>::select_1_type>  , uint32_t , wt_int<> > > TWA(path_bin,bwt,civ, 0);  
  //Arrlfm< Asap< BVTtipo1<sd_vector<> , sd_vector<>::rank_1_type , sd_vector<>::select_1_type>  , uint32_t , wt_int<> > > TWA("Data/coreutils2", 0);  
  end = clock();
  cpu_time_used = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%f seconds to execute \n", cpu_time_used);
  cout << "-------------------------------------\n\n";
  TWA.saveBWT(path_asap1);
  //int_vector<> a = {105, 431}; //coreutils 2
//  int_vector<> a = {14, 431, 2, 67}; // coreutils3
//  int_vector<> a = {2, 866, 2, 910}; // coreutils3
//  int_vector<> a = {2, 1577}; // coreutils3
  
  //int_vector<> a = {1590, 2, 54, 1593, 112, 2, 538, 23};// coreuilts 2
  
//  int_vector<> a = {14,2}; //coreutils 2
  char *nasap2 = "/ARRLFM2";
  char path_asap2[100];   
  strcpy(path_asap2,path_output); 
  strcat(path_asap2,nasap2); 
  remove( path_asap2 );
  cout <<  "Creacion ARRLFM 2";
  begin = clock();
  Arrlfm< Asap< SDBV, uint64_t ,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>   >   >  > TWA2(path_bin,bwt,civ, 0); 
  //Arrlfm< Asap< pef_vector_unif<  100, rank_support_v5<1>, select_support_mcl<1>  >, uint32_t ,wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<>  >   > > TWA2(path_bin,bwt,civ, 0);  
  end = clock();
  cpu_time_used = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%f seconds to execute \n", cpu_time_used);
  cout << "-------------------------------------\n\n";
  TWA2.saveBWT(path_asap2);
/*

  // Creacion estructuras CSA
  char *ncsa1 = "/CSA1";
  char path_csa1[100];           
  strcpy(path_csa1,path_output); 
  strcat(path_csa1,ncsa1); 
  cout <<  "Creacion CSA 1";
  begin = clock();
  Csa<  rl_runs< 64,  wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<> > >  > csa_to(path_csa_rl_runs); 
  end = clock();
  cpu_time_used = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%f seconds to execute \n", cpu_time_used);
  cout << "-------------------------------------\n\n";
  csa_to.saveBWT(path_csa1);

  char *ncsa2 = "/CSA2";
  char path_csa2[100];           
  strcpy(path_csa2,path_output); 
  strcat(path_csa2,ncsa2); 
  cout <<  "Creacion CSA 2";
  begin = clock();
  Csa< wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<> > > csa_to2(path_csa_wt_rlmn); 
   end = clock();
  cpu_time_used = ((double) (end - begin)) / CLOCKS_PER_SEC;
  printf("%f seconds to execute \n", cpu_time_used);
  cout << "-------------------------------------\n\n";
  //csa_to2.saveBWT(path_csa2);

/*
  TWA.getT();
  TWA.printW2S();

  uint32_t pos = 11;
  uint32_t t = 2;
  cout << TWA.AWT->rank(pos,t) << "\n"; // Resultado = 10
  cout << csa_to.csa.bwt.rank(pos,t); // Resultado = 9

*/
/*
  cout <<  "CSA 1";
  cout << csa_to.countbyIntVector(a) << "\n";

  cout <<  "CSA 2";
  cout << csa_to2.countbyIntVector(a) << "\n";
 */


 /* int_vector<> a = {357,58}; // coreutils3

  cout << "Patron: " << a << "\n";

  cout <<  "ASAP sd_vector + wt_rlmn";
  cout << TWA2.countbyIntVector(a) << "\n\n\n";

  cout <<  "ASAP sd_vector + rl_runs";
  cout << TWA.countbyIntVector(a) << "\n";





/*

  uint32_t pos = 83557;
  uint32_t pos2 = 83565;

  uint32_t t = 2;
  uint32_t ars =   TWA.AWT->rank(pos,t);
  uint32_t ars2 =  TWA.AWT->rank(pos2,t);
  uint32_t cars =  csa_to.csa.bwt.rank(pos,t);
  uint32_t cars2 = csa_to.csa.bwt.rank(pos2,t); 

  cout <<   cars << "\n"; // Resultado = 9
  cout << cars2 << "\n";// Resultado = 9

  cout << ars << "\n"; // Resultado = 10
  cout << ars2 << "\n"; // Resultado = 10


  int_vector patron = a;
  uint32_t c = patron[patron.size()-1];

  uint32_t b = TWA.C[c];
  uint32_t e = TWA.C[c+1];
  uint32_t contador = 0;
  cout << "\nPaso 0 |  C: " << c << " |  b: " << b << "  | e: " << e << "  | C[c]: " << TWA.C[c] << "  | C[c+1]: " << TWA.C[c+1] << "\n"; 
  if( patron.size() > 1){
      for ( long int  i = patron.size() - 2 ; i >= 0 ; i = i - 1) { // long int porque al llegar a 0 y hace el -1 se rompe 
          if(b==e){
              break;
          }

          c = patron[i];
          uint32_t aa = TWA.AWT->rank(b,c);
          uint32_t ab = TWA.AWT->rank(e,c);

          uint32_t w = 0;
          while( w < e-1){
             //cout << TWA.AWT->rank(w,c) << "\n";
            // cout << csa_to.csa.bwt.rank(w,c) << "\n";
            //cout << TWA.AWT->access(w) << "  " << w << "\n";
              w++;
          }
          b = TWA.C[c] + TWA.AWT->rank(b,c);
          e = TWA.C[c] + TWA.AWT->rank(e,c);
          contador+=1;
          cout << "Paso "<< contador <<" |  C: " << c << " |  b: " << b << "  | e: " << e << "  | C[c]: " << TWA.C[c] << " |  AWT->rank(b,c): "<<  aa<< " |  AWT->rank(e,c): "<< ab<< "\n"; 

      }
  }
  return e-b;
*/


if(true){

// PATRONES 
  for(int lp = 2 ; lp < 17 ; lp=lp*2){
      
    largo_patroncito = lp;

    if(largo_patroncito == 2){
      largo = "/Patrones/Largo2.txt";
      lectura_patron = "%d\t%d\n";
    }
    else if(largo_patroncito == 4){
      largo = "/Patrones/Largo4.txt";
      lectura_patron = "%d\t%d\t%d\t%d\n";
    }
    else if(largo_patroncito == 8){
      largo = "/Patrones/Largo8.txt";
      lectura_patron = "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n";

    }
    else if(largo_patroncito == 16){
      largo = "/Patrones/Largo16.txt";
      lectura_patron = "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n";
    }

    char path_file_patrones[100];   
    strcpy(path_file_patrones,lectura_path); 
    strcat(path_file_patrones,file); 
    strcat(path_file_patrones,largo); 

    std::string tmp = std::to_string(largo_patroncito);
    char const *number_path = tmp.c_str();
    fichero = fopen( path_file_patrones, "r" );
    printf( "Fichero: %s (para lectura) -> ", path_file_patrones );
    if( fichero )
        printf( "existe (ABIERTO)\n" );
    else
    {
        printf( "Error (NO ABIERTO)\n" );
        return 1;
    }

    printf( "Datos leidos del fichero: %s\n", path_file_patrones );

    for( i=1; i<=cantidad_patrones; i++ )
    {
        int_vector<> patron_lectura;
        if(largo_patroncito == 2){
          fscanf( fichero, lectura_patron, &x1, &x2 );
          patron_lectura = {x1,x2};
        }
        else if(largo_patroncito == 4){
          fscanf( fichero, lectura_patron, &x1, &x2 , &x3, &x4);
          patron_lectura = {x1, x2, x3, x4};
        }
        else if(largo_patroncito == 8){
          fscanf( fichero, lectura_patron, &x1, &x2 , &x3, &x4, &x5, &x6 , &x7, &x8);
          patron_lectura = {x1, x2, x3, x4 ,x5, x6 , x7, x8};
        }
        else if(largo_patroncito == 16){
          fscanf( fichero, lectura_patron, &x1, &x2 , &x3, &x4, &x5, &x6 , &x7, &x8, &x9, &x10 , &x11, &x12, &x13, &x14 , &x15, &x16);
          patron_lectura = {x1, x2, x3, x4 ,x5, x6 , x7, x8, x9, x10 , x11, x12, x13, x14 , x15, x16};
        }


        char path_asap1_largo[100];   
        strcpy(path_asap1_largo,path_asap1); 
        strcat(path_asap1_largo,separate); 
        strcat(path_asap1_largo,number_path); 

        char path_asap2_largo[100];   
        strcpy(path_asap2_largo,path_asap2); 
        strcat(path_asap2_largo,separate); 
        strcat(path_asap2_largo,number_path); 

       /* char path_csa1_largo[100];   
        strcpy(path_csa1_largo,path_csa1); 
        strcat(path_csa1_largo,separate); 
        strcat(path_csa1_largo,number_path); 

        char path_csa2_largo[100];   
        strcpy(path_csa2_largo,path_csa2); 
        strcat(path_csa2_largo,separate); 
        strcat(path_csa2_largo,number_path); 
*/
        if(i == 1){
          remove( path_asap1_largo );
          remove( path_asap2_largo );
    //      remove( path_csa1_largo );
      //    remove( path_csa2_largo );

          
        }

        //cout << patron_lectura << "\n\n";
        TWA.countbyIntVectorSave(patron_lectura,path_asap1_largo) ;
        TWA2.countbyIntVectorSave(patron_lectura,path_asap2_largo) ;
        //csa_to2.countbyIntVectorSave(patron_lectura,path_csa2_largo) ;
        //csa_to.countbyIntVectorSave(patron_lectura,path_csa1_largo) ;
    }

    if( !fclose(fichero) )
        printf( "Fichero cerrado\n" );
    else
    {
        printf( "Error: fichero NO CERRADO\n" ); 
    }
  }
  /**/

}


  return 0;

}

