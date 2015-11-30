#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include "cgi-priv.h"
#include "cgi-lib.h"
#include "html-lib.h"
#include "cgi_main.h"

#include <sys/ioctl.h>

#define cgi_log(msg) {} 

int main(void){

	if(getenv("CONTENT_TYPE")!=NULL && strstr(getenv("CONTENT_TYPE"),"form-data")!=NULL){
		return 	upgrade();
	}else{ 
		return setup();	
	}
}

#define LOGINTIMEOUT 15

int setup(void){
	mime_header("text/html");
	printf("xxxxxxxxxxxxxx\n");
	return 0; 
}

int upgrade(void){
	return 0;
}
