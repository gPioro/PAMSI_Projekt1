#include "algorytmy_sortowania.hh"
#include <math.h>


/* Sortowanie przez scalanie */

template<typename Typ>
void scal(Typ* tab, Typ* pom, int l, int s, int p)
{
    int i, j;
 
    for(i = s + 1; i>l; i--) 
        pom[i-1] = tab[i-1]; 

    for(j = s; j<p; j++) 
        pom[p+s-j] = tab[j+1]; 
 
    for(int k=l;k<=p;k++) 
        if(pom[j]<pom[i])
            tab[k] = pom[j--];
        else
            tab[k] = pom[i++];
}

template<typename Typ>
void sortowaniePrzezScalanie(Typ* tab, Typ* pom, int l, int p)
{
    if(p > l)
    {
        int s = (l+p)/2;
        sortowaniePrzezScalanie(tab, pom, l, s);
        sortowaniePrzezScalanie(tab, pom, s+1, p);
        scal(tab, pom, l, s, p);
    }
}

template void sortowaniePrzezScalanie<int>(int* tab, int* pom, int l, int p);
template void sortowaniePrzezScalanie<double>(double* tab, double* pom, int l, int p);

/* Sortowanie szybkie */

template<typename Typ>
int podziel(Typ* tab, int l, int p)
{
    int podzial = tab[(l + p)/2];
    int i = l, j = p;

    while(true)
    {
        while(tab[j] > podzial)
        j--;

        while(tab[i] < podzial)
        i++;

        if (i < j)
        {
            std::swap(tab[i++],tab[j--]);
        } 
        else
        {
            return j;
        }
    }
}

template<typename Typ>
void sortowanieSzybkie(Typ* tab, int l, int p)
{
    if(l<p)
    {
        int q = podziel(tab, l, p);
        sortowanieSzybkie(tab, l, q);
        sortowanieSzybkie(tab, q + 1, p);
    }
}

template<typename Typ>
void sortujPrzezSortowanieSzybkie(Typ* tab, Typ* pom, int l, int p)
{
    sortowanieSzybkie(tab, l, p);
}

template void sortujPrzezSortowanieSzybkie<int>(int* tab, int* pom, int l, int p);
template void sortujPrzezSortowanieSzybkie<double>(double* tab, double* pom, int l, int p);


template<typename Typ>
void sortowaniePrzezKopcowanie(Typ* tab, int n)
{
    int i;
    for(i = n/2; i>0; --i)
    {
        kopcowanie(tab-1, i, n);
    }
    for(i = n-1; i>0; --i)
    {
        Typ pom;
        pom = tab[0];
        tab[0] = tab[i];
        tab[i] = pom;
        kopcowanie(tab-1, 1, i);
    }
}

template<typename Typ>
void kopcowanie(Typ* tab, int i, int n)
{
    int j;
    Typ pom;
    while(i<=n/2)
    {
        j=2*i;
        if(j+1<=n && tab[j+1]>tab[j])
        {
            j=j+1;
        }
        if(tab[i]<tab[j])
        {           
            pom = tab[i];
            tab[i] = tab[j];
            tab[j] = pom;
        }
        else 
        {
            break;
        }
        i = j;
    }
}

template<typename Typ>
void sortowaniePrzezWstawianie(Typ* tab, int l, int p)
{
    for(int i = l + 1; i <= p; i++)
    {
        int klucz = tab[i];
        int j = i;

        while(j > l && tab[j - 1] > klucz)
        {
            tab[j] = tab[j - 1];
            j--;
        }
        tab[j] = klucz;
    }
}

/* Sortowanie introspektywne */
template<typename Typ>
void sortowanieIntrospektywne(Typ* tab, int n, int M)
{
    int i;
    if(M<=0)
    {
        sortowaniePrzezKopcowanie(tab, n);
        return;
    }
    i = podziel(tab, 0, n);
    if(i>9)
        sortowanieIntrospektywne(tab, i, M-1);
    if(n-1-i>9)
        sortowanieIntrospektywne(tab+1+i, n-1-i, M-1);    
}

template<typename Typ>
void hybrydoweSortowanieIntrospektywne(Typ* tab, int n)
{
    sortowanieIntrospektywne(tab, n, (int)floor(2*log(n)/M_LN2));
    sortowaniePrzezWstawianie(tab, 0, n);
}

template<typename Typ>
void sortujIntrospektywnie(Typ* tab, Typ* pom, int n, int i)
{
    hybrydoweSortowanieIntrospektywne(tab, i);
}

template void sortujIntrospektywnie<int>(int* tab, int* pom, int n, int i);
template void sortujIntrospektywnie<double>(double* tab, double* pom, int n, int i);
