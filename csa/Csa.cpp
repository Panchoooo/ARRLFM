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

using namespace std;
using namespace sdsl;

template<class Estructura >
Csa<Estructura>::Csa ( int_vector<> t0  ) {
    construct_im(csa, t0,0);
}

template<class Estructura >
Csa<Estructura>::Csa ( char* file  ) {
    load_from_file(csa, file);
}


template<class Estructura>
Csa<Estructura>::~Csa ( void ) {
}


template<class Estructura>
unsigned Csa<Estructura>::countbyIntVector (int_vector<> patron) {  
    uint64_t c = patron[patron.size()-1];
    uint64_t b = csa.C[c];
    uint64_t e = csa.C[c+1];
    uint64_t contador = 0;
    cout << "\nPaso 0 |  C: " << c << " |  b: " << b << "  | e: " << e << "  | C[c]: " << csa.C[c] << "  | C[c+1]: " << csa.C[c+1] << "\n"; 
    if( patron.size() > 1){
        for ( long int  i = patron.size() - 2 ; i >= 0 ; i = i - 1) { // long int porque al llegar a 0 y hace el -1 se rompe 
            if(b==e){
                break;
            }
            
            c = patron[i];

            uint64_t aa = csa.bwt.rank(b,c);
            uint64_t ab = csa.bwt.rank(e,c);
            b = csa.C[c] + csa.bwt.rank(b,c);
            e = csa.C[c] + csa.bwt.rank(e,c);
            contador+=1;
            //cout << "\nPaso "<< contador <<" |  C: " << c << " |  b: " << b << "  | e: " << e << "  | C[c]: " << csa.C[c]  << "\n"; 
            //cout << "Paso "<< contador <<" |  C: " << c << " |  b: " << b << "  | e: " << e << "  | C[c]: " << csa.C[c] << " |  AWT->rank(b,c): "<<  csa.bwt.rank(b,c)<< " |  AWT->rank(e,c): "<<  csa.bwt.rank(e,c)<< "\n"; 
            cout << "Paso "<< contador <<" |  C: " << c << " |  b: " << b << "  | e: " << e << "  | C[c]: " << csa.C[c] << " |  AWT->rank(b,c): "<<  aa<< " |  AWT->rank(e,c): "<< ab<< "\n"; 

        }
    }
    return e-b;
}

template<class Estructura>
unsigned Csa<Estructura>::countbyIntVectorSave (int_vector<> patron,char* output) {  

  clock_t begin, end;
  double cpu_time_used;
    ofstream myfile2 (output, std::ios::app);
    begin = clock();
    uint64_t c = patron[patron.size()-1];
    uint64_t b = csa.C[c];
    uint64_t e = csa.C[c+1];

    if( patron.size() > 1){
        for ( long int  i = patron.size() - 2 ; i >= 0 ; i = i - 1) { // long int porque al llegar a 0 y hace el -1 se rompe 
            if(b==e){
                break;
            }

            c = patron[i];
            b = csa.C[c] + csa.bwt.rank(b,c);
            e = csa.C[c] + csa.bwt.rank(e,c);

        }
    }
    end = clock();
    cpu_time_used = ((double) (end - begin)) / CLOCKS_PER_SEC;
    myfile2 << e-b << " " << cpu_time_used <<  "\n";
    return e-b;
}


template<class Estructura>
unsigned Csa<Estructura>::countbyString (string patron) {  

}



template<class Estructura>
void Csa<Estructura>::saveBWT (char* output) {  

    ofstream myfileInfo (output);
    uint64_t largo_runs_promedio = 0; 
    uint64_t largo_runs = 0; 
    uint64_t camtidad_runs = 0; 
    uint64_t promedio;
    for (uint64_t i = 0; i < csa.bwt.size(); i++) { 
        //cout << csa.bwt[i]  << " ";
        if(i>0 && csa.bwt[i] != csa.bwt[i-1]){
            if(largo_runs > 1 ){
                //cout << i << " "<< BWT[i-1]<< "  " << BWT[i] <<  "  " << largo_runs << "\n";
                camtidad_runs += 1;
                largo_runs_promedio+= largo_runs;
            }
            largo_runs = 1 ;
        }else{
            largo_runs +=1;
        }
    }
    if(camtidad_runs != 0){
        promedio = largo_runs_promedio/camtidad_runs;
    }else{
        promedio = 0;
    }
    FILE * pFile;
    myfileInfo << "BWT_cantidad_runs=" << (camtidad_runs) << "\n";
    myfileInfo << "BWT_largo_promedio=" << (promedio) << "\n";

}

