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

bool isNumber( const std::string&);

int main(int argc, char** argv) 
{
    std::unique_ptr <ProblemKomiwojazera> instancjaProblemu;
    std::string opcja_liczba_miast;
    std::string opcja_menu;
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
            if (liczba_miast > 0)
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
        if(opcja_menu[0] == 'i')
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
    std::cout << "b) Wczytaj instancje do pliku tekstowego;" <<std::endl;
    std::cout << "c) Zapisz instancje do pliku tekstowego;" << std::endl;
    std::cout << "d) Wyswietl macierz sasiedztwa;" << std::endl;
    std::cout << "e) Algorytm przegladu zupelnego;" << std::endl;
    std::cout << "f) Algorytm podzialu i ograniczen;" << std::endl;
    std::cout << "g) Algorytm programowania dynamicznego;" << std::endl;
    std::cout << "h) Algorytm aproksymacyjny;" << std::endl;
    std::cout << "i) Wyjscie." << std::endl;
    
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
            instancjaProblemu->zapiszDoPlikuTekstowego(nazwa_pliku);
            system("pause");
            system("cls");
            break;
        }
        case 'd':
        {
            instancjaProblemu->wyswietlMacierzSasiedztwa();
            system("pause");
            system("cls");
            break;
        }
        case 'e':
        {
            std::cout << "Algorytm przegladu zupelnego :" << std::endl;
            
            instancjaProblemu->przegladZupelny();
            
            system("pause");
            system("cls");
            break;
        }
        case 'f':
        {
            std::cout << "Algorytm podzialu i ograniczen :" << std::endl;
                 
            instancjaProblemu->algorytmPodzialuIOgraniczen();
            
            system("pause");
            system("cls");
            break;
        }
        case 'g':
        {
            std::cout << "Algorytm programowania dynamicznego :" << std::endl;
                 
            instancjaProblemu->algorytmProgramowaniaDynamicznego();
            
            system("pause");
            system("cls");
            break;
        }
          case 'h':
        {
            double epsilon;
            std::cout << "Algorytm aproksymacyjny :" << std::endl;
            std::cout << "Podaj epsilon:" << std::endl;
            std::cin >> epsilon;
            instancjaProblemu->Aproksymacyjny(epsilon);
            //instancjaProblemu->schematAproksymacyjny(epsilon);
            
            system("pause");
            break;
        }
        case 'i':
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