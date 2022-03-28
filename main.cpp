#include "algorytmy_sortowania.hh"
#include <iostream>
#include <chrono>
#include <fstream>
#include <math.h>

#define TYP_DANYCH int

template<typename Typ>
using WskaznikAlgorytmu = void(*)(Typ*, Typ*, int, int);

template<typename Typ>
void zapelnijTabliceLosowo(Typ* tab, int n)
{
    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {
        tab[i] = rand() % 150000 + 1;
    }
}

template<typename Typ>
void posortujDanyProcentElementow(Typ* tab, int n, double procent)
{
    if(procent==100)
    {
        std::sort(tab, tab + n, std::greater<Typ>());
        return;
    }

    std::sort(tab, tab + static_cast<int>((n*procent)/100));
}

template<typename Typ>
void czyPosortowana(Typ* tab, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        if (tab[i] > tab[i+1])
        {
            std::cout<<"Tablica nieposortowana!\n";
            exit(1);
        }     
    }
}

template<typename Typ>
void wyswietlTablice(Typ* tab, int n)
{
    for (int i = 0; i < n ; i++)
    {
        std::cout<<tab[i]<<" | ";
    }
    std::cout<<std::endl;
}
template<typename Typ>
double sortuj(WskaznikAlgorytmu<TYP_DANYCH> wsk, int n, Typ* tab, Typ* pom)
{
    auto czasStart = std::chrono::high_resolution_clock::now();
    wsk(tab, pom, 0, n-1);
    auto czasStop = std::chrono::high_resolution_clock::now();

    return std::chrono::duration<double, std::milli>(czasStop - czasStart).count();
}

template<typename Typ>
Typ* stworzTablice(int rozmiar)
{
    return new Typ[rozmiar];
}

template<typename Typ>
void usunTablice(Typ* tab)
{
    delete[] tab;
}

int main()
{
    std::ofstream plik("CzasSortowania1.txt");
    if (!plik.is_open())
    {
        std::cout << "Plik nie otwarty! \n";
        exit(1);
    }

    int iloscTablic = 1;
    int rozmiarTablic[5] = {10000, 50000, 100000, 500000, 1000000};
    double procentPosortowania[8] = {0, 25, 50, 75, 95, 99, 99.7, 100};
    std::string algorytmy[3] = {"Sortowanie przez scalanie", "Sortowanie szybkie", "Sortowanie introspektywne"};

    WskaznikAlgorytmu<TYP_DANYCH> scalanie = &sortowaniePrzezScalanie;
    WskaznikAlgorytmu<TYP_DANYCH> szybkie = &sortujPrzezSortowanieSzybkie;
    WskaznikAlgorytmu<TYP_DANYCH> introspektywne = &sortujIntrospektywnie;
    WskaznikAlgorytmu<TYP_DANYCH> tablicaWsk[3] = {scalanie, szybkie, introspektywne};
    
    double czas = 0;
    int j = 0;

    for(WskaznikAlgorytmu<TYP_DANYCH> wsk : tablicaWsk)
    {
        std::cout<< algorytmy[j] << std::endl;
        plik << algorytmy[j++] << "\n";
        for(double procent : procentPosortowania)
        {
            for(int n : rozmiarTablic)
            {
                TYP_DANYCH *tab = stworzTablice<TYP_DANYCH>(n);
                TYP_DANYCH *pom = stworzTablice<TYP_DANYCH>(n);

                for(int i = 0; i < iloscTablic; i++)
                {
                    zapelnijTabliceLosowo<TYP_DANYCH>(tab, n);
                    posortujDanyProcentElementow<TYP_DANYCH>(tab, n, procent);
                    czas += sortuj<TYP_DANYCH>(wsk, n, tab, pom);
                    czyPosortowana<TYP_DANYCH>(tab, n);
                }
                usunTablice<TYP_DANYCH>(tab);
                usunTablice<TYP_DANYCH>(pom);

                std::cout << "tablice o rozmiarze "<< n << " posortowane" << std::endl;

                plik << czas / iloscTablic << " ";
                czas = 0;
            }
            plik << "\n";
            std::cout << "Tablice o "<< procent <<"%" << " początkowych elementów posegregowanych posortowane" << std::endl; 
        }
        plik << "\n";
    }
    std::cout << "Koniec sortowania! \n";
	plik.close();
}