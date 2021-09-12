string = "absadefa"
n = 10
# A string is repeated infitie times.
# We consider the first n characters of this string
# count the number of occurances of a char

# For large n numbers we simply cannot create the large string. That's why we have to go around it.
char_to_look_for = "a"
count = string.count(char_to_look_for)
num_repetitions = n // len(string) + 1
num_occurances = num_repetitions * count
num_extra_to_cut = len(string) - (n % len(string))
num_extra_counted = string[-num_extra_to_cut:].count(char_to_look_for)
num_occurances -= num_extra_counted

print(num_occurances)
