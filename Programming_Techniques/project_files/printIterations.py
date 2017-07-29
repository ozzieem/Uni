def calcMaxIterations(object):
    
    maxValue = max(object.heaps)
    return maxValue*maxValue - maxValue
    

def printIterations(object):

    global randCount
    count = 0
    nextHeap = []
    cardHistory = []
    
    print("Dina högar av kort består av: " + str(object.heaps) + NEWLINE + \
          "Startar iteration...\n")
    time.sleep(2)
    object.heaps.sort(reverse = True)
    print(object.heaps)

    # Antal max iterationer det får förekomma
    maxIterations = calcMaxIterations(object)

    while (count < maxIterations):
        nextHeap = object.nextStack()
        print(nextHeap)
       
        # Avbryter loop direkt med break om cykel upptäcks
        # Cykel: Kollar om en hög förekommer igen över hela listan utom sista
        if(nextHeap in cardHistory[:-1:]):
            print("Patiensen gick in i en cykel efter %d " \
                  "iterationer. Patiensen avbryts.\n" % count)
            break
        
        # Avbryter om samma hög förekommer i nästa steg
        if (nextHeap == object.heaps):
            print("Patiensen gick ut på %d iterationer.\n" % count)
            randCount += 1
            break

        # Om count mer än maxIterations, gick patiensen inte ut
        elif count >= maxIterations:
            print("Patiensen gick inte ut. Max iterationer: %d \n" \
                  % maxIterations)
            break

        # Lägger till nuvarande hög i history
        count += 1
        cardHistory.append(nextHeap)
        object.heaps = nextHeap
        
