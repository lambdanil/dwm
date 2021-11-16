import os
uinput=""
lenstr = "a"
while uinput != "q":
    uinput = input("> ")
    os.system(f"xsetroot -name {lenstr}")
    lenstr = lenstr+"a"
print(len(lenstr)-1)
