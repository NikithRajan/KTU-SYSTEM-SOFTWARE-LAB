#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pgname[6], inpname[6], address[8];
FILE *inptr, *outptr;
char line[100];

void genhex(int index) {
    if (index >= 0) {
        char hex = address[index];
        if (hex == '9') {
            address[index] = 'A';
        } else if (hex == 'F') {
            address[index] = '0';
            genhex(index - 1);
        } else {
            address[index] = hex + 1;
        }
    }
}

int main() {
    printf("Enter the name of the program: ");
    scanf("%5s", inpname);

    inptr = fopen("input.txt", "r");
    outptr = fopen("output.txt", "w");

    if (inptr == NULL || outptr == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(inptr, "%s", line);
    for (int i = 2, j = 0; line[i] != '^' && j < 5; i++, j++) {
        pgname[j] = line[i];
    }
    pgname[5] = '\0';

    printf("Name of the program: %s\n", pgname);

    if (strcmp(pgname, inpname) == 0) {
        do {
            fscanf(inptr, "%s", line);
            if (line[0] == 'T') {
                int i = 2, j = 0;
                while (line[i] != '^' && j < 7) {
                    address[j++] = line[i++];
                }
                address[j] = '\0';
                i++;

                while (line[i] != '\0') {
                    if (line[i] != '^') {
                        fprintf(outptr, "%s\t%c\t%c\n", address, line[i], line[i + 1]);
                        genhex(7);
                        i += 2;
                    } else {
                        i++;
                    }
                }
            } else if (line[0] == 'E') {
                printf("Program loaded!\n");
                fclose(inptr);
                fclose(outptr);
                exit(0);
            }
        } while (!feof(inptr));
    } else {
        printf("The name of the program doesn't match.\n");
    }

    fclose(inptr);
    fclose(outptr);
    return 0;
}
