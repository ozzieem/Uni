import csv

from tools import get_node


class Node(object):
    neighbours = []

    def __init__(self, name, x, y):
        self.name = name
        self.x = x
        self.y = y

    def __repr__(self):
        return repr((self.name, self.x, self.y))


class Connection(object):
    def __init__(self, start, end):
        self.start = start
        self.end = end

    def __str__(self):
        return str(self.start) + " - " \
               + str(self.end)


def load_node_connection_data():
    destinations = {}

    # Read in connections
    connections_list = []
    with open('../files/sconnections2016.csv') as connect_file:
        connections = csv.DictReader(connect_file, delimiter=';')
        for row in connections:
            l = Connection(row['from'].lower(), row['to'].lower())
            connections_list.append(l)

    # Read in nodes
    nodes = []
    with open('../files/slocations2016.csv') as node_file:
        locations = csv.DictReader(node_file, delimiter=';')
        for row in locations:
            n = Node(row['name'].lower(), int(row['x']), int(row['y']))
            nodes.append(n)

    # Add connections to nodes
    for n in nodes:
        n.neighbours = []
        for place in connections_list:
            if n.name == place.start:
                n.neighbours.append(get_node(place.end, nodes))
        destinations[n.name] = n.neighbours

    return destinations, nodes
