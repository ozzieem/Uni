class CrosswordConstraints:
    def __init__(self):
        self.first_word = None
        self.second_word = None
        self.first_var = None
        self.second_var = None

    # runs the constraint check
    def check(self, f_var, f_wrd, s_var, s_wrd):
        self.first_var = f_var
        self.second_var = s_var
        self.first_word = f_wrd
        self.second_word = s_wrd

        return self.check_arc_constraint()

    # decides which constraint to choose depending on current arc
    def check_arc_constraint(self):
        if self.first_var == "D1":
            return self.D_to_A_constraint(self.second_word[0])
        if self.first_var == "D2":
            return self.D_to_A_constraint(self.second_word[1])
        if self.first_var == "D3":
            return self.D_to_A_constraint(self.second_word[2])
        if self.first_var == "A1":
            return self.A_to_D_constraint(self.second_word[0])
        if self.first_var == "A2":
            return self.A_to_D_constraint(self.second_word[1])
        if self.first_var == "A3":
            return self.A_to_D_constraint(self.second_word[2])
        return False

    # constraints for an arc from D to A
    def D_to_A_constraint(self, a_word_char):
        if self.second_var == "A1":
            if self.first_word[0] == a_word_char:
                return True
        if self.second_var == "A2":
            if self.first_word[1] == a_word_char:
                return True
        if self.second_var == "A3":
            if self.first_word[2] == a_word_char:
                return True
        return False

    # constraints for an arc from A to D
    def A_to_D_constraint(self, d_word_char):
        if self.second_var == "D1":
            if self.first_word[0] == d_word_char:
                return True
        if self.second_var == "D2":
            if self.first_word[1] == d_word_char:
                return True
        if self.second_var == "D3":
            if self.first_word[2] == d_word_char:
                return True
        return False

    # check the passed in word from csp
    def check_word(self, f_cell, s_cell, t_cell, new_word, current_cell):
        if (self.are_letters_equal(f_cell, s_cell, t_cell, current_cell)
            or
                self.are_letters_equal(f_cell, s_cell, t_cell, new_word)):
            return True
        return False

    # compare current variable word to other variable words
    def are_letters_equal(self, letter1, letter2, letter3, other):
        if (letter1 == other[0] and letter2 == other[1] and letter3 == other[2]) or (
                            letter1 == " " and letter2 == " " and letter3 == " "):
            return True
        return False

    # Testing for csp constraint
    def consistent(self, var, val, assignment):

        if var == "A1":
            # check D1[0], D2[0], D3[0]
            if self.check_word(assignment["D1"][0], assignment["D2"][0], assignment["D3"][0], val, var):
                return True
        if var == "A2":
            # check D1[1], D2[1], D3[1]
            if self.check_word(assignment["D1"][1], assignment["D2"][1], assignment["D3"][1], val, var):
                return True
        if var == "A3":
            # check D1[2], D2[2], D3[2]
            if self.check_word(assignment["D1"][2], assignment["D2"][2], assignment["D3"][2], val, var):
                return True

        if var == "D1":
            # check A1[0], A2[0], A3[0]
            if self.check_word(assignment["A1"][0], assignment["A2"][0], assignment["A3"][0], val, var):
                return True
        if var == "D2":
            # check A1[1], A2[1], A3[1]
            if self.check_word(assignment["A1"][1], assignment["A2"][1], assignment["A3"][1], val, var):
                return True
        if var == "D3":
            # check A1[2], A2[2], A3[2]
            if self.check_word(assignment["A1"][2], assignment["A2"][2], assignment["A3"][2], val, var):
                return True

        return False
