from django.contrib import admin
from django.forms import TextInput, Textarea
from django.db import models
from SOPK.models import *


class PrzezInline(admin.TabularInline):
    model = Przez
    extra = 1

class PołączenieAdmin(admin.ModelAdmin):

    fieldsets = [
        (None, {'fields': ['nazwa_połączenia', "dworzec_poczatkowy", "dworzec_koncowy", "odjazd",
                           "przyjazd", "liczba_kilometrow", "liczba_miejsc"]}),
        ("Przydziel Pracownika", {'fields' : ['pracownicy']})
    ]
    filter_horizontal = ['pracownicy',]
    list_display = ('nazwa_połączenia', "dworzec_poczatkowy", "dworzec_koncowy", "odjazd",
                           "przyjazd", "liczba_kilometrow", "liczba_miejsc")
    search_fields = ['nazwa_połączenia', "dworzec_poczatkowy", "dworzec_koncowy", "odjazd",
                           "przyjazd", "liczba_kilometrow", "liczba_miejsc"]
    inlines = [PrzezInline]

class DworzecAdmin(admin.ModelAdmin):

    formfield_overrides = {
        models.CharField: {'widget': TextInput(attrs={'size':'50'})},
        models.TextField: {'widget': Textarea(attrs={'rows':4, 'cols':40})},
    }
    list_display = ('nazwa_dworca', 'miasto', 'ulica', 'numer_budynku', 'zdjecie')
    search_fields = ['nazwa_dworca', 'miasto']
    list_filter = ['miasto']

class StanowiskoAdmin(admin.ModelAdmin):

    fieldsets = [
        (None, {'fields': ['nazwa_stanowiska', 'zarobki', 'uprawnienia']}),
    ]
    list_display = ('nazwa_stanowiska', 'zarobki', 'uprawnienia')
    search_fields = ['nazwa_stanowiska', 'zarobki', 'uprawnienia']
    list_filter = ['nazwa_stanowiska']

class PracownikAdmin(admin.ModelAdmin):

    fieldsets = [
        (None, {'fields': ['imię', 'nazwisko', 'data_urodzenia',
                           'numer_telefonu', 'adres_email', 'stanowisko','zdjecie' ]}),
    ]
    list_display = ('imię', 'nazwisko', 'data_urodzenia', 'numer_telefonu', 'adres_email', 'stanowisko','zdjecie')
    search_fields = ['imię', 'nazwisko', 'data_urodzenia', 'numer_telefonu', 'adres_email', 'stanowisko']
    list_filter = ['stanowisko']

class UżytkownikAdmin(admin.ModelAdmin):

    fieldsets = [
        (None, {'fields': ['login', 'haslo', 'imię', 'nazwisko', 'data_urodzenia', 'adres_email']}),
    ]
    list_display = ('login', 'haslo', 'imię', 'nazwisko', 'data_urodzenia', 'adres_email')
    search_fields = ['login', 'haslo', 'imię', 'nazwisko', 'data_urodzenia', 'adres_email']

class BiletAdmin(admin.ModelAdmin):

    fieldsets = [
        (None, {'fields': ['połączenie', 'uzytkownik', 'skad', 'dokad', 'cena' ]}),
    ]
    list_display = ('połączenie', 'uzytkownik', 'skad', 'dokad', 'cena')
    search_fields = ['połączenie', 'uzytkownik', 'skad', 'dokad', 'cena']
    list_filter = ['połączenie']

class TaryfaAdmin(admin.ModelAdmin):

    fieldsets = [
        (None, {'fields': ['od', 'do', 'cena_za_kilometr' ]}),
    ]
    list_display = ('od', 'do', 'cena_za_kilometr')

class ProfilUżytkownikaAdmin(admin.ModelAdmin):

    fieldsets = [
        (None, {'fields': ['user', 'data_urodzenia', 'strona_www', 'avatar']}),
    ]
    list_display = ('user', 'data_urodzenia', 'strona_www', 'avatar')

class RealizacjaPołączeniaAdmin(admin.ModelAdmin):

    fieldsets = [
        (None, {'fields': ['data_połączenia', 'połączenie','liczba_wolnych_miejsc']}),
    ]
    list_display = ('data_połączenia', 'połączenie', 'liczba_wolnych_miejsc')

admin.site.register(Dworzec, DworzecAdmin)
admin.site.register(Połączenie, PołączenieAdmin)
admin.site.register(Stanowisko, StanowiskoAdmin)
admin.site.register(Pracownik, PracownikAdmin)
admin.site.register(Bilet, BiletAdmin)
admin.site.register(Taryfa, TaryfaAdmin)
admin.site.register(ProfilUżytkownika, ProfilUżytkownikaAdmin)
admin.site.register(RealizacjaPołączenia, RealizacjaPołączeniaAdmin)
admin.register(Przez)