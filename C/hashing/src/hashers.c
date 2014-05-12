 
unsigned long hash_sdbm(const char *str, unsigned long len) {
    unsigned long hash = 0;
    int c;
    while (len) {
        c = *str;
        hash = c + (hash << 6) + (hash << 16) - hash;
        len--;
        str++;
    }
    return hash;
}

unsigned long hash_djb2(const char *str, unsigned long len) {
    unsigned long hash = 5381;
    int c;
    while (len) {
        c = *str;
        hash = ((hash << 5) + hash) + c;
        len--;
        str++;
    }
    return hash;
}
