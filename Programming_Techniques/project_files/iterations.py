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
# Tex så anropas funktionen check_input nu, istället för att kontrollera
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
# kod förekommer igen i en annan funktion.
#
#Uppdatering 3/8:
# check-funktionen har delats upp.
# Alla variabler har bytt namn så att det passar namnkonventionen för Python.
# iterations-funktionen har genomgått en smärre förändring. Den huvudsakliga
# funktionen har gjorts om till en metod inom klassen BulgariskPatiens.
# En annan funktion skriver ut och genomför iterationen


from random import randint
import time
import sys



NEWLINE = '\n'

# (Fel)Meddelanden för check_heaps_input
randomheaps_lines = ["Ange antal patienser: ",
                   "Du måste ha mer än 0 patienser. Försök igen!\n"]
userheaps_lines = ["Ange antal högar: ",
                   "Du måste ha fler än 0 högar. Försök igen!\n"]                   

# För innehåll av message, se listorna längst upp
def check_heaps_input(object, message):
    while True:
        try:
            var = int(input(message[0]))
            if var > 0:
                return int(var)
            else:
                print(message[1])
        except ValueError:
            print("Ange ett positivt heltal!\n")
            

# Inmatnings-kontroll av högar
def check_heapcards_input(object, i):
    while True:
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

            
def return_to_menu():
    time.sleep(2)
    print("Återvänder till huvudmeny\n")
    time.sleep(2)
    main()
    
# Returnerar värden för random_patiens
def start_iteration(object, print_out):

    finished_patiens = 0
    state = 0
    value = 0

    if(print_out):
        print("Dina högar av kort består av: " + str(object.heaps) \
              + NEWLINE + "Startar iteration...\n")
        time.sleep(2)
        object.heaps.sort(reverse = True)
        print(object.heaps)

    state = object.iterations(print_out)

    if (print_out):
        # Se return-värden från iteration för state-värden
        if state == 1:
            print("Patiensen gick in i en cykel efter %d iterationer. " \
                  "Patiensen avbryts.\n" )
            
        elif state == 2:
            print("Patiensen gick ut på %d iterationer.\n" )
            
        elif state == 3:
            print("Patiensen gick inte ut. Max iterationer: %d \n" \
                  )
    if state == 2:
        finished_patiens += 1
        
    return finished_patiens
    

    
#
#  ____________________________Patiens-klassen_________________________________
# Attributerna är antal högar och antal kort
#
class BulgariskPatiens(object):

    def __init__(self, patiens, heaps):
        self.heaps = []
        self.cards = 52
        
    #    
    # Metoden ändrar högarna till nästa tillstånd______________________________
    #
    def next_stack(self):

        new_heap = []
                
        size_stack = len(self.heaps)
        
        # Subtraherar alla tal över 1 och lägger in dem i  en ny array
        for heap in self.heaps:
            if heap > 1:
                heap -= 1
                new_heap.append(heap)
            
        new_heap.append(size_stack)
        new_heap.sort(reverse = True)

        return new_heap

    #
    # Metod som beräknar och om print_out = True(1), skriver ut högar
    # Returnerar två värden: Läget patiensen hamnade i och count
    #
    def iterations(self, print_out):

        count = 0
        next_heap = []
        heap_history = []

        # Beräknar antal max iterationer
        max_iterations = self.calc_max_iterations()
        
        while (count < max_iterations):
            next_heap = self.next_stack()
            if print_out:
                print(next_heap)

            if(next_heap in heap_history[:-1:]):
                return 1, count

            elif (next_heap == self.heaps):
                return 2, count

            count += 1
            self.heaps = next_heap
            heap_history.append(next_heap)
            
        return 3, max_iterations
        
    #        
    # Metoden lägger in användarens inmatade värden i klassen attributer_______
    #
    def user_patiens(self, heaps):
               
        self.heaps = []
        i = 0

        #Rekommenderar max antal kort per hög
        max_recommended_cards = 52/heaps
        print("Rekommenderad max antal kort per hög är %d.\n" \
              % max_recommended_cards)
                    
        while(i < heaps):
                   
            heap_cards = check_heapcards_input(self,i)
                                    
            # Minskar antal kort i patiens-leken
            self.cards -= heap_cards
                                    
            # Utskrifter för antal kort att fördela (Är ej nödvändigt)
            if((i+2) == heaps):
                print("Du har %d kort tillgängligt att fördela över %d hög."\
                      % (self.cards, (heaps-(i+1))))
            elif(heaps > (i+1)):
                print("Du har %d kort tillgängligt att fördela över %d högar."\
                      % (self.cards, heaps-(i+1)))
                                        
            # Lägger till vald hög-storlek i listan
            self.heaps.append(heap_cards)
                                    
            i+=1
                                
        start_iteration(self, 1)
        return_to_menu()
    
    #
    # Funktion som generar framslumpade patienser och sedan skriver ut resultat
    # Finns möjlighet att välja utskrivning av patienser i menyn
    # print_mode = 1: Skriver ut, print_mode = 0: Skriver EJ ut
    #
    def random_patiens(self, print_mode, num_of_patiens):

        j = 0
        rand_count = 0
        print("Beräknar...\n")

        while(j < num_of_patiens):
            self.heaps = []

            # Fem högar per patiens enligt instruktioner
            for number in range(5):        
                randVal = randint(0,10)
                # Tal läggs bara till om det är > 0
                if(randVal > 0):
                    self.heaps.append(randVal)

            if(print_mode):
                time.sleep(2)
                print("Patiens Nr: %d" % (j+1))
                rand_count += start_iteration(self,1)
            else:
                rand_count += start_iteration(self,0)

            j += 1
                    
        time.sleep(1)
        print("Av %d patienser gick %d ut.\n" \
              % (num_of_patiens, rand_count))

        return_to_menu()

    # Beräknar max antal iterationer för patiensen
    # max() används inte eftersom att det orsakade instabilitet vid höga värden
    def calc_max_iterations(self):

        max_value = 0
        for numb in self.heaps:
            if numb > max_value:
                max_value = numb
                
        return max_value * max_value - max_value


#
# Funktion dirigerar till olika funktioner för att avlasta main()______________
#
def program_navigation(option):

    if option == 1:
        
        # Skapas en ny patiens-klass för varje menyval med nollvärden
        user_class = BulgariskPatiens(0,0)
        
        user_heaps = check_heaps_input(user_class, userheaps_lines)
        user_class.user_patiens(user_heaps)
        
    elif option == 2:
        print_choice = input("Vill du se utskrifter av patienser?\n" \
                                " 1. Ja\n 2. Nej\nDitt val: ")
        print(NEWLINE)
                    
        while(True):

            random_class = BulgariskPatiens(0,0)
            
            # 1: Skriver ut, 0: Skriver ej ut
            if(print_choice == '1'):
                num_of_patiens = check_heaps_input(random_class,
                                                   randomheaps_lines)
                random_class.random_patiens(1, num_of_patiens)
                
            elif(print_choice == '2'):
                num_of_patiens = check_heaps_input(random_class,
                                                   randomheaps_lines)
                random_class.random_patiens(0, num_of_patiens)
                
            else:
                print("Ogiltig inmatning! Försök igen!\n")
                time.sleep(1)
                print_choice = input("Vill du se utskrifter av patienser?\n"\
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
            program_navigation(1)
                      
        elif (choice == '2'):
            program_navigation(2)
   
        else:
            print("Ogiltig inmatning! Försök igen!\n")
            choice = input("Skriv in ditt val: ")
            
    print("Avslutar...")
    time.sleep(1)
    sys.exit()

# Initierar program
main()



        
        
        

    

    

###### VERSION AV ITERATIONS INNAN DEN 3/8 -2015 ###############

#
# Funktion som beräknar och om print_out = True(1), skriver ut iterationer
#
def iterations(object, print_out):

    count = 0
    rand_count = 0
    next_heap = []
    heap_history = []
    
    if(print_out):
        print("Dina högar av kort består av: " + str(object.heaps) \
              + NEWLINE + "Startar iteration...\n")
        time.sleep(2)
        object.heaps.sort(reverse = True)
        print(object.heaps)

    # Beräknar antal max iterationer
    max_iterations = object.calc_max_iterations()
    
    while (count < max_iterations):
        next_heap = object.next_stack()
        if(print_out):
            print(next_heap)
       
        # Avbryter loop direkt med break om cykel upptäcks
        # Cykel: Kollar om en hög förekommer igen över hela listan utom sista
        if(next_heap in heap_history[:-1:]):
            if(print_out):
                print("Patiensen gick in i en cykel efter %d " \
                      "iterationer. Patiensen avbryts.\n" % count)
            break
        
        # Avbryter om samma hög förekommer i nästa steg
        if (next_heap == object.heaps):
            rand_count += 1
            if(print_out):
                print("Patiensen gick ut på %d iterationer.\n" % count)
            break

        # Om count mer än max_iterations, gick patiensen inte ut
        elif count >= max_iterations:
            if(print_out):
                print("Patiensen gick inte ut. Max iterationer: %d \n" \
                      % max_iterations)
            break

        # Lägger till nuvarande hög i history
        count += 1
        heap_history.append(next_heap)
        object.heaps = next_heap

    return rand_count



