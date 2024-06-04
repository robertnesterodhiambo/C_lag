#include <stdio.h>
#include <ctype.h>

int main() {
    char file_name[] = "a.txt"; // Replace with your executable file name
    FILE* fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("File Not Found!\n");
        return 1;
    }

    int printable_count = 0;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (isalnum(c) || ispunct(c) || isspace(c))
            printable_count++;
    }

    fclose(fp);
    printf("Number of printable characters: %d\n", printable_count);
    return 0;
}
