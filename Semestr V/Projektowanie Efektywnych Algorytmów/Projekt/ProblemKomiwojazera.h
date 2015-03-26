/* 
 * File:   ProblemKomiwojazera.h
 * Author: Piotr Chmiel, Maciej Stelmaszuk
 *
 * Created on 6 październik 2014, 18:34
 */

#ifndef PROBLEMKOMIWOJAZERA_H
#define	PROBLEMKOMIWOJAZERA_H

#define STALA_EULERA 2.71828182845904523536

#include <algorithm>
#include <chrono>
#include <ctime>
#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>
#include <Windows.h>
#include "KolejkaTabu.h"

struct Osobnik
{
    std::vector<int> sciezka;
    int wartosc_funkcji_celu;
    
    bool operator<(const Osobnik &o) const
	{
		return wartosc_funkcji_celu < o.wartosc_funkcji_celu;
	}
};

class ProblemKomiwojazera 
{
public:
    ProblemKomiwojazera();
    ProblemKomiwojazera(int liczba_miast);
    ProblemKomiwojazera(const ProblemKomiwojazera& orig);
    virtual ~ProblemKomiwojazera();
    
    void algorytmSymulowanegoWyzarzania(double temperatura_poczatkowa, double temperatura_koncowa, double wspolczynnik_obnizania_temperatury);
    void przeszukiwanieTabu(int dlugosc_kolejki_tabu, bool typ_kryterium_stopu, int wartosc_kryterium_stopu);
    void AlgorytmGenetyczny(int liczba_osobnikow, int liczba_iteracji);                       
    
    void przegladZupelny();
    std::vector<Osobnik> Selekcja(std::vector<Osobnik> populacja, int liczba_osobnikow);
    
    void mutacja(std::vector<int> &kombinacja_miast);
    void wyswietlMacierzSasiedztwa();
    void zmienLiczbeMiast(int nowa_liczba_miast);
    void wczytajZPlikuTekstowego(std::string nazwa_pliku);
    void zapiszDoPlikuTekstowego(std::string nazwa_pliku);
    int pobierzLiczbeMiast() { return liczba_miast_;}
    int wyznaczenieOpytmalnejTemperaturyPoczatkowej();
    void wczytajZPlikuATSP (std::string nazwa_pliku);
    void wczytajzPlikuTSP (std::string nazwa_pliku);
    void krzyzowanieOX(std::vector<int> rodzic1, std::vector<int> rodzic2,
                        std::vector<int> &dziecko1, std::vector<int> &dziecko2);
    
       
private: 
    
    void odbicieSymetryczneWzgledemGlownejPrzekatnej();
    void losujOdleglosciZPrzedzialuDoMacierzySasiedztwa(int poczatek_przedzialu, int koniec_przedzialu);
    void generowanieLosowejPermutacji (int * tablica);
    void generowanieLosowejPermutacji(std::vector<int> &tablica);
    void wyswietlKombinacjeMiast(int * kombinacja_miast, int suma_odleglosci_pomiedzy_nimi);
    void wyswietlKombinacjeMiast(std::vector <int> kombinacja_miast, 
                                 int suma_odleglosci_pomiedzy_nimi);
    int sumaOdleglosciDoPokonaniaPomiedzyMiastami(int * kombinacja_miast);
    int sumaOdleglosciDoPokonaniaPomiedzyMiastami(std::vector <int> kombinacja_miast);
    double funkcjaPrawdopodobienstwa(double temperatura, int aktualna_odleglosc, int proponowana_ogleglosc);
    double generowanieLosowejLiczbyRzeczywistejZPrzedzialu(double poczatek_przedzialu, double koniec_przedzialu);
    int generowanieLosowejLiczbyCalkowitejZPrzedzialu(int poczatek_przedzialu, int koniec_przedzialu);
    void wykonanieKopiiTablicy(int * zrodlo, int * kopia);
    void funkcjaKroku(int * kombinacja_miast);
    void funkcjaKrokuTabu (int * kombinacja_miast, int miasto_poczatkowe, int miasto_docelowe);
    void obliczMaksymalnaIloscRuchow(std::vector<ruch> maksymalny_zasieg, int *pozycje, KolejkaTabu * kolejka);
    void inicjalizacjaTablicyJejNumeremIndexu (int * tablica);
    bool czyPodejrzenieTabu(std::vector<ruch> maxr);
    
    unsigned int zmienna_losujaca_;
    int liczba_miast_;
    std::vector<std::vector <int>> macierz_sasiedztwa_;
};

#endif	/* PROBLEMKOMIWOJAZERA_H */

