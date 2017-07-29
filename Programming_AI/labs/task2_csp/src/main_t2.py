import time

from arcconsistency import ArcConsistency
from csp import CSP, print_current_grid
from objects import Domains


def arc_consistent_domain():
    ac = ArcConsistency()
    ac.setup_scenario()
    # extract domain values from the dict
    return [j for i in ac.arc_consistency3().values() for j in i]


def choose_option():
    while True:
        try:
            choice = int(input(" 1. Backtracking\n"
                               " 2. Arc-Consistency(3)\n"
                               " 3. Backtracking with AC\n"
                               "Choose option:\n"))
            if choice < 1 or choice > 3:
                raise IndexError
            return choice
        except IndexError:
            print("Invalid input - Choose an option")


def main():
    choice = None
    while choice != "q":
        try:
            choice = choose_option()
            if choice == 1:
                run_CSP()
            if choice == 2:
                run_ac3()
            if choice == 3:
                run_CSP(with_ac=True)

            choice = input("\nPress Enter to start again or q to quit...")
        except ValueError:
            print("Invalid input - enter a valid number.")
        except IndexError as e:
            print("Can't find data.", e)


def run_CSP(with_ac=False):
    csp = CSP()
    csp.setup_scenario()

    start_time = time.perf_counter()

    if with_ac:
        print("Solving with arc-consistency backtracking. Please wait...\n")
        csp.domains = Domains(arc_consistent_domain())
    else:
        print("Solving with backtracking. Please wait...\n")

    print(f"Variables: {csp.variables}")
    print(f"Domains  : {csp.domains}")

    results = csp.backtracking_search()

    end_time = time.perf_counter()

    if results:
        info_0 = "Problem was solved. Solution:\n"
        info_0 += print_current_grid(results["A1"], results["A2"], results["A3"],
                                     results["D1"], results["D2"], results["D3"])
    else:
        info_0 = "Unable to solve problem. No solution.\n"

    info_1 = f"Number of domains: {csp.domains.size()}\nNumber of variables: {csp.variables.size()}\n"
    info_2 = f"Total assignments: {csp.total_assignments} ({csp.iterations_per_level})\n" \
             f"Total backtracks:  {csp.total_backtracks}\n" \
             f"Approximate time:  {end_time - start_time} s\n"

    print(info_0)
    print(info_1)
    print(info_2)


def run_ac3():
    ac = ArcConsistency()
    ac.setup_scenario()
    domains = ac.arc_consistency3()
    solution = True
    for k, v in domains.items():
        if domains[k]:
            pass
        else:
            solution = False
    if solution:
        print("\nNetwork is Arc-consistent:")
        for k, v in domains.items():
            print(k, domains[k])
    else:
        print("\nEmpty domain detected. No solution.")


def debug_print(*args):
    print("DEBUG-PRINT")
    for arg in args:
        print(arg)

main()
