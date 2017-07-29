# -*- coding: iso8859-1 -*-

# Programmeringsteknik webbkurs KTH P-Uppgift Horoskop
# Fredrik Gummus
# 2015-07-29
# Det h�r programmet tar fram ett personligt horoskop baserat p� anv�ndarens f�delsedatum samt en (slumpvald) sp�dom.
# Programmet tar fram ett f�delseindex och tar sedan fram diverse egenskaper baserat p� detta index.
# F�delseindexet beror p� anv�ndarens �ldersgrupp och hans f�delsem�nad & f�delsedag.
# Programmet kontrollerar s� att anv�ndaren anger ett korrekt f�delsedatum och tar h�nsyn till skott�r och m�nadens antal dagar.
# Om man vill l�gga till en egenskap till horoskopet s� skriver man in den i listan "Horoskop.available_properties" (man m�ste �ven ha en textfil med samma namn som egenskapen).
# Extrauppgift C&B �r gjorda.

from datetime import date, datetime #Anv�nds f�r att r�kna ut anv�ndarens �lder och lagra f�delseinformation.
from random import randrange #Anv�nds f�r att slumpa fram en sp�dom.
from os import path #Anv�nds f�r att kontrollera om en fil finns f�re den l�ses in.

#Klass som beskriver en egenskap (tex pengar) med en lista p� beskrivningar av just den egenskapen.
#   descriptions:   alla beskrivningar av denna egenskap.
class Property:
    #Konstruktor
    def __init__(self):
        self.descriptions = []

    #L�gger till en beskrivning till listan.
    def add_description(self, description):
        self.descriptions.append(description)

#Klass som inneh�ller information om anv�ndarens f�delsedatum.
#Inneh�ller dessutom funktioner relevanta f�r f�delsedatumet.
#Klassen kontrollerar att det angivna f�delsedatumet �r korrekt inskrivet p� formen "yyyy-mm-dd".
#   index:          anv�ndarens f�delseindex. Samma datum ger alltid samma index.
#   date:           anv�ndarens f�delsedatum.
class Birth_date:
    def __init__(self, birth_date):
        self.index = None
        self.date = None

        #Anropar n�dv�ndiga funktioner n�r objektet skapas.
        self.setup_dates(birth_date)
        self.check_if_date_has_occured()
        self.calculate_birth_index()

    #Tilldelar korrekta v�rden till attributen.
    def setup_dates(self, birth_date):
        #Kastar IndexError-exception om angivna datumet �r fel inskrivet.
        #Korrekt datum �r p� formen "yyy-mm-dd", kastar exception vid t.ex. "yyyy-mm".
        splitted_date = birth_date.split('-')
        year = int(splitted_date[0])
        month = int(splitted_date[1])
        day = int(splitted_date[2])

        #Kastar ValueError-exception om angivna datumet �r fel. Fel om:
        #"1 <= month <= 12"
        #"1 <= day <= number of days in the given month and year" (tar h�nsyn till m�nadens antal dagar och skott�r)
        self.date = date(year=year, month=month, day=day)

    #Kontrollerar om det angivna datumet inte har skett �n,
    #dvs om anv�ndaren matar in ett datum i  framtiden.
    def check_if_date_has_occured(self):
        current_date = datetime.now()
        if(current_date.year - self.date.year < 0 or
           current_date.year - self.date.year <= 0 and current_date.month - self.date.month <= 0 or
           current_date.year - self.date.year <= 0 and current_date.month - self.date.month <= 0 and current_date.day - self.date.day <= 0):
            raise ValueError("F�delsedatumet kan inte intr�ffa f�re dagens datum!")

    #R�knar ut personens f�delseindex baserat p� f�delsedatum.
    def calculate_birth_index(self):
        #Index �r baserat p� anv�ndarens �ldersgrupp och en modulober�kning p� f�delsem�nad & dag.
        age = Age()
        age.calculate_age(self.date.year)

        self.index = self.date.month % 6
        self.index += self.date.day % 15
        self.index += age.get_age_index()

        #DEBUG
        #print("index: ", self.index, "\n")
  
#Klass som inneh�ller attribut och funktioner f�r �lder.
#   age:            �lder
#   age_group:      �ldersgrupp
class Age:
    #Konstruktor.
    def __init__(self):
        self.age = 0
        self.age_group = Age_groups()

    #R�knar ut anv�ndarens �lder baserat p� dagens �r.
    def calculate_age(self, birth_year):
        current_date = datetime.now()
        self.age = current_date.year - birth_year

    #Returnerar �ldersgruppens index baserat p� klassens age-attribut.
    def get_age_index(self):
        return self.age_group.age_group_index(self.age)

#Klass som inneh�ller information och funktioner f�r diverse �ldersgrupper.
#   children:           �ldersgruppen barn, 0-17 �r.
#   adult:              �ldersgruppen vuxna, 18-64 �r.
#   senior:             �ldersgruppen pension�rer, 65-100 �r.
#   children_index:     index f�r barn.
#   adult_index:     index f�r vuxna.
#   senior_index:     index f�r pension�rer.
#   others_index:     index f�r �vriga.
class Age_groups:
        #Konstruktor.
        def __init__(self):
            self.children = range(0, 18)
            self.adult = range(18, 65)
            self.senior = range(65, 100)

            self.children_index = 0
            self.adult_index = 5
            self.senior_index = 10
            self.others_index = 0

        #Tar fram index f�r given �lder.
        #age:0-17   => index=0
        #age:18-64  => index=5
        #age:65-100 => index=10
        #�vrigt     => index=0
        def age_group_index(self, age):
            return (self.children_index
                    if age in self.children else self.adult_index
                    if age in self.adult else self.senior_index
                    if age in self.senior else self.others_index)

#En klass som inneh�ller allt om horoskop:
#   birth_date:             Birth-date-objekt som lagrar information och funktioner relevanta till anv�ndarens f�delsedatum.
#   properties:             en dictionary av alla m�jliga egenskaper(objekt) och dess beskrivning som l�ses in fr�n textfiler.
#   available_properties:   en lista med alla tillg�ngliga egenskaper. Om man vill l�gga till en egenskap s� skriver man in den i listan (man m�ste �ven ha en textfil med samma namn som egenskapen).
#   user_horoscope:         lista av str�ngar som inneh�ller anv�ndarens horoskop.
#   prophecy_properties:    egenskaperna f�r en sp�dom. Best�r av en egenskap och en konsekvens.
#   prophecy:               en str�ng med anv�ndarens sp�dom.
class Horoskop:
    #Konstruktor
    def __init__(self, birth_date):
        self.birth_date = Birth_date(birth_date)
        self.properties = {}
        self.available_properties = ["Money", "Love", "Health", "Luck", "Work"]
        self.prophecy_properties = ["Attributes", "Consequences"]
        self.user_horoscope = []
        self.prophecy = ""

    #Ber�knar anv�ndarens horoskop och en slumpvald sp�dom och visar det p� sk�rmen.
    def calculate_and_display(self):
        self.read_properties()
        self.get_user_horoscope()
        self.display_user_horoscope()

        self.create_prophecy()
        self.display_prophecy()

    #L�ser in alla egenskaper och sparar dom i self.properties-objekten.
    #Fyller properties-dictionaryn baserat p� alla egenskaper i "available_properties" samt "prophecy_properties".
    def read_properties(self):
        for property in self.available_properties:
            self.properties[property] = Property()
            self.read_file(property)

        for property in self.prophecy_properties:
            self.properties[property] = Property()
            self.read_file(property)
        
    #L�ser en fil och l�gger in den inl�sta beskrivningen till den egenskapen.
    def read_file(self, property):
        filename = property.lower() + ".txt"

        if(not path.isfile(filename)):
           raise FileNotFoundError("Filen " + filename + " hittades ej.")

        with open(filename, 'r', encoding="utf-8") as file:
            for line in file:
                self.properties[property].add_description(line.strip())

    #Tar fram anv�ndarens horoskop baserat p� f�delseindexet.
    def get_user_horoscope(self):
        for property in self.available_properties:
            description_count_for_property = len(self.properties[property].descriptions)
            list_index = self.birth_date.index % description_count_for_property
            user_description = self.properties[property].descriptions[list_index]
            self.user_horoscope.append(user_description)

    #Printar ut anv�ndarens horoskop.
    def display_user_horoscope(self):
        for description in self.user_horoscope:
            print(description)
    
    #Skapar en slumpm�ssig sp�dom. Slumpar fram en inl�st personlig egenskap och konsekvens
    #och s�tter ihop det till en sp�dom.
    def create_prophecy(self):
        description_count_for_attributes = len(self.properties["Attributes"].descriptions)
        description_count_for_consequences = len(self.properties["Consequences"].descriptions)

        random_attribute = self.properties["Attributes"].descriptions[randrange(0, description_count_for_attributes)]
        random_consequence = self.properties["Consequences"].descriptions[randrange(0, description_count_for_consequences)]

        self.prophecy = "Din " + random_attribute + " f�rorsakar " + random_consequence + "."
    
    #Printar ut anv�ndarens sp�dom.
    def display_prophecy(self):
        print(self.prophecy)


#Huvudprogrammet

#Huvudfunktionen som styr sj�lva programmet
def main():
    start_screen()
    done = False
    while not done:
        display_menu()
        birth_date = choose()
        
        try:
            horoskop = Horoskop(birth_date)
            horoskop.calculate_and_display()
        
        #Intr�ffar om anv�ndaren har matat in ett inkorrekt datum.
        #Tex. en dag som inte finns i den m�naden eller en m�nad som inte finns.
        except ValueError:
            display_error("Ange ett korrekt datum.")
        
        #Intr�ffar om anv�ndaren har matat in ett datum p� fel format, tex som "yyy-mm".
        except IndexError:
            display_error("Ange ett korrekt datum p� formatet �r-m�nad-dag.")

        #Intr�ffar om s�kt fil inte hittades.
        except FileNotFoundError as exception:
            display_error(exception)

        print()

#Visar en startsk�rm med v�lkomstmeddelande.
def start_screen():
    print("----------V�lkommen till Horoskop!----------")

#Visar en meny som visar anv�ndarens alternativ.
def display_menu():
    print("Ange ditt f�delsedatum f�r att se horoskop f�r just dig.")
    print("Du kan st�nga av programmet genom att skriva 'Q'.")

#Visar ett felmeddelande p� sk�rmen.
def display_error(message):
    print(message)

#L�ser och returnerar anv�ndarens alternativ.
def choose():
    choice = input("yyyy-mm-dd: ")
    if (choice == "Q" or choice == "q"):
        quit()
    return choice

main()
