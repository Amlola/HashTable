with open("THE_FIVE_ORANGE_PIPS.txt", 'r') as file: 
    lines = [line for line in file]

file.close()

in_file = open("test_file.txt", "w")

punctuations = "';,.!@#$%^&*()_-+=?/|\"\<>:}{[]~`0123456789"

a = set()

def DeleteMarks(line):
    new_str = ""
    for i in line:
        if not i in punctuations:
            new_str += i
        else:
            new_str += ' '
    return new_str


for i in range(len(lines)):
    if not lines[i]:
        continue

    else:
        words = DeleteMarks(lines[i]).split()
        for j in words:
            a.add(j.lower())
            j = str(len(j)) + ' ' + j.lower() + '\n'
            in_file.write(j)

in_file.close()
print(len(a))