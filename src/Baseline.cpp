#include "Asap.h"
#include "bit_vectors.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <sdsl/wavelet_trees.hpp>
#include <sdsl/vectors.hpp>


#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#include <chrono>
#include <thread>

using namespace std;
using namespace sdsl;


bool checkSymbolb(char w){
    if( isalpha(w) || isdigit(w) ){
        return false;
    }
    return true;
}
std::vector<std::string> readWordsb(std::ifstream& file, size_t reservedSize = 0) {
    std::string buffer;
    std::vector<std::string> words;
    words.reserve(reservedSize);

    int salto_de_linea = 0;
    while (file.good()) {
        std::getline(file, buffer); // Leemos una fila
        if(salto_de_linea == 1){ // Agregamos un salto de linea por cada linea leida solo en caso de existir mas de 1 linea
            words.emplace_back("\n");
        }
        for(size_t start = 0, end = 0; start < buffer.length();) { 
            if (buffer[start] == ' ') { // En caso de encontrar un espacio
                //++start;  // ignoramos el primero
                //end = start;
                while(end < buffer.length() && buffer[end] == ' ') // Contamos cuantos espacios consecutivos existen
                    ++end;
                for (; start != end; ++start)  // Se guardan en el arreglo de palabras
                    words.emplace_back(" ");
            }
            else {
                //skip all whitespace characters, except ' '
                while(start < buffer.length() &&
                        buffer[start] == '\v' &&
                        buffer[start] == '\r' &&
                        buffer[start] == '\n')
                        ++start;
                // Se cuentan caracteres distintos de espacio o caracteres especiales
                if(end < buffer.length() && checkSymbolb((char)buffer[start])){ // Si comienza con caracter especial evitamos ciclo para añadirlo al arreglo
                    ++end;
                }else{
                    while(end < buffer.length() && !isspace(buffer[end]) ){ // En caso contrario, avanzamos en la palabra hasta encontrar un espacio
                        ++end;
                    }
                    while(checkSymbolb((char)buffer[end-1]) ){ // Luego verificamos si termina en caracteres especiales para actualizar indice
                        --end;
                    }
                }
                 words.push_back(buffer.substr(start, end - start));
                start += end - start;
            }
        }
        salto_de_linea=1;
    }
    return words;
}
std::vector<std::string> readWordsOfStringb(string buffer, size_t reservedSize = 0) {
    std::vector<std::string> words;
    words.reserve(reservedSize);
    for(size_t start = 0, end = 0; start < buffer.length();) { 
        if (buffer[start] == ' ') { // En caso de encontrar un espacio
            //++start;  // ignoramos el primero
            //end = start;
            while(end < buffer.length() && buffer[end] == ' ') // Contamos cuantos espacios consecutivos existen
                ++end;
            for (; start != end; ++start)  // Se guardan en el arreglo de palabras
                words.emplace_back(" ");
        }
        else {
            //skip all whitespace characters, except ' '
            while(start < buffer.length() &&
                    buffer[start] == '\v' &&
                    buffer[start] == '\r' &&
                    buffer[start] == '\n')
                    ++start;
            // Se cuentan caracteres distintos de espacio o caracteres especiales
            if(end < buffer.length() && checkSymbolb((char)buffer[start])){ // Si comienza con caracter especial evitamos ciclo para añadirlo al arreglo
                ++end;
            }else{
                while(end < buffer.length() && !isspace(buffer[end]) ){ // En caso contrario, avanzamos en la palabra hasta encontrar un espacio
                    ++end;
                }
                while(checkSymbolb((char)buffer[end-1]) ){ // Luego verificamos si termina en caracteres especiales para actualizar indice
                    --end;
                }
            }
            words.push_back(buffer.substr(start, end - start));
            start += end - start;
        }
    }
    return words;
}


template<class Estructura>
Baseline<Estructura>::~Baseline ( void ) {
}


template<class Estructura >
Baseline<Estructura>::Baseline (char* file, int_vector<> bwt,int_vector<> c ) {
    C = c;
    BWT = bwt;
    construct_im(AWT,bwt,0);
}

template<class Estructura>
unsigned Baseline<Estructura>::countbyIntVectorSave (int_vector<> patron,char* output) {  
    clock_t begin, end;
    double cpu_time_used;
    ofstream myfile2 (output, std::ios::app);
    begin = clock();
    uint64_t c = patron[patron.size()-1];
    uint64_t b = C[c];
    uint64_t e = C[c+1];
    
    cout << "c: " << c << "\n";
    cout << "b:" << b << "  e:" << e << "\n";

    if( patron.size() > 1){
        for ( long int  i = patron.size() - 2 ; i >= 0 ; i = i - 1) { // long int porque al llegar a 0 y hace el -1 se rompe 
            if(b==e){
                break;
            }
            c = patron[i];
            cout << "\n" <<  "c: " << c << "\n";
            cout << "b:" << b << "  e:" << e << "\n";
            b = C[c] + AWT.rank(b,c);
            cout << "bn: "<< b << "\n";
            e = C[c] + AWT.rank(e,c);
            cout << "en: "<< e << "\n";


        }
    }
    end = clock();
    cpu_time_used = ((double) (end - begin)) / CLOCKS_PER_SEC;
    myfile2 << e-b << " " << cpu_time_used <<   "\n";
    return e-b;
}

template<class Estructura>
unsigned long Baseline<Estructura>::size () {  
    unsigned long sum = size_in_bytes(AWT);
    sum+= size_in_bytes(C);
    return sum;
}



template<class Estructura>
void Baseline<Estructura>::testing (char* file,char* nasap1, char *lectura_path) { 
    cout << file << "\n"; 
    cout << nasap1 << "\n"; 
    cout << lectura_path << "\n"; 


  char path_asap1[100];              
  char path_asapfolder[100];           
  clock_t begin, end;
  double cpu_time_used;


  int largo_patroncito = 4;
  FILE *fichero;
  unsigned int i, x1, x2, x3, x4, x5, x6 , x7, x8, x9, x10 , x11, x12, x13, x14 , x15, x16;
  uint32_t cantidad_patrones = 30000;
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
     
  strcpy(path_asap1,path_output); 
  strcat(path_asap1,nasap1); 


  strcpy(path_asapfolder,path_output);
  strcat(path_asapfolder,nasap1); 
  cout << path_bin << "\n";
  fs::create_directories(path_asapfolder); // Crear carpeta si no existe

  /*char path_mem[100];   
  strcpy(path_mem,lectura_path);
  strcat(path_mem,file); 
  strcat(path_mem,"/Memoria/"); 
  strcat(path_mem,nasap1); 
  strcat(path_mem,"_Memoria.txt"); 
  cout << path_mem << "\n";
  ofstream myfile2 (path_mem);
  myfile2 << AWT->size();
  myfile2 << TWA.size2();
 //cout << TWA.size2();*/


if(true){

// PATRONES 
  for(int lp = 4 ; lp < 17 ; lp=lp*2){
      
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
        return;
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


        char path_asap1_largo[500];   
        strcpy(path_asap1_largo,path_asap1); 
        strcat(path_asap1_largo,separate2); 
        strcat(path_asap1_largo,nasap1); 
        strcat(path_asap1_largo,separate); 
        strcat(path_asap1_largo,number_path); 

        if(i == 1){
          remove( path_asap1_largo );
        }
        cout << "\n\n" << patron_lectura << "\n";

        clock_t begin, end;
        double cpu_time_used;

        ofstream myfile2 (path_asap1_largo, std::ios::app);
        begin = clock();
        unsigned r = countbyIntVectorSave(patron_lectura,path_asap1_largo) ;
        end = clock();
        cpu_time_used = ((double) (end - begin)) / CLOCKS_PER_SEC;
        myfile2 << r << " " << cpu_time_used <<   "\n";


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


}