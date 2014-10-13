#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("Usage: cp source dest\n");
        return 1;
    }

    // open up the source file

    // now open up the destination file

    // read the contents of the source file one char (int!) at a time

        // write the character to the destination file!

    // you leak memory if you forget to close!
}
