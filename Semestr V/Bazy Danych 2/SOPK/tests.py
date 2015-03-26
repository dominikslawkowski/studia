from django.test import TestCase, LiveServerTestCase
from selenium.webdriver.firefox.webdriver import WebDriver
from selenium.webdriver.support.wait import WebDriverWait
from django.core.urlresolvers import reverse
from django.contrib.auth.models import User

class ViewsTests(TestCase):

    def test_index_positive_response(self):
        response = self.client.get(reverse('SOPK:index'))
        self.assertEqual(response.status_code, 200)
        self.assertTemplateUsed(response, 'SOPK/index.html')

    def test_rejestruj_postive_response(self):
        response = self.client.get(reverse('SOPK:rejestruj'))
        self.assertEqual(response.status_code, 200)
        self.assertTemplateUsed(response, 'SOPK/rejestruj.html')

    def test_logowanie_postive_response(self):
        response = self.client.get(reverse('SOPK:logowanie'))
        self.assertEqual(response.status_code, 200)
        self.assertTemplateUsed(response, 'SOPK/login.html')

    def test_positive_login(self):

        User.objects._create_user(username='marek', email='marek@wp.pl', password='secret',is_staff=False,
                                                                                                    is_superuser=True)
        response = self.client.post(reverse('SOPK:logowanie'), {'username': 'marek',
                                                                'password': 'secret'})
        self.assertEqual(response.status_code, 302)

    def test_positive_registration(self):
        response = self.client.post(reverse('SOPK:rejestruj'), {'username' : 'zbyszek',
                                                                'password' : 'secret',
                                                                'email' : 'zbigniew.stolarz@wp.pl',
                                                                'first_name' : 'Zbigniew',
                                                                'last_name' : 'Stolarz',
                                                                'data_urodzenia' : '12.12.1991'})
        self.assertEqual(response.status_code, 200)
        self.assertEqual(response.context['zarejestrowany'], True)

    def test_user_already_exists(self):
        response = self.client.post(reverse('SOPK:rejestruj'), {'username' : 'zbyszek',
                                                                'password' : 'secret',
                                                                'email' : 'zbigniew.stolarz@wp.pl',
                                                                'first_name' : 'Zbigniew',
                                                                'last_name' : 'Stolarz',
                                                                'data_urodzenia' : '12.12.1991'})
        self.assertEqual(response.status_code, 200)
        self.assertEqual(response.context['zarejestrowany'], True)
        response = self.client.post(reverse('SOPK:rejestruj'), {'username' : 'zbyszek',
                                                                'password' : 'secret',
                                                                'email' : 'zbigniew.stolarz@wp.pl',
                                                                'first_name' : 'Zbigniew',
                                                                'last_name' : 'Stolarz',
                                                                'data_urodzenia' : '12.12.1991'})
        self.assertEqual(response.status_code, 200)
        self.assertEqual(response.context['zarejestrowany'], False)

    def test_registration_required_filed_error(self):
         response = self.client.post(reverse('SOPK:rejestruj'), {'username' : 'zbyszek',
                                                                'email' : 'zbigniew.stolarz@wp.pl',
                                                                'first_name' : 'Zbigniew',
                                                                'last_name' : 'Stolarz',
                                                                'data_urodzenia' : '12.12.1991'})
         self.assertFormError(response, 'formularz_uzytkownika','password','To pole jest wymagane.')


    def test_registration_required_email_error(self):
         response = self.client.post(reverse('SOPK:rejestruj'), {'username' : 'zbyszek',
                                                                 'password' : 'secret',
                                                                 'email' : 'zbigniew.stolarzwp.pl',
                                                                 'first_name' : 'Zbigniew',
                                                                 'last_name' : 'Stolarz',
                                                                 'data_urodzenia' : '12.12.1991'})
         self.assertFormError(response, 'formularz_uzytkownika','email','Wprowadź poprawną nazwę użytkownika.')

class SeleniumTests(LiveServerTestCase):

    @classmethod
    def setUpClass(cls):
        cls.selenium = WebDriver()
        super(SeleniumTests, cls).setUpClass()

    @classmethod
    def tearDownClass(cls):
        cls.selenium.quit()
        super(SeleniumTests, cls).tearDownClass()

    def test_register(self):
        timeout = 2

        self.selenium.get('%s%s' % (self.live_server_url, '/rejestruj/'))
        username_input = self.selenium.find_element_by_name('username')
        username_input.send_keys("zbyszek")
        password_input = self.selenium.find_element_by_name('password')
        password_input.send_keys("secret")
        email_input = self.selenium.find_element_by_name('email')
        email_input.send_keys("zbigniew.stolarz@wp.pl")
        first_name_input = self.selenium.find_element_by_name('first_name')
        first_name_input.send_keys("Zbigniew")
        last_name_input = self.selenium.find_element_by_name('last_name')
        last_name_input.send_keys("Stolarz")
        data_urodzenia_input = self.selenium.find_element_by_name('data_urodzenia')
        data_urodzenia_input.send_keys("12.12.1991")
        self.selenium.find_element_by_xpath('//input[@value="Zarejestruj"]').click()
        WebDriverWait(self.selenium, 10).until(lambda driver : driver.find_element_by_tag_name('body'))
        label_input = self.selenium.find_element_by_partial_link_text('Powrót do strony głównej.')

    def test_register_user_already_exists(self):
        timeout = 10

        self.selenium.get('%s%s' % (self.live_server_url, '/rejestruj/'))
        username_input = self.selenium.find_element_by_name('username')
        username_input.send_keys("zbyszek")
        password_input = self.selenium.find_element_by_name('password')
        password_input.send_keys("secret")
        email_input = self.selenium.find_element_by_name('email')
        email_input.send_keys("zbigniew.stolarz@wp.pl")
        first_name_input = self.selenium.find_element_by_name('first_name')
        first_name_input.send_keys("Zbigniew")
        last_name_input = self.selenium.find_element_by_name('last_name')
        last_name_input.send_keys("Stolarz")
        data_urodzenia_input = self.selenium.find_element_by_name('data_urodzenia')
        data_urodzenia_input.send_keys("12.12.1991")
        self.selenium.find_element_by_xpath('//input[@value="Zarejestruj"]').click()
        WebDriverWait(self.selenium, 10).until(lambda driver : driver.find_element_by_tag_name('body'))
        label_input = self.selenium.find_element_by_partial_link_text('Powrót do strony')
        label_input.click()
        self.selenium.get('%s%s' % (self.live_server_url, '/rejestruj/'))
        username_input = self.selenium.find_element_by_name('username')
        username_input.send_keys("zbyszek")
        password_input = self.selenium.find_element_by_name('password')
        password_input.send_keys("secret")
        email_input = self.selenium.find_element_by_name('email')
        email_input.send_keys("zbigniew.stolarz@wp.pl")
        first_name_input = self.selenium.find_element_by_name('first_name')
        first_name_input.send_keys("Zbigniew")
        last_name_input = self.selenium.find_element_by_name('last_name')
        last_name_input.send_keys("Stolarz")
        data_urodzenia_input = self.selenium.find_element_by_name('data_urodzenia')
        data_urodzenia_input.send_keys("12.12.1991")
        self.selenium.find_element_by_xpath('//input[@value="Zarejestruj"]').click()
        WebDriverWait(self.selenium, 10).until(lambda driver : driver.find_element_by_tag_name('body'))
        button = self.selenium.find_element_by_xpath('//input[@value="Zarejestruj"]')

    def test_login_user(self):
        timeout = 2

        User.objects._create_user(username='marek', email='marek@wp.pl', password='secret',is_staff=False,
                                                                                                    is_superuser=False)
        self.selenium.get('%s%s' % (self.live_server_url, reverse('SOPK:index')))
        username_input = self.selenium.find_element_by_name('username')
        username_input.send_keys("marek")
        password_input = self.selenium.find_element_by_name('password')
        password_input.send_keys("secret")
        self.selenium.find_element_by_xpath('//button[@value="Zaloguj"]').click()
        WebDriverWait(self.selenium, 10).until(lambda driver : driver.find_element_by_tag_name('body'))
        self.selenium.find_element_by_partial_link_text('Mój profil')

    def test_login_superuser(self):
        timeout = 2

        User.objects._create_user(username='marek', email='marek@wp.pl', password='secret',is_staff=False,
                                                                                                    is_superuser=True)
        self.selenium.get('%s%s' % (self.live_server_url, reverse('SOPK:index')))
        username_input = self.selenium.find_element_by_name('username')
        username_input.send_keys("marek")
        password_input = self.selenium.find_element_by_name('password')
        password_input.send_keys("secret")
        self.selenium.find_element_by_xpath('//button[@value="Zaloguj"]').click()
        WebDriverWait(self.selenium, 10).until(lambda driver : driver.find_element_by_tag_name('body'))
        self.selenium.find_element_by_partial_link_text('Mój profil')
        self.selenium.find_element_by_partial_link_text('Admin')



    def test_failed_login(self):

        self.selenium.get('%s%s' % (self.live_server_url, reverse('SOPK:index')))
        username_input = self.selenium.find_element_by_name('username')
        username_input.send_keys("marek")
        password_input = self.selenium.find_element_by_name('password')
        password_input.send_keys("secret")
        self.selenium.find_element_by_xpath('//button[@value="Zaloguj"]').click()
        WebDriverWait(self.selenium, 10).until(lambda driver : driver.find_element_by_tag_name('body'))
        self.selenium.find_element_by_class_name("bg-danger")

    def test_logout(self):
        timeout = 2

        User.objects._create_user(username='marek', email='marek@wp.pl', password='secret',is_staff=False,
                                                                                                    is_superuser=False)
        self.selenium.get('%s%s' % (self.live_server_url, reverse('SOPK:index')))
        username_input = self.selenium.find_element_by_name('username')
        username_input.send_keys("marek")
        password_input = self.selenium.find_element_by_name('password')
        password_input.send_keys("secret")
        self.selenium.find_element_by_xpath('//button[@value="Zaloguj"]').click()
        WebDriverWait(self.selenium, 10).until(lambda driver : driver.find_element_by_tag_name('body'))
        self.selenium.find_element_by_partial_link_text('Mój profil')
        self.selenium.find_element_by_xpath('//button[@value="Wyloguj"]').click()
        WebDriverWait(self.selenium, 10).until(lambda driver : driver.find_element_by_tag_name('body'))
        self.selenium.find_element_by_xpath('//button[@value="Zaloguj"]')