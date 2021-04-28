l = []

def combination(start, rest, k):
    if k == 0:
        return start
    else:
        global l
        for i in range(len(rest)):
            res = combination(start + rest[i], rest[i + 1:], k - 1)
            if k == 1:
                l.append(res)
    return l


if __name__ == '__main__':
    res = combination("", "12345", 3)
    print(res)
