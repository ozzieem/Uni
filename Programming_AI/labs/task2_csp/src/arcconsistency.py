from crossword_constraints import CrosswordConstraints
from fifo_queue import FIFOQueue

from objects import *


class ArcConsistency:
    def __init__(self):
        self.variables = []
        self.domains = []
        self.neighbours = {}
        self.dom_of_var = {}
        self.total_iterations = 0
        self.constraints = CrosswordConstraints()

    def setup(self, file_name):
        self.variables[:] = setup_string_word_entries()
        self.domains[:] = setup_string_words(file_name)
        self.neighbours = setup_string_neighbours()
        self.dom_of_var = setup_curr_domains(self.variables, self.domains)

    def setup_scenario(self):
        self.setup("../files/words.txt")

    def arc_consistency3(self):
        queue = FIFOQueue([(Xi, Xk) for Xi in self.variables for Xk in self.neighbours[Xi]])
        while not queue.empty():
            (Xi, Xj) = queue.get()  # get the next arc in the queue
            print(f"Arc: {Xi}->{Xj}", end=" - ")
            if self.remove_inconsistent_values(Xi, Xj):
                # arc to changed domain of variable might be inconsistent now, recheck
                for Xk in self.neighbours[Xi]:
                    queue.put((Xk, Xi))
            else:
                print(f"Consistent")
        return self.dom_of_var

    def remove_inconsistent_values(self, f_var, s_var):
        vi_domain = list(self.dom_of_var[f_var])
        vj_domain = list(self.dom_of_var[s_var])
        removed_from_arc = []

        removed = False
        for x in vi_domain:
            # checks current word in first variable against all values in second variable
            consistent = [(lambda y: self.constraints.check(f_var, x, s_var, y))(y) for y in vj_domain]
            # if all checked values are false then remove the current word
            if not any(consistent):
                self.dom_of_var[f_var].remove(x)
                removed_from_arc.append(x)
                removed = True
        if removed:
            print(f"Removed {removed_from_arc}")
        return removed
