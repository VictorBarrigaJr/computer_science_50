/**
 * CS50 Study, memory management, pointers
 * ascii_puzzle.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * passes the seven chars to printf() so that executing your code will print the
 * word "POINTER" 
 *
 */
 
 #include <stdio.h>
 #include <cs50.h>
 
 int main(void)
 {
    int s = 65;
    int* t = &s;
    
    // TODO:print "POINTER" using these chars
    
    char C = 'I';               // I
    char N = s + 'P' - 'A';     // P .
    char B = *t - s + N + 2;    // P R
    char E = &s - t + 78;       // N
    char J = *t + 19;           // T
    char I = N + 'A' - s - 1;   // M O
    char O = 347 / 5;           // E
    
    printf("%c%c%c%c%c%c%c\n", N, I, C, E, J, O, B);
 }
