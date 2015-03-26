from django.shortcuts import render, render_to_response, RequestContext, HttpResponse, HttpResponseRedirect
from django.contrib.auth import authenticate, login, logout
from django.core.urlresolvers import reverse
from django.contrib.auth.decorators import login_required
from django.views.decorators.debug import sensitive_post_parameters
from django.views.decorators.csrf import csrf_protect
from SOPK.forms import *
from SOPK.models import *
from django.contrib.auth import update_session_auth_hash
import collections
import datetime

def index(request):

    context = RequestContext(request)
    context_dict = {'temporary_message': "Witamy w Systemie Obsługi Połączeń Kolejowych !"}

    return render_to_response("SOPK/index.html", context_dict, context)

@csrf_protect
def rejestruj(request):

    zarejestrowany = False
    error_message = collections.OrderedDict()
    if request.method == 'POST':

        formularz_uzytkownika = UżytkownikFormularz(data=request.POST)
        formularz_profilu_uzytkownika = ProfilUżytkownikaFormularz(data=request.POST)

        if formularz_uzytkownika.is_valid() and formularz_profilu_uzytkownika.is_valid():
            uzytkownik = formularz_uzytkownika.save()
            uzytkownik.set_password(uzytkownik.password)
            uzytkownik.save()

            profil_uzytkownika = formularz_profilu_uzytkownika.save(commit=False)
            profil_uzytkownika.user = uzytkownik

            if 'avatar' in request.FILES:
                profil_uzytkownika.avatar = request.FILES['avatar']

            profil_uzytkownika.save()

            zarejestrowany = True

        else:
            if 'username' in formularz_uzytkownika.errors.keys():
                error_message['Login'] = str(formularz_uzytkownika.errors['username'])
            if 'password' in formularz_uzytkownika.errors.keys():
                error_message['Hasło'] = str(formularz_uzytkownika.errors['password'])
            if 'first_name' in formularz_uzytkownika.errors.keys():
                error_message['Imię'] = str(formularz_uzytkownika.errors['first_name'])
            if 'last_name' in formularz_uzytkownika.errors.keys():
                error_message['Nazwisko'] = str(formularz_uzytkownika.errors['last_name'])
            if 'email' in formularz_uzytkownika.errors.keys():
                error_message['E-Mail'] = str(formularz_uzytkownika.errors['email'])
            if 'data_urodzenia' in formularz_profilu_uzytkownika.errors.keys():
                error_message['Data Urodzenia'] = str(formularz_profilu_uzytkownika.errors['data_urodzenia'])
            if 'strona_www' in formularz_profilu_uzytkownika.errors.keys():
                error_message['Strona WWW'] = str(formularz_profilu_uzytkownika.errors['strona_www'])
            if 'avatar' in formularz_profilu_uzytkownika.errors.keys():
                error_message['Avatar'] = str(formularz_profilu_uzytkownika.errors['avatar'])

            for key in error_message:
                error_message[key] = (str(error_message[key])).replace('<ul class="errorlist"><li>', '')
                error_message[key] = (str(error_message[key])).replace('</li></ul>', '')

            print(formularz_uzytkownika.errors, formularz_profilu_uzytkownika.errors)

    else:
        formularz_uzytkownika = UżytkownikFormularz()
        formularz_profilu_uzytkownika = ProfilUżytkownikaFormularz()

    return render(request,
            'SOPK/rejestruj.html',
            {'formularz_uzytkownika': formularz_uzytkownika,
             'formularz_profilu_uzytkownika': formularz_profilu_uzytkownika,
             'zarejestrowany': zarejestrowany,
             'error_message' : error_message} )

def logowanie(request):

    context = {}
    if request.method == 'POST':
        username = request.POST['username']
        password = request.POST['password']

        użytkownik = authenticate(username=username, password=password)

        if użytkownik:
            if użytkownik.is_active:
                login(request, użytkownik)
                return HttpResponseRedirect(reverse('SOPK:index'))
            else:
                context['error_message'] = "Twoje konto jest zablokowane"
        else:
            context['error_message'] = "Podano błędne dane do logowania, spróbuj ponownie !"

    return render(request, 'SOPK/login.html', context)

@login_required
def edycja(request):

    error_message = collections.OrderedDict()
    current_user = request.user
    message = ""
    if request.method == 'POST':
        formularz_uzytkownika = AktualizujProfilFormularz(request.POST, instance=current_user)
        formularz_profilu_uzytkownika = ProfilUżytkownikaFormularz(request.POST, request.FILES, instance=current_user.profilużytkownika)
        if formularz_uzytkownika.is_valid() and formularz_profilu_uzytkownika.is_valid():
            formularz_uzytkownika.save()
            formularz_profilu_uzytkownika.save()
            message = "Zmiany zostały zapisane !"
        else:
            if 'first_name' in formularz_uzytkownika.errors.keys():
                error_message['Imię'] = str(formularz_uzytkownika.errors['first_name'])
            if 'last_name' in formularz_uzytkownika.errors.keys():
                error_message['Nazwisko'] = str(formularz_uzytkownika.errors['last_name'])
            if 'email' in formularz_uzytkownika.errors.keys():
                error_message['E-Mail'] = str(formularz_uzytkownika.errors['email'])
            if 'data_urodzenia' in formularz_profilu_uzytkownika.errors.keys():
                error_message['Data Urodzenia'] = str(formularz_profilu_uzytkownika.errors['data_urodzenia'])
            if 'strona_www' in formularz_profilu_uzytkownika.errors.keys():
                error_message['Strona WWW'] = str(formularz_profilu_uzytkownika.errors['new_password2'])
            if 'avatar' in formularz_profilu_uzytkownika.errors.keys():
                error_message['Avatar'] = str(formularz_profilu_uzytkownika.errors['new_password2'])

            for key in error_message:
                error_message[key] = (str(error_message[key])).replace('<ul class="errorlist"><li>', '')
                error_message[key] = (str(error_message[key])).replace('</li></ul>', '')

    formularz_uzytkownika = AktualizujProfilFormularz(instance=current_user)
    formularz_profilu_uzytkownika = ProfilUżytkownikaFormularz(instance=current_user.profilużytkownika)

    context = {'formularz_uzytkownika': formularz_uzytkownika,
             'formularz_profilu_uzytkownika': formularz_profilu_uzytkownika,
             'message': message,
             'error_message': error_message}

    return render(request, 'SOPK/edytuj.html', context)


@login_required
def wylogowywanie(request):

    logout(request)
    return HttpResponseRedirect(reverse('SOPK:index'))

@sensitive_post_parameters()
@csrf_protect
@login_required
def password_change(request):

    zmieniono_haslo = False
    error_message = collections.OrderedDict()
    context = {}
    form = PasswordChangeForm(request.user)
    context["form"] = form

    if request.method == 'POST':
        formularz_nowego_hasla = PasswordChangeForm(user=request.user, data=request.POST)
        if formularz_nowego_hasla.is_valid():
            formularz_nowego_hasla.save()
            update_session_auth_hash(request, formularz_nowego_hasla.user)
            zmieniono_haslo = True
        else:
            if 'old_password' in formularz_nowego_hasla.errors.keys():
                error_message['Stare Hasło'] = str(formularz_nowego_hasla.errors['old_password'])
            if 'new_password1' in formularz_nowego_hasla.errors.keys():
                error_message['Nowe Hasło'] = str(formularz_nowego_hasla.errors['new_password1'])
            if 'new_password2' in formularz_nowego_hasla.errors.keys():
                error_message['Potwierdź Nowe Hasło'] = str(formularz_nowego_hasla.errors['new_password2'])

            for key in error_message:
                error_message[key] = (str(error_message[key])).replace('<ul class="errorlist"><li>', '')
                error_message[key] = (str(error_message[key])).replace('</li></ul>', '')

            print(error_message)

    context['zmieniono_haslo'] = zmieniono_haslo
    context['error_message'] = error_message
    return render(request, 'SOPK/zmien_haslo.html', context)

def czas_trwania_połączenia(czas_odjazdu, czas_przyjazdu, splitted_date):

    data_odjazdu = datetime.date(int(splitted_date[0]),int(splitted_date[1]), int(splitted_date[2]))
    data_przyjazdu = data_odjazdu

    if(czas_przyjazdu <= czas_odjazdu):
        data_przyjazdu = datetime.date(int(splitted_date[0]),int(splitted_date[1]), int(splitted_date[2]) + 1)


    return datetime.datetime.combine(data_przyjazdu,czas_przyjazdu) - datetime.datetime.combine(data_odjazdu,czas_odjazdu),data_przyjazdu

@csrf_protect
def szukaj(request):
    context = {}

    if request.method == 'POST':
        zbior_polaczen = []

        szukane_miasto_odjazdu = request.POST['skad']
        szukane_miasto_przyjazdu = request.POST['dokad']
        szukana_data_i_czas = request.POST['data']

        context['data_wyszukiwania'] = szukana_data_i_czas
        context['miasto_a'] = szukane_miasto_odjazdu
        context['miasto_b'] = szukane_miasto_przyjazdu

        try:
            odzielona_data_i_czas = str(szukana_data_i_czas).split(' ')
            data = odzielona_data_i_czas[0].split('-')
            czas = odzielona_data_i_czas[1].split(':')

            poszukiwana_data = datetime.date(int(data[0]),int(data[1]),int(data[2]))
            poszukiwany_czas_odjazdu = datetime.time(int(czas[0]), int(czas[1]))

            poszukiwane_połączenia = RealizacjaPołączenia.objects.filter(data_połączenia = poszukiwana_data)
            poszukiwane_połączenia = sorted(list(poszukiwane_połączenia), key=lambda klucz_sort: klucz_sort.połączenie.odjazd)
        except:
            print ("Błędny format day")
        else:
            for polaczenie in poszukiwane_połączenia:

                if (polaczenie.połączenie.odjazd >= poszukiwany_czas_odjazdu
                    and polaczenie.połączenie.dworzec_poczatkowy.miasto == szukane_miasto_odjazdu
                    and polaczenie.połączenie.dworzec_koncowy.miasto == szukane_miasto_przyjazdu):

                    czas_trwania, data_przyjazdu = czas_trwania_połączenia(polaczenie.połączenie.odjazd,
                                                                  polaczenie.połączenie.przyjazd,
                                                                  data)
                    polaczenie_kolejowe = []
                    polaczenie_kolejowe.append(polaczenie)
                    polaczenie_kolejowe.append(czas_trwania)
                    polaczenie_kolejowe.append(data_przyjazdu)
                    zbior_polaczen.append(polaczenie_kolejowe)
        finally:

            if not zbior_polaczen:
                context['error_message'] = "Nie znaleziono połączeń !"
            else:
                context['wyniki'] = zbior_polaczen

            return render(request, 'SOPK/wyniki.html', context)

    return render(request, 'SOPK/search.html', context)
