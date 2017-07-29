#
#   Useful functions
#

# Returns the node with the specified name
def get_node(name, nodes):
    idx = 0
    for node in nodes:
        if node.name == name:
            return nodes[idx]
        idx += 1
    return None


# Prints all available destinations
def available_destinations(nodes):
    print("Available destinations:")
    nodes.sort(key=lambda x: x.name)
    for node in nodes:
        print(node.name.title(), end="\n")
        # print_at(node.x, node.y, node.name)
    print("\n")


# Prints route without costs
def print_route(path, end):
    print("Created path: ", end="")
    for i in range(len(path)):
        print("{" + path[i].name.title() + "}", end="")
        if path[i] != end:
            print("---->", end="")


# Prints route with costs
def print_route_costs(path, cost_per_node, end):
    print("Created path: ", end="")
    for i in range(len(path)):
        print("{" + path[i].name.title() + "}", end="")
        if path[i] != end:
            print("--" + str(cost_per_node.get(path[i + 1])) + "-->", end="")


# Constructs a path
def reconstruct_path(came_from, start, end):
    current = end
    path = [current]
    while current != start:
        current = came_from[current]
        path.append(current)
    path.reverse()
    return path
