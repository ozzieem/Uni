import tkinter as tk


TITLE_FONT = ("Helvetica", 18, "bold")


class SampleApp(tk.Tk):

    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

        # the container is where we'll stack a bunch of frames
        # on top of each other, then the one we want visible
        # will be raised above the others
        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}
        for F in (StartPage, PageOne, PageTwo):
            frame = F(container, self)
            self.frames[F] = frame
            # put all of the pages in the same location;
            # the one on the top of the stacking order
            # will be the one that is visible.
            frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(StartPage)

    def show_frame(self, c):
        '''Show a frame for the given class'''
        frame = self.frames[c]
        frame.tkraise()


class StartPage(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        label = tk.Label(self, text="Inlämningsuppgift 2", font=TITLE_FONT)
        label.pack(side="top", fill="x", pady=10)

        button1 = tk.Button(self, text="Go to Page One",
                            command=lambda: controller.show_frame(PageOne))
        button2 = tk.Button(self, text="Exempel",
                            command=lambda: controller.show_frame(PageTwo))
    
        button1.pack()
        button2.pack()


class PageOne(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        label = tk.Label(self, text="Min egna rondelet", font=TITLE_FONT)
        label.pack(side="top", fill="x", pady=10)
        button = tk.Button(self, text="Go to the start page",
                           command=lambda: controller.show_frame(StartPage))
        button.pack()


class PageTwo(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        label = tk.Label(self, text="Rondelet exempel", font=TITLE_FONT)
        label.pack(side="top", fill="x", pady=10)
        example()
        button = tk.Button(self, text="Go to the start page",
                           command=lambda: controller.show_frame(StartPage))
        button.pack()


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
    

if __name__ == "__main__":
    app = SampleApp()
    app.mainloop()
