#include <stdio.h>
#include <stdlib.h>     /* srand, rand */

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sdsl/vectors.hpp>

#include <sdsl/rl_runs.hpp> // Runlenght | Jose Fuentes
#include <sdsl/wt_rlmn.hpp> // Original de la sdsl Navarro 
#include "../csa/Csa.h" 

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

  char *file = argv[1];
  char *tipo_csa = argv[2];
  int itipo_csa = parse<int>(tipo_csa);

  char *lectura_path = "../Lectura/";
  char *t0_path = "/T0";
  int_vector<> t0 = int_vector<>();

  char path_in[100];   
  strcpy(path_in,lectura_path); 
  strcat(path_in,file); 
  strcat(path_in,t0_path); 
  load_from_file(t0, path_in);

  if(itipo_csa == 1 || itipo_csa == 0){
    Csa<  rl_runs< 64,  wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<> > >  > csa_to(t0); 
    char *tipo_csa = "/csa_rl_runs";
    char path_out[100];   
    strcpy(path_out,lectura_path); 
    strcat(path_out,file); 
    strcat(path_out,tipo_csa); 
    cout << path_out;
    store_to_file(csa_to.csa, path_out);
  }
  if(itipo_csa == 2 || itipo_csa == 0){
    Csa< wt_rlmn<sd_vector<>,sd_vector<>::rank_1_type,sd_vector<>::select_1_type,wt_int<> > > csa_to(t0); 
    char *tipo_csa = "/csa_wt_rlmn";
    char path_out[100];   
    strcpy(path_out,lectura_path); 
    strcat(path_out,file); 
    strcat(path_out,tipo_csa); 
    cout << path_out;
    store_to_file(csa_to.csa, path_out);
  }

  return 0;

}

