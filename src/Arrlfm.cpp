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


#include <chrono>
#include <thread>

using namespace std;
using namespace sdsl;


bool checkSymbol(char w){
    if( isalpha(w) || isdigit(w) ){
        return false;
    }
    return true;
}
std::vector<std::string> readWords(std::ifstream& file, size_t reservedSize = 0) {
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
                if(end < buffer.length() && checkSymbol((char)buffer[start])){ // Si comienza con caracter especial evitamos ciclo para añadirlo al arreglo
                    ++end;
                }else{
                    while(end < buffer.length() && !isspace(buffer[end]) ){ // En caso contrario, avanzamos en la palabra hasta encontrar un espacio
                        ++end;
                    }
                    while(checkSymbol((char)buffer[end-1]) ){ // Luego verificamos si termina en caracteres especiales para actualizar indice
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
std::vector<std::string> readWordsOfString(string buffer, size_t reservedSize = 0) {
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
            if(end < buffer.length() && checkSymbol((char)buffer[start])){ // Si comienza con caracter especial evitamos ciclo para añadirlo al arreglo
                ++end;
            }else{
                while(end < buffer.length() && !isspace(buffer[end]) ){ // En caso contrario, avanzamos en la palabra hasta encontrar un espacio
                    ++end;
                }
                while(checkSymbol((char)buffer[end-1]) ){ // Luego verificamos si termina en caracteres especiales para actualizar indice
                    --end;
                }
            }
            words.push_back(buffer.substr(start, end - start));
            start += end - start;
        }
    }
    return words;
}


template<class Estructura >
Arrlfm<Estructura>::Arrlfm ( string input_file, unsigned method ) {

    // Lectura archivo .txt | cambiar a binario en un futuro
    string word;
    uint64_t contador = 0 ;
    uint64_t ultimo_simbolo = 1;

    // Creamos Texto de simbolos
    ifstream stream(input_file);
    vector<string> words = readWords(stream); // Leemos todas las palabras y las ingresmaos a un arreglo
    for (const string& e : words) { 
        if (W2S.find(e) == W2S.end() ) { // Si no existe en el diccionario, lo agregamos y seteamos simbolo nuevo
            W2S[e] = ultimo_simbolo;
            ultimo_simbolo+=1;
        }
        t.resize(t.size()+1);
        t[t.size()-1] = W2S[e];
        //t0.resize(t0.size()+1);
        //t0[t0.size()-1] = W2S[e];
        contador+=1;

    }
    t0 = t;
    t.resize(t.size()+1);
    t[t.size()-1] = 0;

    long unsigned int simbolo_anterior = -1 ;
    int simbolos_unicos = 0;
    util::bit_compress(t);
    util::bit_compress(t0);

    qsufsort::construct_sa(sa, t); // Se crea arreglo de sufijos sa en base a t
    util::bit_compress(sa);
    BWT = int_vector<>(sa.size()); 
    for (long unsigned int i = 0; i < sa.size(); i++) { // Generamos BWT y arreglo C en base a sa
        if(sa[i]!=0){
            BWT[i] = t[sa[i]-1];
        }else{
            BWT[i] = 0;
        }
        if(t[sa[i]] != simbolo_anterior){
            simbolo_anterior = t[sa[i]];
            simbolos_unicos+=1;
            C.resize(simbolos_unicos);
            C[simbolos_unicos-1] = i;
        }
    }

    C.resize(C.size()+1);
    C[C.size()-1] = t.size();
    uint64_t* buffer = new uint64_t[BWT.size()]; 
    for (uint64_t i = 0; i < BWT.size(); i++) { 
        buffer[i] = BWT[i];
    }
    FILE * pFile;
    pFile = fopen ("Data/binario.bin", "wb");
    fwrite (buffer, sizeof(uint64_t), BWT.size(), pFile);
    AWT = new Estructura("Data/binario.bin", method); // Creamos nuestra estructura entregandole la BWT construida*/
}


template<class Estructura >
Arrlfm<Estructura>::Arrlfm ( int_vector<> tp, unsigned method ) {
    t = tp;
    t0 = t;
    t.resize(t.size()+1);
    t[t.size()-1] = 0;

    long unsigned int simbolo_anterior = -1 ;
    int simbolos_unicos = 0;
    util::bit_compress(t);
    util::bit_compress(t0);

    qsufsort::construct_sa(sa, t); // Se crea arreglo de sufijos sa en base a t
    util::bit_compress(sa);
    BWT = int_vector<>(sa.size()); 
    for (long unsigned int i = 0; i < sa.size(); i++) { // Generamos BWT y arreglo C en base a sa
        if(sa[i]!=0){
            BWT[i] = t[sa[i]-1];
        }else{
            BWT[i] = 0;
        }
        if(t[sa[i]] != simbolo_anterior){
            simbolo_anterior = t[sa[i]];
            simbolos_unicos+=1;
            C.resize(simbolos_unicos);
            C[simbolos_unicos-1] = i;
        }
    }

    C.resize(C.size()+1);
    C[C.size()-1] = t.size();
    uint64_t* buffer = new uint64_t[BWT.size()]; 
    for (uint64_t i = 0; i < BWT.size(); i++) { 
        buffer[i] = BWT[i];
    }
    FILE * pFile;
    pFile = fopen ("binario.bin", "wb");
    fwrite (buffer, sizeof(uint64_t), BWT.size(), pFile);
    AWT = new Estructura("binario.bin", method); // Creamos nuestra estructura entregandole la BWT construida
}

template<class Estructura >
Arrlfm<Estructura>::Arrlfm (char* file, int_vector<> bwt,int_vector<> c, unsigned method ) {
    C = c;
    BWT = bwt;
    /*uint64_t* buffer = new uint64_t[BWT.size()]; 
    for (uint64_t i = 0; i < BWT.size(); i++) { 
        buffer[i] = BWT[i];
    }*/
    //FILE * pFile;
    //pFile = fopen (file, "wb");
    //fwrite (buffer, sizeof(uint64_t), BWT.size(), pFile);
    //AWT = new Estructura("binario.bin", method); // Creamos nuestra estructura entregandole la BWT construida
    AWT = new Estructura(file, method); // Creamos nuestra estructura entregandole la BWT construida*/
}

template<class Estructura>
Arrlfm<Estructura>::~Arrlfm ( void ) {
}



template<class Estructura>
unsigned Arrlfm<Estructura>::countbyIntVector (int_vector<> patron) {  

    uint64_t c = patron[patron.size()-1];
    uint64_t b = C[c];
    uint64_t e = C[c+1];
    uint64_t contador = 0;
    cout << "\nPaso 0 |  C: " << c << " |  b: " << b << "  | e: " << e << "  | C[c]: " << C[c] << "  | C[c+1]: " << C[c+1] << "\n"; 
    if( patron.size() > 1){
        for ( long int  i = patron.size() - 2 ; i >= 0 ; i = i - 1) { // long int porque al llegar a 0 y hace el -1 se rompe 
            cout << "Paso "<<contador ;
            if(b==e){
                break;
            }
            cout << " aun queda" ;

            c = patron[i];

            cout << "  c a leer : " << c<<"\n";
            //uint64_t aa = AWT->rank(b,c);
            //uint64_t ab = AWT->rank(e,c);
            b = C[c] + AWT->rank(b,c);
            cout << "b: " << b<<"\n";

            cout << "e previo: "<< e <<"\n";
            e = C[c] + AWT->rank(e,c);
            cout << "e: " << e<<"\n";




            contador+=1;
            cout << "Paso "<< contador <<" |  C: " << c << " |  b: " << b << "  | e: " << e << "  | C[c]: " << C[c] << "\n"; 

        }
    }
    return e-b;
}


template<class Estructura>
unsigned Arrlfm<Estructura>::countbyIntVectorSave (int_vector<> patron,char* output) {  
    clock_t begin, end;
    double cpu_time_used;
    ofstream myfile2 (output, std::ios::app);
    begin = clock();
    uint64_t c = patron[patron.size()-1];
    uint64_t b = C[c];
    uint64_t e = C[c+1];
    if( patron.size() > 1){
        for ( long int  i = patron.size() - 2 ; i >= 0 ; i = i - 1) { // long int porque al llegar a 0 y hace el -1 se rompe 
            if(b==e){
                break;
            }
            c = patron[i];
            b = C[c] + AWT->rank(b,c);
            e = C[c] + AWT->rank(e,c);
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - begin)) / CLOCKS_PER_SEC;
    myfile2 << e-b << " " << cpu_time_used <<   "\n";
    return e-b;
}

template<class Estructura>
unsigned Arrlfm<Estructura>::countbyString (string patron) {  
    std::vector<std::string> words = readWordsOfString(patron); // Leemos todas las palabras y las ingresmaos a un arreglo
    uint64_t contador = 0 ;
    int_vector<> patron_int;
    for (const string& e : words) {  // Usamos diccionario W2S para transformar el patron a los simbolos respectivos
        string a = e;
        if(W2S[a] == 0 ){
            return 0;
        }
        contador += 1;
        patron_int.resize(contador);
        patron_int[contador-1] = W2S[a];
        
    }
    return countbyIntVector(patron_int);
}

template<class Estructura>
unsigned long Arrlfm<Estructura>::size () {  
    unsigned long sum = AWT->size();
    sum+= size_in_bytes(C);
    return sum;
}
template<class Estructura>
unsigned long Arrlfm<Estructura>::size2 () {  
    unsigned long sum = AWT->size2();
    sum+= size_in_bytes(C);
    return sum;
}
template<class Estructura>
void Arrlfm<Estructura>::getBWT () {  
    cout << "BWT:  ";
    for (long unsigned int i = 0; i < BWT.size(); i++) {
        cout << BWT[i] << " ";
    }
}
template<class Estructura>
void Arrlfm<Estructura>::getT () {  
    cout << "T:  ";
    for (long unsigned int i = 0; i < t.size(); i++) {
        cout << t[i] << " ";
    }
}
template<class Estructura>
void Arrlfm<Estructura>::getC () {  
    cout << "\nC:  ";
    for (long unsigned int i = 0; i < C.size(); i++) {
        cout << C[i] << " ";
    }
}
template<class Estructura>
void Arrlfm<Estructura>::getSA () {  
    cout << "\nSA:  ";
    for (long unsigned int i = 0; i < sa.size(); i++) {
        cout << sa[i] << " ";
    }
}
template<class Estructura>
void Arrlfm<Estructura>::printW2S () {  
    ofstream myfile2 ("dict.txt");
    for (auto const &pair: W2S) {
        myfile2 << "{" << pair.first << ": " << pair.second << "}\n";
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

template<class Estructura>
string Arrlfm<Estructura>::buscarPatron(int largo_patron){
  int v2 = rand() % S2W.size() + 1;
  string patrin_i = "";
  for(int p = 0 ; p < largo_patron ; p++){
    patrin_i += S2W[v2+p];
    if(p + 1 != largo_patron){
      patrin_i+= " ";
    }
  }
  return patrin_i;
}




template<class Estructura>
void Arrlfm<Estructura>::saveBWT (char* output) {  

    uint64_t largo_runs_promedio = 0; 
    uint64_t largo_runs = 0; 
    uint64_t camtidad_runs = 0; 
    int wt_len ;
    int promedio;
    ofstream myfile2 (output);
    for ( auto &x: AWT->s_wt_trees ){

        largo_runs_promedio = 0; 
        largo_runs = 0; 
        camtidad_runs = 0; 
        wt_len = x.second.size(); // cantidad de simbolos 
        for(int w = 0 ; w < wt_len ; w++){
            if(w>0 &&  x.second[w] !=  x.second[w -1 ]){
                if(largo_runs > 1 ){
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

        myfile2 << camtidad_runs << ";" << promedio << "\n";
    }

}