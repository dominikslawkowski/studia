/* 
 * File:   KolejkaTabu.h
 * Author: Piotr Chmiel, Maciej Stelmaszuk
 *
 * Created on 2 grudzień 2014, 16:22
 */

#ifndef KOLEJKATABU_H
#define	KOLEJKATABU_H

#include <vector>

struct ruch{
    int lewo;
    int prawo;


    ruch()
    {
        lewo = -1;
        prawo = -1;
    }
    ruch (int lewo, int prawo)
    {
        this->lewo = lewo;
        this->prawo = prawo;
    }
    
    
};

class KolejkaTabu {
public:
    
    KolejkaTabu(int dlugosc);
    int pobierzDlugosc(){ return dlugosc_;};
    void dodaj(ruch r);
    ruch pobierz(int i);
    KolejkaTabu(const KolejkaTabu& orig);
    virtual ~KolejkaTabu();
    
private:
    int dlugosc_;
    int obecna_dlugosc_;
    int poczatek_;
    std::vector <ruch> kolejka_;
};

#endif	/* KOLEJKATABU_H */

