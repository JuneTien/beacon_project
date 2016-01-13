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
	char /**act=NULL,*/ *service=NULL;

	cgi_input=cgi_input_parse();
	if(!cgi_input){
		cgi_log("No cgi input\n");
		return 0;
	}
	mime_header("text/html");
	//act=find_val(cgi_input, "act");
	//fprintf(stdout, "input: %s\n", act);
	service=find_val(cgi_input, "service");
	if(service){
		//fprintf(stdout, "service: %s\n", service);
		run_service(service, cgi_input);
	}
	return 0; 
}

int run_service(char *service, LIST *cgi_input){
	service=find_val(cgi_input, "service");
	if(!strcmp(service, "set_beacon_config")) // save chipset by UUID
		set_beacon_config(cgi_input);
	return 0;
}

int set_beacon_config(LIST *cgi_input){
	char *uuid=NULL, *chipset=NULL, *date=NULL, *txpower=NULL, *interval=NULL;
	FILE *fp=NULL;

	//fprintf(stdout, "function: %s", __FUNCTION__);
	uuid=find_val(cgi_input, "uuid");
	chipset=find_val(cgi_input, "chipset");
	date=find_val(cgi_input, "date");
	txpower=find_val(cgi_input, "txpower");
	interval=find_val(cgi_input, "interval");
	fprintf(stdout, "input => uuid: %s, chipset: %s, date: %s, txpower: %s, interval: %s<br>", uuid, chipset, date, txpower, interval);
	
	if( (fp=fopen("./beacon_conf", "r+"))==NULL ) goto err;
	//fprintf(fp, "%s=%s|%s|%s|%s", uuid, chipset, date, txpower, interval);
	char /*content[128]={0}, */tmp[128]={0};
	char /**p=NULL, *pbuf=NULL,*/ *ptmp=NULL;
#if 0
	int len=0;
	fseek(fp, 0, SEEK_SET);
	fseek(fp, 0, SEEK_END);
	len=ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if(!(pbuf=malloc(len))) goto err;
	memset(pbuf, 0, len);
	fread(pbuf, 1, len, fp);
	p=pbuf;
	while(p<(pbuf+len-1)){
		char line[128]={0};
		sscanf(p, "%[^\n^\r]", line);
		if(line[0]!='\0'){
			line_num++;
			p=p+strlen(line);
			if((ptmp=strstr(line, uuid))){
				//fprintf(stdout, "%s", line);
				sscanf(ptmp+strlen(uuid)+1, "%s", content);
				fprintf(stdout, "ptmp: %s<br>", ptmp);
				fprintf(stdout, "result => uuid: %s<br>", uuid);
				fprintf(stdout, "content: %s<br>", content);
				sprintf(tmp, "%s=%s|%s|%s|%s", uuid, chipset, date, txpower, interval);
				//fputs(tmp, fp);
			//	if (fseek(fp, line, SEEK_SET)<0) goto err;
				fprintf(fp, "%s\n", tmp);
			}
		}else{
			p++;
		}
	}
#else
	char line[128]={0};
	while(fgets(line, 128, fp)){
		if((ptmp=strstr(line, uuid))){
			if(fseek(fp, -strlen(line), 1)<0) goto err;
			sprintf(tmp, "%s=%s|%s|%s|%s", uuid, chipset, date, txpower, interval);
			fprintf(fp, "%s", tmp);
		}
		memset(line, 0, 128);
	}
#endif
err:
	if(fp) fclose(fp);
	return 0;
}

int set_setuptime(LIST *cgi_input){
	return 0;
}

int upgrade(void){
	return 0;
}
