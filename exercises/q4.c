

int main(void){
    int ba, bb, oa, ob, ha, hb;

    ba = 28;
    bb = 127;

    oa = 1004;
    ob = 4097;

    ha = 65697;
    hb = 725248;

    printf("Add: %p \nSubtract:%p \nMultiply: %p\n\n", (ha+hb), (hb-ha), (ha*hb));
    printf("Add: %o \nSubtract:%o \nMultiply: %o\n\n", oa+ob, ob-oa, ob*oa);
    printf("Add: %d \nSubtract:%d \nMultiply: %d\n\n", ba+bb, bb-ba, bb*ba);
    return 0;
}