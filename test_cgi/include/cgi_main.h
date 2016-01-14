#ifndef __CGI_MAIN_H__
#define __CGI_MAIN_H__

typedef struct service_func_tab_t {
	char *name; 
	int(*service)(LIST *list);
} service_func_tab; 

typedef struct key_func_tab_t {
	char *key; 
	int nv_get; 
	int nv_set;
	int(*get)(char *name, char *value, LIST *list); 
	int(*set)(char *name, char *value, char *alert, LIST *list); 
	int crypto; 
	int chksession;
} key_func_tab; 

#define MAX_CGI_BUF_LEN 65535

#define MAX_CGI_SET_ENTRY 1024

typedef struct cgi_set_entry_t {
	char *name;
	char *val;
}cgi_set_entry;

typedef struct cgi_set_data_t {
	int num;
	cgi_set_entry entry[MAX_CGI_SET_ENTRY];
}cgi_set_data_t;

cgi_set_data_t cgi_set_data;

int setup(void);
int upgrade(void);
int run_service(char *service, LIST *cgi_input);
int set_beacon_config(LIST *cgi_input);
int get_beacon_config(LIST *cgi_input);

#endif

