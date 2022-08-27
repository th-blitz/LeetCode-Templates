from functools import cache

@cache
def factorial(n):
    if n <= 1:
        return 1
    return n * factorial(n - 1)

def permutation(n, r):
    return factorial(n) / factorial(n - r) 

def birthday_probability(n, r):
    return 1 - permutation(n, r) / n**r


print(birthday_probability(73, 10))
