# Titel: Bulgarisk Patiens
# Författare: Özgun Mirtchev
# Datum: 2015-07-23
# Uppdaterad: 2015-07-29
#
# 23/7: <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
# Detta program låter användaren mata in egna högar för ett spel i Bulgarisk
# patiens. Programmet beräknar hur många iterationer det tar för patiensen att
# gå ut, om iterationer överstiger max antal iterationer för högen
# eller om det kommer in i en cykel, avbryts det och användaren återvänder till
# huvudmenyn
#
# Det ska finnas ett fel-meddelande för varje fel-inmatning användaren gör.
# Just nu finns möjlighet för användaren att skriva in en hög med storlek av
# hela kortleket (52), och det tyckte inte jag att lägga in en koll för var värt
# (Varför spela patiens om man inte tänker göra det seriöst?)
# Och därför lade jag ist in en rekommendation på hur stor varje hög bör vara.
#
# Uppdatering 29/7: <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
# I en tidigare version var funktionerna för långa, för många rader, och därför
# utfördes flera utbyten av kodrader mot funktions-anrop istället.
# Tex så anropas funktionen checkInput nu, istället för att kontrollera
# inmatning via loopar. Detta gör så att beräknings-funktionerna är
# någorlunda städade men har fortfarande samma funktion som tidigare.
#
# En funktion för navigering till korrekt funktionsanrop infördes också för
# att avlasta själva main-funktionen. Nu kan man tydligt se vilka val som leder
# till vilka funktioner.
#
# Uppdatering 31/7: <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
# iterations-funktionen hade tidigare två olika versioner, en för ren beräkning
# och en för beräkning och utskrift. Dessa två funktioner har nu kombinerats
# ihop eftersom att det bröt alldeles för mycket mot DRY och jag kunde inte
# låta det vara på det sättet. Även om funktionen är för lång (över 15 rader)
# så tycker jag att det är bättre att det är så istället för att samma identiska
# kod förekommer igen i en annan funktion. Det gör det värre än den långa
# funktion tycker jag. Huvudsaken med programmering är väl att kunna
# skriva bra kod utan att upprepa sig. Det finns givetvis vissa (eller många)
# delar som kan förbättras markant men eftersom jag ännu ej är en expert är
# det svårt att veta alla optimala sätt att skriva kod och därför kan det
# förekomma dålig kod. Jag är alltid öppen för att lära mig och jag provar
# alltid olika sätt att kunna genomföra samma funktion och byter givetvis
# till en bättre version om det passar bättre.
# 

from random import randint
import time
import sys

NEWLINE = '\n'

#
# Inmatnings-kontroll (Bryter(!) mot DRY-principen men sparar kod i andra funk.)
# except måste kombineras med sin egen try-gren, annars skulle de kunna
# kombineras till en.
# Finns möjlighet att förändra funktionen till att ha en try;expect med en
# extra parameter som tar emot en lista med strängar av felmeddelanden.
# Oklart om den förändringen är värt besväret eftersom "heapCards" try är
# inte riktigt samma som de andra två...
#
def checkInput(mode, object, i):

    while True:
#
        if mode == 'userHeaps':
            try:
                var = int(input("Ange antal högar: "))
                if var > 0:
                    return int(var)
                else:
                    print("Du måste ha fler än 0 högar. Försök igen!\n")
            except ValueError:
                print("Ange ett positivt heltal!\n")
#
        elif mode == 'heapCards':
            try:
                var = int(input("Ange hög %d: " % (i+1)))
                print(NEWLINE)
                if var >= 2 and var <= 52 and \
                    object.cards > 0 :
                    return int(var)
                else:
                    print("Högen måste bestå av mellan 2-%d "\
                          "kort.\nFörsök igen!\n"\
                          % (object.cards))
            except ValueError:
                print("Ange ett positivt heltal!\n")
#               
        elif mode == 'randomHeaps':
            try:
                var = int(input("Ange antal patienser: "))
                if var > 0:
                    return int(var)
                else:
                    print("Du måste ha mer än 0 patienser. Försök igen!\n")
            except ValueError:
                print("Ange ett positivt heltal!\n")
            

#
# Liten funktion för avslutning av en del funktioner_________________________
#
def returnMenu():
    time.sleep(2)
    print("Återvänder till huvudmeny\n")
    time.sleep(2)
    main()
    
#
# Funktion som beräknar och om printOut = True(1), skriver ut iterationer
#
def iterations(object, printOut):

    global randCount
    count = 0
    nextHeap = []
    heapHistory = []
    
    if(printOut):
        print("Dina högar av kort består av: " + str(object.heaps) \
              + NEWLINE + "Startar iteration...\n")
        time.sleep(2)
        object.heaps.sort(reverse = True)
        print(object.heaps)

    # Beräknar antal max iterationer
    maxIterations = object.calcMaxIterations()
    
    while (count < maxIterations):
        nextHeap = object.nextStack()
        if(printOut):
            print(nextHeap)
       
        # Avbryter loop direkt med break om cykel upptäcks
        # Cykel: Kollar om en hög förekommer igen över hela listan utom sista
        if(nextHeap in heapHistory[:-1:]):
            if(printOut):
                print("Patiensen gick in i en cykel efter %d " \
                      "iterationer. Patiensen avbryts.\n" % count)
            break
        
        # Avbryter om samma hög förekommer i nästa steg
        if (nextHeap == object.heaps):
            if(printOut):
                print("Patiensen gick ut på %d iterationer.\n" % count)
            randCount += 1
            break

        # Om count mer än maxIterations, gick patiensen inte ut
        elif count >= maxIterations:
            if(printOut):
                print("Patiensen gick inte ut. Max iterationer: %d \n" \
                      % maxIterations)  
            break

        # Lägger till nuvarande hög i history
        count += 1
        heapHistory.append(nextHeap)
        object.heaps = nextHeap
    
#
#  ____________________________Patiens-klassen_________________________________
# Attributerna är antal högar och antal kort
#
class bulgariskPatiens(object):

    def __init__(self, patiens, heaps):
        self.heaps = []
        self.cards = 52
        
    #    
    # Metoden ändrar högarna till nästa tillstånd______________________________
    #
    def nextStack(self):
                
        # Mäter array för en ny hög
        sizeStack = len(self.heaps)

        newCardArray= []

        # Subtraherar alla tal över 1 och lägger in i en ny array
        for heap in self.heaps:
            if heap > 1:
                heap -= 1
                newCardArray.append(heap)
            
        newCardArray.append(sizeStack)
        newCardArray.sort(reverse = True)

        return newCardArray
    
    #        
    # Metoden lägger in användarens inmatade värden i klassen attributer_______
    #
    def userPatiens(self, heaps):
               
        self.heaps = []
        i = 0

        #Rekommenderar max antal kort per hög
        maxRecCards = 52/heaps
        print("Rekommenderad max antal kort per hög är %d.\n" % maxRecCards)
                    
        while(i < heaps):
            
            #Kontroll av inmatning          
            heapCards = checkInput('heapCards', self, i)
                                    
            # Minskar antal kort i patiens-leken 
            self.cards -= heapCards
                                    
            # Utskrifter för antal kort att fördela (Är ej nödvändigt)
            if((i+2) == heaps):
                print("Du har %d kort tillgängligt att fördela över %d hög."\
                      % (self.cards, (heaps-(i+1))))
            elif(heaps > (i+1)):
                print("Du har %d kort tillgängligt att fördela över %d högar."\
                      % (self.cards, heaps-(i+1)))
                                        
            # Lägger till vald hög-storlek i listan
            self.heaps.append(heapCards)
                                    
            i+=1
                                
        iterations(self, 1)
        returnMenu()
    
    #
    # Funktion som generar framslumpade patienser och sedan skriver ut resultat
    # Finns möjlighet att välja utskrivning av patienser i menyn
    # printMode = 1: Skriver ut, printMode = 0: Skriver EJ ut
    #
    def randomPatiens(self, printMode, nPatiens):
        
        print("Beräknar...\n")
        j = 0

        # Lagrar en patiens i taget i temp-lista 
        while(j < nPatiens):
            self.heaps = []

            # Fem högar per patiens enligt instruktioner
            for number in range(5):        
                randVal = randint(0,10)
                # Tal läggs bara till om det är > 0
                if(randVal > 0):
                    self.heaps.append(randVal)
                            
            # Kollar vilken printmode det är i och genomför iterationer
            if(printMode):
                time.sleep(2)
                print("Patiens Nr: %d" % (j+1))
                iterations(self,1)
            else:
                iterations(self,0)

            j += 1
                    
        time.sleep(1)
        print("Av " + str(nPatiens) + \
              " patienser gick " + str(randCount) + " ut.\n")

        returnMenu()

    # Beräknar max antal iterationer för patiensen________________________
    def calcMaxIterations(self):
            
        maxValue = max(self.heaps)
        return maxValue*maxValue - maxValue


#
# Funktion dirigerar till olika funktioner för att avlasta main()______________
#
def programNav(option):

    # Global inkrementation av iteration-beräkning för alla nedanstående
    # funktioner 
    global randCount
    randCount = 0

    if option == 1:
        
        # Skapas en ny patiens-klass för varje menyval med nollvärden
        BP1 = bulgariskPatiens(0,0)
        
        userHeaps = checkInput('userHeaps', BP1,0)
        BP1.userPatiens(userHeaps)
        
    elif option == 2:
        printChoice = input("Vill du se utskrifter av patienser?\n" \
                                " 1. Ja\n 2. Nej\nDitt val: ")
        print(NEWLINE)
            
        while(True):
        
            BP2 = bulgariskPatiens(0,0)
                        
            # 1: Skriver ut, 0: Skriver ej ut
            if(printChoice == '1'):
                nPatiens = checkInput('randomHeaps', BP2, 0)
                BP2.randomPatiens(1, nPatiens)
            elif(printChoice == '2'):
                nPatiens = checkInput('randomHeaps', BP2, 0)
                BP2.randomPatiens(0, nPatiens)
            else:
                print("Ogiltig inmatning! Försök igen!\n")
                time.sleep(1)
                printChoice = input("Vill du se utskrifter av patienser?\n"\
                                    " 1. Ja\n"" 2. Nej\nDitt val: ")
                print(NEWLINE)


                
# ________________________________Huvudmeny____________________________________
def main():
    
    mtitle = "huvudmeny"
    print(mtitle.upper().center(70, ' '))
    print("Bulgarisk Patiens\n" \
          "Välj ett av alternativen nedan:\n 1. Bestäm egna högar\n" \
          " 2. Se statistik över slumpade patienser\n 0. Avsluta programmet\n")
    choice = input("Skriv in önskad siffra: ")
    print(NEWLINE)
    
    while(choice != '0'):
        
        if (choice == '1'):
            programNav(1)
                      
        elif (choice == '2'):
            programNav(2)
   
        else:
            print("Ogiltig inmatning! Försök igen!\n")
            choice = input("Skriv in ditt val: ")
            
    print("Avslutar...")
    time.sleep(1)
    sys.exit()


# Initierar program
main()
