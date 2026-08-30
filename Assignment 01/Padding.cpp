#include <stdio.h>

struct Layout1 { char c1; int i; char c2; };
struct Layout2 { int i; char c1; char c2; };

int main() {
    printf("sizeof(Layout1) = %zu\n", sizeof(struct Layout1));
    printf("sizeof(Layout2) = %zu\n", sizeof(struct Layout2));
    return 0;
}

/*
 * 1. Size Difference: Layout1 (12 bytes) is larger than Layout2 (8 bytes) due to member ordering.
 * 2. Struct Padding: Compiler inserts filler bytes so fields align with CPU memory boundaries for speed.
 * 3. Member Ordering: Placing larger types first or grouping similar types minimizes wasted padding space.
 * 4. Hardware/Network: Padding alters exact byte offsets, breaking network protocols and hardware register maps.
 */