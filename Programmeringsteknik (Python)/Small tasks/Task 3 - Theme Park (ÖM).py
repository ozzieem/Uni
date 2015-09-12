#   Programmeringsteknik webbkurs KTH inlämningsuppgift 1.
#   Özgun Mirtchev
#   2015-06-18
#   Åk din valda attraktion med denna primitiva program.

#   Använder förmodligen för många time.sleep() men de gör det lite roligare...

import sys
import time
from random import randint

#   Super klass
class attraktion(object):
    
    def __init__(self, name, minimalHeight, gravForce, sound, info):
        self.name = name
        self.minimalHeight = minimalHeight
        self.gravForce = gravForce
        self.status = 5
        self.sound = sound
        self.info = info

    def __str__(self):
        return "Accelerationskraft : " + str(self.gravForce) + "G\n"\
               "Minimilängd: " + str(self.minimalHeight) + "cm " + \
               "(Du:" + str(userHeight) + ")\n" \
               "Status: " + str(self.status) + "\n\n" + \
                self.info + "\n"

    def start(self):
        print("Attraktionen startar", end="")
        for i in range(3):
            print(".", end="")
            time.sleep(0.5)
        print("\n")
        for i in self.sound:
            print(i)
            time.sleep(1)
        print("\nÅkturen är slut!\n")
        if(self == tempel):
            self.status -= 4
        else:
            self.status -= 2
        time.sleep(1)

    def haveri(self):
        print("*KLUNK!*")
        time.sleep(1)
        print("*POOF!*")
        time.sleep(1)
        print("Ingen fara, attraktionen har gått sönder!\n" \
              "Mekaniker är på väg, kom tillbaka senare!\n")
        time.sleep(2)
        main(0)

#   Objektmeny
def objectMenu(height, object):

    printMenu("object", object)
    choice = input("Ange val: ")
    print("\n")
    
    while(True):
        
        if choice == '1':
            print(object)
            time.sleep(4)
            printMenu("object", object)
            choice = input("Ange val: ")
            print("\n")
            
        #   Haveri 25% chans
        elif choice == '2':
            haveri = randint(0,3)
            
            if haveri == 0:
                object.haveri()
                
            elif object.status <= 0:
                print("Attraktionen är sönder men en mekaniker är tillkallad\n" \
                      "Kom gärna tillbaka senare!\n")
                object.status = 5
                time.sleep(2)
                main(0)

            #   Kollar längdgränsen med användarens height och startar
            else:
                if height >= object.minimalHeight:
                    object.start()                    
                else:
                    print("Du är för kort för att åka denna attraktion! \n" \
                          "Minimilängd är %d cm.\n" \
                          "Din längd är %d cm..\n" % \
                          (object.minimalHeight, userHeight))
                    
                    time.sleep(2)

                printMenu("object", object)
                choice = input("Ange val: ")
                print("\n")
                
        elif choice == '3':
            main(0)

        else:
            print("Ogiltig inmatning! Försök igen!\n")
            choice = input("Ange val: ")
            print("\n")
#End (objectMenu)


def printMenu(type, object):
    
    if type == "object":
        print("Välkommen till " + object.name + "!\n" + \
              " 1. Visa information\n" + \
              " 2. Åk attraktion\n" + \
              " 3. Återvänd till huvudmenyn\n")
        
    elif type == "main":
        print("Hej och välkommen till Urtidslandet!\n" \
              "Välj vilken attraktion du vill åka med:\n" \
              " 1. Dino Kart\n" \
              " 2. Maya Snurran\n" \
              " 3. Det Förskräcktas Tempel\n" \
              " 4. Ange längd igen\n" \
              " 5. Lämna parken\n")
    else:
        pass
    
#End (printMenu)


#   Huvudmeny
def main(mode):

    if(mode == "height"):
        global userHeight
        userHeight = int(input("Ange din längd i cm: "))
        print("\n")
        
        while(userHeight < 110 or userHeight > 210):
            if userHeight < 110:
                print("Du är för kort för att åka några attraktioner.\n" \
                      "Försök igen!\n")
            else:
                print("Gärna en rimlig längd ;)\n")
                
            userHeight = int(input("Ange din längd i cm: "))
            print("\n")
    else:
        pass
        
    printMenu("main", object)
    choice = input("Skriv in ditt val: ")
    print("\n")
    
    while(True):
        
        if (choice == '1'):
            objectMenu(userHeight, dinoKart)
            
        elif (choice == '2'):
            objectMenu(userHeight, mayaSnurran)
            
        elif (choice == '3'):
            objectMenu(userHeight, tempel)
            
        elif (choice == '4'):
            main("height")
            
        elif (choice == '5'):
            print("Tack och välkommen åter!")
            time.sleep(1)
            sys.exit()
            
        else:
            print("Ogiltig inmatning! Försök igen!\n")
            choice = input("Skriv in ditt val: ")
#End (main)


#   Attraktionsreklam
dinoRek = "Upplev känslan av att köra fort genom djungelns träd " \
              "med höga hopp och tävla mot andra!\n"
mayaRek = "Känn centrifugalkraften dra dig ut mot kanten av plattan" \
              " samtidigt som den roterar upp och ner och ger en gungande" \
              " upplevelse. Kan du hålla dig fast? ;)\n"
tempelRek = "Vågar du åka den läskigaste berg-och-dalbanan? \n" \
              "Dras med i svängarna och de skarpa kurvorna genom djungeln!\n"

#   Attraktionsljud
dinoSound = ['Vroom Vroom..!', 'Swooosh!', 'Crash!', 'Hahaha!']
mayaSound = ['Weeeee!', 'Whooaaa!', 'Hahahah!', 'Oj, jag mår illa...']
tempelSound = ["Hahah!", "WAAAAAHH!", "YAY!", "Whew!"]

#   Attraktionsklasser
dinoKart = attraktion("Dinokart", 130, 1.5, dinoSound, dinoRek)
mayaSnurran = attraktion("Mayasnurran", 110, 3, mayaSound, mayaRek)
tempel = attraktion("Det Förskräcktas Tempel", 150, 4, tempelSound, tempelRek)


#   Initiering
main("height")
