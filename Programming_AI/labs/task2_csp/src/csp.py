import sys

from crossword_constraints import CrosswordConstraints
from objects import *


class CSP:
    variables = Variables()
    domains = Domains()
    constraints = CrosswordConstraints()

    total_assignments = 0
    total_backtracks = 0
    iterations_per_level = {}

    def setup_scenario(self):
        self.variables = Variables(setup_string_word_entries())
        self.domains = Domains(setup_string_words("../files/words.txt"))

    def backtracking_search(self):
        self.total_assignments = 0
        self.total_backtracks = 0
        self.iterations_per_level = {}
        grid = {}
        for var in self.variables.get():
            grid[var] = "   "
        return self.recursive_backtracking(grid, self.domains, self.variables, 1)

    def recursive_backtracking(self, assignment, domains, variables, level):
        if self.assignment_complete(assignment):
            return assignment
        var = self.select_unassigned_variable(assignment, variables)
        for val in domains.get():
            if val not in assignment.values():
                if self.constraints.consistent(var, val, assignment):
                    assignment[var] = val
                    self.total_assignments += 1
                    self.update_level_counter(level)

                    # print(self.print_current_grid(assignment))
                    self.print_progress(level)

                    result = self.recursive_backtracking(assignment, domains, variables, level + 1)
                    if result:
                        return result

                    assignment[var] = "   "  # reset word if unable to find consistency
                    self.total_backtracks += 1
        return False

    def assignment_complete(self, assign):
        complete = 0
        for we in assign:
            if assign[we][0] != " ":
                complete += 1
        if len(assign) == complete:
            return True
        return False

    # select the cell without an assigned word
    def select_unassigned_variable(self, assignment, variables):
        for var in variables.get():
            if assignment[var][0] == " ":
                return var
        return " "

    def print_progress(self, level):
        sys.stdout.write("Iterations: %d - Level: %d \r" % (self.total_assignments, level))
        sys.stdout.flush()

    def update_level_counter(self, level):
        if level not in self.iterations_per_level:
            self.iterations_per_level[level] = 0
        self.iterations_per_level[level] += 1


def print_current_grid(a1_w, a2_w, a3_w, d1_w, d2_w, d3_w):
    grid_str = "                     D1  D2  D3\n"
    grid_str += f"   +-----------+   +-----------+\n"
    grid_str += f"A1 | {a1_w[0]} | {a1_w[1]} | {a1_w[2]} |   | {d1_w[0]} | {d2_w[0]} | {d3_w[0]} |\n"
    grid_str += f"   +-----------+   +-----------+\n"
    grid_str += f"A2 | {a2_w[0]} | {a2_w[1]} | {a2_w[2]} |   | {d1_w[1]} | {d2_w[1]} | {d3_w[1]} |\n"
    grid_str += f"   +-----------+   +-----------+\n"
    grid_str += f"A3 | {a3_w[0]} | {a3_w[1]} | {a3_w[2]} |   | {d1_w[2]} | {d2_w[2]} | {d3_w[2]} |\n"
    grid_str += f"   +-----------+   +-----------+\n"
    return grid_str
