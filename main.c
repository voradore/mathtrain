#include "headers.h"
#include "main.h"


static char name[MAXLINE];

char *logfile = "train_result.txt";

int main (void)
{	

	catch_signal(SIGALRM, times_up);
	srand(time(NULL));
	struct tm *tmp;
	time_t seconds;

	FILE *fp;
	char line[MAXLINE], tmprint[60]; //надо изучить длину массива для вывода времени tmprint
	int size = sizeof userlist;
	setlocale(LC_ALL, "");

	fp = fopen (logfile, "a");
	fprintf(fp, "\n==========================================================================\n");
	getuser(name);
	fprintf (fp, "\n Решает %s",name);
	seconds = time(NULL);
	tmp = localtime(&seconds);
	strftime(tmprint,sizeof tmprint,"\nНачало %d %B %Y\n%X\n", tmp);
	fprintf(fp,"%s",tmprint);
	fclose (fp);
	levsel();
	while (user.exe <= MAX_EX)
	{
		switch (user.exe)
		{
		case 1:	show_status();
				sum1 ();
				break;
		case 2:	show_status();
				dif1 ();
				break;
		case 3:	show_status();
				mux1 ();
				break;
		case 4:	show_status();
				div1 ();
				break;
		case 5: show_status();
				div2 ();
				break;
		case 6:	show_status();
				mux2 ();
				break;
		default: user.exe=MAX_EX+1;
			restabl();
			printf ("Конец!");
			break;
		}
	}
	endlog();
	printf ("\n\n Нажми Enter для выхода\n");
	getchar();
	return 0;
}

/*==================================  Функции   =====================================================*/
void timeout(time_t t)
{
	double tdif;
	tdif=difftime(time(NULL),t);
	FILE *fp;
	fp = fopen (logfile, "a");
	printf ("Слишком долго. %d секунд.\n", (int)tdif);
	fprintf (fp, "\n\tВремя вышло! %d секунд.\n", (int)tdif);
	fclose (fp);
	user.wgloc++;
}

void levsel(void)
{
	char line[5];
	int a;
	if (user.lvl<6)
		user.exe=1;
	else 
	{

		do{
		printf ("Выберите задание от 1 до %d: ", user.lvl/3);
		getlin(line,5);
		a = atoi (line);
		}
		while (a > user.lvl/3 || a < 1);
		user.exe = a;
	}
}

void show_status(void)
{
	printf ("\n|---------------------------------|\n");
	printf ("| Уровень:\t\t%9d |\n", user.lvl);
	printf ("| Правильных ответов:\t%9d |\n", user.rttot);
	printf ("| Неправильных ответов:\t%9d |\n", user.wgtot);
	if ((user.rttot+user.wgtot)!= 0)
		printf ("| Точность:\t\t%8.2f%% |\n", ((float)user.rttot*100/(user.rttot+user.wgtot)));
	else
		printf ("| Точность:\t\t%8.2f%% |\n", 0.0);
	printf ("| Очки опыта:\t\t%9d |\n", user.pts);
	printf ("| Следующий уровень:\t%9d |\n",user.nxlev);
	printf ("|---------------------------------|\n");
	printf ("Enter - следующее задание.\ns - выход.");
	char c;
	c = getchar();
	if (c == 's')
	{
		getchar();
		printf("Точно выйти? y/n\n");
		if ((c = getchar()) == 'y' || c == 'Y')
			{
				restabl();
				endlog();
				exit (0);
			}
		getchar();
	}
	else if (c != '\n')
		while ((c=getchar()) != '\n');
}
//-----------------------------------------------------------------++++++++++++++++++++++++++++++++
void print_result (FILE *fp, time_t tmstart)
{
	double tmdiff;
	tmdiff = difftime(time(NULL), tmstart);
	printf ("|---------------------------------|\n");
	printf ("| Потрачено на упражнение %3d мин %2d сек.\t  |\n", (int)tmdiff/60, (int)tmdiff%60);
	printf ("| Правильно:\t\t\t%d |\n", user.rtloc);
	printf ("| Неправильно:\t\t\t%d |\n", user.wgloc);
	printf ("| Результат:\t\t%8.2f%% |\n", ((float)user.rtloc*100/(user.rtloc+user.wgloc)));
	printf ("|---------------------------------|\n");
	
	fprintf (fp,"Правильно:\t\t%d\n", user.rtloc);
	fprintf (fp,"Неправильно:\t\t%d\n", user.wgloc);
	fprintf (fp,"Результат:\t%.2f%%\n", ((float)user.rtloc*100/(user.rtloc+user.wgloc)));
	fprintf (fp,"----------------------------------------\n");

}

void progress(void)
{
	int x;
	user.rttot += user.rtloc;
	user.wgtot += user.wgloc;
	user.resloc = (user.rtloc*100/(user.rtloc+user.wgloc));
	user.rtloc = user.wgloc = 0;
	user.restot = (user.rttot*100/(user.rttot+user.wgtot));


	if (user.resloc == 100)		//Получение очков
		user.pts+=user.exe;
	else if (user.pts > 0)
		user.pts--;
	if (user.pts>= user.nxlev)		//Повышение уровня
	{
		user.lvl++;
		user.nxlev+=(2*user.lvl);
		printf ("Уровень повышен до %d", user.lvl);
	}
	else if ((user.resloc <= 50) && (user.lvl>0))   //Понижение уровня
	{
		user.nxlev-=(user.lvl);
		user.lvl--;
		user.pts = user.nxlev/2;
		printf ("\nУровень понижен до %d", user.lvl);
	}
	else if (user.resloc <= 50)
	{
		user.pts = 0;
		user.nxlev = 3;
		printf ("\nВсе твои очки сгорели\n");
	}
	pushuser(name);
	savestat(sizeof userlist);
}

void final_check(void)
{
	if ((user.lvl+1)>user.exe&&user.resloc>=100)
		user.exe++;
	if (user.lvl<user.exe&&user.exe>1)
		user.exe--;
}
void endlog(void)
{
	FILE *fp;
	char tmprint[60];
	fp = fopen (logfile, "a");
	time_t seconds = time(NULL);
	struct tm *tmp = localtime(&seconds);
	strftime(tmprint,sizeof tmprint,"%d %B %Y\n%X\n", tmp);
	fprintf(fp,"Конец %s",tmprint);
	fclose (fp);
}

void times_up(int sig)
{
	puts("Слишком долго!");
	user.wgloc++;
	exit(0);
}

int catch_signal(int sig, void (*handler)(int))
{
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return sigaction (sig, &action, NULL);
}



