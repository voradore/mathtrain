
#ifdef _WIN32
	#define CLEAR "cls"
#endif 
#ifdef __linux__
	#define CLEAR "clear"
#endif
#define  EXERCISES  5	/* Количество упражнений на задание*/
#define MAX_EX  6				//Максимальное количество заданий

void show_status(void);
void progress(void);

void print_result (FILE *fp, time_t starttime);
void final_check(void);
void levsel(void);
void timeout(time_t starttime);
void endlog(void);
void times_up(int sig);
int catch_signal(int sig, void (*handler)(int));

