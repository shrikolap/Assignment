
#include <pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"errors.h"
struct input{                                                                   
    unsigned seconds;                                                     
    char message[64];                                                           
    struct input *next;                                                         
                                                                                
}*first = NULL; 

void threadfunc (char *);

pthread_mutex_t resrc_lock = PTHREAD_MUTEX_INITIALIZER;

int main ()
{
	char line[128];
	pthread_t thread;
	struct input *cur = NULL;
	struct input *temp = NULL;
	int status;

	if (0 < (status = pthread_create(&thread, NULL, (void *)threadfunc, NULL))) {
                err_abort(status, "thread creation failed\n");                  
                exit(0);    
	}
	
	while (1) {

		printf("Alarm> ");
		if (fgets (line, sizeof (line), stdin) == NULL) {
			exit(0);
		}
		if ((strlen (line) <= 1))
			continue; 
		pthread_mutex_lock(&resrc_lock);
		cur = (struct input*)malloc(sizeof(struct input));                      
        cur->next = NULL;                  
		
		if (sscanf (line, "%u  %64[^\n]", &(cur->seconds), (cur->message) ) < 2) {                
        	printf("Bad command\n");  
			free(cur); 
			continue;
		}
		strcpy(cur->message,line);
		cur->seconds += time(NULL);

		if(!first)
			first = cur;
		else {                                                               
			temp = first;
			if (first->seconds > cur->seconds){
				cur->next = first;
				first = cur;
				continue;
			}
			while((temp->next) && (cur->seconds > temp->next->seconds))
				temp = temp->next;

			 cur->next = temp->next;                                         
             temp->next = cur;                                                   
        }
		pthread_mutex_unlock(&resrc_lock);
	}	
	return 0;
}

void threadfunc (char *l)
{

	struct input *cur = NULL;
	while(1){
		pthread_mutex_lock(&resrc_lock);
		while(!first)
			sleep(1);
		while(time(NULL) != first->seconds)
			sleep(1);
		printf("%u %lu %s\n",first->seconds,time(NULL),first->message);
		cur = first;
		first = first->next;
		free(cur);
		pthread_mutex_unlock(&resrc_lock);
	}
}

