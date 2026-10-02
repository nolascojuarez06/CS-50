from cs50 import get_int

card = get_int("Number: ")
string_card = str(card)

length = len(string_card)
total = 0

for i in range(length - 2, -1, -2):
    digit = int(string_card[i]) * 2
    if digit < 10:
        total += digit
    else:
        total += (digit // 10) + (digit % 10)

for j in range(length - 1, -1, -2):
    total += int(string_card[j])

if total % 10 == 0:
    if (length == 15 and string_card[0] == '3') and (string_card[1] == '4' or string_card[1] == '7'):
        print("AMEX")
    elif (length == 13 or length == 16) and (string_card[0] == '4'):
        print("VISA")
    elif (length == 16 and string_card[0] == '5') and (string_card[1] >= '1' and string_card[1] <= '5'):
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")
