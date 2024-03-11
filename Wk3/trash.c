  
// C program to reverse a string using strrev() 
#include <stdio.h> 
#include <string.h> 
  
int main() 
{ 
    char str[] = "a+b"; 
    printf("Original String: %s\n", str); 
  
    // reversing string 
    char* str2;
    strcpy(str2, strrev(str));
    printf("Reversed String: %s", str2); 
  
    return 0; 
}