#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* children[2];

    // Keeps track of how many different prefixes make use of the node
    uint32_t addr_counter;

    // For regular nodes: tracks the amount of set last bits of the network addresses
    // For leaves:        stores the masks' values
    uint32_t mask;
} Node;

void init(void);

int add(unsigned int ip_address, char mask);
int check(unsigned int ip_address);
int del(unsigned int ip_address, char mask);