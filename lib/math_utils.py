from functools import singledispatch


@singledispatch
def are_almost_equal(arg_1, arg_2, absolute_error: float = 1e-6) -> bool:
    print(type(arg_1), type(arg_2))
    raise NotImplementedError("Not implemented")


@are_almost_equal.register(float)
def _(arg_1: float, arg_2: float, absolute_error: float = 1e-6) -> bool:
    return (abs(arg_1 - arg_2) <= abs(absolute_error))


@are_almost_equal.register
def _(arg_1: int, arg_2: float, absolute_error: float = 1e-6) -> bool:
    return arg_1 == round(arg_2)


@are_almost_equal.register
def _(arg_1: float, arg_2: int, absolute_error: float = 1e-6) -> bool:
    return arg_2 == round(arg_1)


@are_almost_equal.register(tuple)
@are_almost_equal.register(list)
def _(arg_1, arg_2, absolute_error: float = 1e-6) -> bool:
    for val1, val2 in zip(arg_1, arg_2):
        if not are_almost_equal(val1, val2):
            return False
    return True
