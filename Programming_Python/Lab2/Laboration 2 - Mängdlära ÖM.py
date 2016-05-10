# Özgun Mirtchev

import sys
import math




#Main funktion, tänkt för att navigera mellan uppgifterna för användaren. Fungerar inte perfekt.
def main():
    x = int(input("Vilken uppgift vill ni observera? Var vänlig skriv in uppgiftens siffra (1-5):"))
    print("")
    if x == 1:
        U1(U,x)
    elif x == 2:
        U2(A,B,C,U)
    elif x == 3:
        U3(M1)
    elif x == 4:
        U4(1)
    elif x == 5:
        U5()

#Programmets start
print("Hej och välkommen till laboration 2. Denna version är skriven av ÖM.")
main() #Huvudmeny
prog(1) #Programval


#Programval
def prog(k):
    while k > 0:
        print("\n\n1. Fortsätt.")
        print("0. Avsluta.")
        k = int(input("Skriv in önskad siffra:"))
        if k > 0:
            main()
        elif k == 0:
            sys.exit("Avslutar programmet...")

# Uppgift 1

U = set([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])

def U1(U,x):
    print("Uppgift 1:".upper())

    def comp(set1):
        x = U.difference(set1)
        return x


    print("comp({0,1,2,3,4})\n", comp([0,1,2,3,4]))         #print används för redovisnings-purposes
    prog(1)



#Uppgift 2
# Väldigt många print funktioner. Finns säkerligen ett mycket bättre alternativ till att skriva ut print alla rader..

# Uppgifterna a - p

A = set([1, 2, 3, 4])
B = set([3, 4, 5])
C = set([5])
setempty = set()

def U2(A,B,C,U):
    print("Uppgift 2:".upper())
    print("Våra mängder är A = {}, B = {} och C = {}.".format(A, B, C))
    print(" Uppgift a: 1 är en mängd av A:", 1 in A)
    print(" Uppgift b: 5 är en mängd av A:", 5 in A)
    print(" Uppgift c: 1 är en mängd av den tomma mängden:", 1 in set())
    print(" Uppgift d: 1 är en mängd av Universum:", 1 in U)
    print(" Uppgift e: A är en delmängd av B:", A.issubset(B))
    print(" Uppgift f: C är en delmängd av B:", C.issubset(B))
    print(" Uppgift g: A är en delmängd av den tomma mängden:", A.issubset(setempty))
    print(" Uppgift h: A är en delmängd av Universum:", A <= U)
    print(" Uppgift i: A är snittet av C som är en delmängd av B:", A.intersection(C).issubset(B))
    print(" Uppgift j: A är unionen av C som är en delmängd av B:", A.union(C).issubset(B))
    print(" Uppgift k: Differensen av A och B är lika med C:", A.difference(B) == C)
    print(" Uppgift l: Differensen av B och C är en delmängd av A:", B.difference(C).issubset(A))
    print(" Uppgift m: Differensen av B och C är lika med A:", B.difference(C) == A)
    print(" Uppgift n: A är en delmängd till komplementet av C:", A.issubset(A.difference(C)))
    print(" Uppgift o: Kardinaliteten av U är lika med 5:", len(U) == 5)
    print(" Uppgift p: Kardinaliteten av A plus kardinaliteten av B är lika med 5:", len(A) + len(B) == 5)
    prog(1)




# Uppgift 3 a - c

M1 = set([2, 1]), set([2, 1, 3, 4])

def U3(M1):
    fs1 = frozenset([2,1])      #frozenset mängd
    fs2 = frozenset([2,1,3,4])  #frozenset mängd
    print("Uppgift 3:".upper())
    print(" Uppgift a:", A ,"är en mängd av mängden ", M1, ":", A in set([fs1, fs2]))
    print(" Uppgift b:" ,A, "är en delmängd av mängden ", M1, ":", A.issubset(set([frozenset([2, 1]), frozenset([2, 1, 3, 4])])))
    print(" Uppgift c:", C ,"är en delmängd av mängden ", M1, ":", C.issubset(set([fs1,fs2])))
    print(" ")
    print(" ")
    prog(1)





#Funktion setprod
def setprod(set1, set2):
    setp = set()                       # { } kan inte användas
    for x in set1:                  #Första elementet i den första mängden
        for y in set2:              # Första elementet i den andra mängden
            setp.add((x, y))     # Lägger till båda elementen i den nya mängden setp.
    return setp

# Uppgift 4
def U4(j):
    print("Uppgift 4:".upper())

    while j > 0:
        print("\nVad vill ni göra?")
        print("1. Observera uppgiftens mängder")
        print("2. Skriv in egna mängder")
        print("0. Återgå till huvudmeny")
        h = int(input("\nSkriv in önskad siffra:"))
        if h == 1:
            print("\nsetprod({1,2,3}, {4,5})\n", setprod({1,2,3}, {4,5}))
        elif h == 2:
            print("Skriv in dina element i mängden, i formatet '1234', istället för '{1,2,3,4}")
            setchoice1 = input("Skriv in den första mängden:")
            setchoice2 = input("Skriv in andra mängden:")
            print("setprod(",setchoice1,setchoice2,")\n", setprod(setchoice1, setchoice2))
        elif h == 0:
            prog(1)


#Uppgift 5

Y = setprod(B,C)

def U5():
    print("Uppgift 5:\n".upper())

    print("setprod(A,B)\n",setprod(A,B),"\n")
    print("setprod(A,(B,C))\n",setprod(A,(Y)),"\n")
    print("setprod(A,B)\n", setprod(A,B) == setprod(B,A),"\n")
    print("setprod(A, set())\n", setprod(A, set()) == set(),"\n")
    prog(1)







