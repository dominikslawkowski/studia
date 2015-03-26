# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
import django.core.validators
from django.conf import settings


class Migration(migrations.Migration):

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
    ]

    operations = [
        migrations.CreateModel(
            name='Bilet',
            fields=[
                ('id', models.AutoField(serialize=False, auto_created=True, primary_key=True, verbose_name='ID')),
                ('cena', models.FloatField(verbose_name='Cena [zł]')),
            ],
            options={
                'verbose_name_plural': 'Bilety',
                'db_table': 'Bilety',
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Dworzec',
            fields=[
                ('id', models.AutoField(serialize=False, auto_created=True, primary_key=True, verbose_name='ID')),
                ('nazwa_dworca', models.CharField(max_length=40, verbose_name='Nazwa Dworca')),
                ('miasto', models.CharField(max_length=40, verbose_name='Miasto')),
                ('ulica', models.CharField(max_length=50, verbose_name='Ulica')),
                ('numer_budynku', models.PositiveSmallIntegerField(verbose_name='Numer Budynku')),
                ('zdjecie', models.ImageField(blank=True, null=True, upload_to='media/dworce/', verbose_name='Zdjęcie Dworca')),
            ],
            options={
                'verbose_name_plural': 'Dworce',
                'db_table': 'Dworce',
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Połączenie',
            fields=[
                ('id', models.AutoField(serialize=False, auto_created=True, primary_key=True, verbose_name='ID')),
                ('nazwa_połączenia', models.CharField(max_length=30, verbose_name='Nazwa Połączenia')),
                ('odjazd', models.TimeField(verbose_name='Odjazd')),
                ('przyjazd', models.TimeField(verbose_name='Przyjazd')),
                ('liczba_kilometrow', models.PositiveSmallIntegerField(verbose_name='Liczba Kilometrów')),
                ('liczba_miejsc', models.PositiveSmallIntegerField(verbose_name='Liczba Miejsc')),
                ('dworzec_koncowy', models.ForeignKey(to='SOPK.Dworzec', verbose_name='Dworzec Końcowy', related_name='dworzec_koncowy')),
                ('dworzec_poczatkowy', models.ForeignKey(to='SOPK.Dworzec', verbose_name='Dworzec Początkowy', related_name='dworzec_poczatkowy')),
            ],
            options={
                'verbose_name_plural': 'Połączenia',
                'db_table': 'Połączenia',
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Pracownik',
            fields=[
                ('id', models.AutoField(serialize=False, auto_created=True, primary_key=True, verbose_name='ID')),
                ('imię', models.CharField(max_length=20, verbose_name='Imię')),
                ('nazwisko', models.CharField(max_length=40, verbose_name='Nazwisko')),
                ('data_urodzenia', models.DateField(verbose_name='Data Urodzenia')),
                ('numer_telefonu', models.CharField(validators=[django.core.validators.RegexValidator(regex='^\\+?1?\\d{9,15}$', message="Phone number must be entered in the format: '+999999999'. Up to 15 digits allowed.")], blank=True, max_length=15, verbose_name='Numer Telefonu')),
                ('adres_email', models.EmailField(blank=True, null=True, max_length=75, verbose_name='Adres E-Mail')),
                ('zdjecie', models.ImageField(blank=True, null=True, upload_to='media/pracownicy/', verbose_name='Zdjęcie Legitymacyjne')),
            ],
            options={
                'verbose_name_plural': 'Pracownicy',
                'db_table': 'Pracownicy',
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='ProfilUżytkownika',
            fields=[
                ('id', models.AutoField(serialize=False, auto_created=True, primary_key=True, verbose_name='ID')),
                ('data_urodzenia', models.DateField(verbose_name='Data Urodzenia')),
                ('strona_www', models.URLField(blank=True, null=True, verbose_name='Strona WWW')),
                ('avatar', models.ImageField(blank=True, null=True, upload_to='media/zdjecia_profilowe', verbose_name='Avatar')),
                ('user', models.OneToOneField(to=settings.AUTH_USER_MODEL)),
            ],
            options={
                'verbose_name_plural': 'Profile Użytkowników',
                'db_table': 'ProfileUżytkowników',
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Przez',
            fields=[
                ('id', models.AutoField(serialize=False, auto_created=True, primary_key=True, verbose_name='ID')),
                ('numer_na_trasie', models.PositiveSmallIntegerField(verbose_name='Numer Na Trasie')),
                ('przyjazd', models.TimeField(verbose_name='Przyjazd')),
                ('odjazd', models.TimeField(verbose_name='Odjazd')),
                ('kilometr', models.PositiveSmallIntegerField(verbose_name='Kilometr')),
                ('dworzec', models.ForeignKey(to='SOPK.Dworzec', verbose_name='Dworzec')),
                ('połączenie', models.ForeignKey(to='SOPK.Połączenie', verbose_name='Połączenie')),
            ],
            options={
                'verbose_name_plural': 'Przez',
                'db_table': 'Przez',
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='RealizacjaPołączenia',
            fields=[
                ('id', models.AutoField(serialize=False, auto_created=True, primary_key=True, verbose_name='ID')),
                ('data_połączenia', models.DateField(verbose_name='Data Połączenia')),
                ('liczba_wolnych_miejsc', models.PositiveSmallIntegerField()),
                ('połączenie', models.ForeignKey(to='SOPK.Połączenie')),
            ],
            options={
                'verbose_name_plural': 'Realizacje Połączeń',
                'db_table': 'RealizacjaPołączenia',
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Stanowisko',
            fields=[
                ('nazwa_stanowiska', models.CharField(serialize=False, unique=True, primary_key=True, max_length=100, verbose_name='Nazwa Stanowiska')),
                ('zarobki', models.FloatField(verbose_name='Zarobki [zł]')),
                ('uprawnienia', models.CharField(max_length=100, verbose_name='Uprawnienia')),
            ],
            options={
                'verbose_name_plural': 'Stanowiska',
                'db_table': 'Stanowiska',
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Taryfa',
            fields=[
                ('id', models.AutoField(serialize=False, auto_created=True, primary_key=True, verbose_name='ID')),
                ('od', models.PositiveSmallIntegerField(verbose_name='Od')),
                ('do', models.PositiveSmallIntegerField(verbose_name='Do')),
                ('cena_za_kilometr', models.FloatField(verbose_name='Cena Za Kilometr [zł]')),
            ],
            options={
                'verbose_name_plural': 'Taryfy',
                'db_table': 'Taryfy',
            },
            bases=(models.Model,),
        ),
        migrations.AddField(
            model_name='pracownik',
            name='stanowisko',
            field=models.ForeignKey(to='SOPK.Stanowisko', verbose_name='Stanowisko'),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='połączenie',
            name='pracownicy',
            field=models.ManyToManyField(to='SOPK.Pracownik'),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='bilet',
            name='dokad',
            field=models.ForeignKey(to='SOPK.Dworzec', verbose_name='Dokąd', related_name='dokad'),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='bilet',
            name='połączenie',
            field=models.ForeignKey(to='SOPK.Połączenie'),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='bilet',
            name='skad',
            field=models.ForeignKey(to='SOPK.Dworzec', verbose_name='Skąd', related_name='skad'),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='bilet',
            name='uzytkownik',
            field=models.ForeignKey(to=settings.AUTH_USER_MODEL),
            preserve_default=True,
        ),
    ]
