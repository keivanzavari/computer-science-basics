#include <cstdio>
#include <iostream>
#include <string>
#include <climits> // for CHAR_BIT

const int UniqueSymbols = 1 << CHAR_BIT;
const char* SampleString = "this is an example for huffman encoding";


int main() {
    // Build frequency table
    int frequencies[UniqueSymbols] = {0};
    const char* ptr = SampleString;
    while (*ptr != '\0') {
        ++frequencies[*ptr++];
    }
    printf("%d",1<<CHAR_BIT);
    printf("%d",UniqueSymbols);
    printf("\nchar: %c\n",ptr[104]);

    const char * ch = "hello";
    printf("\nchar[1]%c\n",ch[1]);

    return 0;
}
