/* 
 * File:   KolejkaTabu.cpp
 * Author: Piotr Chmiel, Maciej Stelmaszuk
 * 
 * Created on 2 grudzień 2014, 16:22
 */
#include "KolejkaTabu.h"

KolejkaTabu::KolejkaTabu(int dlugosc):
        dlugosc_(dlugosc),
        obecna_dlugosc_(0),
        poczatek_(0),
        kolejka_(dlugosc, ruch())
{
    
}     
KolejkaTabu::KolejkaTabu(const KolejkaTabu& orig) 
{
}

void KolejkaTabu::dodaj(ruch r) {
    if (kolejka_[poczatek_].lewo == -1) ++obecna_dlugosc_;
		kolejka_[poczatek_++] = r;
		if (poczatek_ == dlugosc_) 
                    poczatek_ = 0;
}

ruch KolejkaTabu::pobierz(int i) {
    if (i < 0 || obecna_dlugosc_ <= i) 
        return ruch();
	int temp = obecna_dlugosc_ - 1 - i;
	if (temp < 0) temp = dlugosc_ + temp;
		return kolejka_[temp];
}


KolejkaTabu::~KolejkaTabu() {
}

