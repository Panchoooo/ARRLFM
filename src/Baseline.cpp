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
    construct_im(&AWT,bwt,0);
}