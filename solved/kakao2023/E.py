value = ["" for i in range(51*51)]
cnt = 0
s = [[0 for i in range(51)] for j in range(51)]
first = [[0 for i in range(51)] for j in range(51)]
for i in range(51):
    for j in range(51):
        s[i][j] = cnt
        cnt += 1
cnt = 0
for i in range(51):
    for j in range(51):
        first[i][j] = cnt
        cnt += 1

def update(r, c, v):
    value[s[r][c]] = v

def merge(r1, c1, r2, c2):
    new_value = value[s[r1][c1]]
    if new_value == "":
        new_value = value[s[r2][c2]]
    mg = s[r2][c2]
    for i in range(51):
        for j in range(51):
            if mg == s[i][j]:
                value[s[i][j]] = ""
                s[i][j] = s[r1][c1]
    value[s[r1][c1]] = new_value

def unmerge(r, c):
    new_value = value[s[r][c]]
    umg = s[r][c]
    for i in range(51):
        for j in range(51):
            if umg == s[i][j]:
                s[i][j] = first[i][j]
                value[first[i][j]] = ""
    value[s[r][c]] = new_value

def pnt(r, c):
    if value[s[r][c]] == "":
        return "EMPTY"
    return value[s[r][c]]

def solution(commands):
    answer = []
    for i in commands:
        here = i.split()
        if here[0] == "UPDATE":
            if len(here) == 4:
                r = int(here[1])
                c = int(here[2])
                v = here[3]
                update(r, c, v)
            else:
                value1 = here[1]
                value2 = here[2]
                for i in range(len(value)):
                    if value[i] == value1:
                        value[i] = value2
        elif here[0] == "MERGE":
            merge(int(here[1]), int(here[2]), int(here[3]), int(here[4]))
        elif here[0] == "UNMERGE":
            unmerge(int(here[1]), int(here[2]))
        elif here[0] == "PRINT":
            answer.append(pnt(int(here[1]), int(here[2])))
    return answer