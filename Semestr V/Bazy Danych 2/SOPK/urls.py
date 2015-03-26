from django.conf.urls import patterns, url
from django.contrib import admin
from SOPK import views
admin.autodiscover()
urlpatterns = patterns('',
     url(r'^$', views.index, name ='index'),
     url(r'^rejestruj/$', views.rejestruj, name='rejestruj'),
     url(r'^logowanie/$', views.logowanie, name='logowanie'),
     url(r'^edycja_profilu/$', views.edycja, name='restricted'),
     url(r'^zmiana_hasla/$', views.password_change, name='password'),
     url(r'^szukaj/$', views.szukaj, name='szukaj'),
     url(r'^wyloguj/$', views.wylogowywanie, name='wylogowywanie'),

)


