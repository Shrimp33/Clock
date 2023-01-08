import itertools

def get_gears(goal, factors):
    combinations = []
    for i in range(1, len(factors) + 1):
        combinations += list(itertools.permutations(factors, i))
    # Find the best combination by multiplying the factors together
    best = 0
    best_combination = []
    for combination in combinations:
        product = 1
        for factor in combination:
            product *= factor
        if abs(product - goal) < abs(best - goal):
            best = product
            best_combination = combination
    return best_combination, best