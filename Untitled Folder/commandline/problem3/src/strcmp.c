#include "header.h"

int strcomp(char *str1,char *str2)
{

	int i=0;
			while( *(str1+i) != '\0') {
				if(*(str1+i) != *(str2+i)) {
					if ( *(str1+i) > *(str2+i) )
						return 0;
					else 
						return -1;
					}			   
				i++;
			}
			return 1;
	
 	
}
