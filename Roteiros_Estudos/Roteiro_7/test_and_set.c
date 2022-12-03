int foo(void) {
    __asm__(
        "mov $100,%eax"
    );

    return 1;
}

int test_and_set(int* L) {
    int prev = *L;
    *L = 1;
    return prev;
}
