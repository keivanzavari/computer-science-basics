# There exists exactly one Pythagorean triplet for which a + b + c = 1000.
# Find the product abc.

# project euler prob 9

# there are primitive pythagorean triplets and their multiples
# (3,4,5) and (5,12,13) are primitive
# but (6,8,10) are not

# there is a formula for generating triplets (does not generate all of them)
# a = ( m2 – n2 ) 
# b = (2 m n)
# c = ( m2 + n2 )

# let's hope it is the case in this problem. 
# therefore we have
# a+b+c = 2m^2 + 2mn 

m = 1
while m<250:
    m +=1
    a = 500 - m**2
    if (a%m == 0):
    	# so if a is divisible by m, then we are half way
        # print "m: ", m
        n = a/m
        if (m>n & n>0):
            print "n: ", n
            a = (m**2 + n**2)
            b = 2*m*n
            c = m**2 - n**2
            print "abc: ", a, b, c
            print "sum: ", a+b+c
            print "prod: ", a*b*c
