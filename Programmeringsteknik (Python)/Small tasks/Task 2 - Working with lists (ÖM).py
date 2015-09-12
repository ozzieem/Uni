#Programmeringsteknik webbkurs KTH inlämningsuppgift 1.
#Özgun Mirtchev
#2015-06-18
#Programmet erbjuder användaren att se exempel på en rondelet
#Eller att skapa en egen rondelet
#Just nu finns ingen fel-checker för ogiltig inmatning för meningar
#Vilket innebär att användaren kan göra dikter med siffror och symboler...


import sys
import time

#Skapa en egen rondelet, se print_out mode = 1
def egen_rondelet():
    
    user_sentence = []
    
    print_out(user_sentence,1)   #print_out(array, mode)
    time.sleep(3)
    
    main()
    

#Exemplet från hemsidan
def example():
    
    example_sentence =[
            "Det fanns ingen fil när jag handlade på Konsum.",
            "Bananerna var också slut.",
            "Jag köpte bröd istället.",
            "Nån sorts limpa med mycket fibrer."
            ]
    
    print_out(example_sentence, 2)

    time.sleep(3)

    main()
        
        
#Gör om en array till 4 ord om in_put = 1
#Skriver annars ut resten av array/mening
def fourWords(array, mode):   
    
    tempSentence = array.split()
    newSentence = []
    
    if (mode == 1):
        newSentence = tempSentence[0:4]
    else:
        newSentence = tempSentence[4::]
        
    newSentence = " ".join(newSentence)
    
    return newSentence


#En liten funktion för utskrivning av linjer för tydlighet
def visible_line(sym, num):
    for i in range(num):
        print(sym, end="")
    print("\n")
    

#Skriver ut resultatet beroende på vilket mode det är i, utan return
#Detta för att undvika extra kod i de andra funktionerna
def print_out(array, mode):

    print("\n")

    visible_line("_",70)
    
    title = "Diktautomaten"
    print(title.upper().center(70, ' ')+ "\n")

    print("Skriv in fyra meningar och få ut en rondelet!\n")

    i = 0
    
    while(i < 4):
        
        if (mode == 1): #Lägger till inskrivna meningar i en lista
            tempArray = input("Skriv mening nr " + str(i+1) +":")
            
            if (tempArray.isdigit() or tempArray == " " or tempArray == ""):
                print("Skriv in en mening!!\n")
            else:
                array.append(tempArray)
                i += 1
        else:
            print("Skriv mening nr " + str(i+1) + ": " + array[i])
            i += 1

    print("\n\n")

    firstSentencePart = fourWords(array[0],1)
                           
    print(firstSentencePart.upper()+"\n" + \
          firstSentencePart+"\n" + \
          fourWords(array[0],2)+"\n" + \
          firstSentencePart+"\n")
    
    for i in range(3):      #Sparar på print-funktioner..
        print(array[i+1])

    print(firstSentencePart + "\n")

    visible_line("_",70)
    

#Menyn
def main():
    mtitle = "huvudmeny"
    print(mtitle.upper().center(70, ' '))
    print("Välj ett av alternativen nedan:\n", \
          "1. Ange egna meningar för en rondelet\n", \
          "2. Se inlämningsuppgiftens exempel\n", \
          "0. Avsluta programmet\n")
    choice = input("Skriv in önskad siffra: ")

    if (choice == '1'):
        egen_rondelet()
        
    elif (choice == '2'):
        example()
        
    elif (choice == '0'):
        print("Avslutar program...")
        sys.exit()
        
    else:
        print("Ogiltig inmatning!\n")
        main()
    


main() #Startar programmet
