#!/usr/bin/python3

from socket import getnameinfo


def getNoteName(index):
    note = ""
    octave = 0
    nIndex = index % 12

    # Get note name based on index
    if nIndex == 1:
        note = "A"
    elif nIndex == 2:
        note = "Bb"
    elif nIndex == 3:
        note = "B"
    elif nIndex == 4:
        note = "C"
    elif nIndex == 5:
        note = "Db"
    elif nIndex == 6:
        note = "D"
    elif nIndex == 7:
        note = "Eb"
    elif nIndex == 8:
        note = "E"
    elif nIndex == 9:
        note = "F"
    elif nIndex == 10:
        note = "Gb"
    elif nIndex == 11:
        note = "G"
    elif nIndex == 0:
        note = "Ab"
    

    # Get octave by index range
    if index in range(1,4):
        octave = 0
    elif index in range(4, 16):
        octave = 1
    elif index in range(16, 28):
        octave = 2
    elif index in range(28, 40):
        octave = 3
    elif index in range(40, 52):
        octave = 4
    elif index in range(52, 64):
        octave = 5
    elif index in range(64, 76):
        octave = 6
    elif index in range(76, 88):
        octave = 7
    else:
        octave = 8
    
    return "{}{}".format(note, octave)


def getFrequency(index):
    fact = float(index - 49) / 12.0
    freq = (2.0 ** fact) * 440.0

    return float(freq)

def formatString(value):
    return ", {{{}, {}f}}".format(value[0], value[1])

def firstString(value):
    return "    {{{}, {}f}}".format(value[0], value[1])



# Main
print("Calculating Frequencies for different notes")
res = []

for i in range(1, 89):
    res.append([getNoteName(i), getFrequency(i)])


print("Formatting as C++ std::map\n\n")

print("static const std::map<Note, float> frequencies = {")
print(firstString(res[0]), formatString(res[1]), formatString(res[2]), ",\n", sep="")

for i in range(3, 87, 12):
    print(firstString(res[i]), formatString(res[i+1]), formatString(res[i+2]), formatString(res[i+3]), ",", sep="")
    print(firstString(res[i+4]), formatString(res[i+5]), formatString(res[i+6]), formatString(res[i+7]), ",", sep="")
    print(firstString(res[i+8]), formatString(res[i+9]), formatString(res[i+10]), formatString(res[i+11]), ",", sep="")
    print()

print(firstString(res[87]))
print("};")