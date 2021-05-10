all_magic_squares = []
magic_square = [[8, 1, 6], [3, 5, 7], [4, 9, 2]]
all_magic_squares.append(magic_square)
magic_square = [[6, 1, 8], [7, 5, 3], [2, 9, 4]]
all_magic_squares.append(magic_square)
magic_square = [[4, 9, 2], [3, 5, 7], [8, 1, 6]]
all_magic_squares.append(magic_square)
magic_square = [[2, 9, 4], [7, 5, 3], [6, 1, 8]]
all_magic_squares.append(magic_square)
magic_square = [[8, 3, 4], [1, 5, 9], [6, 7, 2]]
all_magic_squares.append(magic_square)
magic_square = [[4, 3, 8], [9, 5, 1], [2, 7, 6]]
all_magic_squares.append(magic_square)
magic_square = [[6, 7, 2], [1, 5, 9], [8, 3, 4]]
all_magic_squares.append(magic_square)
magic_square = [[2, 7, 6], [9, 5, 1], [4, 3, 8]]
all_magic_squares.append(magic_square)


def get_row(square, idx) -> list:
    return square[idx]


def get_col(square, idx) -> list:
    col = []
    for row in square:
        col.append(row[idx])
    return col


def get_diagonal(square) -> list:
    diagonal = []
    for idx in range(len(square)):
        diagonal.append(square[idx][idx])
    return diagonal


def is_magic_square(magic_square) -> bool:
    magic_sum = 15
    for idx in range(len(magic_square)):
        if sum(get_row(magic_square, idx)) != magic_sum:
            return False

    for idx in range(len(magic_square[0])):
        if sum(get_col(magic_square, idx)) != magic_sum:
            return False

    if sum(get_diagonal(magic_square)) != magic_sum:
        return False
    return True


def evaluate(square):
    totals = []
    for magic_square in all_magic_squares:
        total = 0
        for m_row, s_row in zip(magic_square, square):
            for m_col, s_col in zip(m_row, s_row):
                if m_col != s_col:
                    total += abs(m_col - s_col)
        totals.append(total)
    return min(totals)
