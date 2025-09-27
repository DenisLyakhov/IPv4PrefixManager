#include "ipv4_prefix_manager_lib.h"

#include <assert.h>

uint32_t ip1 = 0b11000000101010000000000100000001;
uint32_t ip2 = 0b00100000101010000000000100000011;
uint32_t ip3 = 0b11000000101010000000000100000111;
uint32_t ip4 = 0b00000000001010000000000100000111;

void test_case1_add() {
    add(ip1, 12);
    add(ip2, 20);
    add(ip3, 22);
    add(ip4, 23);

    uint32_t ip5 = 0b00000000001010000000000100000110;

    assert(check_prefix(ip1, 12) == 1);
    assert(check_prefix(ip2, 20) == 1);
    assert(check_prefix(ip3, 22) == 1);
    assert(check_prefix(ip4, 23) == 1);

    assert(check_prefix(ip1, 6) == 0);
    assert(check_prefix(ip5, 23) == 0);

    printf("test case 1 - add   - passed\n");
}

void test_case2_del() {
    del(ip1, 12);
    del(ip2, 20);
    del(ip3, 22);
    del(ip4, 23);

    assert(check_prefix(ip1, 12) == 0);
    assert(check_prefix(ip2, 20) == 0);
    assert(check_prefix(ip3, 22) == 0);
    assert(check_prefix(ip4, 23) == 0);

    printf("test case 2 - del   - passed\n");
}

void test_case3_check() {
    add(0b11000000101010000000000100000001, 6);
    add(0b11000000101010000000000100000001, 12);
    add(0b11000000101010000000000100000001, 24);

    add(0b11000000101010000000000100000011, 15);
    add(0b11000000101010000000000100000011, 20);

    add(0b11000000101010000000000100000111, 10);

    add(0b01000000101010000000000100000001, 14);
    add(0b01000000101010000000000100000011, 18);


    assert(check(0b11000000101010000000000100000000) == 24);
    assert(check(0b11000000101010000100001100000000) == 15);
    assert(check(0b11000000001011000100001100000000) == 6);
    assert(check(0b01000000101010010000000100000011) == 14);

    assert(check(0b00000000101010010000000100000011) == 1);

    printf("test case 3 - check - passed\n");
}

int main() {
    init();

    test_case1_add();
    test_case2_del();
    test_case3_check();

    printf("\nAll test cases passed\n");

	return 1;
}