#ifndef __CTYPE_H__
#define __CTYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

int isalnum(int c);
int isascii(int c);
int isdigit(int c);
int isspace(int c);
int tolower(int c);
int toupper(int c);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __CTYPE_H__ */
