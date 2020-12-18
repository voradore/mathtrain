#include "headers.h"
#include "main.h"


/*====================================   Сложение   ========================================*/
extern char name[];
extern char *logfile;
void sum1(void)
{
	int a,b,x,i;
	time_t tmin,tminex;
	char line[20];
	FILE *fp;
	fp = fopen (logfile, "a");
	printf ("\nУпражнение № %d. Сложение.", user.exe);
	fprintf (fp,"\nУпражнение № %d. Сложение.\n", user.exe);
	time(&tminex);	
	pid_t pid;
	int pidstat;
	for (i = 1; i <= EXERCISES; ++i)
	{
	//	time(&tmin);
		srand(time(NULL));
		if ((pid = fork())== -1){
			fprintf(stderr, "Не клонируется процесс: %s", strerror(errno));
			exit (1);
		}
		if(!pid){
			alarm(10);
			do {
				a = rand()%101;
			}
			while ((a == 0) || (a == 1));
			b = rand()%101;
			printf ("\n\t %d+%d=", a, b);
			getlin (line, MAXLINE);
			system (CLEAR);
			x = atoi(line);
	//	if (difftime(time(NULL),tmin) >= 15)
	//	{
	//		timeout(tmin);
	//		continue;
	//	}
			if (a+b == x)
			{
				printf ("\n\n\n\t%d+%d=%d\n Правильно!\n", a,b,x);
				user.rtloc++;
			}
			else
			{
				printf ("\v\v\v\t%d+%d=%d  а не %d\n Неверно!\n", a, b, (a+b), x);
				fprintf (fp, "\n\t%d - Неверно.\n\t%d+%d=%d\n",x, a, b, (a+b));
				user.wgloc++;
			}
			printf("%d", user.wgloc);
			exit(0);
		}
		if (waitpid(pid, &pidstat, 0) == -1){
			fprintf(stderr, "Ошибка ожидания дочернего процесса: %s",
			 strerror(errno));
			exit (1);
		}
	}
	
	print_result(fp,tminex);
	progress();
	final_check();
	fclose (fp);

}
//====================================   Вычитание   ===============================================

void dif1(void)
{
	
	int a,b,x,i;
	time_t tmin,tminex;
	char line[20];
	FILE *fp;
	fp = fopen(logfile, "a");
	printf ("\nУпражнение № %d. Вычитание.", user.exe);
	fprintf (fp,"\nУпражнение № %d. Вычитание.\n", user.exe);
	time(&tminex);
	for (i = 1; i <= EXERCISES; ++i)
	{
		time(&tmin);
		b = rand()%100;
		a = rand()%100;
		if (b>a)
			x=a,a=b,b=x;
		printf ("\n %d-%d=", a, b);
		getlin (line, MAXLINE);
		x = atoi(line);
		if (difftime(time(NULL),tmin) >=15)
		{
			timeout(tmin);;
			continue;
		}
		system (CLEAR);
		if ((a-b == x)){
			printf ("\n\n\n\t%d-%d=%d\n Правильно!\n", a,b,x);
			user.rtloc++;
		}
		else {
			printf ("\v\v\v\t%d-%d=%d  а не %d\n Неверно!\n", a, b, (a-b), x);
			fprintf (fp,"\t\n%d - Неверно.\n%d-%d=%d\n",x, a, b,(a-b));
			user.wgloc++;
		}
	}
	print_result(fp,tminex);
	progress();
	final_check();
	fclose (fp);

}

//====================================   Умножение  один разряд   ==================================/
void mux1 (void)
{
	int a,b,x,i;
	time_t tmin,tminex;
	char line[20];
	FILE *fp;
	fp = fopen (logfile, "a");
	printf ("\nУпражнение № %d. Умножение.", user.exe);
	fprintf (fp,"\nУпражнение № %d. Умножение.\n", user.exe);
	time(&tminex);
	for (i = 1; i <= EXERCISES; ++i)
	{
		time(&tmin);
		do {
			a = rand()%10;
		}
		while ((a == 0) || (a == 1));
		b = rand()%10;
		printf ("\n\t %dx%d=", a, b);
		getlin (line, MAXLINE);
		system (CLEAR);
		x = atoi(line);
		if (difftime(time(NULL),tmin) >= 5)
		{
			timeout(tmin);;
			continue;
		}
		if (a*b == x)
		{
			printf ("\n\n\n\t%dx%d=%d\n Правильно!\n", a,b,x);
			user.rtloc++;
		}
		else
		{
			printf ("\v\v\v\t%dx%d=%d  а не %d\n Неверно!\n", a, b, (a*b), x);
			fprintf (fp, "\n\t%d - Неверно.\n\t%dx%d=%d\n",x, a, b, (a*b));
			user.wgloc++;
		}
	}
	print_result(fp,tminex);
	progress();
	final_check();
	fclose (fp);
}
//================================   Целочисленное деление   ======================================/
void div1 (void)
{
	int a,b,x,i;
	time_t tmin,tminex;
	char line[20];
	FILE *fp;
	fp = fopen(logfile, "a");
	printf ("\nУпражнение № %d. Деление.", user.exe);
	fprintf (fp,"\nУпражнение № %d. Деление.\n", user.exe);
	time(&tminex);
	for (i = 1; i <= EXERCISES; ++i)
	{
		time(&tmin);
		do{
			b = rand()%10;
		}
		while ((b == 0)||(b == 1));
		do{
			a = rand()%82;
		}
		while ((a/b>9)||(a%b != 0) || (a == 0));
		printf ("\n %d/%d=", a, b);
		getlin (line, MAXLINE);
		x = atoi(line);
		if (difftime(time(NULL),tmin) >= 5)
		{
			timeout(tmin);;
			continue;
		}
		system (CLEAR);
		if ((a/b == x)){
			printf ("\n\n\n\t%d/%d=%d\n Правильно!\n", a,b,x);
			user.rtloc++;
		}
		else {
			printf ("\v\v\v\t%d/%d=%d  а не %d\n Неверно!\n", a, b, (a/b), x);
			fprintf (fp,"\t\n%d - Неверно.\n%d/%d=%d\n",x, a, b,(a/b));
			user.wgloc++;
		}
	}
	print_result(fp,tminex);
	progress();
	final_check();
	fclose (fp);

}
//=========================   Деление с остатком   ================================================/
void div2 (void)
{
	int a,b,x,i;
	time_t tmin, tminex;
	char line[20];
	FILE *fp;
	fp = fopen(logfile, "a");
	printf ("\nУпражнение № %d. Деление с остатком.", user.exe);
	fprintf (fp,"\nУпражнение № %d. Деление с остатком.\n", user.exe);
	time(&tminex);
	for (i = 1; i <= EXERCISES; ++i)
	{
		time(&tmin);
		do{
			b = rand()%26;
		}
		while((b == 0)||(b == 1));
		do{
			a = rand()%101;
		}
		while (a<b);
		printf ("\n %d/%d=", a, b);	
		getlin (line, MAXLINE);
		system (CLEAR);
		x = atoi(line);
		if (difftime(time(NULL),tmin >= 15));
		{
			timeout(tmin);;
			continue;
		}
		if ((a/b == x) && (a%b == 0)){
			printf ("\n\n\n\t%d/%d=%d\n Правильно!\n", a,b,x);
					user.rtloc++;
			}
		else if (a/b == x)
		{
			time(&tmin);
			printf ("\n\n\n\t%d/%d=%d\n\tКакой остаток?\n",a,b,x);
			getlin (line, MAXLINE);
			if (difftime(time(NULL),tmin) >=25)
			{
				timeout(tmin);;
				continue;
			}
			if (a%b == (x = atoi(line))){
				printf ("\n\n\nПравильно. Остаток от деления %d на %d = %d\n", a,b,x);
				user.rtloc++;
			}
			else {
				printf ("\n\n\nНет. Остаток от деления %d на %d = %d\n",a,b,(a%b));
				fprintf (fp,"\t\n%d - Неверно.\n%d%%%d=%d\n",x, a, b,(a%b));
				user.wgloc++;
			}
		}
		else{
			printf ("Неверно!\n");
			fprintf (fp,"\t\n%d - Неверно.\n%d/%d=%d\n",x, a, b,(a/b));
			user.wgloc++;
		}
	}
	print_result(fp,tminex);
	progress();
	final_check();
	fclose (fp);

}
//====================================   Умножение  посложнее  ==================================/
void mux2 (void)
{
	int a,b,x,i;
	time_t tmin,tminex;
	char line[20];
	FILE *fp;
	fp = fopen (logfile, "a");
	printf ("\nУпражнение № %d. Умножение 2.", user.exe);
	fprintf (fp,"\nУпражнение № %d. Умножение 2\n.", user.exe);
	time(&tminex);
	for (i = 1; i <= EXERCISES; ++i)
	{
		time(&tmin);
		do {
			a = rand()%100;
		}
		while ((a == 0) || (a == 1));
		do {
			b = rand()%10;
		}
		while ((b == 0) || (b == 1));
		printf ("\n\t %dx%d=", a, b);
		getlin (line, MAXLINE);
		system (CLEAR);
		x = atoi(line);
		if (difftime(time(NULL),tmin) >= 20)
		{
			timeout(tmin);;
			continue;
		}
		if (a*b == x)
		{
			printf ("\n\n\n\t%dx%d=%d\n Правильно!\n", a,b,x);
			user.rtloc++;
		}
		else
		{
			printf ("\v\v\v\t%dx%d=%d  а не %d\n Неверно!\n", a, b, (a*b), x);
			fprintf (fp, "\n\t%d - Неверно.\n\t%dx%d=%d\n",x, a, b, (a*b));
			user.wgloc++;
		}
	}
	print_result(fp,tminex);
	progress();
	final_check();
	fclose (fp);

}
