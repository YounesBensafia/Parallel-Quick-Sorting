#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdbool.h>


void perm(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void afficherTab(int T[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%4d|", T[i]);
    }
    printf("\n");
}

bool exist(int x,int T[],int n){
for (int i = 0; i < n; i++)
if(x==T[i])return true;
return false;

}

void remplirTab(int T[], int n) {
    int x;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        do
        x=rand() % (n+1);
        while(exist(x,T,n));
        T[i] = x;
    }
    
}

int* generate(int n) {
    int* table = (int*)malloc(n * sizeof(int)); 
    int x;
    if (table == NULL) { 
        printf("Memory allocation failed.\n");
        return NULL;
    }
    
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        
        do{
        x=rand() % (n+1);
        //printf("%d",x);
        x=x+rand() % (n+1);
        printf(" %d",x);
        }
        while(exist(x,table,n));
         
        printf(" put %d \n",x);
        table[i] = x;
    }

    return table;
}

int parti(int T[], int debut, int fin) {
    int ip = (debut + fin)/ 2;
    int pv = T[ip]; 
    int i = debut; 
    int j = fin;  
    while (i < j) {
        while (T[i] < pv ) i++;
        while (T[j] > pv ) j--;    
        if (i < j){
            perm(&T[i], &T[j]);
        }
    }
    
    return i; 
}

void quickSort(int T[], int debut, int fin) {
    int ip = parti(T, debut, fin);
    printf("T[%d]=%d\n",ip,T[ip]);
    if (debut < fin) {
            pid_t left_child = fork();
            if (left_child == 0) {
                if (ip > debut)
                {
                 quickSort(T, debut, ip-1);
                } 
                 exit(0);
            }
            pid_t right_child = fork();
            if (right_child == 0) {
                if (ip < fin)
                {
                    quickSort(T, ip + 1, fin);
                }                
            exit(0);
        }

        wait(NULL);
        wait(NULL);

        char left_filename[20], right_filename[20];
    }
}

int main() {
    int n=10;
    int* T=generate(n);
    
    //printf("Entrez la taille du tableau: ");
    //scanf("%d", &n);

    
for (int i ;i<2;i++){
    T=generate(n);
   
    printf("Avant:\n");
    afficherTab(T, n);

    quickSort(T, 0, n - 1);
}

    // parti(T, 0, n-1);
    // printf("\nAprès:\n");
    // afficherTab(T, n);

}
