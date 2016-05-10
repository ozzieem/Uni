__author__ = 'Ozziee'
#Özgun M
#Medlaborant Duy Dinh

from logic import *

print("Well met!")
print("")

#UPPGIFT 1
print("Satslogik Uppgift 1:".upper())

a = (rainy | windy)
b = (rainy > windy)
c = (rainy > wet) & (~rainy > ~wet)
d = (rainy | windy) & (rainy > wet) & (windy > cold)
e = ((rainy & windy) == snow) & winter & (~snow | ~winter)
f = (rainy == windy) & (winter | summer) & (spring | summer) & (~winter > ~windy)
g = (wet > sunny) & (summer | spring) & (snow == winter)

print("Uppg. 1:", val(a,[rainy]), "if rainy is true.")
print("Uppg. 2:", val(b,[windy]), "if windy is true.")
print("Uppg. 3:", val(c,[rainy,wet]), "if rainy and wet are true.")
print("Uppg. 4:", val(d,[rainy,wet]), "if rainy and wet are true.")
print("Uppg. 5:", val(e,[rainy,winter]), "if rainy and winter are true.")
print("Uppg. 6:", val(f,[summer]), "if summer is true.")
print("Uppg. 7:", val(g,[summer]), "if summer is true.")
print("")

#UPPGIFT 2
print("Satslogik Uppgift 2:".upper())

a2 = (~winter == (summer|spring|autumn)) & (~summer == (winter|spring|autumn)) & (~spring == (winter|summer|autumn)) & (~autumn == (winter|summer|spring))
b2 = (snow > winter) & (rainy > winter) & ~(rainy > snow)
c2 = (snow > cold) & (rainy > ~cold)


print("Uppg. 1", val(a2,[summer]),"- Gäller bara summer")
print("Uppg. 1", val(a2,[summer,winter]),"- Gäller summer och winter")
print("Uppg. 1", val(a2,[summer,winter,spring]),"- Gäller summer, winter och spring")
print("Uppg. 2:", val(b2,[rainy,winter]),"- Gäller rainy och winter")
print("Uppg. 2:", val(b2,[rainy,snow]),"- Gäller rainy och snow")
print("Uppg. 3:", val(c2,[rainy, cold]),"- Gäller rainy och cold") #Går även med bara cold.
print("")


#UPPGIFT 3
print("Predikatlogik Uppgift 3:".upper())

a3 = forall(x, hungry(x) > ~happy(x))
b3 = exists(x, hungry(x) & ~happy(x))
c3 = ~hungry(fido) & forall(x,~hungry(x) > happy(x))
d3 = hungry(fido) & happy(cleo) & forall(x,~hungry(x) > happy(x))
e3 = exists(x, hungry(x) & ~happy(x) & ~(x == fido))
f3 = exists(x, loves(x,john) & loves(john,x))
g3 = exists(x, loves(x,john)) & forall(x,forall(y, (loves(x,y) & loves(y,x)) > (happy(x) & happy(y))))
h3 = loves(john, mary) & hates(mary,john) & forall(x, exists(y,(loves(x,y) & hates(y,x)) > ~happy(x)))
i3 = human(john) & human(bob) & forall(x,human(x) > exists(y, (dog(y) | cat(y)) & owns(x,y)))
j3 = exists(x,dog(x)) & exists(y,cat(y)) & exists(z,female(z)) & exists(u,male(u)) & forall(x,male(x) | female(x))


f1 = dog(fido) & hungry(fido)
f2 = forall(x,happy(x))
val(f1, [dog(fido),cat(cleo),hungry(fido),happy(cleo)], [fido, cleo])

print("Uppg. 1:", val(a3,[dog(fido), hungry(fido), sad(fido)],[fido]))
print("Uppg. 2:", val(b3,[human(mary), hungry(mary), sad(mary)], [mary]))
print("Uppg. 3:", val(c3,[dog(fido), happy(fido)],[fido]))
print("Uppg. 4:", val(d3,[dog(fido), hungry(fido), sad(fido), cat(cleo), happy(cleo)],[fido,cleo]))
print("Uppg. 5:", val(e3,[cat(cleo), hungry(cleo), sad(cleo)],[cleo]))
print("Uppg. 6:", val(f3,[loves(john,mary),loves(mary,john)],[john,mary]))
print("Uppg. 7:", val(g3,[human(john),human(mary),loves(john,mary),loves(mary,john), happy(john),happy(mary)],[john,mary]))
print("Uppg. 8:", val(h3,[human(john), human(mary),happy(john),happy(mary), loves(john,mary), sad(mary),sad(john), hates(mary,john)],[john,mary]))
print("Uppg. 9:", val(i3,[human(john),human(bob),dog(fido),cat(cleo),owns(bob,fido),owns(john,cleo)],[bob,john,cleo,fido]))
print("Uppg. 10:", val(j3,[dog(fido),cat(cleo),female(cleo),female(fido),male(fido),male(cleo)],[cleo,fido]))
print("")


#UPPGIFT 4
print("Predikatlogik Uppgift 4:".upper())

c1 = exists(x, dog(x) & hungry(x))
c2 = forall(x, dog(x) > hungry(x))

print("Korrekta uttryck:")
print("exists(x, dog(x) & hungry(x))", val(c1,[hungry(x)],[x]))
print("forall(x, dog(x) > hungry(x))",val(c2,[hungry(y)],[y]))
print("")

d1 = exists(x, dog(x) > hungry(x))
d2 = forall(x, dog(x) & hungry(x))

print("Felaktiga uttryck::")
print("exists(x, dog(x) > hungry(x))", val(d1,[hungry(x)],[x]))
print("forall(x, dog(x) & hungry(x))", val(d2,[hungry(y)],[y]))
print("")


#UPPGIFT 5
print("Relationsdrama uppgift 5".upper())
print("")

#print-variabler
__print_r_ = "Reflexive relations?:"
__print_s_ = "Symmetrical relations?:"
__print_t_ = "Transitive relations?:"


#Knows relationer
print("Knows-relationer:")

i = [knows(bob,john),knows(john,bob),knows(mary,alice),knows(alice,mary)]
t = [bob,john,mary,alice]

print("Are there any :")
r1 = forall(x, knows(x,x))
print(__print_r_, val(r1,i,t))
#Ingen reflexiv relation

r2 = forall(x, forall(y, knows(x,y) > knows(y,x)))
print(__print_s_, val(r2,i,t))
#bob,john - john,bob :: alice,mary - mary,alice

r3 = forall(x, forall(y, forall(z, knows(x,y) & knows (y,z) > knows(x,z))))
print(__print_t_, val(r3,i,t))
#Ingen transitiv relation

print("")


#Loves relationer
print("Loves-relationer:")

k = [loves(bob,mary),loves(john,john),loves(mary,alice),loves(bob,alice)]
g = [bob,john,mary,alice]

print("Are there any :")
l1 = forall(x, loves(x,x))
print(__print_r_, val(l1, k,g))
#John,John är en reflexitivitet

l2 = forall(x, forall(y, loves(x,y) > loves(y,x)))
print(__print_s_, val(l2, k,g))
#Finns ingen symmetrisk relation

l3 = forall(x, forall(y, forall(z, loves(x,y) & loves (y,z) > loves(x,z))))
print(__print_t_, val(l3, k,g))
#bob,mary och bob,alice





















