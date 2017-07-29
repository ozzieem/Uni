class ListClass:
    def __init__(self, in_list=[]):
        self.list = in_list

    def get(self):
        return self.list

    def __repr__(self):
        return str(self.list)

    def size(self):
        return len(self.list)


class Variables(ListClass):
    def __init__(self, variables=[]):
        super().__init__(variables)


class Domains(ListClass):
    def __init__(self, domains=[]):
        super().__init__(domains)


def setup_string_words(file_name):
    domains = []
    try:
        with open(file_name, 'r') as f:
            for line in f:
                domains.append(line.strip())

        return domains
    except FileNotFoundError as e:
        print(e)
        quit(1)


def setup_string_word_entries():
    variables = ["A1", "A2", "A3", "D1", "D2", "D3"]
    return variables


def setup_string_neighbours():
    neighbours = {}
    down = ["D1", "D2", "D3"]
    across = ["A1", "A2", "A3"]

    neighbours["A1"] = down[:]
    neighbours["A2"] = down[:]
    neighbours["A3"] = down[:]
    neighbours["D1"] = across[:]
    neighbours["D2"] = across[:]
    neighbours["D3"] = across[:]

    return neighbours


def setup_curr_domains(variables, dom):
    curr_domains = {}
    for var in variables:
        curr_domains[var] = dom[:]
    return curr_domains


## DEPRECATED ##
class Word:
    def __init__(self, word="   "):
        self.f = word[0]
        self.s = word[1]
        self.t = word[2]

    def __str__(self):
        return "W:" + self.f + self.s + self.t

    def __repr__(self):
        return "W:" + self.f + self.s + self.t


class WordEntry:
    def __init__(self, cell, word=Word()):
        self.cell = cell
        self.word = word

    def __str__(self):
        return "WE:" + self.cell

    def __repr__(self):
        return "WE:" + self.cell


# add the domains
def setup_words(file_name):
    domains = []

    try:
        with open(file_name, 'r') as f:
            for line in f:
                domains.append(Word(line.strip()))

        return domains
    except FileNotFoundError as e:
        print(e)
        quit(1)


# add the variables:
def setup_word_entries():
    variables = [WordEntry("A1"), WordEntry("A2"), WordEntry("A3"), WordEntry("D1"), WordEntry("D2"), WordEntry("D3")]
    return variables
