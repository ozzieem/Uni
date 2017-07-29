
def breadth_first(start, end):
    frontier = []                                  # Paths to be searched
    frontier.append([start])
    tested_nodes = 0
    while frontier:
        if frontier is None:
            return "No path", tested_nodes
        path = frontier.pop(0)                     # First path in queue
        node = path[-1]                         # Setting Node as the last location of path
        if node == end:                         # Check to see if Node is the destination
            return path, tested_nodes
        for adjacent in node.neighbours:    # Adding each neighbour to the Node
            new_path = list(path)
            new_path.append(adjacent)
            frontier.append(new_path)
            tested_nodes += 1     

def run(start, end):
    paths, tested_paths = breadth_first(start, end)
    print("----------Breadth-First-Search Results----------")
    print("Created path: " + str(paths))
    print("Total visited nodes: " + str(tested_paths) + "\n")
    input("\nPress enter to continue...\n\n")