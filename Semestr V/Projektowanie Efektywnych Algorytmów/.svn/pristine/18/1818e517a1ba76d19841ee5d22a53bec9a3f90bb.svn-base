/* 
 * File:   ProblemKomiwojazera.h
 * Author: Piotr Chmiel, Maciej Stelmaszuk
 *
 * Created on 6 październik 2014, 18:34
 */

#ifndef PROBLEMKOMIWOJAZERA_H
#define	PROBLEMKOMIWOJAZERA_H

#include <algorithm>
#include <chrono>
#include <ctime>
#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <vector>
#include <Windows.h>

struct wezel
{
    int poziom_wezla_w_drzewie;
    std::vector <int> kombinacja_miast;
    int granica;
    
    bool operator<(const wezel &o) const
    {
        return granica < o.granica;
    }
};
struct miejsceWMacierzy
{
    std::vector<int> miejsce_w_MS;
    std::vector<int> miejsce_w_TMP;
};

class ProblemKomiwojazera 
{
public:
    ProblemKomiwojazera();
    ProblemKomiwojazera(int liczba_miast);
    ProblemKomiwojazera(const ProblemKomiwojazera& orig);
    virtual ~ProblemKomiwojazera();
    
    void algorytmProgramowaniaDynamicznego();
    std::vector<int> algorytmProgramowaniaDynamicznegoApprox();
    
    void algorytmPodzialuIOgraniczen();
    void Aproksymacyjny(double epsilon);
    void przegladZupelny();
    
    std::vector<std::vector<int>> podzialMiast(double epsilon);
    void wyswietlMacierzSasiedztwa();
    void zmienLiczbeMiast(int nowa_liczba_miast);
    void wczytajZPlikuTekstowego(std::string nazwa_pliku);
    void zapiszDoPlikuTekstowego(std::string nazwa_pliku);
    int pobierzLiczbeMiast() { return liczba_miast_; }
          
private: 
    void losujOdleglosciZPrzedzialuDoMacierzySasiedztwa(int poczatek_przedzialu, 
                                                        int koniec_przedzialu);
    void odbicieSymetryczneWzgledemGlownejPrzekatnej();
    void wyswietlKombinacjeMiast(int * kombinacja_miast, 
                                 int suma_odleglosci_pomiedzy_nimi);
    void wyswietlKombinacjeMiast(std::vector <int> kombinacja_miast, 
                                 int suma_odleglosci_pomiedzy_nimi);  
    void wykonanieKopiiTablicy(int * zrodlo, int * kopia);
    void inicjalizacjaTablicyJejNumeremIndexu (int * tablica);
    void generowanieLosowejPermutacji (int * tablica);
    int funkcjaOgraniczen(wezel wezel_drzewa);
    bool czyJestWKombinacji (int i, wezel wezel_drzewa);
    int sumaOdleglosciDoPokonaniaPomiedzyMiastami(int * kombinacja_miast);
    int sumaOdleglosciDoPokonaniaPomiedzyMiastami(std::vector <int> kombinacja_miast);
    int sumaOdleglosciDoPokonaniaPomiedzyMiastamiAproksymacyjny
                                           (std::vector <int> kombinacja_miast);
    void wierszTrojkataPascala(int * liczba_k_elementowych_podzbiorow);
    void generujPodzbioryKElementowe(int ile_podzbiorw, 
                                     int liczba_elementow_pozdbioru);
    int szukajIndeksu(std::set<int> poszukiwany_zbior); 
    int funkcjaMinimum(int wezel_i, int indeks_rozwazanego_podzbioru,
                       std::vector<std::vector<int>> macierz_kosztow,
                       int *wartosc_min_wezla_j);
    int funkcjaMinimumCalyPodzbior(std::vector<std::vector <int>> macierz_kosztow, 
                                   int *wartosc_min_wezla_j);
    int znajdzIndeksElementu(std::vector <int> zbior_elementow, int element);
    bool czyJestWWektorze (std::vector <int> wektor, int liczba);
    std::vector<int> odczytajSciezke(std::vector<std::vector<int>> macierz_sciezek);
    int wyznaczOdlegloscPodzialu(double epsilon);
   
    int liczba_miast_;
    int indeks_;
    std::vector<std::vector <int>> macierz_sasiedztwa_;
    std::vector<std::set<int>> zbior_wszystkich_podzbiorow_;
    
};

#endif	/* PROBLEMKOMIWOJAZERA_H */

