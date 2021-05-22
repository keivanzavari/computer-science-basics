# 2’s complement of a binary number is 1 added to the 1’s complement of the binary number.
# Note that 1’s complement is simply flip of given binary number.
#
# 2's complement of "0111" is  "1001"
# 2's complement of "1100" is  "0100"

# Algorithm:
# Step 1:  Start from the Least Significant Bit and traverse left until you find a 1.
#  Until you find 1, the bits stay the same
# Step 2: Once you have found 1, let the 1 as it is and now
# Step 3: Flip all the bits left to the 1.


def flip(char: str) -> str:
    return '1' if (char == '0') else '0'


# Print 1's and 2's complement of
# binary number represented by "bin"
def print_one_and_twos_complement(binary_num):

    n = len(binary_num)
    ones = ""
    twos = ""

    # for ones complement flip every bit
    for i in range(n):
        ones += flip(binary_num[i])

    # for two's complement go from right
    # to left in ones complement and if
    # we get 1 make, we make them 0 and
    # keep going left when we get first
    # 0, make that 1 and go out of loop
    ones = list(ones.strip(""))
    twos = list(ones)
    for i in range(n - 1, -1, -1):

        if (ones[i] == '1'):
            twos[i] = '0'
        else:
            twos[i] = '1'
            break

    i -= 1
    # If No break : all are 1 as in 111 or 11111
    # in such case, add extra 1 at beginning
    if (i == -1):
        twos.insert(0, '1')

    print(f"1's complement: ", *ones, sep="")
    print(f"2's complement: ", *twos, sep="")


num_in_str = "00100100"
print_one_and_twos_complement(num_in_str)
num = -int(num_in_str, 2)
# works for negative.
binary_1 = format((1 << 8) + num, "08b")

# works for both negative and positive.
binary_2 = bin(((1 << 8) - 1) & num)
