arr = [1, 2, 3, 4, 5, 6]
n = 2
# rotate array left n times.
# One left rotation turns [1,2,3] to [2,3,1].

# change indices
# [0,1,2,3] -> [1,2,3,0]
# then construct a new array from the new indices
# if number of rotations is the same as the array length we get the same array.
# therefore indices from n until -2 do not change.
# we get n until -2 and then 0,1,2,n-1 follows.

# indices become [n, n+1, ..., -2, 0, 1, ..., n-1]
# -2 is the one element before last len - 2

rotated_arr = []
for i in range(n, len(arr)):
    rotated_arr.append(arr[i])
for i in range(0, n):
    rotated_arr.append(arr[i])

print(rotated_arr)
