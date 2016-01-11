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

int setup(void){
	LIST *cgi_input=NULL;
	char *act=NULL, *service=NULL;

	cgi_input=cgi_input_parse();
	if(!cgi_input){
		cgi_log("No cgi input\n");
		return 0;
	}
	mime_header("text/html");
	act=find_val(cgi_input, "act");
	fprintf(stdout, "input: %s\n", act);
	service=find_val(cgi_input, "service");
	if(service){
		fprintf(stdout, "service: %s\n", service);
		run_service(service, cgi_input);
	}
	return 0; 
}

int run_service(char *service, LIST *cgi_input){
	service=find_val(cgi_input, "service");
	if(!strcmp(service, "set_chipset")) // save chipset by UUID
		set_chipset(cgi_input);
	else if(!strcmp(service, "set_setuptime")) // save setup time by UUID
		set_setuptime(cgi_input);
	return 0;
}

int set_chipset(LIST *cgi_input){
	fprintf(stdout, "function: %s", __FUNCTION__);
	return 0;
}

int set_setuptime(LIST *cgi_input){
	return 0;
}

int upgrade(void){
	return 0;
}
