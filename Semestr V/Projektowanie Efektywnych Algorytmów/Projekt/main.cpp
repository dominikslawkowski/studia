/* 
 * File:   main.cpp
 * Author: Piotr Chmiel, Maciej Stelmaszuk
 *
 * Created on 6 październik 2014, 18:28
 */

#include <iostream>
#include <memory>
#include <cstdlib>
#include "ProblemKomiwojazera.h"
#include "KolejkaTabu.h"

bool isNumber( const std::string&);

int main(int argc, char** argv) 
{
    std::unique_ptr <ProblemKomiwojazera> instancjaProblemu;
    std::string opcja_liczba_miast;
    std::string opcja_menu;
    std::string opcja_podmenu;
    std::string nazwa_pliku;
    int liczba_miast = 3;
    
    
    while (true)
    {
    std::cout << "Problem Komiwojazera" << std::endl;
    std::cout << "Prosze podaj liczbe miast (liczba calkowita dodatnia wieksza niz 2): ";
    std::getline(std::cin, opcja_liczba_miast);
    
        if(isNumber(opcja_liczba_miast))
        {
            int liczba_miast = std::atoi(opcja_liczba_miast.c_str());
            if (liczba_miast > 2)
            {
            instancjaProblemu = std::unique_ptr<ProblemKomiwojazera> 
                                        (new ProblemKomiwojazera(liczba_miast));
            break;
            }
            else
            {
                std::cout << std::endl << "Podano nieprawidlowe dane ! "
                                          "Sprobuj ponownie !" << std::endl;
                system("pause");
                system("cls");
                continue;
            }           
        }
        else
        {
            std::cout << std::endl << "Podano nieprawidlowe dane ! "
                                      "Sprobuj ponownie !" << std::endl;
            system("pause");
            system("cls");
        }
    }
    system("cls");
    
    while (true)
    {
        if(opcja_menu[0] == 'k')
        {
            std::cout << "Program zostanie zakonczony!" << std::endl;
            std::system("pause");
            break;
        }
        
    std::cout << "Problem Komiwojazera - wybrano " 
            << instancjaProblemu->pobierzLiczbeMiast() << " miast." <<std::endl;
    std::cout << std::endl;
    std::cout << "MENU GLOWNE:" <<std::endl;
    std::cout << "a) Wygeneruj nowa instancje problemu;" <<std::endl;
    std::cout << "b) Wczytaj instancje z pliku tekstowego;" <<std::endl;
    std::cout << "c) Wczytaj instancje z pliku *.atsp" << std::endl;
    std::cout << "d) Wczytaj instancje z pliku *.tsp" << std::endl;
    std::cout << "e) Zapisz instancje do pliku tekstowego;" << std::endl;
    std::cout << "f) Wyswietl macierz sasiedztwa;" << std::endl;
    std::cout << "g) Algorytm przegladu zupelnego;" << std::endl;
    std::cout << "h) Algorytm Symulowanego Wyzarzania;" << std::endl;
    std::cout << "i) Algorytm Przeszukiwania Tabu;" << std::endl;
    std::cout << "j) Algorytm Genetyczny;" << std::endl;
    std::cout << "k) Wyjscie." << std::endl;
    
    
    std::cout << std::endl << "Podaj wybrana opcje: ";
    std::getline(std::cin, opcja_menu);
    std::cout << std::endl;
   
    switch(opcja_menu[0])
    {
        case 'a':
        {
            std::cout << "Prosze podaj liczbe miast (liczba calkowita dodatnia wieksza niz 2): ";
            std::getline(std::cin, opcja_liczba_miast);
    
            if(isNumber(opcja_liczba_miast))
            {
                int liczba_miast = std::atoi(opcja_liczba_miast.c_str());
                
                if (liczba_miast > 2)
                {
                    instancjaProblemu = std::unique_ptr<ProblemKomiwojazera> 
                                        (new ProblemKomiwojazera(liczba_miast));
                    std::cout << "Wygenerowano nowa instancje" << std::endl;
                    system("pause");
                    system("cls");
                    break;
                }
                else
                {
                    std::cout << std::endl << "Podano nieprawidlowe dane ! "
                                              "Sprobuj ponownie !" << std::endl;
                    system("pause");
                    system("cls");
                    break;
                }
            
        }
        else
        {
            std::cout << std::endl << "Podano nieprawidlowe dane ! "
                                      "Sprobuj ponownie !" << std::endl;
            system("pause");
            system("cls");
        }
        break;
    }     
        case 'b':
        {
            std::cout << "Podaj nazwe pliku : ";
            std::getline(std::cin, nazwa_pliku);
            instancjaProblemu->wczytajZPlikuTekstowego(nazwa_pliku);
            system("pause");
            system("cls");
            break;
        }
        case 'c':
        {
            std::cout << "Podaj nazwe pliku : ";
            std::getline(std::cin, nazwa_pliku);
            instancjaProblemu->wczytajZPlikuATSP(nazwa_pliku);
            system("pause");
            system("cls");
            break;
        }
        case 'd':
        {
            std::cout << "Podaj nazwe pliku : ";
            std::getline(std::cin, nazwa_pliku);
            instancjaProblemu->wczytajzPlikuTSP(nazwa_pliku);
            system("pause");
            system("cls");
            break;
            
        }
        case 'e':
        {
            std::cout << "Podaj nazwe pliku : ";
            std::getline(std::cin, nazwa_pliku);
            instancjaProblemu->zapiszDoPlikuTekstowego(nazwa_pliku);
            system("pause");
            system("cls");
            break;
        }
        case 'f':
        {
            instancjaProblemu->wyswietlMacierzSasiedztwa();
            system("pause");
            system("cls");
            break;
        }
        case 'g':
        {
            std::cout << "Algorytm przegladu zupelnego :" << std::endl;
            
            instancjaProblemu->przegladZupelny();
            
            system("pause");
            system("cls");
            break;
        }
        case 'h':
        {
            double temperatura_poczatkowa, temperatura_koncowa, wspolczynnik_schladzania;
            std::cout << "Algorytm sumylowanego wyzarzania :" << std::endl;         
            std::cout << "Podaj temperature koncowa z przedzialu R(0,x): ";
            std::cin >> temperatura_koncowa;
            std::cout << std::endl;
            std::cout << "Podaj wspolczynnik obnizania temperatury z przedzialu R(0,1): ";
            std::cin >> wspolczynnik_schladzania;
            std::cout << std::endl;
            
            temperatura_poczatkowa = instancjaProblemu->wyznaczenieOpytmalnejTemperaturyPoczatkowej();                
            instancjaProblemu->algorytmSymulowanegoWyzarzania(temperatura_poczatkowa, temperatura_koncowa, wspolczynnik_schladzania);
            
            system("pause");
            system("cls");
            break;
        }
        case 'i':
        {
            bool poprawny_wybor = false;
            bool typ_kryterium_stopu;
            int wartosc_kryterium_stopu = 50;
            int dlugosc_kolejki;
            
            std::string wpisana_wartosc;
            
            while (!poprawny_wybor)
            {
                system ("cls");
                std::cout << "Algorytm Przeszukiwania Tabu :" << std::endl;
                std::cout << "Podaj dlugosc Kolejki Tabu:" << std::endl;
                std::cin >> dlugosc_kolejki;
                std::cin.sync();
                std::cout << "Wybierz kryterium koncowe: " << std::endl;
                std::cout << "a) Liczba nieefektywnych krokow" << std::endl;
                std::cout << "b) Liczba iteracji" << std::endl;
                std::getline(std::cin, opcja_podmenu);
                switch (opcja_podmenu[0])
                    {
                    case 'a':
                    {
                        typ_kryterium_stopu = 1;
                        std::cout << "Wybrano a) Liczba nieefektywnych krokow\n";
                        std::cout << "Podaj wartosc kryterium: (domyslnie: 50) " << std::endl;
                        std::getline(std::cin, wpisana_wartosc);
                        if(isNumber(wpisana_wartosc))
                            wartosc_kryterium_stopu = std::atoi(wpisana_wartosc.c_str());
                        poprawny_wybor = true;
                        system("pause");
                        system("cls");
                        break;
                    }
                    case 'b':
                    {
                        typ_kryterium_stopu = 0;
                        std::cout << "Wybrano b) Liczba iteracji\n";
                        std::cout << "Podaj wartosc kryterium: (domyslnie: 50) " << std::endl;
                        std::getline(std::cin, wpisana_wartosc);
                        
                        if(isNumber(wpisana_wartosc))
                            wartosc_kryterium_stopu = std::atoi(wpisana_wartosc.c_str());
                        poprawny_wybor = true;
                        system("pause");
                        system("cls");
                        break;
                    }
                    default:
                    {
                        std::cout <<"Nie ma takiej opcji!" << std::endl;
                        system("pause");
                        system("cls");
                        break;
                    }
                    }
            }
                    
                instancjaProblemu->przeszukiwanieTabu(dlugosc_kolejki,
                                  typ_kryterium_stopu, wartosc_kryterium_stopu);
            
            system("pause");
            system("cls");
            break;
        }
        case 'j':
        {
            int liczba_osobnikow_populacji, liczba_iteracji;
            std::cout << "Algorytm genetyczny :" << std::endl;         
            std::cout << "Podaj liczbe osobnikow populacji: ";
            std::cin >> liczba_osobnikow_populacji;
            std::cout << std::endl;
            std::cout << "Podaj liczbe iteracji: ";
            std::cin >> liczba_iteracji;
            std::cout << std::endl;
            instancjaProblemu->AlgorytmGenetyczny(liczba_osobnikow_populacji, liczba_iteracji);
            system("pause");
            system("cls");
            break;
        }
        case 'k':
        {
            system("cls");
            break;
        }
        default:
        {
            std::cout << "Taka opcja nie istnieje ! "
                         "Sprobuj ponownie !" << std::endl;
            system("pause");
            system("cls");
            break;
        }
    
    }
      
    }
   return 0;    
}

bool isNumber( const std::string& wzorzec )
{
  
  for( char znak : wzorzec )
  {
    if( !isdigit( znak ) ) 
      return 0 ;
  }
  return 1 ;
}
