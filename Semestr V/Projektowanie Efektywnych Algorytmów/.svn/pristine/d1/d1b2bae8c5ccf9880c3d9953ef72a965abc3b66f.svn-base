/* 
 * File:   ProblemKomiwojazera.cpp
 * Author: Piotr Chmiel, Maciej Stelmaszuk
 * 
 * Created on 6 październik 2014, 18:34
 */

#include "ProblemKomiwojazera.h"

ProblemKomiwojazera::ProblemKomiwojazera() 
{
}

ProblemKomiwojazera::ProblemKomiwojazera(int liczba_miast) : 
    liczba_miast_(liczba_miast), 
    macierz_sasiedztwa_(liczba_miast_, std::vector<int>(liczba_miast_, -1)),
    zmienna_losujaca_(0)
{
    losujOdleglosciZPrzedzialuDoMacierzySasiedztwa(0,100);
    odbicieSymetryczneWzgledemGlownejPrzekatnej();
}
ProblemKomiwojazera::ProblemKomiwojazera(const ProblemKomiwojazera& orig) 
{
}

ProblemKomiwojazera::~ProblemKomiwojazera() 
{
}
void ProblemKomiwojazera::przeszukiwanieTabu(int dlugosc_kolejki_tabu, bool typ_kryterium_stopu, int wartosc_kryterium_stopu)
{
    VOID WINAPI GetSystemTimePreciseAsFileTime(LPFILETIME lpSystemTimeAsFileTime);

    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, czas;
    LARGE_INTEGER Frequency;
    czas.QuadPart = 0;
    Frequency.QuadPart = 0;
    StartingTime.QuadPart = 0;							
    EndingTime.QuadPart = 0;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);
    
    int *kombinacja_miast = new int [liczba_miast_];
    int *najlepsza_kombinacja_miast = new int[liczba_miast_];
    generowanieLosowejPermutacji(kombinacja_miast);
    
    int *pozycje = new int [liczba_miast_];
    
    for (int i=0; i < liczba_miast_; ++i)
    {
        pozycje[kombinacja_miast[i]] = i;
    }
    
    int najkrotsza_droga = std::numeric_limits<int>::max();
    
    KolejkaTabu * kolejka_tabu = new KolejkaTabu(dlugosc_kolejki_tabu);
    
    int licznik_nieefektywnych_ruchow = 0, liczba_iteracji = 0;
    std::vector<ruch> maxr(liczba_miast_, ruch());
    
    bool kontynuuj;
    
    if (typ_kryterium_stopu)
        kontynuuj = licznik_nieefektywnych_ruchow < wartosc_kryterium_stopu;
    else
        kontynuuj = liczba_iteracji < wartosc_kryterium_stopu;
    
    while(kontynuuj)
    {
        
        ++liczba_iteracji;
        obliczMaksymalnaIloscRuchow(maxr, pozycje,kolejka_tabu);
        
         bool podejrzenieTabu = czyPodejrzenieTabu(maxr);
        
         int aktualna_droga = std::numeric_limits<int>::max();
         ruch aktualny_ruch;
         
         for (int i = 0; i < liczba_miast_ - 1; ++i)
		{
			for (int j = i + 1; j < liczba_miast_; ++j)
			{
				if (j > maxr[kombinacja_miast[i]].prawo)
				{
					if (!podejrzenieTabu)
					{
						break;
					}
				}
				else if (i < maxr[kombinacja_miast[j]].lewo && !podejrzenieTabu) continue;

				funkcjaKroku(kombinacja_miast);

				int nowa_droga = sumaOdleglosciDoPokonaniaPomiedzyMiastami(kombinacja_miast);
			
				if (nowa_droga < aktualna_droga)
				{
					aktualna_droga = nowa_droga;
					aktualny_ruch.lewo = i;
					aktualny_ruch.prawo = j;
				}

				funkcjaKroku(kombinacja_miast);
			}
		}
         
                kolejka_tabu->dodaj(ruch(kombinacja_miast[aktualny_ruch.lewo], kombinacja_miast[aktualny_ruch.prawo]));
		funkcjaKroku(kombinacja_miast);
		pozycje[kombinacja_miast[aktualny_ruch.lewo]] = aktualny_ruch.lewo;
		pozycje[kombinacja_miast[aktualny_ruch.prawo]] = aktualny_ruch.prawo;

		if (aktualna_droga < najkrotsza_droga)
		{
			najkrotsza_droga = aktualna_droga;
                        wykonanieKopiiTablicy(kombinacja_miast, najlepsza_kombinacja_miast);
			licznik_nieefektywnych_ruchow = 0;
		}
		else
		{
                        
			++licznik_nieefektywnych_ruchow;
		}
				
		if (typ_kryterium_stopu)
                    kontynuuj = licznik_nieefektywnych_ruchow < wartosc_kryterium_stopu;
                else
                    kontynuuj = liczba_iteracji < wartosc_kryterium_stopu;
	}
    
    QueryPerformanceCounter(&EndingTime);										
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    czas.QuadPart += ElapsedMicroseconds.QuadPart;    
    wyswietlKombinacjeMiast(najlepsza_kombinacja_miast, najkrotsza_droga);
    std::cout << std::endl << "Czas trwania algorytmu : " << czas.QuadPart << " mikrosekund ." << std::endl;
        
        
        delete [] kombinacja_miast;
        delete [] pozycje; 
        delete kolejka_tabu;
}




void ProblemKomiwojazera::algorytmSymulowanegoWyzarzania(double temperatura_poczatkowa, double temperatura_koncowa, double wspolczynnik_obnizania_temperatury) 
{
    VOID WINAPI GetSystemTimePreciseAsFileTime(LPFILETIME lpSystemTimeAsFileTime);

    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, czas;
    LARGE_INTEGER Frequency;
    czas.QuadPart = 0;
    Frequency.QuadPart = 0;
    StartingTime.QuadPart = 0;							
    EndingTime.QuadPart = 0;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);
    
    int *kombinacja_miast = new int [liczba_miast_];
    int *aktualna_kombinacja_miast = new int [liczba_miast_];
    int *najlepsza_kombinacja_miast = new int [liczba_miast_];
    int droga, aktualna_droga, najkrotsza_droga;
       
    generowanieLosowejPermutacji(kombinacja_miast);
    wykonanieKopiiTablicy(kombinacja_miast, najlepsza_kombinacja_miast);
    
    najkrotsza_droga = sumaOdleglosciDoPokonaniaPomiedzyMiastami(kombinacja_miast);
    aktualna_droga = sumaOdleglosciDoPokonaniaPomiedzyMiastami(kombinacja_miast);
    double temperatura = temperatura_poczatkowa;
            
    while (temperatura > temperatura_koncowa)
    {
              
        funkcjaKroku(kombinacja_miast);
        droga = sumaOdleglosciDoPokonaniaPomiedzyMiastami(kombinacja_miast);
        
        if (droga <= aktualna_droga || generowanieLosowejLiczbyRzeczywistejZPrzedzialu(0.0, 0.99) < funkcjaPrawdopodobienstwa(temperatura, aktualna_droga, droga))
        {
            aktualna_droga = droga;
            if (aktualna_droga < najkrotsza_droga)
                najkrotsza_droga = aktualna_droga;
        }
        else
        {
            funkcjaKroku(kombinacja_miast);
        }
        
        temperatura *= wspolczynnik_obnizania_temperatury;
        
    }
    QueryPerformanceCounter(&EndingTime);										
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    czas.QuadPart += ElapsedMicroseconds.QuadPart;
    
    wyswietlKombinacjeMiast(najlepsza_kombinacja_miast, najkrotsza_droga);
    std::cout << std::endl << "Czas trwania algorytmu : " << czas.QuadPart << " mikrosekund ." << std::endl;
        
    delete [] kombinacja_miast;
    delete [] najlepsza_kombinacja_miast; 
    delete [] aktualna_kombinacja_miast;
}

void ProblemKomiwojazera::przegladZupelny()
{
    VOID WINAPI GetSystemTimePreciseAsFileTime(LPFILETIME lpSystemTimeAsFileTime);

    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, czas;
    LARGE_INTEGER Frequency;
    czas.QuadPart = 0;
    Frequency.QuadPart = 0;
    StartingTime.QuadPart = 0;							
    EndingTime.QuadPart = 0;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);
        
    int aktualna_najkrotsza_droga = std::numeric_limits<int>::max(), index = 0;
    int *aktualna_kombinacja_miast = new int [liczba_miast_];
    int *najlepsza_kombinacja_miast = new int [liczba_miast_];
    
    inicjalizacjaTablicyJejNumeremIndexu(aktualna_kombinacja_miast);
    
    do
    {
        int suma_odleglosci = sumaOdleglosciDoPokonaniaPomiedzyMiastami(aktualna_kombinacja_miast);
           
        if( suma_odleglosci < aktualna_najkrotsza_droga)
        {
            wykonanieKopiiTablicy(aktualna_kombinacja_miast, najlepsza_kombinacja_miast);
            aktualna_najkrotsza_droga = suma_odleglosci;
        }
    }
    while(std::next_permutation(aktualna_kombinacja_miast, aktualna_kombinacja_miast + liczba_miast_));
    
    QueryPerformanceCounter(&EndingTime);										
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    czas.QuadPart += ElapsedMicroseconds.QuadPart;
                
    wyswietlKombinacjeMiast(najlepsza_kombinacja_miast, aktualna_najkrotsza_droga);
    std::cout << std::endl << "Czas trwania algorytmu : " << czas.QuadPart << " mikrosekund ." << std::endl;
    
    delete [] aktualna_kombinacja_miast;
    delete [] najlepsza_kombinacja_miast;
}
void ProblemKomiwojazera::wyswietlMacierzSasiedztwa()
{
    std::cout << "Liczba miast: " << liczba_miast_ << " ;" << std::endl;
    std::cout << std::endl;
   
    for (auto wiersz : macierz_sasiedztwa_)
    {
        for (auto kolumna : wiersz)
	{
            std::cout << kolumna << '\t';
	}
	std::cout << std::endl;
    }
}
void ProblemKomiwojazera::zmienLiczbeMiast(int nowa_liczba_miast)
{
    liczba_miast_ = nowa_liczba_miast;
    macierz_sasiedztwa_.clear();
    macierz_sasiedztwa_.resize(nowa_liczba_miast, std::vector <int> (nowa_liczba_miast, -1));
    
    losujOdleglosciZPrzedzialuDoMacierzySasiedztwa(0,100);
    odbicieSymetryczneWzgledemGlownejPrzekatnej();
    
}
void ProblemKomiwojazera::wczytajZPlikuTekstowego(std::string nazwa_pliku)
{
    std::ifstream plik_do_odczytu;
    
    plik_do_odczytu.open(nazwa_pliku);
    
    if(!plik_do_odczytu.is_open())
    {
        std::cout << "Odczyt pliku " << nazwa_pliku << " nie powiodl sie!" << std::endl << std::endl;               
    }
    else
    {
        plik_do_odczytu >> liczba_miast_;
        macierz_sasiedztwa_.clear();
        macierz_sasiedztwa_.resize(liczba_miast_, std::vector <int> (liczba_miast_, -1));
        
        for (auto &wiersz : macierz_sasiedztwa_)
        {
            for (auto &kolumna : wiersz)
            {
                plik_do_odczytu >> kolumna;
            }
        }
        std::cout << "Odczyt pliku " << nazwa_pliku << " zakonczony powodzeniem!" << std::endl << std::endl; 
    }
    
    plik_do_odczytu.close();
}
void ProblemKomiwojazera::zapiszDoPlikuTekstowego(std::string nazwa_pliku)
{
    std::ofstream plik_do_zapisu;
    
    plik_do_zapisu.open(nazwa_pliku);
    if(!plik_do_zapisu.is_open())
    {
        std::cout << "Zapis pliku " << nazwa_pliku << " nie powiodl sie!" << std::endl << std::endl;               
    }
    plik_do_zapisu << liczba_miast_ << std::endl;
    
    for (auto wiersz : macierz_sasiedztwa_)
    {
        for (auto kolumna : wiersz)
	{
            plik_do_zapisu << kolumna << '\t';
	}
	plik_do_zapisu << std::endl;
    }
    
    plik_do_zapisu.close();
    std::cout << "Zapis pliku " << nazwa_pliku << " zakonczony powodzeniem!" << std::endl << std::endl;
}
int ProblemKomiwojazera::wyznaczenieOpytmalnejTemperaturyPoczatkowej()
{
    int delta = 0, nowa_delta;
    int liczba_powtorzen = std::pow(liczba_miast_, 2.0);
    int *permutacja_inicjalizacyjna = new int [liczba_miast_];
    generowanieLosowejPermutacji(permutacja_inicjalizacyjna);
    int suma_odleglosci_permutacja_inicjalizacyjna = sumaOdleglosciDoPokonaniaPomiedzyMiastami(permutacja_inicjalizacyjna);
    int *permutacja_tymczasowa = new int [liczba_miast_];
    
    for(int i = 0; i < liczba_powtorzen; ++i)
    {
        generowanieLosowejPermutacji(permutacja_tymczasowa);
        nowa_delta = sumaOdleglosciDoPokonaniaPomiedzyMiastami(permutacja_tymczasowa) -
                        suma_odleglosci_permutacja_inicjalizacyjna;
        if(nowa_delta > delta)
            delta = nowa_delta;
    }
    
    delete [] permutacja_inicjalizacyjna;
    delete [] permutacja_tymczasowa;
    return delta;
}

void ProblemKomiwojazera::losujOdleglosciZPrzedzialuDoMacierzySasiedztwa(int poczatek_przedzialu, int koniec_przedzialu)
{
    auto aktualny_czas = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 silnik_losujacy_liczby(aktualny_czas);
    std::uniform_int_distribution<int> rozklad_liczb_losowych
                            (poczatek_przedzialu, koniec_przedzialu);
    
    auto generator_odleglosci = std::bind(rozklad_liczb_losowych, silnik_losujacy_liczby);
    
    for(unsigned wiersz = 0; wiersz < macierz_sasiedztwa_.size(); ++wiersz)
    {
        for(unsigned kolumna = wiersz + 1; kolumna < macierz_sasiedztwa_.size(); ++kolumna)
        {
            macierz_sasiedztwa_[wiersz][kolumna] = generator_odleglosci();
        }
    }
}
void ProblemKomiwojazera::odbicieSymetryczneWzgledemGlownejPrzekatnej()
{
    for(unsigned wiersz = 0; wiersz < macierz_sasiedztwa_.size(); ++wiersz)
    {
        for(unsigned kolumna = wiersz + 1; kolumna < macierz_sasiedztwa_.size(); ++kolumna)
        {
            macierz_sasiedztwa_[kolumna][wiersz] = 
                                            macierz_sasiedztwa_[wiersz][kolumna];
        }
    }
}
void ProblemKomiwojazera::generowanieLosowejPermutacji(int* tablica)
{
    
        for(int index = 0; index < liczba_miast_; ++index)
        {
        tablica[index] = index;
        }
        std::random_shuffle(tablica,tablica+liczba_miast_);
   
}
void ProblemKomiwojazera::generowanieLosowejPermutacji(std::vector<int> &tablica)
{
    
        for(int index = 0; index < liczba_miast_; ++index)
        {
            tablica[index] = index;
        }
        std::random_shuffle(tablica.begin(),tablica.end());
   
}

void ProblemKomiwojazera::wyswietlKombinacjeMiast(int* kombinacja_miast, int suma_odleglosci_pomiedzy_nimi)
{
        std::cout << std::endl << "Permutacja : " << std::endl;
	
        for (int index = 0; index < liczba_miast_ ;++index)
	{
		std::cout << kombinacja_miast[index] << " -> ";
	}
        
        std::cout << std::endl;
	std::cout << "Suma odlegosci: " << suma_odleglosci_pomiedzy_nimi << std::endl;
}
void ProblemKomiwojazera::wyswietlKombinacjeMiast(std::vector <int> kombinacja_miast, int suma_odleglosci_pomiedzy_nimi)
{
        std::cout << std::endl << "Permutacja : " << std::endl;
	
        for (int index = 0; index < liczba_miast_ ;++index)
	{
		std::cout << kombinacja_miast[index] << " -> ";
	}
        
        std::cout << std::endl;
	std::cout << "Suma odlegosci: " << suma_odleglosci_pomiedzy_nimi << std::endl;
}
int ProblemKomiwojazera::sumaOdleglosciDoPokonaniaPomiedzyMiastami(int * kombinacja_miast)
{
    int sumaOdleglosci = 0;
    
    for (int i = 0; i < liczba_miast_ - 1; ++i)
    {
	sumaOdleglosci += macierz_sasiedztwa_[kombinacja_miast[i]][kombinacja_miast[i + 1]];		
    }
    sumaOdleglosci += macierz_sasiedztwa_[kombinacja_miast[liczba_miast_ - 1]][kombinacja_miast[0]];
    
    return sumaOdleglosci;
}
int ProblemKomiwojazera::sumaOdleglosciDoPokonaniaPomiedzyMiastami(std::vector <int> kombinacja_miast)
{
    int sumaOdleglosci = 0;
    
    for (int i = 0; i < kombinacja_miast.size() - 1; ++i)
    {
	sumaOdleglosci += macierz_sasiedztwa_[kombinacja_miast[i]][kombinacja_miast[i + 1]];		
    }
    sumaOdleglosci += macierz_sasiedztwa_[kombinacja_miast[liczba_miast_ - 1]][kombinacja_miast[0]];
    
    return sumaOdleglosci;
}
double ProblemKomiwojazera::funkcjaPrawdopodobienstwa(double temperatura, int aktualna_odleglosc, int proponowana_ogleglosc)
{
    if (proponowana_ogleglosc <= aktualna_odleglosc)
        return 1;
    else 
        return std::pow(STALA_EULERA,(((proponowana_ogleglosc-aktualna_odleglosc)*((-2)*std::log(temperatura)))/proponowana_ogleglosc));
        
}
double ProblemKomiwojazera::generowanieLosowejLiczbyRzeczywistejZPrzedzialu(double poczatek_przedzialu, double koniec_przedzialu)
{
    auto aktualny_czas = std::chrono::system_clock::now().time_since_epoch().count() + zmienna_losujaca_;
    std::mt19937 silnik_losujacy_liczby(aktualny_czas);
    std::uniform_real_distribution<double> rozklad_liczb_losowych
                            (poczatek_przedzialu, koniec_przedzialu);
    
    auto generator_liczby_rzeczywistej = std::bind(rozklad_liczb_losowych, silnik_losujacy_liczby);
    
    ++zmienna_losujaca_;
    return generator_liczby_rzeczywistej();
}
int ProblemKomiwojazera::generowanieLosowejLiczbyCalkowitejZPrzedzialu(int poczatek_przedzialu, int koniec_przedzialu)
{
    auto aktualny_czas = std::chrono::system_clock::now().time_since_epoch().count() + zmienna_losujaca_;
    std::mt19937 silnik_losujacy_liczby(aktualny_czas);
    std::uniform_int_distribution<int> rozklad_liczb_losowych
                            (poczatek_przedzialu, koniec_przedzialu);
    
    auto generator_liczby_calkowitej = std::bind(rozklad_liczb_losowych, silnik_losujacy_liczby);
    
    ++zmienna_losujaca_;
    return generator_liczby_calkowitej();
}
void ProblemKomiwojazera::wykonanieKopiiTablicy(int* zrodlo, int* kopia)
{
    for (int index = 0; index < liczba_miast_; ++index)
    {
	kopia[index] = zrodlo[index];
    }
}
void ProblemKomiwojazera::funkcjaKroku(int* kombinacja_miast)
{
    auto aktualny_czas = std::chrono::system_clock::now().time_since_epoch().count() + zmienna_losujaca_;
    std::mt19937 silnik_losujacy_liczby(aktualny_czas);
    std::uniform_int_distribution<int> rozklad_liczb_losowych
                            (0, liczba_miast_ - 1);
    
    auto generator_indeksu = std::bind(rozklad_liczb_losowych, silnik_losujacy_liczby);
    
    int pierwszy_losowy_indeks, drugi_losowy_indeks;
    
    pierwszy_losowy_indeks = generator_indeksu();
    
    do
    {
    drugi_losowy_indeks = generator_indeksu();
    }
    while(pierwszy_losowy_indeks == drugi_losowy_indeks);
            
    std::swap(kombinacja_miast[pierwszy_losowy_indeks], kombinacja_miast[drugi_losowy_indeks]);
    
    ++zmienna_losujaca_;
}
void ProblemKomiwojazera::mutacja(std::vector<int> &kombinacja_miast)
{
    auto aktualny_czas = std::chrono::system_clock::now().time_since_epoch().count() + zmienna_losujaca_;
    std::mt19937 silnik_losujacy_liczby(aktualny_czas);
    std::uniform_int_distribution<int> rozklad_liczb_losowych
                            (0, liczba_miast_ - 1);
    
    auto generator_indeksu = std::bind(rozklad_liczb_losowych, silnik_losujacy_liczby);
    
    int pierwszy_losowy_indeks, drugi_losowy_indeks;
    
    pierwszy_losowy_indeks = generator_indeksu();
    
    do
    {
    drugi_losowy_indeks = generator_indeksu();
    }
    while(pierwszy_losowy_indeks == drugi_losowy_indeks);
            
    std::swap(kombinacja_miast[pierwszy_losowy_indeks], kombinacja_miast[drugi_losowy_indeks]);
    
    ++zmienna_losujaca_;
}


void ProblemKomiwojazera::funkcjaKrokuTabu(int* kombinacja_miast, int miasto1, int miasto2)
{
    std::swap(kombinacja_miast[miasto1], kombinacja_miast[miasto2]);
}

void ProblemKomiwojazera::inicjalizacjaTablicyJejNumeremIndexu(int* tablica)
{
    for(int index = 0; index < liczba_miast_; ++index)
    {
        tablica[index] = index;
    }
}

void ProblemKomiwojazera::wczytajZPlikuATSP(std::string nazwa_pliku)
{
    std::ifstream plik_do_odczytu;
    
    plik_do_odczytu.open(nazwa_pliku);
    
    if(!plik_do_odczytu.is_open())
    {
        std::cout << "Odczyt pliku " << nazwa_pliku << " nie powiodl sie!" << std::endl << std::endl;               
    }
    else
    {
        std::string linia;
       while (linia.compare("EDGE_WEIGHT_SECTION"))
       {
            std::getline (plik_do_odczytu, linia);
            int dwukropek = linia.find(':');
            std::string name, value;
            if (dwukropek > 0)
		{
			name = linia.substr(0, dwukropek);
			value = linia.substr(dwukropek + 1);

			if (!name.compare("DIMENSION"))
			{
				liczba_miast_ = atoi(value.c_str());
			}
		}
       }       
    }
    
    macierz_sasiedztwa_.clear();
    macierz_sasiedztwa_.resize(liczba_miast_, std::vector <int> (liczba_miast_, -1));
    
    for (auto &wiersz : macierz_sasiedztwa_)
        {
            for (auto &kolumna : wiersz)
            {
                plik_do_odczytu >> kolumna;
            }
        }
        std::cout << "Odczyt pliku " << nazwa_pliku << " zakonczony powodzeniem!" << std::endl << std::endl;
        
    plik_do_odczytu.close();
}

void ProblemKomiwojazera::wczytajzPlikuTSP(std::string nazwa_pliku)
{
    std::ifstream plik_do_odczytu;
    
    plik_do_odczytu.open(nazwa_pliku);
    
    if(!plik_do_odczytu.is_open())
    {
        std::cout << "Odczyt pliku " << nazwa_pliku << " nie powiodl sie!" << std::endl << std::endl;               
    }
    else
    {
        std::string linia;
       while (linia.compare("EDGE_WEIGHT_SECTION"))
       {
            std::getline (plik_do_odczytu, linia);
            int dwukropek = linia.find(':');
            std::string name, value;
            if (dwukropek > 0)
		{
			name = linia.substr(0, dwukropek);
			value = linia.substr(dwukropek + 1);

			if (!name.compare("DIMENSION"))
			{
				liczba_miast_ = atoi(value.c_str());
			}
		}
       }       
    }
    
    macierz_sasiedztwa_.clear();
    macierz_sasiedztwa_.resize(liczba_miast_, std::vector <int> (liczba_miast_, -1));
    
    for (int i=0; i < liczba_miast_; ++i)
    {
        for (int ii = 1+i; ii < liczba_miast_; ++ii)
        {
            plik_do_odczytu >> macierz_sasiedztwa_[i][ii];
        }
    }
    odbicieSymetryczneWzgledemGlownejPrzekatnej();
    
        std::cout << "Odczyt pliku " << nazwa_pliku << " zakonczony powodzeniem!" << std::endl << std::endl;
        
    plik_do_odczytu.close();
}

void ProblemKomiwojazera::obliczMaksymalnaIloscRuchow(std::vector<ruch> maksymalny_zasieg, 
        int * pozycje,KolejkaTabu * kolejka){

    for (int i = 0; i < liczba_miast_; ++i)
	{
                
		maksymalny_zasieg[i].lewo = 0;
                maksymalny_zasieg[i].prawo = liczba_miast_ - 1;
                
	}
    
    for (int i = 0; i < kolejka->pobierzDlugosc(); ++i)
	{
                int tL = kolejka->pobierz(i).lewo;
                int tR = kolejka->pobierz(i).prawo;
                
                if (tL > 0&& tR >0)
                {
                maksymalny_zasieg[tL].lewo = std::min(pozycje[tL], std::max(pozycje[tR] +1, maksymalny_zasieg[tL].lewo));
                
                maksymalny_zasieg[tR].prawo = std::max(pozycje[tR], std::min(pozycje[tL] - 1, maksymalny_zasieg[tR].prawo));
                
                             
                }
	}    
}

bool ProblemKomiwojazera::czyPodejrzenieTabu(std::vector<ruch> maxr)
{
    for (int i = 0; i < liczba_miast_; ++i)
        {
          if (maxr[i].lewo != maxr[i].prawo)
          {
              return false;
          }
        }
    
    return true;
}

void ProblemKomiwojazera::krzyzowanieOX(std::vector<int> rodzic1, std::vector<int> rodzic2
                            ,std::vector<int> &dziecko1, std::vector<int> &dziecko2)
{
    int punkt_krzyzowania1 = -1;
    int punkt_krzyzowania2 = -1;
    int tmp = 0;
    while (punkt_krzyzowania1 == punkt_krzyzowania2)
    {
        punkt_krzyzowania1 = generowanieLosowejLiczbyCalkowitejZPrzedzialu(0, liczba_miast_-1);
        punkt_krzyzowania2 = generowanieLosowejLiczbyCalkowitejZPrzedzialu(0, liczba_miast_-1);
     
    }
    
    if (punkt_krzyzowania1 > punkt_krzyzowania2)
        std::swap(punkt_krzyzowania1, punkt_krzyzowania2);
   
    for (int i = punkt_krzyzowania1; i < punkt_krzyzowania2; ++i)
    {
        dziecko1[i] = rodzic2[i];
        rodzic2[i] = -1;
        dziecko2[i] = rodzic1[i];
        rodzic1[i] = -1;
    }
    
    for (int i = punkt_krzyzowania2; i < liczba_miast_; ++i)
    {
        while (rodzic2[tmp] == -1)
            ++tmp;
        
        dziecko1[i] = rodzic2[tmp];
        dziecko2[i] = rodzic1[tmp];
        ++tmp;
    }
    for (int i = 0; i < punkt_krzyzowania1; ++i)
    {
        while (rodzic2[tmp] == -1)
            ++tmp;
        
        dziecko1[i] = rodzic2[tmp];
        dziecko2[i] = rodzic1[tmp];
        ++tmp;
    }
}

std::vector<Osobnik> ProblemKomiwojazera::Selekcja(std::vector<Osobnik> populacja, int liczba_osobnikow)
{
    std::vector<Osobnik> wyselekcjonowana_populacja(liczba_osobnikow);
    
    std::sort(populacja.begin(),populacja.end());
    
    for (int i=0; i < wyselekcjonowana_populacja.size();++i)
    {
        wyselekcjonowana_populacja[i] = populacja[i];
    }
    
    return wyselekcjonowana_populacja;  
}

void ProblemKomiwojazera::AlgorytmGenetyczny(int liczba_osobnikow, int liczba_iteracji)
{    
    VOID WINAPI GetSystemTimePreciseAsFileTime(LPFILETIME lpSystemTimeAsFileTime);

    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, czas;
    LARGE_INTEGER Frequency;
    czas.QuadPart = 0;
    Frequency.QuadPart = 0;
    StartingTime.QuadPart = 0;							
    EndingTime.QuadPart = 0;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);
    
    std::vector<Osobnik> populacja(liczba_osobnikow);
    std::vector<int> dziecko1(liczba_miast_);
    std::vector<int> dziecko2(liczba_miast_);
    
    for (int i=0; i< populacja.size(); ++i)
    {
        populacja[i].sciezka = std::vector<int>(liczba_miast_);
        generowanieLosowejPermutacji(populacja[i].sciezka);
        populacja[i].wartosc_funkcji_celu = sumaOdleglosciDoPokonaniaPomiedzyMiastami(populacja[i].sciezka);
    }
    for (int i =0; i < liczba_iteracji;++i)
    {
    std::random_shuffle(populacja.begin(),populacja.end()); 
    
    for (int i=0; i < liczba_osobnikow; i +=2)
    {
        if(generowanieLosowejLiczbyRzeczywistejZPrzedzialu(0.0,1.0) < generowanieLosowejLiczbyRzeczywistejZPrzedzialu(0.2,0.5))
        {
            krzyzowanieOX(populacja[i].sciezka, populacja[i+1].sciezka,dziecko1, dziecko2);
            Osobnik tymczasowy;
            tymczasowy.sciezka = dziecko1;
            tymczasowy.wartosc_funkcji_celu = sumaOdleglosciDoPokonaniaPomiedzyMiastami(dziecko1);
            populacja.push_back(tymczasowy);
            tymczasowy.sciezka = dziecko2;
            tymczasowy.wartosc_funkcji_celu = sumaOdleglosciDoPokonaniaPomiedzyMiastami(dziecko2);
            populacja.push_back(tymczasowy);  
        }
    }
    
    for (int i=0; i < populacja.size(); ++i)
    {
        if(generowanieLosowejLiczbyRzeczywistejZPrzedzialu(0.0,1.0) < generowanieLosowejLiczbyRzeczywistejZPrzedzialu(0.0,0.01))
        {
            mutacja(populacja[i].sciezka);
            populacja[i].wartosc_funkcji_celu = sumaOdleglosciDoPokonaniaPomiedzyMiastami(populacja[i].sciezka);
        }
    }
    
    populacja = Selekcja(populacja, liczba_osobnikow);
        
    }
    QueryPerformanceCounter(&EndingTime);										
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    czas.QuadPart += ElapsedMicroseconds.QuadPart;
    wyswietlKombinacjeMiast(populacja[0].sciezka, populacja[0].wartosc_funkcji_celu);
    std::cout << std::endl << "Czas trwania algorytmu : " << czas.QuadPart << " mikrosekund ." << std::endl;    
}