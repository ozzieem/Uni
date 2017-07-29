from sys import *

kw_str = "STR"
kw_num = "NUM"
kw_exp = "EXP"
kw_var = "VAR"
kw_print = "out"
keywords = [kw_str, kw_num, kw_exp, kw_var]

integers = ["0","1","2","3","4","5","6","7","8","9"]
math_symb = ["+", "-", "*", "/", "(", ")"]
tokens = []
symbols = {}

def open_file(filename):
    try: 
        data = open(filename, "r").read()
        data += "<EOF>"
        return data
    except FileNotFoundError:
        print("ERROR! Filename was not found!")
        confirm_quit()

# Lexer-function that makes tokens tells the interpreter 
# what to do with certain keywords in a file
# such as print-equivalent functions.
def lex(filedata):
    tok = ""
    is_string = 0
    is_expression = 0
    is_var = 0
    var = ""
    string = ""
    expression = ""
    number = ""

    filedata = list(filedata)
    for char in filedata:
        tok += char
        if tok == " ":
            if is_string == 0:
                tok = ""
        elif tok in ["\n", "<EOF>", "<"]:
            if expression != "":
                if is_expression == 1:
                    tokens.append(kw_exp + ":" + expression)
                    is_expression = 0
                    expression = ""
                elif is_expression == 0:
                    tokens.append(kw_num + ":" + expression)
                    expression = ""
            if var != "":
                tokens.append(kw_var + ":" + var)
                var = ""
                is_var = 0
            tok = ""
        elif tok == "=" and is_string == 0:
            if var != "":
                tokens.append(kw_var + ":" + var)
                var = ""
                is_var = 0
            tokens.append("EQUALS")
            tok = ""
        elif tok == "#" and is_string == 0:
            is_var = 1
            var += tok
            tok = ""
        elif is_var == 1:
            var += tok
            tok = ""
        elif tok == kw_print:   # Printing values
            tokens.append(kw_print)
            tok = ""
        elif tok == "\"":
            if is_string == 0:
                is_string = 1
            elif is_string == 1:
                tokens.append(kw_str + ":" + string)
                string = ""
                tok = ""
                is_string = 0
        elif tok in integers:
            expression += tok
            tok = ""
        elif tok in math_symb:
                is_expression = 1
                expression += tok
                tok = ""
        if is_string == 1:
            if(tok != "\""):
                string += char
            tok = ""

    print(tokens)
    return tokens

def assign_var(name, value):
    symbols[name] = value

def get_var(name):
    try:
        return symbols[name]
    except KeyError as keyerr:
        return "Undefined Variable: " + str(keyerr)

def eval_expr(expr):
    return eval(expr)

# To parse from test.lang:
# ['output', 'String:Hello World', 
# 'output', 'String:Test again'
# 'Expression:46545 + 23',
# 'NUMBER:23']
def parse(toks):
        it = 0
        while(it < len(toks)):
            if(toks[it] == kw_print):   # Parse outputs
               kw_type = toks[it+1][0:3]
               if(kw_type in keywords):
                   if(kw_type == kw_var):
                       var_name = toks[it+1][5::]
                       print(get_var(var_name))
                   else:
                       print(toks[it+1][4::])
               it += 2
            elif(toks[it][0:3] == kw_exp):  # Parse expression
                loc_expr = toks[it][4::] 
                print(str(eval_expr(loc_expr)))
                it += 1
            elif(toks[it][0:3] == kw_num):  # Parse number
                print(toks[it][4::])
                it += 1
            elif(toks[it][0:3] + " " + toks[it+1] == "VAR EQUALS"): # Parse variables
               var_name = toks[it][5::]
               var_type = toks[it+2][0:3]
               var_value = toks[it+2][4::]
               if(var_type == kw_str or var_type == kw_num):
                   assign_var(var_name, var_value)
               if(var_type == kw_exp):
                   assign_var(var_name, eval_expr(var_value))
               if(var_type == kw_var):
                   assign_var(var_name, get_var(var_value[1::]))    #[1::] to only send varname without the #
               it += 3


def confirm_quit():
    input("Press Enter to quit...")
    quit()

def run():
    data = open_file("test.lang")
    toks = lex(data)
    parse(toks)

run()
