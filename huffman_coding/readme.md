
As a common convention, bit *0* represents following the left child and bit *1* represents following the right child.

### implementation using a priority queue
A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.

A user-provided Compare can be supplied to change the ordering, e.g. using `std::greater<T>` would cause the smallest element to appear as the `top()`.

<img src="https://upload.wikimedia.org/wikipedia/commons/a/a0/Huffman_coding_visualisation.svg" width="50%">

Also look [here](http://rosettacode.org/wiki/Huffman_coding#C.2B.2B)
and the [wikipedia article](https://en.wikipedia.org/wiki/Huffman_coding)
