a = int(input("Enter A Number"))
b = int(input("Enter A Number"))

sum = 0
while b>0:
    print("a:",a)
    print("b:",b)
    if b %2 == 1:
        sum = sum+a
    a = 2*a
    b = b//2
print(sum)