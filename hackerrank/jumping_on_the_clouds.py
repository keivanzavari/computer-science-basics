path = [0, 0, 0, 0, 1, 0]

# You can jump 1 or 2 steps.
# You cannot land on 1.
# It is always possible to finish the game, so always start and end are 0.

# Start at 0, always try to jump 2 otherwise jump 1.
if len(path) <= 3:
    num_jumps = 1
else:
    at_end = False
    idx = 0
    current_position = idx
    num_jumps = 0
    while not at_end:
        jump_size = 2 if path[current_position + 2] == 0 else 1

        current_position += jump_size
        num_jumps += 1
        if current_position + 2 > len(path):
            at_end = True
        if current_position + 2 == len(path):
            at_end = True
            num_jumps += 1

print(num_jumps)
