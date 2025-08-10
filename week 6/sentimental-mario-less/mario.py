


while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
    except ValueError:
        pass

for i in range(0, height):
    for j in range (0, height - i - 1):
        print(" ", end="")
    for n in range (0, i + 1):
        print("#", end="")
    print()






