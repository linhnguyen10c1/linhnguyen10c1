#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<Windows.h>

#define MAX_ITER 1000
#define epsilon 1e-6

struct Node{
    int data;
    struct Node *next;
};
void displayMatrix(struct Node **Array){
	int i=0;
	while(Array[i]!=NULL){
		printf("|");
		struct Node *t=Array[i];
		while(t!=NULL){
			for(int k=0;k<8;k++){
				printf("-");
			}
			printf("%8d|",t->data);
			t=t->next;
		}
		printf("|");
		printf("\n");
		i++;
	}
	
}
void SET_COLOR(int color)
{
	WORD wColor;
     

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
}
void swap(double *a,double *b){
    float temp=*a;
    *a=*b;
    *b=temp;
}
void push(int x, struct Node **top){
    struct Node *t;
    t=(struct Node *)malloc(sizeof(struct Node));
    if(t==NULL) printf("stack is full");
    else{
        t->data=x;
        t->next=*top;
        *top=t;
    }
}
void display(struct Node *t){
	while(t!=NULL){
		SET_COLOR(11);
		printf("%8d|",t->data);
		t=t->next;
	}
	printf("\n");
}
void readMatrixFromFile(double** a, const char* filename, int n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dont open file.\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fscanf(file, "%lf", &a[i][j]);
        }
    }

    fclose(file);
}
void readMatrixFromFile1(const char* filename,int n,struct Node **Array){
	FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dont open file.\n");
        return;
    }
     for(int i = 0; i < n; i++) {
     	Array[i]=NULL;
     	int h[20];
        for(int j = 0; j < n-1; j++) {
            fscanf(file, "%d", &h[j]);
            push(h[j],&Array[i]);
            
        }
    }

    fclose(file);
}
void writeLinkedListToFile(struct Node* head, const char* filename) {
    FILE* file = fopen(filename, "a");
    if (file == NULL) {
        printf("Dont open file.\n");
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
void writeVectorToFile(double* x, const char* filename, int n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Dont open file.\n");
        return;
    }

    for(int i = 0; i < n; i++) {
        fprintf(file, "%lf\n", x[i]);
    }

    fclose(file);
}
// check ma tran co bao nhieu nghiem
void addColumn(double** a, double* b, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        a[i] = (double*)realloc(a[i], (n + 1) * sizeof(double));
    }

    for (i = 0; i < n; i++) {
        a[i][n] = b[i];
    }
}
void removeColumn(double** a, int n) {
    int i;
    for (i = 0; i < n; i++) {
        a[i] = (double*)realloc(a[i], n * sizeof(double));
    }
}
int Check_N(double** a, double* b,int n){
    int i,j,k=0,c,m=0;
    addColumn( a,b,n); 
    float pro=0;
    for(i=0;i<n;i++){
        if(a[i][i]==0){
            c=1;
            while((i+c)<n&&a[i+c][i]==0) c++;
            if((i+c)==n){
                break;
            }
            for(j=i,k=0;k<=n;k++){
                swap(&a[j][k],&a[j+c][k]);
            }
        }
        for(j=0;j<n;j++){
            if(i<j){
                float pro=a[j][i]/a[i][i];
                for(k=0;k<=n;k++){
                    a[j][k]=a[j][k]-(a[i][k])*pro;
                }
            }
        }
    }
    if(a[n-1][n]==0&&a[n-1][n-1]==0) return 1;
    else if(a[n-1][n]!=0&&a[n-1][n-1]==0) return 2;
    else return 3;
}
//check dieu kien hoi tu ma tran
int Check_Matrix(double** a,int n){
	for(int i=0;i<n;i++){
		double s=0;
		for(int j=0;j<n;j++){
			if(i!=j) s+=fabs(a[i][j]);
		}
		if(s>=a[i][i]||a[i][i]==0) return 0;
	}
	return 1;
}
//pp lap don
void interetiveMethod(double** r, double* b, double* x, int n) {
    double* y = (double*)malloc(n * sizeof(double));
    int iter = 0, t;

    do {
        t = 0;
        SET_COLOR(8);
            for(int i=0;i<n;i++){
        printf("|");
        for(int j=0;j<10;j++){
            printf("-");
        }
    }
    printf("|");
    printf("\n");
    printf("|");
    for(int i=0;i<n;i++){
        printf("%10lf|",x[i]);
    }
    printf("\n");
        for(int i = 0; i < n; i++) {
            double S = 0;
            for(int j = 0; j < n; j++) {
                if(j != i) {
                    S += r[i][j] * x[j];
                }
            }
            y[i] = (b[i] - S) / r[i][i];
            if(fabs(x[i] - y[i]) >= epsilon) {
                t = 1;
            }
        }
            for(int i=0;i<n;i++){
            x[i] = y[i];
        }
        iter++;
    } while(t && iter < MAX_ITER);

    free(y);
}
//pp Gauss
void  Gauss(double** a, double* x, int n){
    int i,j,k=0,c,m=0;
    float pro=0;
    for(i=0;i<n;i++){
        if(a[i][i]==0){
            c=1;
            while((i+c)<n&&a[i+c][i]==0) c++;
            if((i+c)==n){
                break;
            }
            for(j=i,k=0;k<=n;k++){
                swap(&a[j][k],&a[j+c][k]);
            }
        }
        for(j=0;j<n;j++){
            if(i!=j){
                float pro=a[j][i]/a[i][i];
                for(k=0;k<=n;k++){
                    a[j][k]=a[j][k]-(a[i][k])*pro;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
    	x[i]=a[i][n]/a[i][i];
	}
}
void Checkresult(double *x,struct Node **Array,int n, double *b){
       int i=0;
       while(i<n){
        double sum=0;
        int j=0;
        struct Node *t=Array[i];
            while(j<n){
                sum+=(x[j]*(t->data));
                t=t->next;
                j++;
            }
            printf("check fuction B'[%d]=%lf and B[%d]=%lf\n",i,sum,i,b[i]);
            printf("saiso:%lf\n",fabs(sum-b[i]));
            i++;
       }
}
int main(){
	SET_COLOR(10);
    printf("DO YOU WANT ENTER DATA FROM KEYBOARD OR FILE\n");
    SET_COLOR(13);
    printf("Type 1 to enter data from keyboard\n");
    SET_COLOR(13);
    printf("Type 2 to enter data from file\n");
    int choice;
    scanf("%d",&choice);
   SET_COLOR(14);
           int n;
           printf("Enter row of matrix: ");
           scanf("%d",&n);
           struct Node **Array=(struct Node **)malloc(n*sizeof(struct Node*));

    switch(choice){
        case 1:{
           for(int i=0;i<n;i++){
           Array[i]=NULL;
           int x[20];
           for(int j=0;j<n-1;j++){
              scanf("%d",&x[j]);
              push(x[j],&Array[i]);
            }
            }
         break;
        }
        case 2:
    {   
           readMatrixFromFile1("DAYSO.IN",n,Array);
           
 break;}
    }
  SET_COLOR(11);
             printf("\nResult matrix:\n");
             
        for(int i=0;i<n;i++){
        	printf("|");
        	for(int j=0;j<n-1;j++){
               for(int k=0;k<8;k++){
				printf("-");
			}
			printf("|");
		}
		printf("\n");
		printf("|");
		display(Array[i]);
		}
		printf("|");
		for(int j=0;j<n-1;j++){
		for(int k=0;k<8;k++){
			printf("-");
		}
		printf("|");
	}
	printf("\n");
        //them phan tu moi
        SET_COLOR(14);
        printf("\nEnter element need add in each linklist:\n");
         int l;
        for(int i=0;i<n;i++){
    	scanf("%d",&l);
    	push(l,&Array[i]);
    	writeLinkedListToFile(Array[i], "RESULT1.OUT");
        }
        //ma tran sau khi them
        SET_COLOR(11);
        printf("\nMatrix after add new element:\n");
        for(int i=0;i<n;i++){
        	printf("|");
        	for(int j=0;j<n;j++){
               for(int k=0;k<8;k++){
				printf("-");
			}
			printf("|");
		}
		printf("\n");
		printf("|");
		display(Array[i]);
		}
		printf("|");
		for(int j=0;j<n;j++){
		for(int k=0;k<8;k++){
			printf("-");
		}
		printf("|");
	}
	printf("\n");
        
        
    //tao ma tran B, va doc ma tran A    
        double** a = (double**)malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++) {
        a[i] = (double*)malloc(n * sizeof(double));
    }
    double* b = (double*)malloc(n * sizeof(double));
    double* x = (double*)malloc(n * sizeof(double));
	 readMatrixFromFile(a, "RESULT1.OUT", n);
	 SET_COLOR(14);
    printf("\nEnter matrix B:\n");
    for(int i = 0; i < n; i++) {
        scanf("%lf", &b[i]);
    }
    //check co bn nghiem
    int w=Check_N(a,b,n);
    SET_COLOR(12);
    if(w==1) printf("\nInfinite Equation\n");
    else if(w==2) printf("\nThe Equation has no Solution\n");
    else if (w==3){
    //neu co mot nghiem    
	 printf("\nEquation");
    int q=Check_Matrix(a,n);
    //check ma tran co dk hoi tu 
     if(q==1){
     	double** r = (double**)malloc(n * sizeof(double*));
    for(int i = 0; i < n; i++) {
        r[i] = (double*)malloc(n * sizeof(double));
    }
    readMatrixFromFile(r, "RESULT1.OUT", n);
    SET_COLOR(14);
     	printf("\nEnter first value for x:\n");
        for(int i = 0; i < n; i++) {
        scanf("%lf", &x[i]);
        }
        interetiveMethod(r, b, x, n);
    for(int k=0;k<n;k++){
        printf("|");
        for(int h=0;h<10;h++){
            printf("-");
        }
    }
    printf("|");
    printf("\n");
    }
    //neu ko thoa man sd pp Gauss
    else if(q==0){
    	int ch=0;
    	SET_COLOR(12);
    	printf("\nif you want to try Gauss method type 3: ");
    	scanf("%d",&ch);
    	if(ch==3){
    		Gauss(a,x,n);
		}	
	}    
    writeVectorToFile(x, "RESULT2.OUT", n);
    printf("\n");
    SET_COLOR(11);
    printf("\nRESULT X:\n");
    for(int i=0;i<n;i++){
        printf("|");
        for(int j=0;j<10;j++){
            printf("-");
        }
    }
    printf("|");
    printf("\n");
    printf("|");
    for(int i=0;i<n;i++){
        printf("%10lf|",x[i]);
    }
    printf("\n");
    for(int k=0;k<n;k++){
        printf("|");
        for(int h=0;h<10;h++){
            printf("-");
        }
    }
    printf("|");
    printf("\n");
    
    printf("\n");

    Checkresult(x,Array,n,b);


    for(int i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
    free(x);
    
         }
    
}


