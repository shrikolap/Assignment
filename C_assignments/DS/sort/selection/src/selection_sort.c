#include"sel.h"                                                                 
                                                                                
int selection_sort(int *arr)                                                    
{                                                                               
    int i;                                                                      
    int j;                                                                      
    int min;                                                                    
    int temp;                                                                   
                                                                                
                                                                                
    for(i = 0; i < MAX-1; i++){                                                 
        min = i;                                                                
        for(j = i+1; j < MAX; j++){                                             
            if(arr[min] > arr[j])                                               
                min = j;                                                        
        }                                                                       
        temp = arr[i];                                                          
        arr[i] = arr[min];                                                      
        arr[min] = temp;                                                        
    }                                                                           
                                                                                
    printf("\nData::");                                                         
     for(i = 0; i < MAX; i++)                                                   
           printf("%d ",arr[i]);                                                
    return 0;                                                                   
}
