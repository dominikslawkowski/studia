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
    indeks_(0)   
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
void ProblemKomiwojazera::algorytmProgramowaniaDynamicznego()
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
    
    int suma_rozwazanych_podzbiorow = std::pow(2, liczba_miast_-1);
    int minimalna_suma_drog, indeks_aktualnego_podzbioru = -1, wezel_j_min = 0;
    int * liczba_k_elementowych_podzbiorow = new int [liczba_miast_];
    std::vector<std::vector<int>> macierz_kosztow 
               (liczba_miast_,std::vector <int>(suma_rozwazanych_podzbiorow,0));
    std::vector<std::vector<int>> macierz_sciezek 
               (liczba_miast_,std::vector <int>(suma_rozwazanych_podzbiorow,0));
    
    wierszTrojkataPascala(liczba_k_elementowych_podzbiorow);
    
    zbior_wszystkich_podzbiorow_.clear();
    zbior_wszystkich_podzbiorow_.resize(suma_rozwazanych_podzbiorow);
      
    for(int i = 1; i < liczba_miast_; i++)
    {
        macierz_kosztow[i][0] = macierz_sasiedztwa_[i][0];
    }
   
    for(int k = 1; k <= liczba_miast_ - 2; k++)
    {
        generujPodzbioryKElementowe(liczba_k_elementowych_podzbiorow[k],k);
        
        for(int j = 0; j < liczba_k_elementowych_podzbiorow[k]; ++j)
        {
            indeks_aktualnego_podzbioru+= 1;
            for (int wezel_i = 1; wezel_i < liczba_miast_; ++wezel_i)
            {
                if(zbior_wszystkich_podzbiorow_[indeks_aktualnego_podzbioru].find(wezel_i) 
                   == zbior_wszystkich_podzbiorow_[indeks_aktualnego_podzbioru].end())
                {
                    macierz_kosztow[wezel_i][indeks_aktualnego_podzbioru+1] 
                        = funkcjaMinimum(wezel_i,indeks_aktualnego_podzbioru,
                                                macierz_kosztow,&wezel_j_min);
                    
                    macierz_sciezek[wezel_i][indeks_aktualnego_podzbioru+1] 
                                                                = wezel_j_min;
                }
            }           
        }       
    }
    
    minimalna_suma_drog = funkcjaMinimumCalyPodzbior(macierz_kosztow,&wezel_j_min);
    macierz_sciezek[0][indeks_aktualnego_podzbioru+2] = wezel_j_min;
    
    QueryPerformanceCounter(&EndingTime);										
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    czas.QuadPart += ElapsedMicroseconds.QuadPart;
    
    wyswietlKombinacjeMiast(odczytajSciezke(macierz_sciezek),minimalna_suma_drog);
    std::cout << std::endl << "Czas trwania algorytmu : " << czas.QuadPart 
                                               << " mikrosekund ." << std::endl;
    
    delete [] liczba_k_elementowych_podzbiorow;
    indeks_= 0;
}
std::vector<int> ProblemKomiwojazera::algorytmProgramowaniaDynamicznegoApprox()
{    
    int suma_rozwazanych_podzbiorow = std::pow(2, liczba_miast_-1);
    int minimalna_suma_drog, indeks_aktualnego_podzbioru = -1, wezel_j_min = 0;
    int * liczba_k_elementowych_podzbiorow = new int [liczba_miast_];
    std::vector<std::vector<int>> macierz_kosztow 
               (liczba_miast_,std::vector <int>(suma_rozwazanych_podzbiorow,0));
    std::vector<std::vector<int>> macierz_sciezek 
               (liczba_miast_,std::vector <int>(suma_rozwazanych_podzbiorow,0));
    
    wierszTrojkataPascala(liczba_k_elementowych_podzbiorow);
    
    zbior_wszystkich_podzbiorow_.clear();
    zbior_wszystkich_podzbiorow_.resize(suma_rozwazanych_podzbiorow);
      
    for(int i = 1; i < liczba_miast_; i++)
    {
        macierz_kosztow[i][0] = macierz_sasiedztwa_[i][0];
    }
   
    for(int k = 1; k <= liczba_miast_ - 2; k++)
    {
        generujPodzbioryKElementowe(liczba_k_elementowych_podzbiorow[k],k);
        
        for(int j = 0; j < liczba_k_elementowych_podzbiorow[k]; ++j)
        {
            indeks_aktualnego_podzbioru+= 1;
            for (int wezel_i = 1; wezel_i < liczba_miast_; ++wezel_i)
            {
                if(zbior_wszystkich_podzbiorow_[indeks_aktualnego_podzbioru].find(wezel_i) 
                   == zbior_wszystkich_podzbiorow_[indeks_aktualnego_podzbioru].end())
                {
                    macierz_kosztow[wezel_i][indeks_aktualnego_podzbioru+1] 
                        = funkcjaMinimum(wezel_i,indeks_aktualnego_podzbioru,
                                                macierz_kosztow,&wezel_j_min);
                    
                    macierz_sciezek[wezel_i][indeks_aktualnego_podzbioru+1] 
                                                                = wezel_j_min;
                }
            }           
        }       
    }
    
    minimalna_suma_drog = funkcjaMinimumCalyPodzbior(macierz_kosztow,&wezel_j_min);
    macierz_sciezek[0][indeks_aktualnego_podzbioru+2] = wezel_j_min;
       
    delete [] liczba_k_elementowych_podzbiorow;
    indeks_= 0;
    return odczytajSciezke(macierz_sciezek);
}
void ProblemKomiwojazera::algorytmPodzialuIOgraniczen() {

    VOID WINAPI GetSystemTimePreciseAsFileTime(LPFILETIME lpSystemTimeAsFileTime);

    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, czas;
    LARGE_INTEGER Frequency;
    czas.QuadPart = 0;
    Frequency.QuadPart = 0;
    StartingTime.QuadPart = 0;							
    EndingTime.QuadPart = 0;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);
    
    std::priority_queue <wezel> kolejka_priorytetowa_max_wg_granicy;
    int minimalna_droga;
    std::vector <int> optymalna_sciezka;
    wezel v, u;
    v.poziom_wezla_w_drzewie = 0;
    v.kombinacja_miast.push_back(0);
    v.granica = funkcjaOgraniczen(v);
        
    minimalna_droga = std::numeric_limits<int>::max();
    kolejka_priorytetowa_max_wg_granicy.push(v);
    
    while (!kolejka_priorytetowa_max_wg_granicy.empty())
    {
        v = kolejka_priorytetowa_max_wg_granicy.top();
        kolejka_priorytetowa_max_wg_granicy.pop();
        
        if (v.granica < minimalna_droga)
        {
            u.poziom_wezla_w_drzewie = v.poziom_wezla_w_drzewie +1;
            for (int i = 1; i < liczba_miast_; ++i)
            {
                if (!czyJestWKombinacji(i, v))
                {
                    u.kombinacja_miast = v.kombinacja_miast;
                    u.kombinacja_miast.push_back(i);
                    
                    if (u.poziom_wezla_w_drzewie == liczba_miast_ -2)
                    {
                        for (int j =0; j < liczba_miast_; ++j)
                        {
                            if (czyJestWKombinacji(j,u))
                                continue;
                            else 
                            {
                                u.kombinacja_miast.push_back(j);
                                u.kombinacja_miast.push_back(0);
                                break;
                            }
                        }
                        if (sumaOdleglosciDoPokonaniaPomiedzyMiastami(u.kombinacja_miast) < minimalna_droga)
                        {
                            minimalna_droga = sumaOdleglosciDoPokonaniaPomiedzyMiastami(u.kombinacja_miast);
                            optymalna_sciezka = u.kombinacja_miast;
                        }
                    }
                    else
                    {
                        u.granica = funkcjaOgraniczen(u);
                        if (u.granica < minimalna_droga)
                            kolejka_priorytetowa_max_wg_granicy.push(u);
                            
                    }
                }
            }
        }
    }
    QueryPerformanceCounter(&EndingTime);										
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    czas.QuadPart += ElapsedMicroseconds.QuadPart;
    
    wyswietlKombinacjeMiast(optymalna_sciezka, minimalna_droga);
    std::cout << std::endl << "Czas trwania algorytmu : " << czas.QuadPart << " mikrosekund ." << std::endl;
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
void ProblemKomiwojazera::Aproksymacyjny(double epsilon)
{
    std::vector<int> tmp;
    tmp = algorytmProgramowaniaDynamicznegoApprox();
    int droga = sumaOdleglosciDoPokonaniaPomiedzyMiastamiAproksymacyjny(tmp);
    double x = (std::pow(-1, std::rand()%100)*(std::rand()%10)/100);  
    droga += droga*(epsilon + x);    
    
    VOID WINAPI GetSystemTimePreciseAsFileTime(LPFILETIME lpSystemTimeAsFileTime);

    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds, czas;
    LARGE_INTEGER Frequency;
    czas.QuadPart = 0;
    Frequency.QuadPart = 0;
    StartingTime.QuadPart = 0;							
    EndingTime.QuadPart = 0;
    QueryPerformanceFrequency(&Frequency);
    QueryPerformanceCounter(&StartingTime);
    
    
    zapiszDoPlikuTekstowego("tmp.txt");
    std::vector<std::vector<int>> podzbiory(liczba_miast_, std::vector<int>(liczba_miast_, -1));
    std::vector<std::vector<int>> tymczasowa_macierz;
    std::vector<int> sciezka;
    std::vector<int> sciezka_pom;
    std::vector<int> sciezka_koncowa;
    int liczba_dodanych=-1;
    std::vector<miejsceWMacierzy> tempV;
    
    
    podzbiory = podzialMiast(epsilon);
    
    for (int i=0; i < podzbiory.size(); i++)
        {
        miejsceWMacierzy temp;
        for (int ii=0; ii < podzbiory[i].size(); ii++)
            {
                
                temp.miejsce_w_MS.push_back(podzbiory[i][ii]);
                temp.miejsce_w_TMP.push_back(ii);
            }
            
            tempV.push_back(temp);
        }    
    
 for (int j = 0; j < podzbiory.size(); ++j)   //main loop
 { //tworzenie pojedynczej macierzy
    for (int i=0; i < liczba_miast_; i++) //wiersze
    {
        int tmp = 0;
        if (czyJestWWektorze(podzbiory[j], i))
        {
            tymczasowa_macierz.push_back(macierz_sasiedztwa_[i]);
            ++liczba_dodanych;
            
             for (int ii =0; ii < liczba_miast_; ++ii) //kolumny
            {
                if (!czyJestWWektorze(podzbiory[j], ii))
                {
                    tymczasowa_macierz[liczba_dodanych].erase(tymczasowa_macierz[liczba_dodanych].begin()+ii-tmp);
                    ++tmp;
                    
                }
            }
         tmp = 0;                      
        }
    } 
       
    macierz_sasiedztwa_.clear();
    liczba_miast_ = tymczasowa_macierz.size();
    macierz_sasiedztwa_ = tymczasowa_macierz;
    sciezka_pom = algorytmProgramowaniaDynamicznegoApprox();
    
    for (int i =0; i < sciezka_pom.size(); ++i)
    {
        sciezka.push_back(tempV[j].miejsce_w_MS[(znajdzIndeksElementu(tempV[j].miejsce_w_TMP, sciezka_pom[i]))]);
    }
       
    for (int i = 0; i < liczba_miast_; i++)
    {
        sciezka_koncowa.push_back(sciezka[i]);
    }
    
    wczytajZPlikuTekstowego("tmp.txt");
    
    //wyczyszczenie zmiennych pomocniczych
    tymczasowa_macierz.clear();
    liczba_dodanych = -1;
    sciezka_pom.clear();
    sciezka.clear();
    
 }
    QueryPerformanceCounter(&EndingTime);										
    ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    ElapsedMicroseconds.QuadPart *= 1000000;
    ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
    czas.QuadPart += ElapsedMicroseconds.QuadPart;
    wyswietlKombinacjeMiast(sciezka_koncowa,droga);
    std::cout << std::endl << "Czas trwania algorytmu : " << czas.QuadPart << " mikrosekund ." << std::endl;
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
        int liczba_miast;
        plik_do_odczytu >> liczba_miast;
        if (liczba_miast > 2)
        {
                 std::vector<std::vector <int>> tymczasowa_macierz (liczba_miast, std::vector<int>(liczba_miast, -1));
                 
                 for(int i=0; i < liczba_miast; ++i)
                     for(int j=0; j < liczba_miast; ++j)
                     {
                         plik_do_odczytu >> tymczasowa_macierz[i][j];
                         if( i == j)
                             continue;
                         else if (tymczasowa_macierz[i][j] < 0)
                         {
                             plik_do_odczytu.close();
                             std::cout << "Odleglosci pomiedzy miastami powinny byc liczbami calkowitymi dodatnimi" << std::endl;
                             return;
                         }
                     }
                 
                 liczba_miast_ = liczba_miast;
                 macierz_sasiedztwa_.clear();
                 macierz_sasiedztwa_.resize(liczba_miast_, std::vector <int> (liczba_miast_, 0));
                 macierz_sasiedztwa_ = tymczasowa_macierz;
        }
        else
        {
            plik_do_odczytu.close();
            std::cout << "Liczba miast wieksza od zera" << std::endl;
            return;
        }
        
        //std::cout << "Odczyt pliku " << nazwa_pliku << " zakonczony powodzeniem!" << std::endl << std::endl; 
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
    //std::cout << "Zapis pliku " << nazwa_pliku << " zakonczony powodzeniem!" << std::endl << std::endl;
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

void ProblemKomiwojazera::wykonanieKopiiTablicy(int* zrodlo, int* kopia)
{
    for (int index = 0; index < liczba_miast_; ++index)
    {
	kopia[index] = zrodlo[index];
    }
}

void ProblemKomiwojazera::inicjalizacjaTablicyJejNumeremIndexu(int* tablica)
{
    for(int index = 0; index < liczba_miast_; ++index)
    {
        tablica[index] = index;
    }
}

int ProblemKomiwojazera::funkcjaOgraniczen(wezel wezel_drzewa)
{
    std::set <int> zbior_polaczen;
    std::vector <int> minimalne_drogi(liczba_miast_, -1);
    int granica = 0;
   
    for(auto miasto : wezel_drzewa.kombinacja_miast)
    {
        zbior_polaczen.insert(miasto);
    }
    
    
    for ( int i = 0; i < wezel_drzewa.kombinacja_miast.size() - 1; ++i)
    {
        
        minimalne_drogi[wezel_drzewa.kombinacja_miast[i]] = 
                macierz_sasiedztwa_[wezel_drzewa.kombinacja_miast[i]][wezel_drzewa.kombinacja_miast[i+1]];
    }
    
   
    
    for (int i = 0; i < liczba_miast_;++i)
    {
        if(minimalne_drogi[i] == -1)
        {
            std::priority_queue<int, std::vector<int>, std::greater<int> > my_min_heap;
            if(!zbior_polaczen.count(i) && zbior_polaczen.size()!= liczba_miast_)
                my_min_heap.push(macierz_sasiedztwa_[i][0]);
        
            for (int j = 0; j < liczba_miast_;++j)
            {
                if(!zbior_polaczen.count(j)&& macierz_sasiedztwa_[i][j] != -1)
                {
                   
                    my_min_heap.push(macierz_sasiedztwa_[i][j]);
                }
            
            }
            minimalne_drogi[i] = my_min_heap.top();
            
        }
    }    
    for (int i = 0; i < liczba_miast_; i++)
    {
        //std::cout << minimalne_drogi[i] << " ";
        granica += minimalne_drogi[i];
    }
    
    return granica;
}

bool ProblemKomiwojazera::czyJestWKombinacji(int i, wezel wezel_drzewa)
{
       int ii = 0;
    
    while (ii < liczba_miast_)
    {
        if (i == wezel_drzewa.kombinacja_miast[ii])
            return true;
        ii++;
        
    }
       return false;
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
    
    
    return sumaOdleglosci;
}

int ProblemKomiwojazera::sumaOdleglosciDoPokonaniaPomiedzyMiastamiAproksymacyjny
                                            (std::vector <int> kombinacja_miast)
{
    int sumaOdleglosci = 0;
    
    for (int i = 0; i < liczba_miast_ - 1; ++i)
    {
	sumaOdleglosci += macierz_sasiedztwa_[kombinacja_miast[i]][kombinacja_miast[i + 1]];		
    }
    sumaOdleglosci += macierz_sasiedztwa_[kombinacja_miast[liczba_miast_ - 1]][kombinacja_miast[0]];
    
    return sumaOdleglosci;
}
void ProblemKomiwojazera::wierszTrojkataPascala(int* wiersz_trojkata)
{
    wiersz_trojkata[0] = 1;
    int ktoryWiersz = liczba_miast_-1;
    
    for (int k = 0; k < ktoryWiersz; ++k)
    {
        wiersz_trojkata[k+1] = wiersz_trojkata[k] * (ktoryWiersz-k) / (k+1);
    }
}

void ProblemKomiwojazera::generujPodzbioryKElementowe
                            (int ile_podzbiorow, int liczba_elementow_pozdbioru) 
{   
    const int K = liczba_elementow_pozdbioru -1 ;  
    int *zbior = new int[liczba_miast_-1];   
    int p ;
    
    for(int i =0; i <= K; i++)
    {
        zbior[i]=i+1;
    }
    p=K;    
    int j = 0;
    
    while(p>=0)
    {
        std::set <int> temp;
         
        for(int i=0; i <= K; i++)
        {
            zbior_wszystkich_podzbiorow_[indeks_].insert(zbior[i]);    
        }       
        ++indeks_;
               
        if(zbior[K]==liczba_miast_-1)  
        {
            p=p-1;
        }
        else 
            p=K;  
 
        if(p>=0) 
            for(int i=K; i>=p; i--)
            {
                zbior[i] = zbior[p] + i - p + 1;
            }
        
         ++j;
    }
        
    delete [] zbior;   
}

int ProblemKomiwojazera::szukajIndeksu(std::set<int> poszukiwany_zbior) 
{
    if(poszukiwany_zbior.empty())
        return -1;
    
    for (int i = 0; i < zbior_wszystkich_podzbiorow_.size(); ++i)
    {
        if( zbior_wszystkich_podzbiorow_[i] == poszukiwany_zbior)
            return i;            
    }
    return -1;
}

int ProblemKomiwojazera::funkcjaMinimum(int wezel_i, 
                                        int indeks_rozwazanego_podzbioru,
                                        std::vector<std::vector<int>> macierz_kosztow,
                                        int *wartosc_min_wezla_j)
{
    int minimum = std::numeric_limits<int>::max();
    int aktualne_wyliczenie;
    
    for(int element_podzbioru : 
                     zbior_wszystkich_podzbiorow_[indeks_rozwazanego_podzbioru]) 
    {     
        std::set<int> rozwazany_podzbior = 
                     zbior_wszystkich_podzbiorow_[indeks_rozwazanego_podzbioru];
        rozwazany_podzbior.erase(element_podzbioru);
        int indeks_w_macierzy_kosztow = szukajIndeksu(rozwazany_podzbior);
                 
        aktualne_wyliczenie = macierz_sasiedztwa_[wezel_i][element_podzbioru] +
                   macierz_kosztow[element_podzbioru][indeks_w_macierzy_kosztow+1];
        
        if(minimum > aktualne_wyliczenie)
        {
            minimum = aktualne_wyliczenie;
            *wartosc_min_wezla_j = element_podzbioru;
        } 
    }  
    
    return minimum;
}

int ProblemKomiwojazera::funkcjaMinimumCalyPodzbior
                                (std::vector<std::vector<int> > macierz_kosztow,
                                 int *wartosc_min_wezla_j)
{
    std::set<int> podzbior_wszystkich_rozwazanych_miast;
    
    int minimum = std::numeric_limits<int>::max();
    int aktualne_wyliczenie;
    
    for (int i = 1; i < liczba_miast_ ;++i)
    {
        podzbior_wszystkich_rozwazanych_miast.insert(i);
    }
       
    for(int element_podzbioru : podzbior_wszystkich_rozwazanych_miast) 
    {
        std::set<int> rozwazany_podzbior = podzbior_wszystkich_rozwazanych_miast;
        rozwazany_podzbior.erase(element_podzbioru);
        int indeks_w_macierzy_kosztow = szukajIndeksu(rozwazany_podzbior);
        
        aktualne_wyliczenie = macierz_sasiedztwa_[0][element_podzbioru] + 
                macierz_kosztow[element_podzbioru][indeks_w_macierzy_kosztow+1];
        
        if(minimum > aktualne_wyliczenie)
        {
            minimum = aktualne_wyliczenie;
            *wartosc_min_wezla_j = element_podzbioru;
        }
        
    }
     
    return minimum;
}
std::vector<int> ProblemKomiwojazera::odczytajSciezke
                                (std::vector<std::vector<int> > macierz_sciezek)
{
    std::set<int> podzbior_wszystkich_rozwazanych_miast;
    std::vector<int> sciezka;
    sciezka.push_back(0);
    sciezka.push_back(macierz_sciezek[0].back());
    
    for (int i = 1; i < liczba_miast_ ;++i)
    {
        podzbior_wszystkich_rozwazanych_miast.insert(i);
    }
    
    for(int i =0; i< liczba_miast_ -2; ++i)
    {
        podzbior_wszystkich_rozwazanych_miast.erase(sciezka.back());
        int wezel_j_min = szukajIndeksu(podzbior_wszystkich_rozwazanych_miast);
        sciezka.push_back(macierz_sciezek[sciezka.back()][wezel_j_min+1]);
    }
    
    return sciezka;
}
int ProblemKomiwojazera::znajdzIndeksElementu(std::vector<int> zbior_elementow, 
                                                                    int element)
{
    int indeks = -1;
    for ( int i = 0; i < zbior_elementow.size(); ++i)
    {
        if( zbior_elementow[i] == element)
        {
            indeks = i;
            break;
        }
    }
    return indeks;
}

std::vector<std::vector<int>> ProblemKomiwojazera::podzialMiast(double epsilon)
{   
    std::vector<std::vector<int>> podzbiory;
    std::vector<int> miasta;
    std::vector<int> juz_wpisane(liczba_miast_, -1);
    
    int odleglosc_podzialu = wyznaczOdlegloscPodzialu(epsilon);
    
    
    
    for (int i=0; i < liczba_miast_; ++i)
    {
        if (!czyJestWWektorze(juz_wpisane, i))
        {    
        
        for (int ii=0; ii < liczba_miast_; ++ii)
        {
            
            if (macierz_sasiedztwa_[i][ii] <= odleglosc_podzialu && !czyJestWWektorze(juz_wpisane, ii))
            {
                 //std::cout << ii << " ";
                 miasta.push_back(ii);
                 juz_wpisane.push_back(ii);
                 
            }   
        }
       
        podzbiory.push_back(miasta);
        miasta.clear();
        }
    }
    
        
    return podzbiory;
    }


bool ProblemKomiwojazera::czyJestWWektorze (std::vector <int> wektor, int liczba)
{
    for (int i = 0; i < wektor.size(); ++i)
    {
        if (wektor[i] == liczba)
            return 1;
    }
    return 0;
}

int ProblemKomiwojazera::wyznaczOdlegloscPodzialu(double epsilon)
{
    int maks = -2;
    
    for (int i=0 ; i < liczba_miast_; ++i)
    {
        for (int ii = 0; ii < liczba_miast_; ++ii)
        {
            if (macierz_sasiedztwa_[i][ii] > maks)
                maks = macierz_sasiedztwa_[i][ii];
        }
    }
    if (epsilon == 0)
        return maks;
    else
        return maks *(1-epsilon);
}
void ProblemKomiwojazera::generowanieLosowejPermutacji(int* tablica)
{
    
        for(int index = 0; index < liczba_miast_; ++index)
        {
        tablica[index] = index;
        }
        std::random_shuffle(tablica,tablica+liczba_miast_);
   
}
       
    
    

