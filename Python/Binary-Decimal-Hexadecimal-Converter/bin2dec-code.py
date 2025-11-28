def menu(): #? create a menu function

    print("""
    #############################################
    Please choose an option:
    1. Convert Binary to Decimal
    2. Convert Decimal to Binary
    3. Convert Hexadecimal to Decimal
    4. Convert Decimal to Hexadecimal
    5. Exit
    #############################################
    """)

def bin2dec(binary): #? create a bin2dec function
    decimal = 0
    for i in range(len(binary)):
        decimal += int(binary[i]) * 2 ** (len(binary) - i - 1)
    return decimal

def dec2bin(decimal): #? create a dec2bin function
    binary = ""
    while decimal > 0:
        binary = str(decimal % 2) + binary
        decimal = decimal // 2
    return binary

def hex2dec(hexadecimal): #? create a hex2dec function
    decimal = 0
    for i in range(len(hexadecimal)):
        if hexadecimal[i] in "0123456789":
            decimal += int(hexadecimal[i]) * 16 ** (len(hexadecimal) - i - 1)
        elif hexadecimal[i] in "ABCDEF":
            decimal += 10 + ord(hexadecimal[i]) - ord("A")
        elif hexadecimal[i] in "abcdef":
            decimal += 10 + ord(hexadecimal[i]) - ord("a")
    return decimal

def dec2hex(decimal): #? create a dec2hex function
    hexadecimal = ""
    while decimal > 0:
        if decimal % 16 > 9:
            hexadecimal = chr(decimal % 16 + ord("A") - 10) + hexadecimal
        else:
            hexadecimal = str(decimal % 16) + hexadecimal
        decimal = decimal // 16
    return hexadecimal

print("Welcome to the Binary/Decimal/Hexadecimal Converter!")
while True:
    menu()
    choice = input("Please choose an option: ")
    if choice == "1":
        binary = input("Please enter a binary number: ")
        print("The decimal equivalent of", binary, "is", bin2dec(binary))
    elif choice == "2":
        decimal = int(input("Please enter a decimal number: "))
        print("The binary equivalent of", decimal, "is", dec2bin(decimal))
    elif choice == "3":
        hexadecimal = input("Please enter a hexadecimal number: ")
        print("The decimal equivalent of", hexadecimal, "is", hex2dec(hexadecimal))
    elif choice == "4":
        decimal = int(input("Please enter a decimal number: "))
        print("The hexadecimal equivalent of", decimal, "is", dec2hex(decimal))
    elif choice == "5":
        print("Thank you for using the Binary/Decimal/Hexadecimal Converter!")
        break
    else:
        print("That is not a valid option. Please try again.")
        continue
    again = input("Would you like to convert another number? (y/n): ")
    if again == "y":
        continue
    elif again == "n":
        print("Thank you for using the Binary/Decimal/Hexadecimal Converter!")
        break
    else:
        print("That is not a valid option. Please try again.")
        continue