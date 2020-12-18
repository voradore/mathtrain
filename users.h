#ifndef MAXUSER
#define MAXUSER 20
#endif
#ifndef MAXLINE
#define MAXLINE 100
#endif
#ifndef SAVE
#define SAVE "save.sav"
#endif

struct data {
	int lvl,rttot,wgtot,pts,nxlev,rtloc,wgloc,exe;
	float restot, resloc;
	};
struct ulist{
	char name[MAXLINE];
	struct data user;
};
struct ulist userlist[MAXUSER];
struct data user;

int getlin(char s[], int lim);
char * getname (char line[]);
struct ulist *lookup(char s[]);
struct ulist *install(char s[]);
struct ulist * listusr(struct ulist arr[]);
int getuser(char *username);
struct data inituser(struct ulist *);
int savestat(int size);
int loadstat(int size);
int pushuser(char name[]);
void restabl(void);
