# -*- coding: iso8859-1 -*-

# Programmeringsteknik webbkurs KTH P-Uppgift Horoskop
# Fredrik Gummus
# 2015-07-29
# Det här programmet tar fram ett personligt horoskop baserat på användarens födelsedatum samt en (slumpvald) spådom.
# Programmet tar fram ett födelseindex och tar sedan fram diverse egenskaper baserat på detta index.
# Födelseindexet beror på användarens åldersgrupp och hans födelsemånad & födelsedag.
# Programmet kontrollerar så att användaren anger ett korrekt födelsedatum och tar hänsyn till skottår och månadens antal dagar.
# Om man vill lägga till en egenskap till horoskopet så skriver man in den i listan "Horoskop.available_properties" (man måste även ha en textfil med samma namn som egenskapen).
# Extrauppgift C&B är gjorda.

from datetime import date, datetime #Används för att räkna ut användarens ålder och lagra födelseinformation.
from random import randrange #Används för att slumpa fram en spådom.
from os import path #Används för att kontrollera om en fil finns före den läses in.

#Klass som beskriver en egenskap (tex pengar) med en lista på beskrivningar av just den egenskapen.
#   descriptions:   alla beskrivningar av denna egenskap.
class Property:
    #Konstruktor
    def __init__(self):
        self.descriptions = []

    #Lägger till en beskrivning till listan.
    def add_description(self, description):
        self.descriptions.append(description)

#Klass som innehåller information om användarens födelsedatum.
#Innehåller dessutom funktioner relevanta för födelsedatumet.
#Klassen kontrollerar att det angivna födelsedatumet är korrekt inskrivet på formen "yyyy-mm-dd".
#   index:          användarens födelseindex. Samma datum ger alltid samma index.
#   date:           användarens födelsedatum.
class Birth_date:
    def __init__(self, birth_date):
        self.index = None
        self.date = None

        #Anropar nödvändiga funktioner när objektet skapas.
        self.setup_dates(birth_date)
        self.check_if_date_has_occured()
        self.calculate_birth_index()

    #Tilldelar korrekta värden till attributen.
    def setup_dates(self, birth_date):
        #Kastar IndexError-exception om angivna datumet är fel inskrivet.
        #Korrekt datum är på formen "yyy-mm-dd", kastar exception vid t.ex. "yyyy-mm".
        splitted_date = birth_date.split('-')
        year = int(splitted_date[0])
        month = int(splitted_date[1])
        day = int(splitted_date[2])

        #Kastar ValueError-exception om angivna datumet är fel. Fel om:
        #"1 <= month <= 12"
        #"1 <= day <= number of days in the given month and year" (tar hänsyn till månadens antal dagar och skottår)
        self.date = date(year=year, month=month, day=day)

    #Kontrollerar om det angivna datumet inte har skett än,
    #dvs om användaren matar in ett datum i  framtiden.
    def check_if_date_has_occured(self):
        current_date = datetime.now()
        if(current_date.year - self.date.year < 0 or
           current_date.year - self.date.year <= 0 and current_date.month - self.date.month <= 0 or
           current_date.year - self.date.year <= 0 and current_date.month - self.date.month <= 0 and current_date.day - self.date.day <= 0):
            raise ValueError("Födelsedatumet kan inte inträffa före dagens datum!")

    #Räknar ut personens födelseindex baserat på födelsedatum.
    def calculate_birth_index(self):
        #Index är baserat på användarens åldersgrupp och en moduloberäkning på födelsemånad & dag.
        age = Age()
        age.calculate_age(self.date.year)

        self.index = self.date.month % 6
        self.index += self.date.day % 15
        self.index += age.get_age_index()

        #DEBUG
        #print("index: ", self.index, "\n")
  
#Klass som innehåller attribut och funktioner för ålder.
#   age:            ålder
#   age_group:      åldersgrupp
class Age:
    #Konstruktor.
    def __init__(self):
        self.age = 0
        self.age_group = Age_groups()

    #Räknar ut användarens ålder baserat på dagens år.
    def calculate_age(self, birth_year):
        current_date = datetime.now()
        self.age = current_date.year - birth_year

    #Returnerar åldersgruppens index baserat på klassens age-attribut.
    def get_age_index(self):
        return self.age_group.age_group_index(self.age)

#Klass som innehåller information och funktioner för diverse åldersgrupper.
#   children:           åldersgruppen barn, 0-17 år.
#   adult:              åldersgruppen vuxna, 18-64 år.
#   senior:             åldersgruppen pensionärer, 65-100 år.
#   children_index:     index för barn.
#   adult_index:     index för vuxna.
#   senior_index:     index för pensionärer.
#   others_index:     index för övriga.
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

        #Tar fram index för given ålder.
        #age:0-17   => index=0
        #age:18-64  => index=5
        #age:65-100 => index=10
        #Övrigt     => index=0
        def age_group_index(self, age):
            return (self.children_index
                    if age in self.children else self.adult_index
                    if age in self.adult else self.senior_index
                    if age in self.senior else self.others_index)

#En klass som innehåller allt om horoskop:
#   birth_date:             Birth-date-objekt som lagrar information och funktioner relevanta till användarens födelsedatum.
#   properties:             en dictionary av alla möjliga egenskaper(objekt) och dess beskrivning som läses in från textfiler.
#   available_properties:   en lista med alla tillgängliga egenskaper. Om man vill lägga till en egenskap så skriver man in den i listan (man måste även ha en textfil med samma namn som egenskapen).
#   user_horoscope:         lista av strängar som innehåller användarens horoskop.
#   prophecy_properties:    egenskaperna för en spådom. Består av en egenskap och en konsekvens.
#   prophecy:               en sträng med användarens spådom.
class Horoskop:
    #Konstruktor
    def __init__(self, birth_date):
        self.birth_date = Birth_date(birth_date)
        self.properties = {}
        self.available_properties = ["Money", "Love", "Health", "Luck", "Work"]
        self.prophecy_properties = ["Attributes", "Consequences"]
        self.user_horoscope = []
        self.prophecy = ""

    #Beräknar användarens horoskop och en slumpvald spådom och visar det på skärmen.
    def calculate_and_display(self):
        self.read_properties()
        self.get_user_horoscope()
        self.display_user_horoscope()

        self.create_prophecy()
        self.display_prophecy()

    #Läser in alla egenskaper och sparar dom i self.properties-objekten.
    #Fyller properties-dictionaryn baserat på alla egenskaper i "available_properties" samt "prophecy_properties".
    def read_properties(self):
        for property in self.available_properties:
            self.properties[property] = Property()
            self.read_file(property)

        for property in self.prophecy_properties:
            self.properties[property] = Property()
            self.read_file(property)
        
    #Läser en fil och lägger in den inlästa beskrivningen till den egenskapen.
    def read_file(self, property):
        filename = property.lower() + ".txt"

        if(not path.isfile(filename)):
           raise FileNotFoundError("Filen " + filename + " hittades ej.")

        with open(filename, 'r', encoding="utf-8") as file:
            for line in file:
                self.properties[property].add_description(line.strip())

    #Tar fram användarens horoskop baserat på födelseindexet.
    def get_user_horoscope(self):
        for property in self.available_properties:
            description_count_for_property = len(self.properties[property].descriptions)
            list_index = self.birth_date.index % description_count_for_property
            user_description = self.properties[property].descriptions[list_index]
            self.user_horoscope.append(user_description)

    #Printar ut användarens horoskop.
    def display_user_horoscope(self):
        for description in self.user_horoscope:
            print(description)
    
    #Skapar en slumpmässig spådom. Slumpar fram en inläst personlig egenskap och konsekvens
    #och sätter ihop det till en spådom.
    def create_prophecy(self):
        description_count_for_attributes = len(self.properties["Attributes"].descriptions)
        description_count_for_consequences = len(self.properties["Consequences"].descriptions)

        random_attribute = self.properties["Attributes"].descriptions[randrange(0, description_count_for_attributes)]
        random_consequence = self.properties["Consequences"].descriptions[randrange(0, description_count_for_consequences)]

        self.prophecy = "Din " + random_attribute + " förorsakar " + random_consequence + "."
    
    #Printar ut användarens spådom.
    def display_prophecy(self):
        print(self.prophecy)


#Huvudprogrammet

#Huvudfunktionen som styr själva programmet
def main():
    start_screen()
    done = False
    while not done:
        display_menu()
        birth_date = choose()
        
        try:
            horoskop = Horoskop(birth_date)
            horoskop.calculate_and_display()
        
        #Inträffar om användaren har matat in ett inkorrekt datum.
        #Tex. en dag som inte finns i den månaden eller en månad som inte finns.
        except ValueError:
            display_error("Ange ett korrekt datum.")
        
        #Inträffar om användaren har matat in ett datum på fel format, tex som "yyy-mm".
        except IndexError:
            display_error("Ange ett korrekt datum på formatet år-månad-dag.")

        #Inträffar om sökt fil inte hittades.
        except FileNotFoundError as exception:
            display_error(exception)

        print()

#Visar en startskärm med välkomstmeddelande.
def start_screen():
    print("----------Välkommen till Horoskop!----------")

#Visar en meny som visar användarens alternativ.
def display_menu():
    print("Ange ditt födelsedatum för att se horoskop för just dig.")
    print("Du kan stänga av programmet genom att skriva 'Q'.")

#Visar ett felmeddelande på skärmen.
def display_error(message):
    print(message)

#Läser och returnerar användarens alternativ.
def choose():
    choice = input("yyyy-mm-dd: ")
    if (choice == "Q" or choice == "q"):
        quit()
    return choice

main()
