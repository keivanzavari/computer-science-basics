#include <iostream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>

// As a common convention, bit '0' represents following the left child and bit '1' represents following the right child.

/* left shift operator shift lhs CHAR_BIT times to the left, hence multiplying
with 2^8 (on most computers) which is 256, as there are 256 unique symbols */
const int UniqueSymbols = 1 << CHAR_BIT;
const char* SampleString = "this is an example for huffman encoding";

typedef std::vector<bool> HuffCode;
typedef std::map<char, HuffCode> HuffCodeMap;

class INode
{
public:
    const int weight;

    virtual ~INode() {}

protected:
    INode(int f) : weight(f) {}
    bool operator>(const INode& rhs)
    {
      return this->weight > rhs.weight;
    }
};

class InternalNode : public INode
{
public:
    INode *const left;
    INode *const right;

    InternalNode(INode* c0, INode* c1) :
    INode(c0->weight + c1->weight),
    left(c0),
    right(c1) {}
    ~InternalNode()
    {
        delete left;
        delete right;
    }
};

class LeafNode : public INode
{
public:
    const char c;

    LeafNode(int f, char c) : INode(f), c(c) {}
};

struct NodeCmp
{
    bool operator()(const INode* lhs, const INode* rhs) const
    {
        return lhs->weight > rhs->weight;
    }
};

INode* BuildTree(const int (&frequencies)[UniqueSymbols])
{

    // declare priority queue as: <class, container, comparison function>
    // comparison function could also simply be std::less of std::greater
    // if the class has the necessary overloading for '>' or '<'
    // in this case we are using a predicate NodeCmp
    std::priority_queue<INode*, std::vector<INode*>, NodeCmp> trees;

    // Create a leaf node for each symbol and add it to the priority queue.
    for (int i = 0; i < UniqueSymbols; ++i)
    {
        if(frequencies[i] != 0)
            trees.push(new LeafNode(frequencies[i], (char)i));
    }

    // now sort the letters by increasing frequency and build a partial tree
    while (trees.size() > 1)
    {
        // take the two nodes of highest priority
        INode* child_right = trees.top();
        trees.pop();

        INode* child_left = trees.top();
        trees.pop();

        // create a new internal node with these two nodes and frequency
        // equal to the sum of the two nodes
        INode* parent = new InternalNode(child_right, child_left);

        // add the new node to the queue
        trees.push(parent);
    }

    // the remaining node is now the root node
    return trees.top();
}

/**
* given the root node of a tree with sorted nodes, this function recursivey
* traverses the tree and makes up the binary code for each character
* the result is then placed in a hash map of the character as key and
* the binary code as the value
*/
void GenerateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& out_codes)
{
    if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
    {
        // when we reach a leaf node from the top:
        // insert the prefix as value and the character as key
        // this is equal to insert command of a hash map
        out_codes[lf->c] = prefix;
    }
    else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
    {
        // when we are still in internal nodes, have a look at the right and left
        // then choose to add zero or one as prefix.
        // as a common convention, bit '0' represents following the left child
        // and bit '1' represents following the right child.
        HuffCode left_prefix = prefix;
        left_prefix.push_back(0);
        GenerateCodes(in->left, left_prefix, out_codes);

        HuffCode right_prefix = prefix;
        right_prefix.push_back(1);
        GenerateCodes(in->right, right_prefix, out_codes);
    }
}

int main()
{
    // Build weight table
    int frequencies[UniqueSymbols] = {0};
    const char* ptr = SampleString;
    while (*ptr != '\0') {
        ++frequencies[*ptr++];
    }

    // frequencies contains both the characters and their frequency of appearance
    // therefore tree can be built from one array
    INode* root = BuildTree(frequencies);

    HuffCodeMap codes;
    GenerateCodes(root, HuffCode(), codes);
    delete root;

    // print the characters & the binary codes
    for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
    {
        std::cout << it->first << " ";
        std::copy(it->second.begin(), it->second.end(),
                  std::ostream_iterator<bool>(std::cout));
        std::cout << std::endl;
    }
    return 0;
}
