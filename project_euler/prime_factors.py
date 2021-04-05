# prime factors of a given number based on
# Pollard Rho algorithm, described here:
# https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm

# the problem is also presented on Project Euler
# https://projecteuler.net/problem=3


def gcd(a, b):
    while (b != 0):
        remainder = a % b
        a = b
        b = remainder

    return a


number = 600851475143
x_fixed = 2
cycle_size = 2
x = 2
factor = 1
new_number = number

print("\nThe factors are: ")

while (new_number != factor):
    while (factor == 1):
        count = 1
        # print "\n " , factor, x

        while ((count <= cycle_size) & (factor <= 1)):
            x = (x * x + 1) % number
            factor = gcd(x - x_fixed, number)
            count += 1

        cycle_size *= 2
        x_fixed = x
    print(factor)

    number /= factor
    new_number = number
    factor = 1
    x = 2
    x_fixed = 2
    cycle_size = 2
