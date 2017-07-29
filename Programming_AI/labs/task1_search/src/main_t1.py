import os

from node_connection import *
from tools import available_destinations, get_node

import iterative_deepening
import a_star

destinations, nodes = load_node_connection_data()  # Dictionary, and list of nodes
algorithm_menu = "Algorithms menu:\n " \
                 "1. Iterative Deepening Search\n " \
                 "2. A* Search\n " \
                 "0. Change route\nEnter your choice: "


def clean_input(input_str):
    regex = ",'.:;´`^~<>|!#¤%&/()=?@£$€{[]}-_"
    for char in regex: input_str = input_str.replace(char, "")
    return input_str


# Algorithm choice menu
def algorithm_choice(start, end):
    while True:
        try:
            print("\n---------Route: " + start.title() + " to " + end.title() + "---------")
            choice = int(input(algorithm_menu))

            if choice == 1:
                iterative_deepening.run(get_node(start, nodes), get_node(end, nodes))
            elif choice == 2:
                a_star.run(get_node(start, nodes), get_node(end, nodes))
            elif choice == 0:
                break
            else:
                raise ValueError("Enter a valid option.\n")

        except ValueError as err:
            print(err)


def get_place(prompt_str):
    while True:
        try:
            place = clean_input(input(prompt_str).lower())

            if not place:
                raise ValueError("Missing data in a field.  Try again.\n")
            if place not in destinations:
                raise ValueError("Specified place not available.\n")
            return place
        except ValueError as error_message:
            print(error_message)


# Route menu
def route():
    print("\n---------Decide your route---------")
    start = get_place("Enter start:")
    end = get_place("Enter destination:")
    algorithm_choice(start, end)


def main():
    os.system("cls")
    available_destinations(nodes)
    while True:
        route()


main()
