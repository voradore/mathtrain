#include "headers.h"

/////////////////////////////////////////////////////////////////////////////////////////////
int getuser(char name[])
{
	int i=0;		/* 		STRUCT ARRAY INIT */
	for (i=0; i<MAXUSER; i++)
		userlist[i].name[0] = '\0';
	int size = sizeof userlist;
	if (loadstat(size) == 1)
		savestat(size);
	listusr(userlist);
	printf ("Введите имя.\n");

	getname(name);						// Здесь останется имя структуры
	user = install(name)->user;
	//printf ("%s :\nnext level = %d\ntotal result = %f\n", line, usr.nxlev, usr.restot );
	savestat(size);
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////
int pushuser(char name[])
{
	struct ulist *np;
	np = lookup(name);
	np->user = user;
}
struct ulist * listusr(struct ulist arr[])
{
	int i;
	for (i = 0;i < MAXUSER && arr[i].name[0] != '\0'; ++i)
		printf("%d. %s:\t\tlevel:  %d\tresults:  %0.2f%%\n", i, arr[i].name, \
			arr[i].user.lvl, arr[i].user.restot);
	return arr;
}
int savestat(int size)
{
	FILE *fp;
	char *c;
	int i;
	if ((fp = fopen(SAVE, "w")) == NULL)
	{
		printf("Error while opening file\n");
		return 1;
	}
	c = (char *)userlist;
	for (i=0; i<size;++i)
		fputc(*c++, fp);
	fclose (fp);
	return 0;
}

int loadstat(int size)
{
	
	FILE *fp;
	char *c;
	int i;
	if ((fp = fopen(SAVE, "r")) == NULL)
	{
		printf("Save file exist\n");
		return 1;
	}
	c = (char *)userlist;
	for (i = 0; i < size; ++i)
		*c++ = fgetc(fp);
	fclose(fp);
	return 0;
}


struct ulist *lookup(char s[])
{
	int i;
	struct ulist *np;
	for (i=0; i<MAXUSER; i++)
	{
		np=&userlist[i];
		if (strcmp(s, np->name) == 0)
		{
			return np;
		}
	}
	return NULL;
}
struct ulist *install(char s[])
{
	char c;
	int i, j;
	struct ulist *np;
	while(1)
	{
		if ((np = lookup(s)) == NULL)
		{
			printf ("Пользователь не найден. Создать? y/n\n");
			if ((c=getchar()) == 'y' || c == 'Y')
			{
				getchar();
				for (i = 0,np = &userlist[i]; i<=MAXUSER && isalnum(np->name[0]); i++)
					np = &userlist[i];
				if (i==MAXUSER)
					printf("Нет места для новых пользователей.\n"), exit(1);
				for (j = 0; s[j] != '\0';++j)
					np->name[j]=s[j];
				if (np == NULL)
					return NULL;
				inituser(np);
				return np;
			}
			else if (c == 'n' || c == 'N')
			{
				getchar();
				printf("Ввести заново? y/n \n");
				if ((c=getchar()) == 'y' || c == 'Y')
				{
					getchar();
					getname(s);
					continue;
				}
				else 
				printf("Выход\n"), exit (0);
			}
			else 
				printf("Выход\n"), exit (0);
		}
		else
			return np;
	}
}

struct data inituser(struct ulist *name)
{
	struct data user = {1,0,0,0,3,0,0,0,0,0};
	name->user = user;
	return user;
}


int getlin(char s[], int lim)
{
	int i, c;
	
	for (i = 0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; )
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
char *getname (char usrnm[])
{
	char c;
	int i;
	for (i = 0; i<MAXLINE-1 && (c=getchar()) != EOF && c != '\n'; )
		if (isalnum(c) || c==' ')
			usrnm[i++] = c;
	usrnm[i] = '\0';
	while(usrnm[1] == '\0')
	{
		printf (" \n Ошибка!\n Имя должно быть написано на латинице.\n Ввести заново? y/n\n");
		if ((c = getchar()) != 'Y' && c != 'y')
			printf("Выход\n"), exit(0);
		else
		{
			getchar();
			for (i = 0; i<MAXLINE-1 && (c=getchar()) != EOF && c != '\n'; )
				if (isalnum(c)||c==' ')
					usrnm[i++] = c;
			usrnm[i] = '\0';
		}
	}
	return usrnm;
}	

void restabl(void)
{
	int i, j, flag=0;
	struct  res{char *name;
	float results;};
	struct res tmp;
	struct res top[MAXUSER];
	for (i = 0; i < MAXUSER && userlist[i].name[0] != '\0'; ++i)
	{
		top[i].name = userlist[i].name;
		top[i].results = userlist[i].user.restot;
	}
	while(flag == 0)
	{
		flag = 1;
		for (j = 0; j < i-1; j++)
		{

			if (top[j].results < top[j+1].results)
			{
				tmp = top[j];
				top[j] = top[j+1];
				top[j+1] = tmp;
				flag = 0;
			}
		}
	}
	printf ("\n\tПять лучших результатов:\n\n");
	printf("\t|-----------------------------------\n");
	for (j=0; j < i && j < 5; ++j)
	{
		printf ("\t|%s\n\t|\t\t\t%0.2f%%\n", top[j].name, top[j].results);
		printf("\t|-----------------------------------\n");
	}
}
