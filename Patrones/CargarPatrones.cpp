#include <stdio.h>
#include <stdlib.h>   
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <sdsl/vectors.hpp>

#include <bits/stdc++.h>
#include <cstdlib>
#include <filesystem>

using namespace std;
using namespace sdsl;
namespace fs = std::filesystem;

template <class T>
T parse(const std::string& s)
{
  T out;
  std::stringstream ss(s);
  ss >> out;
  return out;
}

# define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))

int main(int argc, char *argv[]) {

  srand (time(NULL));

  char *file = argv[1];

  char *t0_path = "/T0";
  char *out_path = "/Patrones/";
  char *lectura_path = "../Lectura/";
  char path_t0[100];   

  int_vector<> t0 = int_vector<>();

  strcpy(path_t0,lectura_path); 
  strcat(path_t0,file); 
  strcat(path_t0,t0_path); 
  load_from_file(t0, path_t0);

  uint64_t extension_patrones[4] = {2,4,8,16};
  uint64_t size = my_sizeof(extension_patrones)/my_sizeof(extension_patrones[0]);  
  uint64_t cantidad_por_largo = 50000;

  for( uint64_t l = 0; l < size ; l++){ 
    uint64_t ext_patr = extension_patrones[l] ; // Patrones de largo : 3,5,7
      
    char path_out[100];   
    strcpy(path_out,lectura_path); 
    strcat(path_out,file); 
    strcat(path_out,out_path); 
    std::string tmp = std::to_string(ext_patr);
    char const *num_char = tmp.c_str();
    fs::create_directories(path_out); // Crear carpeta si no existe

    strcat(path_out,"Largo"); 
    strcat(path_out,num_char); 
    strcat(path_out,".txt"); 
    //cout<< "\n\n" << path_out << "\n";
    ofstream myfile2 (path_out); // Archivo con los patrones

    for( uint64_t cpl = 0; cpl < cantidad_por_largo  ;cpl++){ // Queremos 10 muestras por cada largo de patron
      int random = rand() % (t0.size()-(ext_patr+1)) + 1;; // Posicion random en el texto
      //cout << ext_patr << "\n";
      for(uint64_t r = 0 ; r < ext_patr ; r++){ // Extraemos los r necesarios
        //cout << t0[random+r] ;
        myfile2 << t0[random+r];
        if(r + 1 != ext_patr){
          myfile2 << " ";
          //cout << " ";
        }
      }
      if(cpl + 1 != cantidad_por_largo){
        myfile2 << "\n";
       // cout << "\n";
      }
    }
  }
  //cout << "\n";
}