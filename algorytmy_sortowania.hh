#ifndef ALGORYTMY_SORTOWANIA_HH 
#define ALGORYTMY_SORTOWANIA_HH    

#include <algorithm>

template<typename Typ>
void sortowaniePrzezScalanie(Typ* tab, Typ* pom, int l, int p);

template<typename Typ>
void sortujPrzezSortowanieSzybkie(Typ* tab, Typ* pom, int l, int p);

template<typename Typ>
void sortowanieIntrospektywne(Typ* tab, int n, int M);

template<typename Typ>
void hybrydoweSortowanieIntrospektywne(Typ* tab, int n);

template<typename Typ>
void sortujIntrospektywnie(Typ* tab, Typ* pom, int n, int i);

template<typename Typ>
void kopcowanie(Typ* tab, int i, int n);

// template<typename Typ>
// void scal(Typ* tab, Typ* pom,  int l, int s, int p);

// template<typename Typ>
// int podziel(Typ* tab, int l, int p);

// template<typename Typ>
// void sortowanieSzybkie(Typ* tab, int l, int p);

// template<typename Typ>
// void sortowaniePrzezKopcowanie(Typ* tab, int n);


// template<typename Typ>
// void sortowaniePrzezWstawianie(Typ* tab, int l, int p);


 #endif