# Laborant: Özgun M
# Medlaborant: Duy D
# Datum: Någon gång under senare HT 2014

from automata import*
import re


#Uppgift 1 - Accepterande Automater:
print("Uppgift 2:".upper())

auto1_run('0')
print("")
auto1_run('1')
print("")
auto1_run('01')
print("")
auto1_run('10')
print("")
auto1_run('0001')
print("")
auto1_run('00010')
print("")
auto1_run('01010101')
print("")
print("")


#Uppgift 2 - Mealy-automater:
print("Uppgift 3:".upper())

mealy_run('0')
print("")
mealy_run('1')
print("")
mealy_run('1101')
print("")
mealy_run('001010100')
print("")
mealy_run('111111')
print("")
print("")


#Reguljära uttryck:

#Uppgift 4
print("Uppgift 4:".upper())

print("Tillhör dessa strängar språket: ((auto|flyg)(mat|pilot))?")
print("Läskautomat:", re.match('((auto|flyg)(mat|pilot))$','läskautomat')) #Ska bli falsk

print("Auto:", re.match('((auto|flyg)(mat|pilot))$','auto')) #Falsk då auto inte kan matchas ensamt när det står (auto)(x), blir isåfall autox.

print("Autopiloten:", re.match('((auto|flyg)(mat|pilot))$','autopiloten')) #Falsk då pilot inte kan matchas med piloten

print("Autopilot:", re.match('((auto|flyg)(mat|pilot))$','autopilot'),"<-- (Betyder tydligen true...)",) #Sann då auto kan matchas med pilot
print("")

#Uppgift 5
print("Uppgift 5:".upper())

#UPPGIFT A:
#Söker enbart efter extensionen .tex genom att använda specialtecknet \. och sedan bokstäverna tex.
print("Uppgift a: (Har extension .tex)".upper())
print("myfile.tex:",re.search('\.tex$','myfile.tex'))
print("yourfile:",re.search('\.tex$','yourfile'))
print("cooldoc123.tex:",re.search('\.tex$','cooldoc123.tex'))
print("textdocument.doc:",re.search('\.tex$','textdocument.doc'))
print("filebile.ini:",re.search('\.tex$','filebile.ini'))
print("")

#UPPGIFT B:
#Söker efter alla tecken i strängen utan punkt.
print("Uppgift b: (Saknar extension)".upper())
print("myfile.tex:",re.search('(^[^\.]$)','myfile.tex'))
print("yourfile:",re.search('(^[^\.])','yourfile'))
print("cooldoc123.tex:",re.search('(^[^\.]$)','cooldoc123.tex'))
print("textdocument.doc:",re.search('(^[^\.]$)','textdocument.doc'))
print("filebile.ini:",re.search('(^[^\.]$)','filebile.ini'))
print("")

#UPPGIFT C:
#Söker efter bokstäver och sedan 3 siffror.
print("Uppgift c: (Har tre avslutande siffror innan extension)".upper())
print("myfile.tex:",re.search('([a-z])*([0-9]{3})','myfile.tex'))
print("yourfile:",re.search('([a-z])*([0-9]{3})','yourfile'))
print("cooldoc123.tex:",re.search('([a-z])*([0-9]{3})','cooldoc123.tex'))
print("textdocument.doc:",re.search('([a-z])*([0-9]{3})','textdocument.doc'))
print("filebile.ini:",re.search('([a-z])*([0-9]{3})','filebile.ini'))
print("")

#UPPGIFT D:
#Söker efter enbart de extensionerna som har inlagts.
print("Uppgift d: (Har extensionerna: .txt .doc .tex. ini) ".upper())
print("myfile.tex:",re.search('\.([txt])|\.([doc])|\.([tex])|\.([ini])','myfile.tex'))
print("yourfile:",re.search('\.([txt])|\.([doc])|\.([tex])|\.([ini])','yourfile'))
print("cooldoc123.tex:",re.search('\.([txt])|\.([doc])|\.([tex])|\.([ini])','cooldoc123.tex'))
print("textdocument.doc:",re.search('\.([txt])|\.([doc])|\.([tex])|\.([ini])','textdocument.doc'))
print("filebile.ini:",re.search('\.([txt])|\.([doc])|\.([tex])|\.([ini])','filebile.ini'))
print("")


#UPPGIFT 6

print("uppgift 6:".upper())
print("Ingår de tecken nedan i de Naturliga talen?:")

print("0:",re.match('([1-9]|[0])$|([1-9])([1-9]|[0])(([1-9]|[0])*)$','0'))
print("0a:",re.match('([1-9]|[0])$|([1-9])([1-9]|[0])(([1-9]|[0])*)$','0a'))
print("04:",re.match('([1-9]|[0])$|([1-9])([1-9]|[0])(([1-9]|[0])*)$','04'))
print("15:",re.match('([1-9]|[0])$|([1-9])([1-9]|[0])(([1-9]|[0])*)$','15'))
print("1066:",re.match('((\d)*)$','1066'))
print("femton:",re.match('([1-9]|[0])$|([1-9])([1-9]|[0])(([1-9]|[0])*)$','femton'))
print("")


#UPPGIFT 7

print("uppgift 7:".upper())
###Det mesta nedan är copypaste från uppgift 6, men de artimetiska räknesymbolerna är tillagda i mitten eftersom vi söker efter strängar med två naturliga tal med bara en räknesymbol emellan.
##print("0:",re.match('(\d+)$|(((\d+)([\+]|[\-]|[\*]|[\/])(\d+)))$|((\d+)((\+)|(\-)|(\*)|(\/))(\d+)((\+)|(\-)|(\*)|(\/))(\d+))*$','0'))
##print("10:",re.match('(\d+)$|(((\d+)([\+]|[\-]|[\*]|[\/])(\d+)))$|((\d+)((\+)|(\-)|(\*)|(\/))(\d+)((\+)|(\-)|(\*)|(\/))(\d+))*$','10'))
##print("10+20:",re.match('(\d+)$|(((\d+)([\+]|[\-]|[\*]|[\/])(\d+)))$|((\d+)((\+)|(\-)|(\*)|(\/))(\d+)((\+)|(\-)|(\*)|(\/))(\d+))*$','10+20'))
##print("7*8+33/5-9:",re.match('(\d+)$|(((\d+)([\+]|[\-]|[\*]|[\/])(\d+)))$|((\d+)((\+)|(\-)|(\*)|(\/))(\d+)((\+)|(\-)|(\*)|(\/))(\d+))*$','7*8+33/5-999'))
##print("mycket:",re.match('(\d+)$|(((\d+)([\+]|[\-]|[\*]|[\/])(\d+)))$|((\d+)((\+)|(\-)|(\*)|(\/))(\d+)((\+)|(\-)|(\*)|(\/))(\d+))*$','mycket'))
##print("22*13+-4:",re.match('(\d+)$|(((\d+)([\+]|[\-]|[\*]|[\/])(\d+)))$|((\d+)((\+)|(\-)|(\*)|(\/))(\d+)((\+)|(\-)|(\*)|(\/))(\d+))*$','22*13+-4'))
##print("+32:",re.match('(\d+)$|(((\d+)([\+]|[\-]|[\*]|[\/])(\d+)))$|((\d+)((\+)|(\-)|(\*)|(\/))(\d+)((\+)|(\-)|(\*)|(\/))(\d+))*$','+32'))
##print("15+:",re.match('(\d+)$|(((\d+)([\+]|[\-]|[\*]|[\/])(\d+)))$|((\d+)((\+)|(\-)|(\*)|(\/))(\d+)((\+)|(\-)|(\*)|(\/))(\d+))*$','15+'))
##

## Uppdaterad 20/8 - 2015
##ELLER SÅ SKRIVER MAN IN ALLT I EN FOR-lOOP LIKSOM......(!!!!!1111)
reg_list = ['0','10','10+20','7*8+33/5-999','mycket','22*13+-4','+32','15+','4+5*4/5+2', '234+5-67/867*65']         
uttryck = '(\d+)$|(((\d+)([\+]|[\-]|[\*]|[\/])(\d+)))$|((\d*)((\+)|(\-)|(\*)|(\/))(\d*)((\+)|(\-)|(\*)|(\/))(\d*))*$'

for sträng in reg_list:
    svar = re.match(uttryck, sträng)
    print("Searching for", sträng, end=": ")
    if svar:
        print('Match found:', svar.group())
    else:
        print('No match')


