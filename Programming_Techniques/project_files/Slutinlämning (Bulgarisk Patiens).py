# Titel: Bulgarisk Patiens
# Författare: Özgun Mirtchev
# Datum: 2015-08-04
#
# Detta program låter användaren mata in egna högar eller låta programmet
# slumpa fram högar av kort för ett spel i Bulgarisk
# patiens. Programmet beräknar hur många iterationer det tar för patiensen att
# gå ut. Om det kommer in i en cykel, avbryts det och användaren återvänder
# till huvudmenyn.
#
# Om programmet körs i console så kan man se procent-progress om line 253-254
# inte är kommenterad. Detta är mestadels för att visa hur mycket det är kvar
# av iterationen ifall man har valt att framslumpa väldigt många patienser
# såsom 100 000, eller 1 000 000.
#
# Anledningen till att det inte fungerar i shell är pga att '\r' inte fungerar
# korrekt. Ett annat alternativ testades med att skriva ut punkter istället
# men i det fallet kunde man inte se hur långt det var kvar tills slutet.

from random import randint
from time import sleep
import sys


NEWLINE = '\n'

# (Fel)Meddelanden
random_msgs = ["Ange antal patienser: ",
              "Ange fler än 0 patienser. Försök igen!\n"]
user_msgs = ["Ange antal högar: ",
              "Ange fler än 0 högar. Försök igen!\n"]
print_msgs = ["Vill du se utskrifter av patienser?\n"
                " 1. Ja\n"" 2. Nej\nAnge ditt val: "]
error_msg = "Ogiltig inmatning! Försök igen!\n"
positive_int_msg = "Ange ett positivt heltal!\n"
#


# Skriver ut patiensens slutstatus
def print_out_iteration_status(state, value):
    # Se return-värden från iteration för state-värden
    if state == 1:
        print("Patiensen gick in i en cykel efter %d iterationer. " \
              "Patiensen avbryts.\n" % value )
        
    elif (state == 2):
        print("Patiensen gick ut på %d iterationer.\n" % value )

#Rekommenderar max antal kort per hög
def recommended_heap_size(heaps):
    max_cards = 52
    max_heap_size = max_cards/heaps
    print("Rekommenderad max antal kort per hög är %d.\n" \
          % max_heap_size)

    
#  ____________________________Patiens-klassen_________________________________
# Attributerna är antal högar och antal kort
#
class BulgarianSolitaire(object):

    def __init__(self):
        self.heaps = []
        self.cards = 52
          
    # Metoden ändrar högarna till nästa tillstånd
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

    
    # Inmatnings-kontroller av högar
    # För innehåll av message, se listorna längst upp
    def check_heaps_input(self, message):
        print(NEWLINE)
        while True:
            try:
                user_input = int(input(message[0]))
                if user_input > 0:
                    return int(user_input)
                else:
                    print(message[1])
            except ValueError:
                print(positive_int_msg)
                
    # Skriver ut högnummer och kontrollerar inmatning av varje hög.      
    def check_heapcards_input(self, heap_number):
        min_cards = 2
        max_cards = 52
        
        while True:
            try:
                user_input = int(input("Ange hög %d: " % (heap_number+1)))
                print(NEWLINE)
                if user_input >= min_cards and user_input <= max_cards \
                   and self.cards > 0:
                    return int(user_input)
                else:
                    print("Högen måste bestå av mellan %d-%d "\
                          "kort.\nFörsök igen!\n"\
                          % (min_cards, self.cards))
            except ValueError:
                print(positive_int_msg)


    # Metod som beräknar och om print_out = True, skriver ut högen
    # Returnerar två värden: Läget patiensen hamnade i och antal iterationer
    def iterations(self, print_out):
        
        next_heap = []
        heap_history = []
        count = 0
        
        while (True):

            # Utför iteration till nästa hög
            next_heap = self.next_stack()

            if (print_out): print(next_heap)
                
            # Cykel: Om samma hög har förekommit förut
            if(next_heap in heap_history[:-1:]):
                return 1, count
            
            # Gick ut: Om samma hög förekom i högen innan
            elif (next_heap == self.heaps):
                return 2, count

            #DEBUG
            #print(str(count+1) + ": " + str(next_heap))

            count += 1
            self.heaps = next_heap
            heap_history.append(next_heap)
    

    # Skriver ut start-meddelande för start_iteration och sorterar högen
    def starting_iteration_msg(self):
        print("Dina högar av kort består av: " + str(self.heaps) \
              + NEWLINE + "Startar iteration...\n")
        sleep(1.5)
        self.heaps.sort(reverse = True)
        print(self.heaps)
        
    # Returnerar värde för random_solitaire men skriver ut för både user
    # och random
    def start_iteration(self, print_out):

        if (print_out): self.starting_iteration_msg()
            
        # Iteration sker 
        state, value = self.iterations(print_out)

        if (print_out): print_out_iteration_status(state, value)
                
        finished_patiens = 0
        if (state == 2): finished_patiens = 1
            
        return finished_patiens
    
    # Utskrifter för antal kort kvar att fördela (Är ej nödvändigt)
    def print_remaining_cards(self, total_heaps, current_heap):
        if((current_heap+2) == total_heaps):
            print("Du har %d kort tillgängligt att fördela över %d hög."\
                  % (self.cards, (total_heaps-(current_heap+1))))
        elif(total_heaps > (current_heap+1)):
            print("Du har %d kort tillgängligt att fördela över %d högar."\
                  % (self.cards, total_heaps-(current_heap+1)))
          
    # Metoden lägger in användarens inmatade värden i klassens attributer
    def user_solitaire(self, number_of_heaps):
               
        self.heaps = []

        recommended_heap_size(number_of_heaps)

        iteration = 0     
        while(iteration < number_of_heaps):
                   
            user_heap = self.check_heapcards_input(iteration)
            
            self.cards -= user_heap
            self.print_remaining_cards(number_of_heaps, iteration)
            self.heaps.append(user_heap)
                                    
            iteration += 1
                                
        self.start_iteration(print_out = True)

        
    # Slumpar fram fem högar
    def random_heaps(self):
        
        for number in range(5):        
            random_heap = randint(0,10)
            if (random_heap > 0):
                self.heaps.append(random_heap)
    
    # Metod som generar framslumpade patienser och sedan skriver ut resultat
    # Finns möjlighet att välja utskrivning av patienser i menyn
    def random_solitaire(self, print_mode, num_of_solitaire):

        iteration = 0
        finished = 0

        print("Beräknar: ")
        
        while(iteration < num_of_solitaire):
            
            self.heaps = []
            self.random_heaps()
            
            if(print_mode):
                sleep(1)
                print(NEWLINE + "Patiens nr: %d" % (iteration+1))

            if(not print_mode):
                progress_percent(iteration, num_of_solitaire)
                
            finished += self.start_iteration(print_mode)

            iteration += 1

        finished_percent = finished/num_of_solitaire*100
        print("Klart!\n")
        sleep(1)
        print("Av %d patienser gick %d ut. (%.1f%%)\n" \
              % (num_of_solitaire, finished, finished_percent))

# Ännu en bonus-grej. Skriver ut procent-progress
# Fungerar bra i console, inte shell
# Används shell, kommentera ut line 229-230
def progress_percent(step, total):
       print ("%d%%" % (step/total*100), end="\r")

    
#Skriver ut fildata
def print_out_file_content(file):
    print(file.read())

#Läser in fil med information
def read_info_file(file_name):
    try:
        with open(file_name, 'r') as info_file:
            print_out_file_content(info_file)
    except FileNotFoundError as file_error:
        print(file_error,"\nKontrollera filnamn.\n")


# Tar inmatning för program_navigation och kontrollerar
def check_print_choice(message):
    while True:
        try:
            user_input = int(input(message[0]))
            if (user_input == 1):
                return True
            elif (user_input == 2):
                return False
            else:
                print(error_msg)
        except ValueError:
            print(error_msg)


# Återvänder till meny
def return_to_menu():
    print("Återvänder till huvudmeny\n")
    sleep(1)
    
# Väntar på att användaren trycker Enter för att fortsätta
# Mest till för att låta användaren läsa i sin egen takt
def wait_for_input():
    input("Tryck ENTER för att fortsätta...")
    print(NEWLINE)
    

# Funktion dirigerar till olika funktioner
def initiate_program(option):
    
    solitaire = BulgarianSolitaire()

    if (option == 1):
        
        user_heaps = solitaire.check_heaps_input(user_msgs)
        solitaire.user_solitaire(user_heaps)
        
    elif (option == 2):

        print_choice = check_print_choice(print_msgs)
        num_of_solitaire = solitaire.check_heaps_input(random_msgs)
        solitaire.random_solitaire(print_choice, num_of_solitaire)

    elif(option == 3):

        print(NEWLINE)
        read_info_file('solitaireinfo.txt')
    
    sleep(1)    
    wait_for_input()
    return_to_menu() #Anropar inte main, skriver enbart ut ett medd med sleep(1)

    
# Ger effekt av clear screen
def clear_screen():
    print(NEWLINE*100)

# Skriver ut meny för huvudmeny
def print_menu():
    clear_screen()
    mtitle = "huvudmeny"
    print(mtitle.upper().center(70, ' '))
    print("Välkommen till programmet Bulgarisk Patiens!\n" \
          "Välj ett av alternativen nedan:\n"
          " 1. Bestäm egna högar för ett spel\n" \
          " 2. Se statistik över framslumpade patienser\n"\
          " 3. Information om Bulgarisk Patiens\n"\
          " 0. Avsluta programmet\n")
    
# Avslutar program
def shut_down():
    print("Avslutar...")
    sleep(0.5)
    sys.exit()

# Returnerar vald meny-alternativ
def main_choice():
    while True:
        try:
            user_input = int(input("Skriv in önskad siffra: "))
            #if (user_input == 1 or user_input == 2 or user_input == 3):
            if user_input in(1,2,3):
                return user_input                
            elif (user_input == 0):
                shut_down()
            else:
                print(error_msg)
        except ValueError:
            print(error_msg)
            
# Huvudmeny
def main():
    while True:
        print_menu()
        user_choice = main_choice()
        initiate_program(user_choice)


# Initierar program
main()


    


