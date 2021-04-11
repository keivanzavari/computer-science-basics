from typing import Any


class PairNode:
    def __init__(self, key: Any, value: Any) -> None:
        self.k = key
        self.v = value
        self.next: PairNode = None

    def __repr__(self):
        if self.next is None:
            return f"({self.k}, {self.v}) -> ()"
        return f"({self.k}, {self.v}) -> {self.next.__repr__()}"


class LinkedListIterator:
    def __init__(self, head: PairNode) -> None:
        self.current = head

    def __iter__(self) -> "LinkedListIterator":
        return self

    def __next__(self) -> PairNode:
        if self.current is None:
            raise StopIteration
        else:
            item = self.current
            self.current = self.current.next
            return item


class LinkedList:
    def __init__(self, key: Any, value: Any):
        self.head = PairNode(key, value)

    def __repr__(self):
        return f"{self.head.__repr__()}"

    def __iter__(self):
        return LinkedListIterator(self.head)

    def insert_end(self, key: Any, value: Any) -> None:
        new_node = PairNode(key, value)
        end = self.head
        while end.next is not None:
            end = end.next
        end.next = new_node

    def insert_begin(self, key: Any, value: Any) -> None:
        begin = PairNode(key, value)
        begin.next = self.head
        self.head = begin

    def delete(self, key: Any) -> bool:
        if self.head.k == key:
            self.head = self.head.next
            return True
        node = self.head
        next_node = node.next
        prev_node = node
        while True:
            if node.k == key:
                prev_node.next = next_node
                return True
            if node is None or node.next is None:
                raise KeyError(f"Key {key} doesn't exist.")

            prev_node = node
            node = node.next
            next_node = node.next

    def search(self, key: Any) -> Any:
        node = self.head
        while True:
            if node.k == key:
                return node.v
            if node is None or node.next is None:
                raise KeyError(f"Key {key} doesn't exist.")

            node = node.next


if __name__ == '__main__':
    p = LinkedList(1, 2)
    p.insert_end(3, 4)
    p.insert_begin(6, 7)
    for item in p:
        print(f"({item.k}, {item.v})")

    p.delete(6)
