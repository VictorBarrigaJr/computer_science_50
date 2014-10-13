/**
 * CS50 Study, memory management, dynamic memory allocation
 * free.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 * 
 * free all heap used in the program
 *
 */
 
 #include <stdio.h>
 #include <cs50.h>
 
 int main(void)
 {
    char* ptr = malloc(sizeof(char) * 7);
    
    for (int i = 0; i < 6; i++)
        *(ptr + i) = 'z';
    
    ptr[6] = '\0';
    
    while (*ptr != '\0')
    {
        printf("%c", *ptr);
        ptr++;
    }
    
    // reset ptr
    ptr -= 6;
    
    // free ptr
    free(ptr);
}   
