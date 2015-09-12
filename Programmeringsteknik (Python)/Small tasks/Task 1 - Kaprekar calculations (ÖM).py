#Programmeringsteknik webbkurs KTH inlämningsuppgift 1.
#Özgun Mirtchev
#2015-06-15
#Programmet beräknar hur många iterationer det tar för
#ett inmatat tal att räkna till 6174 genom Kaprekars konstant.

import time
import sys

#Sorterar talet, beräknar och skriver ut varje iteration(bonus-grej)
def sort_num(number):
    big_numb = "".join(sorted(number, reverse = True))
    sml_numb = "".join(sorted(big_numb))
    
    result = str(int(big_numb)-int(sml_numb))
    print(big_numb + "-" + sml_numb + "=" + result)
    return result


#Kaprekar-funktionen. Kollar fel-inmatat(dock inte alla möjliga)
#Beräknar tills talet når 6174 med while-loop
def kaprekar():
    numb = input("Ange ett fyr-siffrigt tal: ")

    if (len(numb) != 4):
        print("Talet måste ha 4 siffror!\n")
        kaprekar()
    if (len(set(numb)) < 2):    #Kollar om tal är identiska genom set()
        print("Talet får inte bestå av bara identiska siffror.\n")
        kaprekar()
    if (numb <= '0' or numb >= '9998'):
        print("Ange ett tal mellan 1 och 9998\n")
        kaprekar()
    for i in numb:
        try:
           val = int(numb)
           break
        except ValueError:
            print("Ange endast siffror!\n")
            kaprekar()

        
    print("Beräknar", end="")
    i = 0
    for i in range(3):
        print(".", end="")
        time.sleep(0.5)
    print("\n\n")


        
    count = 0
    while (numb != '6174'):
            
        numb += '0' * (4 - len(numb)) #Lägger till nollor
        count += 1
        numb = sort_num(numb)

    print("\nDet tog " + str(count) + " iterationer att nå 6174.\n\n")
    time.sleep(2)    

    main()


#Menyn
def main():
    mtitle = "huvudmeny"
    print(mtitle.upper().center(70, ' '))
    
    print("Välj ett av alternativen nedan:\n", \
          "1. Beräkna antal iterationer av ett tal med Kaprekars konstant\n", \
          "0. Avsluta programmet\n")
    choice = input("Skriv in önskad siffra: ")

    if (choice == '1'):
        kaprekar()
    elif (choice == '0'):
        print("Avslutar program...")
        time.sleep(1)
        sys.exit()
    else:
        print("Ogiltig inmatning!\n")
        main()


main() #Behövs för att starta programmet
