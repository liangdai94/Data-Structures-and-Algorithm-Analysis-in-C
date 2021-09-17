#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char ** argv){
	if(argc != 3){
		fprintf(stderr, "usage: ./a.out  number  precision\n");
		return 0;
	}
	
	char * str = argv[1];
	int pre = atoi(argv[2]);
	
	char * tmp = &str[0];
	
	while(*tmp != '\0' && *tmp != '.'){
		putchar(*tmp);
		tmp++;
	}
	
	if(*tmp == '.'){
		putchar('.');
		tmp++;
		while(*tmp != '\0' && pre != 0){
			putchar(*tmp);
			tmp++; 
			pre--;
		}
		
		while(pre){
			putchar('0');
			pre--;
		}
	}
	else if(*tmp == '\0'){
		putchar('.');
		while(pre){
			putchar('0');
			pre--;
		}
	}
	putchar('\n');
	return 0;
}
