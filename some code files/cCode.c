// Online C compiler to run C program online
#include <stdio.h>
typedef struct {
    int mode;
    int in;
    int out;
    
    
    
}gpio;
int main() {
    
    int var;
	
	printf("address of var %p  \n",&var);
    gpio *ps1 = (gpio *)&var;
	int *a = (int*)0x0061FF20, pa;
	
	//pa = &a;
	//*a=11;
	ps1->mode = 2;
	
	
	
    //ps1->a = 1;]
    // Write C code here
    printf("Hello world %i \n",sizeof(gpio));
	//while (1);
    return 0;
}