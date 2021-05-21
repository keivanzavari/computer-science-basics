def are_almost_equal(val1: float, val2: float, absolute_error: float = 1e-6) -> bool:
    return (abs(val1 - val2) <= abs(absolute_error))
