#Programmeringsteknik webbkurs KTH inlämningsuppgift 1.
#Özgun Mirtchev
#2015-06-18
#Programmet erbjuder användaren att se exempel på en rondelet
#Eller att skapa en egen rondelet
#Just nu finns ingen fel-checker för ogiltig inmatning för meningar
#Vilket innebär att användaren kan göra dikter med siffror och symboler...


import sys
from tkinter import *

#Menyn
def main():
    
    mainGUI = Tk()

    mainGUI.title('Inlämningsuppgift 2')
    mainGUI.geometry("250x150")
    
    Label(mainGUI, text="Välj ett av alternativen nedan:").pack()
    Button(mainGUI, text="Ange egna meningar för en rondelet \n(Funkar ej)",
           command = egen_rondelet).pack()
    Button(mainGUI, text="Se exempel på en rondelet", command = example).pack()
    Button(mainGUI, text="Avsluta programmet", command = mainGUI.destroy).pack()      



#Skapa en egen rondelet, se print_out mode = 1
def egen_rondelet():

    def arrayAppend(word):
        atext = word.get()
        user_sentence.append(atext)
        return
    
    egen_rondeletGUI = Tk()
    egen_rondeletGUI.title("Din egen rondelet")
    user_sentence = []

    
    title = "DIKTAUTOMATEN"
    Label(egen_rondeletGUI, text=title).pack()
    Label(egen_rondeletGUI, text="Skriv in fyra meningar och få ut en rondelet!\n").pack()
    
    
    for i in range(4):
        userSentence = StringVar()
        Label(egen_rondeletGUI, text="Skriv mening nr " + str(i+1) +": ").pack()
        Entry(egen_rondeletGUI, textvariable=userSentence).pack()
        Button(egen_rondeletGUI, text="Ok", command=arrayAppend(userSentence)).pack()
##        user_sentence.append(userSentence)

        
    print_out(user_sentence)
    
    Button(egen_rondeletGUI, text="Stäng fönster", command = egen_rondeletGUI.destroy).pack()


    egen_rondelet.mainloop()

#Exemplet från hemsidan
def example():
    
    exampleGUI = Tk()
    exampleGUI.title("Rondelet-exempel")
    
    example_sentence =[
            "Det fanns ingen fil när jag handlade på Konsum.",
            "Bananerna var också slut.",
            "Jag köpte bröd istället.",
            "Nån sorts limpa med mycket fibrer."
            ]

    title = "DIKTAUTOMATEN"
    Label(exampleGUI, text=title).pack()

    Label(exampleGUI, text="Skriv in fyra meningar och få ut en rondelet!\n").pack()
    
    for i in range(4):
            Label(exampleGUI, text="Skriv mening nr " + str(i+1)
                  + ": " + example_sentence[i]).pack()
            
    Label(exampleGUI, text="\n\n").pack()

    firstSentencePart = fourWords(example_sentence[0],1)
    
    Label(exampleGUI, text=firstSentencePart.upper()+"\n").pack()
    Label(exampleGUI, text=firstSentencePart).pack()
    Label(exampleGUI, text=fourWords(example_sentence[0],2)).pack()
    Label(exampleGUI, text=firstSentencePart).pack()

    for i in range(3):
        Label(exampleGUI, text=example_sentence[i+1]).pack()

    Label(exampleGUI, text=firstSentencePart + "\n").pack()

    Button(exampleGUI, text="Stäng fönster",
           command = exampleGUI.destroy).pack()

    exampleGUI.mainloop()
        
        
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
#Detta för att undika extra kod i de andra funktionerna
def print_out(array):

            
    Label(exampleGUI, text="\n\n").pack()

    firstSentencePart = fourWords(array[0],1)
    
    Label(egen_rondeletGUI, text=firstSentencePart.upper()+"\n").pack()
    Label(egen_rondeletGUI, text=firstSentencePart).pack()
    Label(egen_rondeletGUI, text=fourWords(user_sentence[0],2)).pack()
    Label(egen_rondeletGUI, text=firstSentencePart).pack()

    for i in range(3):
        Label(egen_rondeletGUI, text=user_sentence[i+1]).pack()

    Label(egen_rondeletGUI, text=firstSentencePart + "\n").pack()


main()

