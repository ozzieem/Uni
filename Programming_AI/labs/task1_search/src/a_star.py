#
# A* Search
#

from math import sqrt

from tools import reconstruct_path, print_route_costs


def a_star(start, goal):
    frontier = {start: 0}  # Queue to iterate the next node
    came_from = {}  # Stores where a node came from
    cost_so_far = {start: 0}  # Stores cost for each visited node
    explored = []  # All explored nodes
    total_explored = 0

    while True:
        # If there are no nodes in frontier, no path (FAIL)
        if not frontier:
            return None, None, None

        # Pick the node with the least cost
        current = min(frontier, key=frontier.get)

        # Returns the path if reached goal node
        if current == goal:
            return (reconstruct_path(came_from, start, goal),
                    cost_so_far,
                    total_explored)

        del frontier[current]
        explored.append(current)

        # Iterate through all neighbour nodes of current node
        for next_neighbour in current.neighbours:
            total_explored += 1

            # Calculates cost for current node
            new_cost = int(cost_so_far[current] + heuristic_euclidean(current, next_neighbour))

            # Update the neighbour cost if its cheaper to get there than before
            if next_neighbour in explored:
                if new_cost < cost_so_far[next_neighbour]:
                    explored.remove(next_neighbour)
                    frontier[next_neighbour] = new_cost
                    came_from[next_neighbour] = current
                    cost_so_far[next_neighbour] = new_cost
            # Same as above but if it's in frontier instead
            elif next_neighbour in frontier.keys():
                if new_cost < cost_so_far[next_neighbour]:
                    cost_so_far[next_neighbour] = new_cost
                    came_from[next_neighbour] = current
            # If none of above, just add the node to frontier
            else:
                frontier[next_neighbour] = new_cost
                cost_so_far[next_neighbour] = new_cost
                came_from[next_neighbour] = current


# Manhattan distance
def heuristic_manhattan(a, b):
    (x1, y1) = a.x, a.y
    (x2, y2) = b.x, b.y
    cost = abs(x1 - x2) + abs(y1 - y2)
    return cost


# Euclidean distance
def heuristic_euclidean(a, b):
    x = pow(b.x - a.x, 2)
    y = pow(b.y - a.y, 2)
    cost = sqrt(x + y)
    return cost


def run(start, end):
    path, total_cost_list, total_tests = a_star(start, end)
    print("\n----------A*-Search Results----------")
    if path is not None:
        print_route_costs(path, total_cost_list, end)
        print("\n\nTotal path nodes: " + str(len(path)))
        print("Total tested nodes: " + str(total_tests))
    else:
        print("\nUnable to find path")
    input("\nPress enter to continue...\n\n")
