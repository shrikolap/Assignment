#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include <sys/mman.h>                                                           
#include <sys/stat.h>                                                           
#include <fcntl.h>                                                              
#include <string.h>       
#include <semaphore.h>
#define MAX 64                                                                  
#define PAGE_SIZE 4096                                                          

int main(void)                                                                  
{                    
	sem_t *sv;
	char buf[MAX];                                                              
	int fd;                                                                     
	char *addr;

	if(-1 == (fd = shm_open("/shm", O_RDWR | O_CREAT, 0666))) {                 
		perror("creating shm object failed\n");                                 
		exit(EXIT_FAILURE);                                                     
	}                                                                           

	if(SEM_FAILED == (sv = sem_open("/semaphore", O_CREAT, 0666, 1u))) {
		perror("Semaphore creation fialed\n");
		exit(1);
	}

	if(-1 == (ftruncate(fd, PAGE_SIZE)))  {                                     
		perror("ftrucate failed\n");                                            
		exit(1);                                                                
	}                                                                           

	if((void*) -1 == (addr = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0))) {
		perror("mmap failed\n");
		exit(1);
	}

	if(-1 == sem_wait(sv)) {
		perror("wait failed\n");
		exit(1);
	}

	if(NULL == fgets(buf, MAX, stdin)) {                                    
		perror("fgets failed\n");                                           
		exit(1);                                                            
	}
	
	memcpy(addr, buf, MAX);                                         

	if(-1 == (write(1, addr, strlen(buf)))){
		perror("write failed\n");
		exit(1);
	}

	if(-1 == munmap(addr, PAGE_SIZE)) {                                         
		perror("munmap failed\n");                                              
		exit(1);                                                                
	} 
	
	if(-1 == (sem_post(sv))) {
		perror("post failed\n");
		exit(1);
	}

	if(-1 == close(fd)) {
		perror("close failed\n");
		exit(1);
	}

	return 0;                                                                   
}                                                                                  
