#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// THIS PROGRAM ONLY TAKES INPUT OF  THE FILENAME IN AN INFINITE LOOP AND PRINTS IT ....
// HERE NO STORY OF CHILD PROCESSES ... 

int main()
{
    int a = 1;         // Variable to control the loop
    char filename[64]; // Array to store the filename, not a pointer

    while (a)
    {
        printf("Enter filename: ");
        fgets(filename, sizeof(filename), stdin);

        // Remove the newline character from the filename
        size_t len = strlen(filename);
        if (len > 0 && filename[len - 1] == '\n')
        {
            filename[len - 1] = '\0';
        }

        printf("Entered filename is %s\n", filename);
    }

    return 0;
}
