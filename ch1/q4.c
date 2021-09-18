/*
	author: dai liang
	date: 2021.08.13 14:30:12 CST
*/
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<regex.h>
#include<string.h>
#include<stdlib.h>

#define TMPFILE	"file.tmp"
#define LINE_MAX	256

typedef struct {
	short fileNum;
	char ** fileNames;
} FILEDICT;

FILEDICT filedict = {0, NULL};

/*
	to test whether the fileName is used
*/
unsigned char check(const char * fileName){
	int i = 0;
	
	for(; i < filedict.fileNum; i++){
		if(0 == strcmp(fileName, filedict.fileNames[i])){
			return 0;
		}
	}
	
	return 1;
}

void solution(const char * fileName, FILE* tmpFd, regex_t * preg){
	
	FILE* fd = NULL;
	//size_t len;
	int status;
	char buf[LINE_MAX] = {0};
	regmatch_t pmatch[1];
	
	fd = fopen(fileName, "r");
	if(NULL == fd){
		//perror("open %s error", fileName);
		fprintf(stderr, "%s open fail: %s\n", fileName, strerror(errno));
		return;
	}
	
	while(fgets(buf, LINE_MAX, fd)){
		status = regexec(preg, buf, 1, pmatch, 0);
		if(status == REG_NOMATCH){
			fputs(buf, tmpFd);
			continue;
		}
		
		buf[pmatch[0].rm_eo] = '\0';
		if(check(&buf[pmatch[0].rm_so]) == 0){
			continue;
		}
		filedict.fileNames[filedict.fileNum] = strdup(&buf[pmatch[0].rm_so]);
		filedict.fileNum++;
		//len = pmatch[0].rm_eo - pmatch[0].rm_so;
		solution(&buf[pmatch[0].rm_so], tmpFd, preg);
	}
	fclose(fd);
}

int main(int argc, char ** argv){
	
	if(argc != 2){
		fprintf(stderr, "usage: ./a.out fileName\n");
		return 0;
	}
	
	const char * fileName = argv[1];
	FILE* tmpFd = NULL;
	const char * pattern = "[ ]*([ ]*[a-z]{1,9}\\.h[ ]*)";
	int cflags = REG_EXTENDED;
	regex_t reg;
	
	regcomp(&reg, pattern, cflags);
	
	filedict.fileNames = (char **)malloc(sizeof(char*) * 64);
	filedict.fileNames[filedict.fileNum] = strdup(argv[1]);
	filedict.fileNum++;
	
	tmpFd = fopen(TMPFILE, "w+");
	if(NULL == tmpFd){
		perror("open tmpfile error: ");
		return 0;
	}
	
	solution(fileName, tmpFd, &reg);
	
	//release
	fclose(tmpFd);
	while(--filedict.fileNum >= 0){
		printf("%s\n", filedict.fileNames[filedict.fileNum]);
		free(filedict.fileNames[filedict.fileNum]);
	}
	return 0;
}
