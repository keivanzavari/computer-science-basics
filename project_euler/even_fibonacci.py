# By considering the terms in the Fibonacci sequence whose values do not 
# exceed four million, 
# find the sum of the even-valued terms.

# project euler prob 2

ni = [1,2]
while (ni[-1]< 1e7):
    ni.append(ni[-1] + ni[-2]);

sum_even = 0
for num in ni:
    if (num%2 ==0):
        sum_even += num;

print ni

print sum_even
