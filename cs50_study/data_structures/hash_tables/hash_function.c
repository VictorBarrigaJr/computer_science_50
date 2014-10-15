/***
 * CS50 Study, data structures, hash tables
 * hash_function.c
 *
 * Victor Barriga
 * victorbarriga@live.com
 *
 * A hash function for strings that sums the ASCII values of the argument key's
 * characters. 
 *
 **/
 
 #include <cs50.h>
 #include <ctype.h>
 #include <stdio.h>
 
 int hash_function(char *key, int size);
 
 int main(int argc, char *argv[])
 {
    // get hash table size
    printf("Hash table size: ");
    int size = GetInt();
    
    // get key
    printf("Key: ");
    char *key = GetString();
    
    // calculate and print index
    printf("The sting '%s' is mapped to index %i\n", key, 
            hash_function(key, size));
            
    return 0;
 }
 
 int hash_function(char *key, int size)
 {
    // initialize index to 0
    int index = 0;
    
    // sum ascii values
    for (int i = 0; key[i] != '\0'; i++)
    {
        index += toupper(key[i]);
    }
    // mod by size to stay w/in bound of table
    return index % size;
 }
