#binclude <stdio.h> // error: invalid preprocessing directive - preprocessor 

int main(void) { 
    int a; 
    ink b; // error: unknown type name 'ink' - Semantiska steget 
    float a; // error: conflicting types for 'a'- semantiska steget 

    printf("Hej!\n); // error: missing terminating " character - Lexern 
    print("Tal: "); // error: undefined reference to `print' - Länkningen 
    scanf("%d", &a); - Krasch vid exekvering (float läses in i en int) 
    printf("Talet = %d\n", a); 

    return "OK"; // warning: return makes integer from pointer - semantisk 
} 