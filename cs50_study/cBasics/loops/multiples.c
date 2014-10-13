/**
 *CS50, CS50 Study, Loops
 *multiples
 *Victor Barriga
 *victorbarriga@live.com
 *Take as input a number between 1 and 100.
 *Use a for loop to print every multiple of that number between 1 and 100 (inclusive).
 *Give me a number between 1 and 100: 5
 *5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100
 */
 
 #include <cs50.h>
 #include <stdio.h>

int main(int argc, string argv[])
{
    int multiple;
    // get multiple from user
    do
    {
        printf("Give me a number between 1 and 100: ");
        multiple = GetInt();
    }
    while (multiple <= 0 || multiple > 100);
    
    // iterate from multiple through 100
    for (int i = multiple; i <= 100; i = i + multiple)
    {
        // if not first, print comma and space
        if (i != multiple)
            printf(", ");
            
            // print number
            printf("%i", i);            
    }
    printf("\n");
}
