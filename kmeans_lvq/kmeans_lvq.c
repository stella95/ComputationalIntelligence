#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 10
#define N 900

float w[M][2], finalw[M][2];
float D[N][2];
int O[N];
float minError;

void readD(){
    FILE *infile;
    int i;
    infile = fopen("s2.txt", "r");
    for(i = 0; i < N; i++){
        fscanf(infile, "%f %f", &D[i][0], &D[i][1]);
    }
}

float distance(float p1[2], float p2[2]){
    
    float sum = pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2);
    return sqrt(sum);
}

void assignO(){
    int i, j;
    
    for(i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            if(distance(D[i], w[O[i]]) > distance(D[i], w[j])){
                O[i] = j;
            }
        }
    }
}

void newWLVQ(int i, float n){
    w[O[i]][0] = w[O[i]][0] + n*(D[i][0] - w[O[i]][0]);
    w[O[i]][1] = w[O[i]][1] + n*(D[i][1] - w[O[i]][1]);
}

void assignOLVQ(float n){
    int i, j;
    
    for(i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            if(distance(D[i], w[O[i]]) > distance(D[i], w[j])){
                O[i] = j;
            }
        }
        newWLVQ(i, n);
    }
}
void init(){
    int i, j;
    int ids[M];
    
    
    for(i = 0; i < M; i++){
       ids[i] = -1; 
    }
    
    i = 0;
    while(i < M){
        ids[i] = rand()%N;
        for(j = 0; j < i; j++){
            if(ids[i] == ids[j]){
                break;
            }
        }
        if(i == j){
            i++;
        }
    }
    
    for(i = 0; i < M; i++){
        w[i][0] = D[ids[i]][0];
        w[i][1] = D[ids[i]][1];
    }
    for(i = 0; i < N; i++){
        O[i] = rand()%M;
    }
    assignO();
}
void newW(){
    int i;
    int num[M];
    for(i = 0; i < M; i++){
        w[i][0] = 0;
        w[i][1] = 0;
        num[i] = 0;
    }
    
    for(i = 0; i < N; i++){
        w[O[i]][0] += D[i][0];
        w[O[i]][1] += D[i][1];
        num[O[i]]++;
    }
    
    for(i = 0; i < M; i++){
        w[i][0] /= num[i];
        w[i][1] /= num[i];
    }
}



float calcError(){
    float error = 0;
    int i;
    
    for(i = 0; i < N; i++){
        error += distance(D[i], w[O[i]]);
    }
    return error;
}
void bestW(int j){
    float error = calcError();
    int i;
    
    if(j == 0 || error < minError){
        for(i = 0; i < M; i++){
            finalw[i][0] = w[i][0];
            finalw[i][1] = w[i][1];
        }
        minError = error;
    }
}
void kmeans(){
    int i, j;
    float wlocal[M][2];
    
    for(j = 0; j < 5; j++){
        init();
        assignO();
        newW();
        while(1){
            for(i = 0; i < M; i++){
                wlocal[i][0] = w[i][0];
                wlocal[i][1] = w[i][1];
            }
            assignO();
            newW();
            
            for(i = 0; i < M; i++){
                if(distance(wlocal[i], w[i]) > 0.000001){
                    break;
                }
            }
            if(i == M){
                break;
            }
        }
        bestW(j);
    }
}


void lvq(){
    int i, j;
    float wlocal[M][2];
    float n = 0.1;
    
    for(j = 0; j < 5; j++){
        init();
        assignO();
        n = 0.1;
        
        while(1){
            for(i = 0; i < M; i++){
                wlocal[i][0] = w[i][0];
                wlocal[i][1] = w[i][1];
            }
            assignOLVQ(n);
            
            for(i = 0; i < M; i++){
                if(distance(wlocal[i], w[i]) > 0.000001){
                    break;
                }
            }
            if(i == M){
                break;
            }
            n = 0.95*n;
        }
        bestW(j);
    }
}

void writeW(char *name){
    FILE *outfile;
    char filename[40];
    int i;
    
    sprintf(filename, "%s_%d.txt", name, M);
    outfile = fopen(filename, "w");
    
    for(i = 0; i < M; i++){
        fprintf(outfile, "%f %f\n", finalw[i][0], finalw[i][1]);
    }
}

int main(){
    FILE *infile;
    
    int i;
    srand(time(NULL));
    readD();
    kmeans();
    writeW("kmeans");
    
    printf("M = %d\n", M);
    printf("kmeans error = %f\n", minError);
    lvq();
    writeW("lvq");
    printf("lvq error = %f\n", minError);
    
    
}