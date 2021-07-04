# If A is a (p x q) matrix and B is a (q x r) matrix, the resulting matrix C is a (p x r) matrix.
# The time to compute C is dominated by the number of scalar multiplications, which is p.q.r.

# We are given a sequence (chain) [A1 A2 ... An]
# of n matrices to be multiplied, and we wish to compute the product
# A1 . A2 . ... . An
# Knowing that matrix multiplication is associative, what is the best way of parenthesization?
# Or in other words: What is the least computationaly expensive way of doing this multiplication?
dimensions = [(30, 35), (35, 15), (15, 5), (5, 10), (10, 20), (20, 25)]
