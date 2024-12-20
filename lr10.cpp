#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include  <queue>
#include <limits.h>
using namespace std;

int **createOG(int size) {
    int **G;
    G = (int **)malloc(size*sizeof(int *));
    for (int i = 0; i < size; i++){
        G[i] = (int*)malloc(size*sizeof(int));
    }
    for (int i=0; i<size; i++){
        for (int j=i; j<size; j++){
            G[i][j] = (rand()%2);
            if (G[i][j]==1) G[i][j]=G[i][j]*rand()%30;
            if (i == j) G[i][j] = 0;
            G[j][i] = G[i][j];
        }
    }
    return G;
}

int **createNG(int size) {
    int **G;
    G = (int **)malloc(size*sizeof(int *));
    for (int i = 0; i < size; i++){
        G[i] = (int*)malloc(size*sizeof(int));
    }
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            G[i][j] = (rand()%2);
            if (G[i][j]==1) G[i][j]=G[i][j]*rand()%30;
            if (i == j) G[i][j] = 0;
        }
    }
    return G;
}

int printG(int **G ,int size) {
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            printf("%d ",G[i][j]);
        }
    printf("\n");
    }
    return 0;
}

void BFSD(int **G, int s,int size, int *dist){
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    while (!q.empty()){
        s = q.front();
        q.pop();
        for (int i=0; i<size; i++) {
            if (G[s][i]>0 && dist[i] > dist[s] + G[s][i]) {
                q.push(i);
                dist[i]=dist[s]+G[s][i];
            }
        }
    }
    return;

}

int main() {
    srand(time(NULL));
    int *exOG;
    int *exNG;
    int D;
    int R;
    int sizeOG;
    int sizeNG;
    int **oG;
    int **nG;
    int **distMatrixOG;
    int **distMatrixNG;
    int *distOG = NULL;
    int *distNG = NULL;
    printf("Введите количество вершин ориентированного графа: ");
    scanf("%d", &sizeOG);
    oG = createOG(sizeOG);
    printf("Введите количество вершин неориентированного графа: ");
    scanf("%d", &sizeNG);
    oG = createOG(sizeOG);
    nG = createNG(sizeNG);
    distMatrixOG = createOG(sizeOG);
    distMatrixNG = createNG(sizeNG);
    distOG = (int*)malloc(sizeOG*sizeof(int));
    distNG = (int*)malloc(sizeNG*sizeof(int));
    printf("Неориентированный граф: \n");
    printG(oG, sizeOG);
    printf("\n");
    printf("Ориентированный граф: \n");
    printG(nG, sizeNG);
    printf("\n");
    exOG = (int*)malloc(sizeOG*sizeof(int));
    exNG = (int*)malloc(sizeNG*sizeof(int));

    
    for (int i=0;i<sizeOG;i++) {
        for (int k=0;k<sizeOG;k++) {
            distOG[k] = 1000;
        }
        BFSD(oG,i,sizeOG,distOG);
        for (int j=0;j<sizeOG;j++) {
            distMatrixOG[j][i] = distOG[j];
        }    
    }
    printf("\n");
    printf("Матрица расстояний для неориентированного графа: \n");
    printG(distMatrixOG, sizeOG);
    printf("\n");
    for (int i=0;i<sizeOG;i++) {
        int maxV = -2;
        for (int j=0;j<sizeOG;j++) {
            if (distMatrixOG[j][i]>maxV) maxV = distMatrixOG[j][i];
        }
        exOG[i] = maxV;
        printf("%d ", exOG[i]);
    }
    printf("\n");
    R = 120;
    D = -2;
    for (int i=0;i<sizeOG;i++) {
        if (exOG[i]<R and exOG[i]!=0) R = exOG[i];
        if (exOG[i]>D and exOG[i]!=0) D = exOG[i];
    }
    printf("Радиус неориентированного графа: %d\n",R);
    printf("Диаметр неориентированного графа: %d\n",D);
    for (int i=0;i<sizeOG;i++) {
        if (exOG[i]==R) printf("Вершина %d является центральной.\n",i);
        if (exOG[i]==D) printf("Вершина %d является периферийной.\n",i);
    }
    printf("\n");



    for (int i=0;i<sizeNG;i++) {
        for (int k=0;k<sizeNG;k++) {
            distNG[k] = 1000;
        }
        BFSD(nG,i,sizeNG,distNG);
        for (int j=0;j<sizeNG;j++) {
            distMatrixNG[j][i] = distNG[j];
        }    
    }
    printf("\n");
    printf("Матрица расстояний для ориентированного графа: \n");
    printG(distMatrixNG, sizeNG);
    printf("\n");
    for (int i=0;i<sizeNG;i++) {
        int maxV = -2;
        for (int j=0;j<sizeNG;j++) {
            if (distMatrixNG[i][j]>maxV) maxV = distMatrixNG[i][j];
        }
        exNG[i] = maxV;
        printf("%d ",exNG[i]);
    }
    printf("\n");
    R = 120;
    D = -2;
    for (int i=0;i<sizeNG;i++) {
        if (exNG[i]<R and exNG[i]!=0) R = exNG[i];
        if (exNG[i]>D and exNG[i]!=0) D = exNG[i];
    }
    printf("Радиус ориентированного графа: %d\n",R);
    printf("Диаметр ориентированного графа: %d\n",D);
    for (int i=0;i<sizeNG;i++) {
        if (exNG[i]==R) printf("Вершина %d является центральной.\n",i);
        if (exNG[i]==D) printf("Вершина %d является периферийной.\n",i);
    }
    printf("\n");

    return 0;
}
