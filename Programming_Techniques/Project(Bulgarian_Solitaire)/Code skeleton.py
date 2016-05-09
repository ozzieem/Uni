#Titel: Bulgarisk Patiens
#Författare: Özgun Mirtchev
#Datum: 2015-07-23
#
#Detta program låter användaren mata in egna högar för ett spel i Bulgarisk
#patiens. Programmet beräknar hur många iterationer det tar för patiensen att
#gå ut, om det tog mer än 25 iterationer eller kommer in i en cykel, avbryts det

#Klasser används inte i detta fall eftersom det inte behövs...
#Hade kortens färg och värde spelat roll skulle klasser kunna användas.
#Men i detta fall används bara korten som nummer

# Funktion för att låta användaren själv bestämma högar
def initialStack():

    #Fråga användare om antal högar

    #Loopa igenom så många högar
        #Fråga om storlek på hög
            #If - Kollar om storleken på högen är mellan 2-52
                #If true, läggs högen till i en lista
                #else skrivs felmeddelande ut \
                #Användaren får skriva om högen igen
                
    return cardList


# Funktion för att köra en omgång av patiensen
# En lista med högar tas in och ut kommer en ny lista med högar
def nextStack(cardArray):

    # Storlek på cardArray

    #Skapa nyArray och lägg till från cardArray men med varje värde -1
    #Lägg till storlek på cardArray i nyArray

    #Sortera nyArray
    
    return newcardArray



# Funktion som kör igenom iterationer med inmatade lista med högar
# Räknar ut iterationer
# Kollar även om samma hög har förekommit innan, = cykel
# Kollar om det tar mer än 25 iterationer, 
def patiensIterations(currentHeap):

    # Första returnerade värdet från nextStack lagras i en variabel firstValue
    # Alla iterationer lagras i en lista för att kolla om en cykel uppstått

    # Loop som skriver ut varje iteration
        #Lägger till iteration i history-listan
        #Ny iteration av förra hög
    
        #If - Kollar om förra hög == Ny hög
            print("Patiensen gick ut med count iterationer")
            break  

        #If - Kollar om det är en cykel
            print("Patiens i cykel")
            break
        #If - Kollar om count >= 25
            print("Patiens ej ut")
            break
        
    #Återvänder till meny när patiens avslutad

        
#Huvudprogram
#En enkel meny där man kan välja om man vill lägga in högar själv eller se ex
def main():

# choice = användaren matar in val

#1. Bestäm egna högar
    #Initialstack() till var för att ange egna högar
    #Därefter patiensIteration(var) för beräkning
#2. Se exempel av redan bestämda högar
    #En som går ut, en som inte går ut, en som hamnar i en cykel.
#0. avsluta

#Givetvis kollas korrekt inmatning och sånt också











    
    
