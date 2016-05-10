# Programmerad av Özgun M
# Datum: Någon gång i september/oktober 2014


def area(l,b):
    return l*b

def volume(l,b,h):
    return l*b*h

print("1. Area")
print("2. Volume")
print("3. Both")

choice = int(input("Which would you like to calculate? Enter with a number."))

if choice == 1:
    l = int(input("What is the length?"))
    print("The entered length is ", l)
    
    b = int(input("What is the width?"))
    print("The width is ", b)
    
    print("The entered area is ", l,"*", b,"=", area(l,b))

elif choice == 2:
    l = int(input("What is the length?"))
    print("The entered length is ", l)
    
    b = int(input("What is the width?"))
    print("The entered width is ", b)

    h = int(input("What is the height?"))
    print("The entered height is ", h)
    
    print("The volume is ", l,"*",b,"*",h,"=", volume(l,b,h))

else:
    l = int(input("What is the length?"))
    print("The length is ", l)
    
    b = int(input("What is the width?"))
    print("The width is ", b)

    h = int(input("What is the height?"))
    print("The height is ", h)

    print("The area is ", l,"*", b,"=", area(l,b)," and the volume is ", l,"*",b,"*",h,"=", volume(l,b,h))
