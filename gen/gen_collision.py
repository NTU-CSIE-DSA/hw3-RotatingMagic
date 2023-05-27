m = int(1e9+7)
# m = 97
d = {}
p = "A"*6
car = 26

def hsh(ss):
    hh = 0
    for i in ss:
        hh = (hh *car + ord(i) - ord('A'))%m
    return hh
hp = hsh(p)
cur = [0] * 6
for i in range(car**6):
    j = 0
    cur[0] += 1
    while cur[j] >= car:
        cur[j] = 0
        cur[j+1] +=1
        j+=1
    curs = [chr(c + ord('A')) for c in cur]
    tmp = hsh(curs)
    if tmp in d:
        d[tmp].append("".join(curs))
        print(d[tmp])
        exit(0)
    else:
        d[tmp] = ["".join(curs)]