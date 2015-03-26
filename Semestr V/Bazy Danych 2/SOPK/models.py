# -*- coding: utf-8 -*-
from django.db import models
from django.core.validators import RegexValidator
from django.contrib.auth.models import User

class Dworzec (models.Model):

    def __str__(self):
        return '{0}: {1}'.format(self.nazwa_dworca, self.miasto)

    nazwa_dworca = models.CharField(max_length=40, verbose_name="Nazwa Dworca")
    miasto = models.CharField(max_length=40, verbose_name="Miasto")
    ulica = models.CharField(max_length=50, verbose_name="Ulica")
    numer_budynku = models.PositiveSmallIntegerField(verbose_name="Numer Budynku")
    zdjecie = models.ImageField("Zdjęcie Dworca", upload_to= "media/dworce/", blank = True, null = True,)
    class Meta:
        db_table = "Dworce"
        verbose_name_plural = "Dworce"

class Stanowisko (models.Model):

    def __str__(self):
        return self.nazwa_stanowiska

    nazwa_stanowiska = models.CharField(primary_key=True, unique=True, max_length=100,
                                        verbose_name="Nazwa Stanowiska")
    zarobki = models.FloatField(verbose_name="Zarobki [zł]")
    uprawnienia = models.CharField(max_length=100, verbose_name="Uprawnienia")

    class Meta:
        db_table = "Stanowiska"
        verbose_name_plural = "Stanowiska"


class Pracownik (models.Model):

    def __str__(self):
        return '{0}: {1} {2}'.format(self.stanowisko, self.imię, self.nazwisko)

    imię = models.CharField(max_length= 20, verbose_name="Imię")
    nazwisko = models.CharField(max_length=40, verbose_name="Nazwisko")
    data_urodzenia = models.DateField(verbose_name="Data Urodzenia")
    telefon_regex = RegexValidator(regex=r'^\+?1?\d{9,15}$',
                        message="Phone number must be entered in the format: '+999999999'. Up to 15 digits allowed.")
    numer_telefonu = models.CharField(validators=[telefon_regex], max_length=15, blank=True,
                                      verbose_name="Numer Telefonu")
    adres_email = models.EmailField(blank=True, null= True, verbose_name="Adres E-Mail")
    stanowisko = models.ForeignKey(Stanowisko, verbose_name="Stanowisko")
    zdjecie = models.ImageField("Zdjęcie Legitymacyjne", upload_to= "media/pracownicy/", blank = True, null = True)

    class Meta:
        db_table = "Pracownicy"
        verbose_name_plural = "Pracownicy"

class Połączenie (models.Model):

    def __str__(self):
        return '{0} {1} Relacja: {2}-{3}'.format(self.id, self.nazwa_połączenia, self.dworzec_poczatkowy,
                                                 self.dworzec_koncowy)

    nazwa_połączenia = models.CharField(max_length=30, verbose_name="Nazwa Połączenia")
    dworzec_poczatkowy = models.ForeignKey(Dworzec, related_name='dworzec_poczatkowy', verbose_name="Dworzec Początkowy")
    dworzec_koncowy = models.ForeignKey(Dworzec, related_name='dworzec_koncowy', verbose_name= "Dworzec Końcowy")
    odjazd = models.TimeField(verbose_name="Odjazd")
    przyjazd = models.TimeField(verbose_name="Przyjazd")
    liczba_kilometrow = models.PositiveSmallIntegerField(verbose_name="Liczba Kilometrów")
    liczba_miejsc = models.PositiveSmallIntegerField(verbose_name="Liczba Miejsc")
    pracownicy = models.ManyToManyField(Pracownik)

    class Meta:
        db_table = "Połączenia"
        verbose_name_plural = "Połączenia"

class Przez (models.Model):

    def __str__(self):
        return '{0} {1} Odjazd: {2}'.format(self.numer_na_trasie, self.dworzec, self.odjazd)

    połączenie = models.ForeignKey(Połączenie, verbose_name="Połączenie")
    numer_na_trasie = models.PositiveSmallIntegerField(verbose_name="Numer Na Trasie")
    dworzec = models.ForeignKey(Dworzec, verbose_name="Dworzec")
    przyjazd = models.TimeField(verbose_name="Przyjazd")
    odjazd = models.TimeField(verbose_name="Odjazd")
    kilometr = models.PositiveSmallIntegerField(verbose_name="Kilometr")

    class Meta:
        db_table = "Przez"
        verbose_name_plural = "Przez"

class Bilet (models.Model):

    def __str__(self):
        return '{0} {1} {2} zł'.format(self.id, self.połączenie, self.cena)

    połączenie = models.ForeignKey(Połączenie)
    uzytkownik = models.ForeignKey(User)
    skad = models.ForeignKey(Dworzec, related_name='skad', verbose_name="Skąd")
    dokad = models.ForeignKey(Dworzec, related_name='dokad', verbose_name="Dokąd")
    cena = models.FloatField(verbose_name="Cena [zł]")

    class Meta:
        db_table = "Bilety"
        verbose_name_plural = "Bilety"

class Taryfa(models.Model):

    def __str__(self):
        return 'Od: {0}km do {1}km cena\km {3}zł: {2}'.format(self.od, self.do, self.cena_za_kilometr)

    od = models.PositiveSmallIntegerField(verbose_name= "Od")
    do = models.PositiveSmallIntegerField(verbose_name= "Do")
    cena_za_kilometr = models.FloatField(verbose_name="Cena Za Kilometr [zł]")

    class Meta:
        db_table = "Taryfy"
        verbose_name_plural = "Taryfy"

class ProfilUżytkownika(models.Model):

    user = models.OneToOneField(User)
    data_urodzenia = models.DateField(verbose_name= "Data Urodzenia")
    strona_www = models.URLField(blank=True, null = True, verbose_name= "Strona WWW")
    avatar = models.ImageField(upload_to='media/zdjecia_profilowe', blank=True, null=True, verbose_name= "Avatar")

    class Meta:
        db_table = "ProfileUżytkowników"
        verbose_name_plural = "Profile Użytkowników"

    def __str__(self):
        return self.user.username

class RealizacjaPołączenia(models.Model):

    def __str__(self):
        return 'Odjazd: {0}'.format(self.data_połączenia)

    data_połączenia = models.DateField(null=False, blank=False, verbose_name="Data Połączenia")
    połączenie = models.ForeignKey(Połączenie)
    liczba_wolnych_miejsc = models.PositiveSmallIntegerField()

    class Meta:
        db_table = "RealizacjaPołączenia"
        verbose_name_plural = "Realizacje Połączeń"
