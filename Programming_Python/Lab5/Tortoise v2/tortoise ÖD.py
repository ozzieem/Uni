
import tkinter
from math import *
import random
import time
import _thread



# This is the class for the window displaying the tortoise and its world
class TortoiseFrame(tkinter.Frame):

    tort_img_canvas=False
    
    def __init__(self,grid_size,tortoise_brain):
        tkinter.Frame.__init__(self,None)
        self.master.title('Tortoise World')
        self.canvas = tkinter.Canvas(self,width=40*grid_size,height=40*grid_size+60,bg='white')
        self.canvas.pack(expand=1,anchor=tkinter.CENTER)
        self.pack()
        self.tkraise()
        # Create the world
        self.tw = TortoiseWorld(grid_size,tortoise_brain)
        # Load images
        self.images = {}
        for img in ['wall','lettuce','pond','ground','stone','tortoise-n','tortoise-s','tortoise-w','tortoise-e',]:
            self.images[img]=tkinter.PhotoImage(file='./'+img+'.gif')
        # Draw environment
        for y in range(grid_size):
            for x in range(grid_size):
                self.canvas.create_image(x*40,y*40,image=self.images[self.tw.worldmap[y][x]],anchor=tkinter.NW)
        # Set up a table for handling the tortoise images to use for each self.direction
        self.direction_img_table=['tortoise-n','tortoise-e','tortoise-s','tortoise-w']
        # Set up text item for drawing info
        self.text_item=self.canvas.create_text(40,(grid_size)*40,anchor=tkinter.NW, text='')
        self.after(1,self.step)

        
    def step(self):
        # Update time (Increase the value to raise the simulation speed. Max: 1.0)
        self.tw.curr_time += 1.0
        if self.tw.curr_time >= self.tw.next_time:
            # Step tortoise world
            self.tw.step()
            # Update ground if necessary
            if self.tw.update_current_place:
                self.canvas.create_image(self.tw.xpos*40,self.tw.ypos*40,
                                         image=self.images[self.tw.worldmap[self.tw.ypos][self.tw.xpos]],anchor=tkinter.NW)
            # Redraw tortoise
            tort_image=self.direction_img_table[self.tw.direction]
            if self.tort_img_canvas != False:
                self.canvas.delete(self.tort_img_canvas)
            self.tort_img_canvas = self.canvas.create_image(self.tw.xpos*40,self.tw.ypos*40,image=self.images[tort_image],anchor=tkinter.NW)
        # Display text information
        self.canvas.itemconfigure(self.text_item, text='Action: %-7s Food: %2d Drink: %2d Time: %4d' %
                                      (self.tw.action, self.tw.food_level, self.tw.drink_level, int(self.tw.curr_time)))
        if not self.tw.dead and not self.tw.action == 'stop' and self.tw.curr_time <= self.tw.max_time:
            self.after(100,self.step)

        # Added by ÖM to print out the status text on the frame instead
        if self.tw.dead:
            if self.tw.drink_level <= 0:
                self.canvas.itemconfigure(self.text_item, text='The tortoise died of thirst!\n' \
                                          'It survived for %d seconds!' % int(self.tw.curr_time))
            elif self.tw.food_level <= 0:
                self.canvas.itemconfigure(self.text_item, text='The tortoise died of hunger!\n' \
                                          'It survived for %d seconds!' % int(self.tw.curr_time))




class TortoiseWorld():    
    max_drink = 100
    max_food = 100
    max_time = 1000
    xpos,ypos=1,1
    drink_level=0
    food_level=0
    curr_time=0.0
    direction=0 #north=0, east=1, south=2, west=3
    worldmap=None
    action = 'None'
    state = 0
    next_time = 0
    update_current_place=False
    dead=False
    
    def __init__(self,grid_size,tortoise_brain):
        self.direction_table=[(0,-1),(1,0),(0,1,),(-1,0)]
        self.food_level=self.max_food 
        self.drink_level=self.max_drink
        self.create_world_map(grid_size)
        self.grid_size=grid_size
        self.tortoise_brain = tortoise_brain

        
    def step(self):
        self.curr_time = self.next_time
        time_change = 1
        self.next_time = self.curr_time + time_change
        self.update_current_place=False
        dx,dy=self.direction_table[self.direction]
        # Sensing
        ahead = self.worldmap[self.ypos+dy][self.xpos+dx]
        here = self.worldmap[self.ypos][self.xpos] 
        free_ahead = (ahead not in ['stone','wall'])
        lettuce_ahead = (ahead == 'lettuce')
        lettuce_here = (here == 'lettuce')
        water_ahead = (ahead == 'pond')
        water_here = (here == 'pond')
        hungry = (self.food_level <= self.max_food/2)       # Edit divider to change hunger limit
        thirsty = (self.drink_level <= self.max_drink/2)    # Edit divider to change thirst limit
        # Tortoise thinks!
        self.state, self.action = self.tortoise_brain(self.state,free_ahead,lettuce_ahead,lettuce_here,water_ahead,water_here,hungry,thirsty)
        # Perform action
        if self.action=='left':
            self.direction= (self.direction-1)%4
            self.food_level += -2
            self.drink_level += -2
        elif self.action=='right':
            self.direction= (self.direction+1)%4
            self.food_level += -2
            self.drink_level += -2
        elif self.action=='forward':
            if free_ahead:
                self.xpos += dx
                self.ypos += dy
            self.drink_level += -2
            self.food_level += -2
        elif self.action=='eat':
            if lettuce_here:
                self.food_level = self.max_food
            self.drink_level += -1
        elif self.action=='drink':
            if water_here:
                self.drink_level=self.max_drink                
        elif self.action=='wait':
            self.drink_level += -1
            self.food_level += -1
        if self.food_level < 0 or self.drink_level < 0:
            self.dead = True
        
    # Build a random world map 
    def create_world_map(self,grid_size):
        self.worldmap = [ [  ((y in [0,grid_size-1] or  x in [0,grid_size-1]) and 'wall') or 'ground'
                        for x in range(grid_size) ] for y in range(grid_size) ]
        # First put out the stones randomly
        for i in range(int((grid_size-2)**2/6)):
            ok=False
            while not ok: 
                (x,y) = random.randint(1,grid_size-1), random.randint(1,grid_size-1)
                if self.worldmap[y][x] == 'ground':
                    count_stones = 0
                    count_walls = 0
                    # Check that the stone will not be adjacent to two other stones,
                    # or one other stone and a wall.
                    # This is to prevent the appearance of inaccessible areas.
                    for dx in [-1,0,1]:
                        for dy in [-1,0,1]:
                           if self.worldmap[y+dy][x+dx] == 'stone':
                               count_stones += 1
                           if self.worldmap[y+dy][x+dx] == 'wall':
                               count_walls += 1
                    if count_stones == 0 or (count_stones <= 1 and count_walls == 0):        
                        self.worldmap[y][x] = 'stone'
                        ok=True
                    elif random.random() <= 0.1:
                        ok=True
        # Then put out the lettuces randomly
        for i in range(int((grid_size-2)**2/7)):
            ok=False
            while not ok: 
                (x,y) = random.randint(1,grid_size-1), random.randint(1,grid_size-1)
                if self.worldmap[y][x] == 'ground':
                    self.worldmap[y][x] = 'lettuce'
                    ok=True
        # Finally put out the water ponds randomly
        for i in range(int((grid_size-2)**2/7)):
            ok=False
            while not ok: 
                (x,y) = random.randint(1,grid_size-1), random.randint(1,grid_size-1)
                if self.worldmap[y][x] == 'ground':
                    self.worldmap[y][x] = 'pond'
                    ok=True

        


# Here you define the tortoise's brain
# The sensing input consists of the following parameters:
# - free_ahead (not blocked to rock or wall)
# - lettuce_ahead (in square in front of tortoise)
# - lettuce_here (can eat)
# - water_ahead (in square in front of tortoise)
# - water_here (can drink)
# - drink level (integer) 
# The available actions are:
#  - 'eat' (if on lettuce)
#  - 'drink' (if on water)
#  - 'left' (relative to current heading)
#  - 'right' (relative to current heading)
#  - 'forward' (relative to current heading)
#  - 'wait'
# -  'stop' (terminate simulation)

def call_automata(state,free_ahead,lettuce_ahead,lettuce_here,water_ahead,water_here,hungry,thirsty):
    
    if state==0:
        if hungry and lettuce_here:
            return 0,'eat'
        elif thirsty and water_here:
            return 0,'drink'
        elif thirsty and water_ahead:
            return 0, 'forward'
        elif hungry and lettuce_ahead:
            return 0, 'forward'
        elif thirsty and not water_ahead and free_ahead:
            return 1, 'forward'
        elif hungry and not lettuce_ahead and free_ahead:
            return 1, 'forward'
        elif thirsty and not free_ahead:
            return 0, 'right'
        elif hungry and not free_ahead:
            return 0, 'right'
        else:
            return 0,'wait'

    elif state == 1:                #Kollar framför om finns annars svänger höger
        if hungry and lettuce_ahead:            
            return 0, 'forward'
        elif thirsty and water_ahead:
            return 0, 'forward'
        elif hungry and not lettuce_ahead:
            return 2, 'right'
        elif thirsty and not water_ahead:
            return 2, 'right'

    elif state == 2:                #Kollar framför om finns annars svänger vänster (Till samma riktning som förut)
        if hungry and lettuce_ahead:            
            return 0, 'forward'
        elif thirsty and water_ahead:
            return 0, 'forward'
        elif hungry and not lettuce_ahead:
            return 3, 'left'
        elif thirsty and not water_ahead:
            return 3, 'left'

    elif state == 3:                #Kollar framför om finns annars svänger vänster
        if hungry and lettuce_ahead:            
            return 0, 'forward'
        elif thirsty and water_ahead:
            return 0, 'forward'
        elif hungry and not lettuce_ahead:
            return 4, 'left'
        elif thirsty and not water_ahead:
            return 4, 'left'

    elif state == 4:                #Kollar framför om finns annars svänger tillbaka till ursprungliga riktning
        if hungry and lettuce_ahead:            
            return 0, 'forward'
        elif thirsty and water_ahead:
            return 0, 'forward'
        elif hungry and not lettuce_ahead:
            return 0, 'right'
        elif thirsty and not water_ahead:
            return 0, 'right'

#State 2-4 är mestadels riktnings-ändrare. Han kollar åt höger/vänster för mat och vatten och om det inte finns,
#forsätter han framåt och kollar det igen. Det är förmodligen inte det effektivaste programmet. Och jag försökte
#att göra så att han skiftar riktning varannan gång men kunde inte göra det på ett bra sätt utan att det förstörde hela
#simulationen. Vi har testat denna automat ett par gånger och sköldpaddan har klarat sig alla gånger. Det är det bästa
#resultatet vi har kunnat få. Självklart finns det säkert en random map som är lite svår att klara sig men denna
#sköldpadda klarar sig i de flesta fallen tänker vi oss. 
        
        


tf = TortoiseFrame(8,call_automata)
tf.mainloop()
print('The tortoise survived for', int(tf.tw.curr_time), 'seconds!')
    
