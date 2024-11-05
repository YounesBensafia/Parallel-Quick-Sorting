#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

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

void remplirTab(int T[], int n) {
    for (int i = 0; i < n; i++) {
        T[i] = (rand() % 100);
    }
}

int Indice_pv(int T[], int debut, int fin, int pv) {
    for (int k = debut; k <= fin; k++) {
        if (T[k] == pv) {
            return k;
        }
    }
}

int parti(int T[], int debut, int fin) {
    int ip = (debut + fin)/ 2;
    int pv = T[ip]; 
    int i = debut; 
    int j = fin;  
    while (i < j) {
        while (T[i] < pv && i < j) i++;
        while (T[j] > pv && i < j) j--;    
        if (i < j){
            perm(&T[i], &T[j]);
            // i++;
            // j--;
        }
    }
    ip = Indice_pv(T, debut, fin, pv);

    if (ip > i) {
        perm(&T[ip], &T[i]);
        return i;
    }

    if (ip < i) {
        perm(&T[ip], &T[i - 1]);
        return i - 1;
    }
    return ip; 
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
    int T[100];
    int n;
    printf("Entrez la taille du tableau: ");
    scanf("%d", &n);

    srand(time(NULL));

    remplirTab(T, n);
   
    printf("Avant:\n");
    afficherTab(T, n);

    quickSort(T, 0, n - 1);


    // parti(T, 0, n-1);
    // printf("\nAprès:\n");
    // afficherTab(T, n);

}