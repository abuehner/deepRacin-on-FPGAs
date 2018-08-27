#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "glib_functions.h"
#include <stdlib.h>

gboolean g_file_set_contents (const gchar *filename, const gchar *contents, unsigned long length, GError **error){
	return false;
}

gboolean g_strcmp0(gchar str1[], gchar str2[]){
	if(!str1 && !str2){
		return TRUE;
	} else if (!str1)  {
		return FALSE;
	} else if(!str2){
		return FALSE;
	} else {
		gboolean b = strcmp(str1, str2);
		return b;
	}
}

int g_snprintf(int, int, void*){
	return 0;
}
int g_snprintf(int, int, void*, void*, void*){
	return 0;
}
int g_snprintf(int, int, void*, void*, void*,void*){
	return 0;
}
int g_snprintf(int, int, void*, void*){
	return 0;
}
char* g_build_path(char* seperator, char* e1, char* e2, void* n){
	char* path;
	int del1 = 0;
	int del2 = 0;
	if(e1[strlen(e1)-1] == *seperator) del1 = 1;
	if(e2[0] == *seperator) del2 = 1;
	path = (char *)malloc(strlen(e1)+strlen(e2)-(del1+del2)*sizeof(char));
	if(del1 && del2){
		path[0] = e1[0];
		path[strlen(e1)] = e2[1];
	} else if(del1){
		path[0] = e1[0];
		path[strlen(e1)] = e2[0];
	} else if(del2){
		path[0] = e1[0];
		path[strlen(e1)] = e2[0];
	} else {
		path[0] = e1[0];
		path[strlen(e1)] = *seperator;
		path[strlen(e1)+1] = e2[0];
	}
	printf("in path: %s", path);
	return path;
}
char* g_build_filename(char* e1, char* e2, void* n){
	//char sep = '/';
	//char* result = g_build_path(&sep, e1, e2, n);
	char * result = (char *)malloc((strlen(e1)+strlen(e2))*sizeof(char));
	strcat(result, e1);
	printf("gbf1: %s", result);
	strcat(result, "/");
	printf("gbf2: %s", result);
	strcat(result, e2);
	printf("gbf3: %s", result);
	return result;
}
gchar* g_strjoin (const gchar* s1, const gchar* s2,const gchar* s3,const gchar* s4){
	/*gchar* result = (gchar*)malloc((strlen(s2)+strlen(s3))*sizeof(char));
	strcat(result, s2);
	strcat(result, s3);
	return result;*/

    char* result = (char*)malloc((strlen(s2)+strlen(s3))*sizeof(char));
    int end = 0;
    for(int i2 = 0; i2 <= strlen(s2); i2++){
    	result[i2] = s2[i2];
    	end = i2;
    }
    int c = 0;
    for(int i3 = end; i3 <= end+strlen(s3); i3++){
    	result[i3] = s3[c];
    	c++;
    }

	return result;
}

gchar* g_strdup_printf(const gchar *format, gchar* a1){
	gchar* result = (char *)malloc((sizeof(format)+sizeof(a1))*sizeof(char));
	sprintf(result, format, a1);
	return result;
}

gchar* g_strdup_printf(const gchar *format, gchar* a1, gchar* a2 , gchar* a3){
	 char* result;
	 sprintf(result, format, a1, a2, a3);
	 return result;
}

gchar* g_strdup_printf(const gchar *format, ...){
	 char* result;
	 va_list arg;
	 va_start(arg,format);
	 sprintf(result, format, arg);
	 va_end(arg);
	 return result;
}

void g_get_current_time(GTimeVal *result){
    time_t now;
    now = time(0);
    struct tm *tm;
    tm = localtime (&now);
    result->tv_sec = tm->tm_sec;
    result->tv_usec = tm;
}

gchar* g_strdup(const gchar *str){
	gchar* str2 =(gchar*)malloc(strlen(str)*sizeof(char));
	strcpy (str2, str);
	return str2;
}



GString * g_string_new (const gchar *init){
	GString result;
	result.str = init;
	result.len = strlen(*init);
	result.allocated_len = sizeof(*init);
	return &result;
}

GString *g_string_new_len (const gchar *init, gsize len){
	GString result;
	result.str = init;
	result.len = strlen(*init);
	result.allocated_len = len;
	return &result;
}



gboolean g_file_get_contents(const gchar *filename, gchar **contents, gsize *length, GError **error){
	FILE *file;
	//unsigned char *contentString;

	file = fopen(filename, "rb");
	if(!file){
		fclose(file);
		return FALSE;
	}
	fseek (file, 0L, SEEK_END);
	size_t fileSize = ftell(file)+1;
	printf("g_file_get_contents: \n fileSize: %zu \n", fileSize);
	fseek(file, 0, SEEK_SET);
	*contents = (gchar *)malloc(fileSize*sizeof(unsigned char));
	//contentString = (unsigned char *) malloc(fileSize);
	//size_t contentSize = fread(*contents, sizeof(unsigned char), fileSize, file);
	size_t contentSize = fread(*contents, fileSize, 1, file);
	printf("contentSize: %zu \n", contentSize);
	float* outputString = (float*)*contents;
	printf("*contents: %f \n", outputString[0]);	//*contents = contentString;
	length = &contentSize;
	fclose(file);
	return TRUE;
}


void g_error_free(GError *error){
	g_free(error);
}

char* g_strconcat(char* s1,char* s2,char* s3,char* s4,char* s5,char* s6,char* s7, int){
	char * result = malloc(strlen(s1)+ strlen(s2)+ strlen(s3)+strlen(s4)+strlen(s5)+strlen(s6)+strlen(s7));
	strcpy(result, s1);
	strcpy(result, s2);
	strcpy(result, s3);
	strcpy(result, s4);
	strcpy(result, s5);
	strcpy(result, s6);
	strcpy(result, s7);
	return result;
}
gboolean g_path_is_absolute (const gchar *file_name){
	if(file_name[0] == '/'){
		return true;
	}
	return false;
}

void g_string_free(GString* str, gboolean){
	free(str);
}


gchar *g_get_current_dir (){
	  //char cwd[1024];
	  //getcwd(cwd, sizeof(cwd));
	  //printf("%s \n", cwd);
      //return cwd;
		return "/mnt";
}

gint g_mkdir_with_parents (const gchar *pathname, gint mode){
	return -1;
}
//glib2 ersatz
