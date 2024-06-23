#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int v1;
	int v2;
	struct Node* next;
}Node;

void printList(Node* n);
void insert(struct Node** head_ref, int v1, int v2);
Node* intersection(Node* start1, Node* start2,  int (*reduce_f)(Node*, Node* ) );
int compare_by_v1(Node* node1, Node* node2);
int compare_by_v2(Node* node1, Node* node2);

int main(){
    Node* list1 = NULL;
    Node* list2 = NULL;
	
	//Burada lab3 soru pdf'indeki listeler elle insert edilmiştir.
	insert(&list1, 1, 10);
    insert(&list1, 2, 20);
    insert(&list1, 3, 5);
	insert(&list2, 2, 5);
    insert(&list2, 1, 25);
    insert(&list2, 4, 20);
	int selection=1;
    
	while(selection==1 || selection==2){
		printf("Hangi compare fonksiyonunu kullanmak istersiniz? v1:1 v2:2\n");
    	scanf("%d",&selection);
    	
		if(selection==1){
			Node* intersection_list = intersection(list1, list2, compare_by_v1);
			printf("v1'e gore kesisim listesi: ");
    		printList(intersection_list);
    		printf("\n");
		}
		
		if(selection==2){
			Node* intersection_list = intersection(list1, list2, compare_by_v2);
			printf("v2'ye gore kesisim listesi: ");
    		printList(intersection_list);
    		printf("\n");
		}
	}	
	
	return;
}

void printList(Node* n){
    while(n != NULL){
        printf("(%d, %d) ", n->v1, n->v2);
        n = n->next;
    }
    printf("\n");
    return;
}

void insert(struct Node** head_ref, int v1, int v2){
    Node* new_node = (Node*) malloc(sizeof(Node));
    Node* last = *head_ref;
    
    new_node->v1 = v1;
    new_node->v2 = v2;
    new_node->next = NULL;
    
    if(*head_ref == NULL){
        *head_ref = new_node;
        return;
    }
    
    while(last->next != NULL)
        last = last->next;
    
    last->next = new_node;
    return;
}

Node* intersection(Node* start1, Node* start2, int (*reduce_f)(Node*, Node*)) {
    Node* result = NULL;
	
	while (start1 != NULL) {
        Node* temp2 = start2;
        while (temp2 != NULL) {
            int comparison_result = reduce_f(start1, temp2);
            if (comparison_result == 1) {
                insert(&result, start1->v1, start1->v2); //Sadece 1.listedekileri ekliyorum.
            }
            temp2 = temp2->next;
        }
        start1 = start1->next;
    }
    return result;
}

int compare_by_v1(Node* node1, Node* node2) {
    if (node1->v1 == node2->v1)
        return 1;
    else
        return 0;
}

int compare_by_v2(Node* node1, Node* node2) {
    if (node1->v2 == node2->v2)
        return 1;
    else
        return 0;
}
