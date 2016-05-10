__author__ = 'Ozziee'
#Özgun M

import math
import tkinter
from math import sin, cos, radians


#Uppgift 1
print("Uppgift 1:".upper())

def klocka(a,b):
    h1 = a[0]
    m1 = a[1]
    h2 = b[0]
    m2 = b[1]
    #Tilldelar en variabel för varje tupel-del.

    m3 = (m1 + m2) % 60
    extrah = (m1+m2) // 60
    h3 = (h1 + h2 + extrah) % 24
    return(h3,m3)

print("klocka((10,45), (14,30)): ", klocka((10,45), (14,30)))
print("klocka((10,45),(-14,-30)): ", klocka((10,45),(-14,-30)))
print("")


# Uppgift 2
print("Uppgift 2:".format())

def delare(x,y):
    if x == 0:
        return print("Error: Divided by Zero. Undefined.")
    else:
        return y % x == 0   #En delare till ett heltal är en delare utan rest. Dvs modulo ett tal ska bli 0.
print("Exempel - Delare:")
print("Is 6 a divider to 3?", delare(6,3))
print("Is 3 a divider to 6?", delare(3,6))
print("Is 3 a divider to 9?", delare(3,9))
print("Is 0 a divider to 9?", delare(0,9))
print("")



def prime(x):
    if x == 2:
        return True
    elif x < 2:
        return False
    for d in range(2,x):
        if delare(d,x) == True:
            return False
        else:
            return True

print("Prime number examples:")
print("Is number 12 a prime number?", prime(12))
print("Is number 13 a prime number?", prime(13))
print("Is number 4 a prime number?", prime(4))
print("Is number 3 a prime number?", prime(3))
print("Is number 2 a prime number?", prime(2))
print("")

# Uppgift 3
print("Uppgift 3:".upper())

#Power
def loopPower(a,n):
    ans=1
    for i in range(n):
        ans=ans*a
    return ans

def recPower(a,n):
    if n == 0:
        return 1
    else:
        factor = recPower(a, n//2)
        if n % 2 == 0:
            return factor * factor
        else:
            return factor*factor*a

loopPower(3,2)


#Fibonacci
def fib(n):
    if n < 3:
        return 1
    else:
        x = fib(n-1) + fib(n-2) #Kräver fler iterationer för att beräkna funktionsanropningen pga två rekursiva funktioner.
        print("Computing fib(",n,")""\n""...""\n""Leaving fib(",n,") -> returning", x,"\n")
        return x

#Fibonacci 2
def fibi(n): # Denna räknar ut talet på en gång istället för att anropa funktionen i funktionen igen.
    a, b = 0, 1
    for i in range(n):
        a, b = b, a + b
        print("Computing fib(",n,")""\n""...""\n""Leaving fib(",n,") -> returning", a,"\n")
    return a

fibi(4)


#Uppgift 5
print("Uppgift 5:".upper())

print("Input 1 for tree with two branches")
print("Input 2 for tree with tree branches")

choice = int(input("What is your choice?:")) #Innehåller tyvärr ingen loop denna gång...
if choice == 1:

    class DrawingWindow(tkinter.Frame):
        def __init__(self):
            tkinter.Frame.__init__(self,None)
            self.canvas = tkinter.Canvas(self,width=500,height=500,bg='white')
            self.canvas.pack(expand=1,anchor=tkinter.CENTER)
            self.pack()

    def drawTree(x,y,angle,dangle,length,dlength,steps,canvas):
        if steps == 0:
            pass
        else:
            x2 = x+sin(radians(angle))*length
            y2 = y-cos(radians(angle))*length
            canvas.create_line(x,y,x2,y2)
            drawTree(x2,y2,angle+dangle,dangle,length/dlength,dlength,steps-1,canvas)
            drawTree(x2,y2,angle-dangle,dangle,length/dlength,dlength,steps-1,canvas) # Lade till en extra funktion och ändrade + tecknet till - i "angle+dangle" i originalfunktionen.


    w = DrawingWindow()
    drawTree(250,250,0,40,100,1.5,5,w.canvas)
    w.mainloop()

elif choice == 2:
    class DrawingWindow(tkinter.Frame):
        def __init__(self):
            tkinter.Frame.__init__(self,None)
            self.canvas = tkinter.Canvas(self,width=500,height=500,bg='white')
            self.canvas.pack(expand=1,anchor=tkinter.CENTER)
            self.pack()

    def drawTree(x,y,angle,dangle,length,dlength,steps,canvas):
       if steps == 0:
           pass
       else:
           x2 = x+sin(radians(angle))*length
           y2 = y-cos(radians(angle))*length
           canvas.create_line(x,y,x2,y2)
           drawTree(x2,y2,angle+dangle,dangle,length/dlength,dlength,steps-1,canvas)
           drawTree(x2,y2,angle-dangle,dangle,length/dlength,dlength,steps-1,canvas)
           drawTree(x2,y2,angle,dangle,length/dlength,dlength,steps-1,canvas)           #Lade till en extra rekursiv funktion och tog bort "-dangle" från original funktionen


    w = DrawingWindow()
    drawTree(250,300,0,40,100,1.5,5,w.canvas)
    w.mainloop()
