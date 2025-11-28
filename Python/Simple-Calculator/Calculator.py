from cmath import *

def addfunc():
    a = float(input('Enter the first number: '))
    b = float(input('Enter the second number: '))
    return print('The sum of',a,'and',b,'is',a+b)

def subfunc():
    a = float(input('Enter the first number: '))
    b = float(input('Enter the second number: '))
    return print('The difference of',a,'and',b,'is',a-b)

def mulfunc():
    a = float(input('Enter the first number: '))
    b = float(input('Enter the second number: '))
    return print('The product of',a,'and',b,'is',a*b)

def divfunc():
    a = float(input('Enter the first number: '))
    b = float(input('Enter the second number: '))
    return print('The quotient of',a,'and',b,'is',a/b)

def sqrtfunc():
    a = float(input('Enter the number: '))
    return print('The square root of',a,'is',a**0.5)

def modfunc():
    a = float(input('Enter the first number: '))
    b = float(input('Enter the second number: '))
    return print('The modulus of',a,'and',b,'is',a%b)

def powfunc():
    a = float(input('Enter the first number: '))
    b = float(input('Enter the second number: '))
    return print('The power of',a,'and',b,'is',a**b)

def facfunc():
    a = int(input('Enter the number: '))
    if a == 0:
        return print('The factorial of',a,'is 1')
    else:
        return print('The factorial of',a,'is',a*facfunc(a-1))

def sinfunc():
    a = float(input('Enter the number: '))
    return print('The sine of',a,'is',sin(a))

def cosfunc():
    a = float(input('Enter the number: '))
    return print('The cosine of',a,'is',cos(a))

def tanfunc():
    a = float(input('Enter the number: '))
    return print('The tangent of',a,'is',tan(a))

def logfunc():
    a = float(input('Enter the number: '))
    return print('The log of',a,'is',log(a,e))

def lnfunc():
    a = float(input('Enter the number: '))
    return print('The log of',a,'is',log(a,e))

def expfunc():
    a = float(input('Enter the number: '))
    return print('The exponential of',a,'is',exp(a))

def menuchoice():
    choice = input("Enter your choice: ")
    return choice

def menu(choice):
    if choice == '1':
        addfunc()
    elif choice == '2':
        subfunc()
    elif choice == '3':
        mulfunc()
    elif choice == '4':
        divfunc()
    elif choice == '5':
        sqrtfunc()
    elif choice == '6':
        modfunc()
    elif choice == '7':
        powfunc()
    elif choice == '8':
        facfunc()
    elif choice == '9':
        sinfunc()
    elif choice == '10':
        cosfunc()
    elif choice == '11':
        tanfunc()
    elif choice == '12':
        logfunc()
    elif choice == '13':
        lnfunc()
    elif choice == '14':
        expfunc()
    else:
        print('Invalid choice')

while True:
    print("""
    ###############################################################################
    Welcome to the calculator!
    ###############################################################################
    Please choose one of the following options:

    1. Addition
    2. Subtraction
    3. Multiplication
    4. Division
    5. Square root
    6. Modulus
    7. Power
    8. Factorial
    9. Sine
    10. Cosine
    11. Tangent
    12. Log
    13. Natural Log
    14. Exponential
    15. Exit
    ###############################################################################
    """)
    choice = menuchoice()
    if choice == '15':
        print("thank you for using the calculator!")
        break
    elif choice == '1' or choice == '2' or choice == '3' or choice == '4' or choice == '5' or choice == '6' or choice == '7' or choice == '8' or choice == '9' or choice == '10' or choice == '11' or choice == '12' or choice == '13' or choice == '14':
        menu(choice)
    else:
        print('Invalid choice')
    print("\n")
    again = input("Do you want to use the calculator again? (y/n): ")
    if again == 'n':
        print("thank you for using the calculator!")
        break
    elif again == 'y':
        continue
    else:
        print("Invalid choice, please try again")
        continue