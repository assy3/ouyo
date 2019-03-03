#include <stdio.h>

void outString(void *);

int main() {
        int i = 65 ;
        double d = 10.101;

        outString(&i);
        outString(&d);
        outString("Kitty on your lap");

        return 0;
}

void outString(void *text) {
        char *str = (char *)text;
        printf("%s\n" , str);
}
