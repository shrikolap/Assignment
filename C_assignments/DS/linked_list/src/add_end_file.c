
/*Node Add End*/

#include"list.h"

sll *add_end_file(sll *head, int data)
{
	sll *ptr = create_node_file(data);
	sll *last_node = NULL;

	if(head == NULL){
		head = ptr;
	}
	else{
		last_node = getlast_node(head);
		last_node->next = ptr;
	}
	return head;
}
