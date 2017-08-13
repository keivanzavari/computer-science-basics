# Sum of prime numbers
# The primality test is done based on the method described
# https://en.wikipedia.org/wiki/Primality_test
# which looks to numbers less than square root of 'n'

# The problem is also presented on Project Euler 
# https://projecteuler.net/problem=10

def isPrime(n):
    if (n <= 1):
        return False
    elif (n <= 3):
        return True
    elif (n % 2 == 0) | (n % 3 == 0):
        return False

    i = 5
    while (i * i <= n):
        if (n % i == 0) | (n % (i + 2) == 0):
            return False
        i += 6
    return True


n_max = 2e6
sum = 0
n = 1

while (n != n_max):
    if (isPrime(n)):
        # print n
        sum += n
    n+=1

print 'sum: ', sum