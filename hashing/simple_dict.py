from typing import Any, Optional
from linked_list import LinkedList
# Pre-hash from given keys to integer keys

# hash the integer keys to an index in the hash table of size m
# why should these two be separate?


def init_table(size: int) -> list:
    t = []
    for _ in range(size):
        t.append(None)
    return t


# Another way is to implement with open addressing
# https://en.wikipedia.org/wiki/Open_addressing
class DictWithChaining:
    def __init__(self):
        self.table_size = 2
        self.num_items = 0
        self.table = init_table(self.table_size)

    def __repr__(self):
        ret = "-----------\n"
        for row in self.table:
            if row is None:
                ret += "O\n"
            else:
                ret += row.__repr__() + "\n"
        ret += "-----------\n"
        return ret

    def get_index(self, k: Any, size: int) -> int:
        hk = hash(k)
        index = hk % size
        return index

    def generic_insert(self, generic_table: list, k: Any, v: Any, size: int) -> bool:
        idx = self.get_index(k, size)
        inserted = False
        if generic_table[idx] is None:
            generic_table[idx] = LinkedList(k, v)
            inserted = True
        else:
            # Unique keys
            if generic_table[idx].head.k == k:
                generic_table[idx].head.v = v
            else:
                generic_table[idx].insert_begin(k, v)
                inserted = True
        return inserted

    def insert(self, k: Any, v: Any):
        inserted = self.generic_insert(self.table, k, v, self.table_size)
        if inserted:
            self.num_items += 1
        self.maybe_grow()

    # TODO implement delete and consider the cases where there was a collision.
    def delete(self, k: Any):
        idx = self.get_index(k, self.table_size)
        self.table[idx] = None

    def search(self, k: Any):
        idx = self.get_index(k, self.table_size)
        # search should make sure to return the correct value if
        # the index has more than one element.
        return self.table[idx].search(k)

    def resize(self, new_size: int) -> None:
        print(f"resize is called to new size {new_size}")
        # resize the table, either grow or shrink.
        # after resizing, we'll need to rehash
        new_table = init_table(new_size)
        for item in self.table:
            if item is not None:
                for pair in item:
                    self.generic_insert(new_table, pair.k, pair.v, new_size)

        self.table = new_table
        self.table_size = new_size

    def maybe_grow(self) -> None:
        if self.num_items >= self.table_size:
            new_table_size = self.table_size * 2
            self.resize(new_table_size)

    def mayb_shrink(self) -> None:
        if self.table_size >= (self.num_items / 4):
            new_table_size = int(self.table_size / 2)
            self.resize(new_table_size)


if __name__ == '__main__':
    # keys = ["a", "b", "c", "1", "2", "3"]
    # m = 16
    # for key in keys:
    #     hk = hash(key)
    #     index = hk % m
    #     print(f"hashed {hk}, index {index}")
    d = DictWithChaining()
    d.insert("k1", "v1")
    d.insert("k2", "v2")
    d.insert("k3", "v3")
    d.insert("k3", "v33")
    assert d.num_items == 3
    assert d.num_items < d.table_size
    d.insert("k4", "v4")

    # d.insert(2, "v2")
    # d.insert("asd", "v2_asd")
    # d.insert("adb", "v2_adb")
    print(d)

    # v = d.search("adb")
    # assert v == "v2_adb"
