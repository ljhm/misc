#include <stdio.h>
#include <string.h>

//16.5: Formatted Output (printf and friends)
//http://www.c-faq.com/~scs/cclass/int/sx2e.html

//dst: destination array
//size: length of destination array
//cnt: count of sub-string
//index: index of sub-string in source string
char *substr(char *dst, size_t size, int cnt, char *index)
{
    if (!dst || !index)
        return NULL;
    snprintf(dst, size, "%.*s", cnt, index);

    return dst;
}

int main(int argc, char *argv[])
{
    char *str = "hello world";
    char buf[1024] = {0};
    char *p1 = strstr(str, "o");
    char *p2 = strstr(p1 + 1, "o");
    int cnt = (int)(p2 - p1) + 1;
    substr(buf, sizeof buf, cnt, p1);
    printf("%d: %s\n", __LINE__, buf);
}
