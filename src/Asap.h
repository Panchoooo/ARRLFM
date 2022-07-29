#ifndef ASAP
#define ASAP

#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <sdsl/vectors.hpp>
#include <sdsl/wavelet_trees.hpp>
#include "bit_vectors.h"
#include "m_wt/m_wt.h"

template<class BitVectorClass = SDBV, class IntType = uint8_t, class WaveletClass = sdsl::wt_gmr<> >
class Asap{
  private:
    unsigned text_length;
    std::unordered_map<IntType, unsigned> freq;


    std::tuple<IntType*, unsigned, std::unordered_map<IntType, unsigned>> readfile(std::string);

  public:
    std::unordered_map<unsigned, WaveletClass > s_wt_trees;
    std::unordered_map<unsigned, BitVectorClass* > bit_vectors;
    M_WT<IntType> *m;

    
    Asap<BitVectorClass, IntType, WaveletClass> ( std::string, unsigned);
    ~Asap<BitVectorClass, IntType, WaveletClass> (void);

    IntType access ( unsigned );
    unsigned rank (unsigned , IntType);
    int select ( unsigned, IntType );
    IntType* waccess ( unsigned, unsigned );

    std::tuple<IntType, double, bool, double, double, double, double> access_timecheck ( unsigned );
    std::tuple<unsigned, double, double, bool, double, double, double> rank_timecheck ( IntType, unsigned );
    std::tuple<int, double, bool, double, double, double, double> select_timecheck ( IntType, unsigned );

    std::tuple<IntType, bool, unsigned, double, double> accessTime ( unsigned );
    std::tuple<unsigned, bool, unsigned, double, double> rankTime ( IntType, unsigned );
    std::tuple<int, bool, unsigned, double, double> selectTime ( IntType, unsigned );
    std::tuple<IntType*, std::unordered_map<unsigned, double>> waccessTime ( unsigned, unsigned );

    unsigned length();
    unsigned long size ();
    unsigned long size2 ();
    unsigned long size3 (int tipo);
    unsigned long m_size ();
    unsigned partitions ();
    unsigned long b_size ();
    unsigned long sl_size ();
    unsigned long textsize ();

    unsigned alphabet_size();
    std::unordered_map<IntType, unsigned> frequency();
    std::vector<IntType> alphabet();
};

#include "Asap.cpp"
#endif
