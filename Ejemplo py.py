#Ejemplo py
s1 = 'String in single quotes'
s2 = "String in double quotes"
print(s1)
print(s2)
longitud=len("a string")
print(longitud)
words = ["apple", "banana", "cherry", "date"]
result = ""
for word in words:
    if len(word) %2 == 0:
        result += word[0]
else:
    result += word[-1]
print(result)

s3 = "Name\tAge\tMarks"
print(s3)
s4 = 'One\nTwo\nThree'
print(s4)

s1 = "This is " + "one complete string"
print(s1)

s2 = "www " * 5
print(s2)

s1 = "object oriented"
if "ted" in s1:    # Does "ted" exists in s1 ? T or F
    print("esta en el string\n")
else:
    print("NO esta en el string\n")

quote = "The best is the enemy of the good"
print(quote[len(quote)-1])
print(quote[len(quote)-2])
print(quote[len(quote)-3])
print(quote[len(quote)-4])
print(quote[2:10])
print(quote.upper())
print(quote.lower())