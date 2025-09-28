#include "ipv4_prefix_manager_lib.h"

#include <stdlib.h>

Node* head;

// Initializes a node representing one bit
Node* create_node() {
    Node* node = (Node*)malloc(sizeof(Node));

    if (!node) return NULL;

    node->children[0] = NULL;
    node->children[1] = NULL;

    node->addr_counter = 0;
    node->mask = 0;

    return node;
}

// Initializes the data structure
void init() {
    head = create_node();
}

// Returns the value of a bit on particular position of the address
uint8_t check_mask(uint32_t masks, uint8_t pos) {
    if (pos < 0 || pos > 31) {
        return 0;
    }

    return (masks >> (31 - pos)) & 1;
}

// Sets the value of a bit on particular position of the address
uint32_t set_mask(uint32_t masks, uint8_t pos, uint8_t val) {
    if (val == 0) {
        return masks & ~(1U << 32 - pos - 1);
    }

    return masks | (1U << 32 - pos - 1);
}

// Check if the prefix exists in the data structure
uint8_t check_prefix(uint32_t ip_address, uint8_t mask) {
    Node* curr = head;

    for (int i = 31; i >= 0; i--) {
        uint8_t bit = (ip_address >> i) & 1;

        if (curr->children[bit] == NULL)
            return 0;

        curr = curr->children[bit];
    }

    return check_mask(curr->mask, mask);
}

int add(unsigned int ip_address, char mask) {

    if (check_prefix(ip_address, mask) == 1) {
        printf("IP Already exists\n");
        return 0;
    }

    Node* curr = head;

    for (int i = 31; i >= 0; i--) {
        uint8_t bit = (ip_address >> i) & 1;

        if (curr->children[bit] == NULL) {
            Node* node = create_node();
            curr->children[bit] = node;
            curr = node;
        }
        else {
            curr = curr->children[bit];
        }

        curr->addr_counter++;

        if (i == 32 - mask) {
            curr->mask++;
        }

    }

    curr->mask = set_mask(curr->mask, mask, 1);

    return 1;
}

int check(unsigned int ip_address) {
    Node* curr = head;

    uint8_t result = 1;

    for (int i = 31; i >= 0; i--) {
        uint8_t bit = (ip_address >> i) & 1;

        if (curr->children[bit] == NULL) {
            return result;
        }

        curr = curr->children[bit];

        // If the mask exists
        if (i > 0 && curr->mask > 0) {
            if (32 - i > result) {
                result = 32 - i;
            }
        }
    }

    return result;
}

int del(unsigned int ip_address, char mask) {

    if (check_prefix(ip_address, mask) == 0) {
        printf("IP Doesn't exist\n");
        return 0;
    }

    Node* curr = head;
    Node* tmp = NULL;

    int i;

    uint8_t bit;

    // Iterating until the first node to delete is found
    for (i = 31; i >= 0; i--) {
        bit = (ip_address >> i) & 1;

        tmp = curr->children[bit];

        tmp->addr_counter--;

        if (tmp->addr_counter == 0)
            break;

        if (i == 32 - mask && tmp->mask > 0) {
            tmp->mask--;
        }

        curr = tmp;
    }

    // Setting the pointer of the prev node to NULL
    curr->children[bit] = NULL;
    curr = tmp;
    i--;


    // Removing the remaining nodes;
    for (i; i >= 0; i--) {
        bit = (ip_address >> i) & 1;

        tmp = curr;
        curr = curr->children[bit];

        free(tmp);
    }

    curr->mask = set_mask(curr->mask, mask, 0);

    return 1;
}