#
# Iterative-Deepening Algorithm with Depth-Limited Search
#

from tools import reconstruct_path, print_route


def getDepth():
    # return 50     # hard value
    while True:
        try:
            depth = int(input("Enter max depth:"))
            return depth
        except ValueError:
            print("Enter a valid number")


def iterative_deepening(start, end):
    max_depth = getDepth()
    depth = 0
    while max_depth >= depth:
        result = depth_limited_search(start, end, depth)
        if result:
            return result
        depth += 1
    return None, depth, 0


def depth_limited_search(start, end, max_depth):
    frontier = [start]

    node_depth = {start: 0}  # Keeps track of how deep a node is
    node_from_node = {start: None}  # Stores where a node came from

    visited = []
    total_explored = 0

    while True:
        if not frontier:
            return None
        node = frontier.pop()

        if not (node_depth[node] > max_depth):
            # If node is goal, return path
            if node == end:
                return reconstruct_path(node_from_node, start, end), node_depth[node], total_explored

            # Iterate neighbours of current node
            for next_n in node.neighbours:
                total_explored += 1

                if (next_n not in visited) and (next_n not in frontier):
                    frontier.append(next_n)
                    node_depth[next_n] = node_depth[node] + 1
                    node_from_node[next_n] = node
                    visited.append(next_n)


def run(start, end):
    path, reached_depth, total_tests = iterative_deepening(start, end)
    print("\n----------Iterative-Deepening-Search Results----------")
    if path is not None:
        print_route(path, end)
        print("\n\nReached depth: " + str(reached_depth))
        print("Total path nodes: " + str(len(path)))
        print("Total tested nodes: " + str(total_tests))
    else:
        print(f"\nReached max depth - No path")

    input("\nPress enter to continue...\n\n")
