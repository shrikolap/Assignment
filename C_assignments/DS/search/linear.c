/*
	Program : To implement Binary Search
	Author : Pritam Krishna Mali.
*/
#include<stdio.h>
#define MAX 5
int main()
{
	int l_arr[MAX];
	int s_num;
	int count = 0;
	int i = 0;
	printf("\nEnter The Data");
	while(count++ < MAX)
		scanf("%d",&l_arr[count]);
	
	printf("\nEnter The Search Num");
	scanf("%d",&s_num);

	while(i++ < MAX){
		if(s_num == l_arr[i]){
			printf("\nNumber Is Found At %d Position",i);
			break;
		}
	}

	if(i == (MAX+1))
		printf("\nNumber Not Found");
	return 0;
}
