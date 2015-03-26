from django import forms
from django.contrib.auth.models import User
from SOPK.models import ProfilUżytkownika
from django.utils.translation import gettext as _
from collections import OrderedDict
from django.core.exceptions import ValidationError

def validate_dlugosc(password):
    if len(password) < 8:
        raise ValidationError("Hasło powinno mieć co najmniej 8 znaków")

def validate_liczba(password):
    jestLiczba = any(char.isdigit() for char in password)
    if not jestLiczba:
        raise ValidationError("Hasło powinno mieć co najmniej 1 cyfrę")

def validate_spacja(password):
    jestSpacja = any(char == " " for char in password)
    if jestSpacja:
        raise ValidationError("Hasło nie może zawierać spacji")

class UżytkownikFormularz(forms.ModelForm):

    username = forms.CharField(help_text="Login:")
    password = forms.CharField(widget=forms.PasswordInput(), help_text="Hasło:", validators=[validate_dlugosc,
                                                                                             validate_liczba,
                                                                                             validate_spacja])
    email = forms.EmailField(help_text="E-Mail:")
    first_name = forms.CharField(help_text="Imię:")
    last_name = forms.CharField(help_text="Nazwisko:")

    class Meta:
        model = User
        fields = ('username','password','email', 'first_name', 'last_name')

class ProfilUżytkownikaFormularz(forms.ModelForm):

    data_urodzenia = forms.DateField(help_text="Data Urodzenia:")
    strona_www = forms.URLField(help_text="Strona WWW:", required=False)
    avatar = forms.ImageField(help_text="Avatar:", required=False)
    class Meta:
        model = ProfilUżytkownika
        fields = ('data_urodzenia', 'strona_www', 'avatar')

class AktualizujProfilFormularz(forms.ModelForm):

    email = forms.EmailField(help_text="E-Mail:")
    first_name = forms.CharField(help_text="Imię:")
    last_name = forms.CharField(help_text="Nazwisko:")

    class Meta:
        model = User
        fields = ('email', 'first_name', 'last_name')

class SetPasswordForm(forms.Form):
    """
    A form that lets a user change set their password without entering the old
    password
    """
    error_messages = {
        'password_mismatch': _("Dwa pola nowego hasła nie pasują do siebie."),
    }
    new_password1 = forms.CharField(label=_("Nowe hasło"),
                                    widget=forms.PasswordInput)
    new_password2 = forms.CharField(label=_("Potwierdź Nowe Hasło"),
                                    widget=forms.PasswordInput)

    def __init__(self, user, *args, **kwargs):
        self.user = user
        super(SetPasswordForm, self).__init__(*args, **kwargs)

    def clean_new_password2(self):
        password1 = self.cleaned_data.get('new_password1')
        password2 = self.cleaned_data.get('new_password2')
        if password1 and password2:
            if password1 != password2:
                raise forms.ValidationError(
                    self.error_messages['password_mismatch'],
                    code='password_mismatch',
                )
        return password2

    def save(self, commit=True):
        self.user.set_password(self.cleaned_data['new_password1'])
        if commit:
            self.user.save()
        return self.user

class PasswordChangeForm(SetPasswordForm):
    """
    A form that lets a user change their password by entering their old
    password.
    """
    error_messages = dict(SetPasswordForm.error_messages, **{
        'password_incorrect': _("Podano nieprawidłowe hasło ! "
                                "Ponów próbę."),
    })
    old_password = forms.CharField(label=_("Stare hasło"),
                                   widget=forms.PasswordInput)

    def clean_old_password(self):
        """
        Validates that the old_password field is correct.
        """
        old_password = self.cleaned_data["old_password"]
        if not self.user.check_password(old_password):
            raise forms.ValidationError(
                self.error_messages['password_incorrect'],
                code='password_incorrect',
            )
        return old_password

PasswordChangeForm.base_fields = OrderedDict(
    (k, PasswordChangeForm.base_fields[k])
    for k in ['old_password', 'new_password1', 'new_password2']
)