

ar = [1,2,3,1,2,3,4]
# Each number in the array represents the color.
# Find the number of matching socks.
sorted_list = sorted(ar)
min_color = sorted_list[0]
max_color = sorted_list[-1]
tot_num_pairs = 0
for color in range(min_color, max_color+1):
    num_occurances = sorted_list.count(color)
    num_pairs = num_occurances//2
    tot_num_pairs += num_pairs

print(tot_num_pairs)
