from process import get_gears
# given a list of factors and a goal, find the best combination of factors


def spares():
    factors = []
    while True:
        factor = input("Spares: ")
        if factor == "":
            break
        times = int(input("x: "))
        factor = float(factor)
        for i in range(times):
            factors.append(factor)
    return factors

def test():
    factors = spares()
    dev = []
    for i in range(10, 30):  # Regional test
        i = i / 8
        res, diff = get_gears(i, factors)
        dev.append(abs(i - diff))
    print(sum(dev) / len(dev))
    print(max(dev))

def main():
    goal = float(input("Goal of gear ratio: "))
    goal = goal  # Starting gear's s/r
    factors = spares()
    res = get_gears(goal, factors)
    print(res)

test()