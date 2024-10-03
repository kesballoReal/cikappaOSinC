int strCmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void trim_whitespace(char* str) {
    char* start = str;
    char* end;

    while (*start == ' ' || *start == '\t') {
        start++;
    }

    if (*start == '\0') {
        str[0] = '\0';
        return; 
    }

    end = start;
    while (*end != '\0') {
        end++;
    }
    end--;

    while (end > start && (*end == ' ' || *end == '\t')) {
        end--;
    }

    size_t len = end - start + 1;

    for (size_t i = 0; i < len; i++) {
        str[i] = start[i];
    }

    str[len] = '\0';
}
