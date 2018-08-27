#include <stdio.h>


#define FALSE false
#define TRUE true
#define g_malloc malloc
#define g_print printf
#define FALSE false
#define TRUE true
#define g_malloc malloc
#define g_print printf
#define _G_BOOLEAN_EXPR
#define G_LIKELY(expr) (__builtin_expect ((expr), 1))
#define g_free free

typedef signed long gint64;
typedef unsigned int guint;
typedef char gchar;
typedef unsigned long gsize;
typedef signed long gint64;
typedef void* gpointer;
typedef int GQuark;
typedef int gint;
typedef int gint32;
typedef bool gboolean;
typedef double gdouble;
typedef long glong;typedef float gfloat;



struct GError {
  GQuark       domain;
  gint         code;
  gchar       *message;
};

struct GTimeVal {
  long tv_sec;
  long tv_usec;
};

struct GString {
  gchar  *str;
  gsize len;
  gsize allocated_len;
};

gboolean g_strcmp0(gchar* str1, gchar* str2);

gboolean
g_file_set_contents (const gchar *filename,
                     const gchar *contents,
                     unsigned long length,
                     struct GError **error);
int g_snprintf(int, int, void*);
int g_snprintf(int, int, void*, void*, void*);
int g_snprintf(int, int, void*, void*, void*,void*);
int g_snprintf(int, int, void*, void*);
char* g_build_path(char* seperator, char* e1, char* e2, void* n);
char* g_build_filename(char* e1, char* e2, void* n);
gchar* g_strdup_printf(const gchar *format, ...);
void g_get_current_time(GTimeVal *result);
gchar* g_strdup(const gchar *str);
GString * g_string_new (const gchar *init);
GString *g_string_new_len (const gchar *init, gsize len);
gboolean g_file_get_contents(const gchar *filename, gchar **contents, gsize *length, GError **error);
void g_error_free(GError *error);
char* g_strconcat(char* s1,char* s2,char* s3,char* s4,char* s5,char* s6,char* s7, int);
gboolean g_path_is_absolute (const gchar *file_name);
void g_string_free(GString* str, gboolean);
gint g_mkdir_with_parents (const gchar *pathname, gint mode);
gchar *g_get_current_dir ();
gchar* g_strjoin (const gchar* s1, const gchar* s2,const gchar* s3,const gchar* s4);
