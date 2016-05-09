# Titel: Bulgarisk Patiens
# Författare: Özgun Mirtchev
# Datum: 2015-07-23
#
# Detta program låter användaren mata in egna högar för ett spel i Bulgarisk
# patiens. Programmet beräknar hur många iterationer det tar för patiensen att
# gå ut, om iterationer överstiger max antal iterationer för högen
# eller om det kommer in i en cykel, avbryts det och användaren återvänder till
# huvudmenyn
#
# Klasser används inte i detta fall eftersom det inte behövs...
# Hade kortens färg och värde spelat roll skulle klasser kunna användas.
# Men i detta fall används bara korten som nummer


from random import randint
import time
import sys

NEWLINE = '\n'


# Funktionen ändrar högarna till nästa tillstånd____________________________
def nextStack(cardArray):
    
    # Denna lades in för val 3 i menyn, annars behövs den inte
    # Om de förbestämda högarna i val 3 har nollor i sig dvs.
    for i in cardArray:
        if i == 0:
            cardArray.remove(i)
            
    # Mäter array för en ny hög
    sizeStack = len(cardArray)

    newCardArray= []
        
    for i in cardArray:
        if i > 1:
            i -= 1
            newCardArray.append(i)
        
    newCardArray.append(sizeStack)
    newCardArray.sort(reverse = True)

    return newCardArray


# Liten funktion för avslutning av en del funktioner_________________________
def returnMenu():
    time.sleep(2)
    print("Återvänder till huvudmeny\n")
    time.sleep(2)
    main()


# Funktion som beräknar och/eller skriver ut iterationer_____________________
def iterate(currentHeap, mode):

    global randCount
    count = 0
    nextHeap = []
    cardHistory = []

    if(mode == 'user' or mode == 'randprint'):
        time.sleep(2)
        print("Dina högar av kort består av: " + str(currentHeap))
        print("Startar iteration om", end="")

        #Skriver ut punkter för effekt..
        for i in range(3):
            print(" " + str (3-i), end="")
            time.sleep(0.8)
        print(".\n")
        
        currentHeap.sort(reverse = True)
        print(currentHeap)

    # Antal max iterationer det får förekomma 
    maxValue = max(currentHeap)
                    #(k*k -k där k = största talet i högen)
    maxIterations = maxValue*maxValue - maxValue
    
    while (count < maxIterations):
        nextHeap = nextStack(currentHeap)
        
        if(mode == 'user' or mode == 'randprint'):
            print(nextHeap)
            
        # Avbryter loop direkt med break om cykel upptäcks
        # Cykel: Kollar om en hög förekommer igen över hela listan utom sista
        if(nextHeap in cardHistory[:-1:]):
            if(mode == 'user' or mode == 'randprint'):
                print("Patiensen gick in i en cykel efter %d " \
                      "iterationer. Patiensen avbryts.\n" % count)
            break
        
        # Avbryter om samma hög förekommer i nästa steg
        if (nextHeap == currentHeap):
            if(mode == 'user' or mode == 'randprint'):
                print("Patiensen gick ut på %d iterationer.\n" % count)
            randCount += 1
            break

        # Om count mer än maxIterations, gick patiensen inte ut
        elif count >= maxIterations:
            if(mode == 'user' or mode == 'randprint'):
                print("Patiensen gick inte ut. Max iterationer: %d \n" % x)
            break

        # Lägger till nuvarande hög i history
        count += 1
        cardHistory.append(nextHeap)
        currentHeap = nextHeap

    if(mode == 'user'):
        returnMenu()

        
# Funktion som generar framslumpade patienser och sedan skriver ut resultat__
# Finns möjlighet att välja utskrivning av patienser i menyn
def randomPatiens(printMode):
    
    # Global så att inkrementation även sker i en annan funktion
    global randCount
    randCount = 0
    randomCardsList = []
 
    nPatiens = input("Ange antal patienser: ")
    print(NEWLINE)
    
    while(True):
        
        # Kollar om input-type är av int, annars except
        # (Försökte för övrigt göra en funktion av denna men funkade inte bra)
        try:
            nPatiens = int(nPatiens)
        except ValueError:
            print("Ange ett heltal!\n")
            nPatiens = input("Ange antal patienser: ")
            print(NEWLINE)

        # Kollar om nPatiens-typ är av int, annars återvänder det till try
        if(type(nPatiens) is int):
            
            if(nPatiens > 0):
                j = 0

                # Lagrar en patiens i taget i temp-lista 
                while(j < nPatiens):
                    tempList = []

                    # Fem högar per patiens enligt instruktioner
                    for i in range(5):        
                        randVal = randint(0,10)
                        # Tal läggs bara till om det är > 0
                        if(randVal > 0):
                            tempList.append(randVal)
                            
                    # Lägger temp-lista i random-lista
                    randomCardsList.append(tempList)
                    j += 1

                # Kollar vilken printmode det är i och genomför iterationer
                for i in range(len(randomCardsList)):
                    if(printMode == 1):
                        time.sleep(2)
                        print("Patiens Nr: %d" % (i+1))
                        iterate(randomCardsList[i], 'randprint')
                    elif(printMode == 0):
                        iterate(randomCardsList[i], '')

                print("Av " + str(len(randomCardsList)) + \
                      " patienser gick " + str(randCount) + " ut.\n")
                
                break # Break ur while när klar
            
            else:
                print("Du måste ha mer än 0 patienser. Försök igen!\n")
                nPatiens = input("Ange antal patienser: ")
                print(NEWLINE)

    returnMenu()
    
    
# Funktion för användarinmatning ____________________________________________
def userStack():
    cards = 52
    userCards = []
    
    stacks = input("Ange antal högar: ")
    print(NEWLINE)

    i = 0
    
    while(True):

        try:
            stacks = int(stacks)
        except ValueError:
            print("Ange ett positivt heltal!\n")
            stacks = input("Ange antal högar: ")
            print(NEWLINE)

        if(type(stacks) is int):
        
            if(stacks > 0):
                
                while(i < stacks):
                    
                    nCards = int(input("Ange hög %d: " % (i+1)))
                    print(NEWLINE)
                    # TODO: Lägga in kontroll av input
                    
                    if (nCards >= 2 and nCards <= 52):
                        userCards.append(nCards)
                        cards -= nCards
                        
                        #Skriver ut ett annat medd om 1 hög kvar
                        if((i+2) == stacks):
                            print("Du har %d kort tillgängligt att fördela " \
                                  "över %d hög\n"\
                                  % (cards, (stacks-(i+1))))
                        elif(stacks > (i+2)):
                            print("Du har %d kort tillgängligt att fördela " \
                                  "över %d högar\n" % (cards, stacks-(i+1)))                    
                        i+=1
                        
                    else:
                        print("Högen får bestå av mellan 2-%d kort.\n" \
                              "Försök igen!" % (cards-(i)))
                        
                break #break ur while(true)

            #Felmeddelande om inmatning inte är > 0.
            else:
                print("Du måste ha mer än 0 högar. Försök igen!\n")
                stacks = input("Ange antal högar: ")
                print(NEWLINE)
                
    return userCards


# Huvudmeny__________________________________________________________________
def main():
    
    mtitle = "huvudmeny"
    print(mtitle.upper().center(70, ' '))
    print("Bulgarisk Patiens\n" \
          "Välj ett av alternativen nedan:\n", \
          "1. Bestäm egna högar\n", \
          "2. Se statistik över slumpade patienser\n", \
          "3. Se resultat av egna högar (Läggs in i preHeaps i koden)\n", \
          "0. Avsluta programmet\n")
    choice = input("Skriv in önskad siffra: ")
    print(NEWLINE)
    
    while(choice != '0'):
        
        if (choice == '1'):
            global randCount
            randCount = 0
    
            userCards = userStack()
            iterate(userCards, 'user')
                      
        elif (choice == '2'):
            printChoice = input("Vill du se utskrifter av patienser?\n" \
                                    "1. Ja\n" \
                                    "2. Nej\n" \
                                    "Ditt val: ")
            print(NEWLINE)            
            
            while(True):
                if(printChoice == '1'):
                    randomPatiens(1)
                elif(printChoice == '2'):
                    randomPatiens(0)
                else:
                    print("Försök igen!\n")
                    time.sleep(1)
                    printChoice = input("Vill du se utskrifter av"\
                                            " patienser?\n 1. Ja\n 2. Nej\n" \
                                            "Ditt val:")
                    print(NEWLINE)
                    
        # Denna val är mest tänkt för om ni vill testa koden med egna
        # förbestämda högar utan att behöva skriva in det genom programmet
        elif (choice == '3'):
            
            randCount = 0

            # Lägg in dina egna högar i denna lista
            preHeaps = [[2,3,6,5,5,6]]

            #Ändra andra parametern i iterate:
            # För utskrifter av iterationer till: 'randprint'
            # För inga utskrifter: '' (Eller vadsomhelst förutom 'user' & ovan)
            for i in preHeaps:
                iterate(i, 'randprint')
                
            print("Av " + str(len(preHeaps)) + \
                    " patienser gick " + str(randCount) + " ut.\n")
            
            returnMenu()
            
        else:
            print("Ogiltig inmatning! Försök igen!\n")
            choice = input("Skriv in ditt val: ")
            
    print("Avslutar...")
    time.sleep(1)
    sys.exit()

    
main()
        
