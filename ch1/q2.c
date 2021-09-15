#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

static int len;

static char strs[4][4] = {{'t', 'h', 'i', 's'}, \
						{'w', 'a', 't', 's'}, \
						{'o', 'a', 'h', 'g'}, \
						{'f', 'g', 'd', 'c'}};
						
/*
	search in 8 directions
*/
static int change_x[8] = {1,1,0,-1,-1,-1,0,1};
static int change_y[8] = {0,1,1,1,0,-1,-1,-1};

/*
	[return]: 0 false 1 true
*/
char solution(int x, int y, char * str, int index, int dir){
	if(len == index){
		printf("end %d  %d\n", x , y);
		return 1;
	}
	
	x += change_x[dir];
	y += change_y[dir];
	
	if(x >= 0 && x < 4 && y >= 0 && y < 4 && strs[x][y] == str[index]){
		return solution(x, y, str, index+1, dir);
	}
	
	return 0;
}

int main(int argc, char ** argv){
						
	if(argc != 2){
		fprintf(stderr, "usage: ext string\n");
		return 0;
	}
	
	char * str = argv[1];
	
	printf("%s\n", str);
	
	if((len = strlen(str)) > 16){
		printf("can not find\n");
		return 0;
	}
	
	int x1, y1;
	int x2, y2;
	int i, j, k;
	
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(strs[i][j] == str[0]){
				for(k = 0; k < 8; k++){
					if(solution(j, i, str, 1, k) != 0){
						printf("begin %d  %d\n", j, i);
					}
				}
			}
		}
	}
	
	return 0;
}
