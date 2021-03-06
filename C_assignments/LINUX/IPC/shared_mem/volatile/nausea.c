#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

/*Macro*/
#define SHM_SIZE 512
#define SHM_NAME "/shm"
int main( void )
{
	int f_trunk;
	const size_t region_size = sysconf(_SC_PAGE_SIZE);
		

	int fd = shm_open(SHM_NAME, O_CREAT | O_TRUNC | O_RDWR, 0666);

	if(fd == -1){
		printf("\nshm_open:failed");
		exit(EXIT_FAILURE);
	}
	
	f_trunk =ftruncate(fd, region_size);

	if (f_trunk != 0){
		printf("\nftuncate:failed");
		exit(EXIT_FAILURE);
	}
	
	int *ptr = (int *)mmap(0, region_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED)
	{
		printf("\nmmap:Failed");
		exit(EXIT_FAILURE);	
	}	
	
	*(ptr + 0) = 80;

	getchar();

	*(ptr + 0) = 85;
	
	
	if(munmap(ptr, region_size) != 0 )
		printf("\nmunmap:failed");


	if(close(fd) != 0)
		printf("shm_unlink:failed");	
	
	return 0;
}


