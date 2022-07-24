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

#include <sdsl/suffix_arrays.hpp> // CSA nativo
#include <algorithm>

using namespace std;
#include <cstdlib>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using namespace sdsl;

template <class T>
T parse(const std::string& s)
{
  T out;
  std::stringstream ss(s);
  ss >> out;
  return out;
}
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
void load ( string input_file, unsigned method ) {

    string word;
    int_vector<> t; // texto de simbolos
    int_vector<> t0; // texto de simbolos sin 0 final
    uint64_t contador = 0 ;
    uint64_t ultimo_simbolo = 1;  
    int_vector<> C; // arreglo C
    int_vector<> sa; // suffix array
    unordered_map<uint64_t, string > S2W; // Symbol to Word
    unordered_map<string, uint64_t> W2S; // Word to Symbol
    int_vector<> BWT; // barrows wheeler

    string prepath = "/data/pizzachili/";


    // Creamos Texto de simbolos
    ifstream stream("/data/pizzachili/"+input_file);

    fs::create_directories(prepath+input_file);
/*
    ofstream myfile2 (prepath+input_file+"/Simbolos.txt");
    ofstream myfileInfo (prepath+input_file+"/InfoTexto.txt");
    vector<string> words = readWords(stream); // Leemos todas las palabras y las ingresmaos a un arreglo
    for (const string& e : words) { 
        if (W2S.find(e) == W2S.end() ) { // Si no existe en el diccionario, lo agregamos y seteamos simbolo nuevo
            W2S[e] = ultimo_simbolo;
            ultimo_simbolo+=1;
        }
        t.resize(t.size()+1);
        t[t.size()-1] = W2S[e];
        myfile2 << W2S[e] << " ";
        contador+=1;
    }
    contador+=1;
    myfile2 << 0;

    t0 = t;

    myfileInfo << "Cantidad_simbolos=" << (contador-1) << "\n";
    myfileInfo << "Simbolos_distintos=" << (ultimo_simbolo-1) << "\n";

    string file = "T0";
    store_to_file(t0, prepath+input_file+"/"+file);

    t.resize(t.size()+1);
    t[t.size()-1] = 0;

    ofstream myfile3 (prepath+input_file+"/dict.txt");
    for (auto const &pair: W2S) {
        myfile3 << "{" << pair.first << ": " << pair.second << "}\n";
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }

    long unsigned int simbolo_anterior = -1 ;
    int simbolos_unicos = 0;
    util::bit_compress(t);

    qsufsort::construct_sa(sa, t); // Se crea arreglo de sufijos sa en base a t
    util::bit_compress(sa);
    BWT = int_vector<>(sa.size()); 
    uint64_t i = 0;
    for ( i = 0; i < sa.size(); i++) { // Generamos BWT y arreglo C en base a sa
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
    
    //BWT[i]= 0;

    file = "BWT";
    store_to_file(BWT, prepath+input_file+"/"+file);
    /*int_vector<> bwwt = int_vector<>();
    load_from_file(bwwt, "BWT");
    cout << "BWT:  " << bwwt.size() << "\n";
    for (long unsigned int i = 0; i < bwwt.size(); i++) {
        cout << bwwt[i] << " ";
    }*/

      ofstream myfile4 (prepath+input_file+"/bwtsimbolos.txt");
    for (long unsigned int i = 0; i < BWT.size(); i++) {
        myfile4 << BWT[i] << " ";
    }

   
    file = "C";
    store_to_file(C, prepath+input_file+"/"+file);
    /*int_vector<> cc = int_vector<>();
    load_from_file(cc, "C");
    cout << "C:  " << cc.size() << "\n";
    for (long unsigned int i = 0; i < cc.size(); i++) {
        cout << cc[i] << " ";
    }*/
    uint64_t* buffer = new uint64_t[BWT.size()];
    uint64_t largo_runs_promedio = 0; 
    uint64_t largo_runs = 0; 
    uint64_t camtidad_runs = 0; 
    for (uint64_t i = 0; i < BWT.size(); i++) { 

        if(i>0 && BWT[i] != BWT[i-1]){
            if(largo_runs > 1 ){
                //cout << i << " "<< BWT[i-1]<< "  " << BWT[i] <<  "  " << largo_runs << "\n";
                camtidad_runs += 1;
                largo_runs_promedio+= largo_runs;
            }
            largo_runs = 1 ;
        }else{
            largo_runs +=1;
        }
        buffer[i] = BWT[i];
    }
    FILE * pFile;
    myfileInfo << "BWT_cantidad_runs=" << (camtidad_runs) << "\n";
    myfileInfo << "BWT_largo_promedio=" << (largo_runs_promedio/camtidad_runs) << "\n";

    string s = prepath+input_file+"/binario.bin";
    int n = s.length();
    char char_array[n + 1];
    strcpy(char_array, s.c_str());
    pFile = fopen (char_array, "wb");
    fwrite (buffer, sizeof(uint64_t), BWT.size(), pFile);

    */
}


int main(int argc, char *argv[]) {

  char* file = argv[1];
  load(file, 0);  
  return 0;

}

