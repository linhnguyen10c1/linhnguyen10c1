#include <stdio.h>
#include<stdlib.h>
#include <math.h>
struct Node{
    int data;
    struct Node *next;
};

void push(int x,struct Node **top){
    struct Node *t;
    t=(struct Node *)malloc(sizeof(struct Node));
    if(t==NULL) printf("stack is full");
    else{
        t->data=x;
        t->next=*top;
        *top=t;
    }
}
void writeLinkedListToFile(struct Node* head, const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        fprintf(file, "%d ", current->data);
        current = current->next;
    }
    fprintf(file,"\n"); 

    fclose(file);
}
int main(){
    int n;
     printf("Enter row of matrix: ");
     scanf("%d",&n);
     struct Node **Array=(struct Node **)malloc(n*sizeof(struct Node*));
     if(n>=5){
     for(int i=0;i<n;i++){
           Array[i]=NULL;
           int x[20];
           for(int j=0;j<n-1;j++){
              scanf("%d",&x[j]);
              push(x[j],&Array[i]);
            }
            }
        }
    for(int i=0;i<n;i++){
        writeLinkedListToFile(Array[i],"DAYSO.IN");
    }    
}


