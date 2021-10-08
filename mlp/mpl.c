#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 3000
#define B (N/100)

#define d 2
#define K 4

#define H1 7
#define H2 4

#define isSigmoid 0

#define n 0.0001

float Dtrain[N][d], Dtest[N][d];
int DtrainC[N][K],DtestC[N][K];

float Y01[d];
float w01[H1][d], b1[H1], u1[H1], Y12[H1], d1[H1], dEw01[H1][d], dEb1[H1];
float w12[H2][H1], b2[H2], u2[H2], Y23[H2], d2[H2], dEw12[H2][H1], dEb2[H2];
float w23[K][H2], b3[K], u3[K], d3[K], dEw23[K][H2], dEb3[K];


void forward_pass(float *x, float *y);
void backprop(float *x, int *t);
void gradient_descent();
void testMLP();

void main(){
    FILE *infile;
    int i, j;
    
    srand(time(NULL));
    infile = fopen("trainS1.txt","r");
    
    for(i = 0; i < N; i++){
        for(j = 0; j < K; j++){
            DtrainC[i][j] = 0;
            DtestC[i][j] = 0;
        }
    }
    for(i = 0; i < N; i++){
        fscanf(infile,"%f %f %d %d %d %d", &Dtrain[i][0],&Dtrain[i][1],&DtrainC[i][0],&DtrainC[i][1],&DtrainC[i][2],&DtrainC[i][3]);
    }
    
    fclose(infile);
    infile = fopen("testS1.txt","r");
    
    for(i = 0; i < N; i++){
        fscanf(infile,"%f %f %d %d %d %d", &Dtest[i][0], &Dtest[i][1], &DtestC[i][0], &DtestC[i][1], &DtestC[i][2], &DtestC[i][3]);
    }
    
    fclose(infile);
    
    
    for(i = 0; i < H1; i++){
        b1[i] = (rand()/(float)RAND_MAX)*2 -1;
        for(j = 0; j < d; j++){
            w01[i][j] = (rand()/(float)RAND_MAX)*2 -1;
        }
    }

    for(i = 0; i < H2; i++){
        b2[i] = (rand()/(float)RAND_MAX)*2 -1;
        for(j = 0; j < H1; j++){
            w12[i][j] = (rand()/(float)RAND_MAX)*2 -1;
        }
    }

    for(i = 0; i < K; i++){
        b3[i] = (rand()/(float)RAND_MAX)*2 -1;
        for(j = 0; j < H2; j++){
            w23[i][j] = (rand()/(float)RAND_MAX)*2 -1;
        }
    }
    
   
    for(i = 0; i < H1; i++){
        dEb1[i] = 0;
        for(j = 0; j < d; j++){
            dEw01[i][j] = 0;
        }
    }

    for(i = 0; i < H2; i++){
        dEb2[i] = 0;
        for(j = 0; j < H1; j++){
            dEw12[i][j] = 0;
        }
    }

    for(i = 0; i < K; i++){
        dEb3[i] = 0;
        for(j = 0; j < H2; j++){
            dEw23[i][j] = 0;
        }
    }
    
    gradient_descent();
    testMLP();
    
}



void forward_pass(float *x, float *y){
    int i,j;

    for(i = 0; i < d; i++){
        Y01[i] = x[i];
    }

    for(i = 0; i < H1; i++){
        u1[i] = b1[i];
        for(j = 0; j< d; j++){
            u1[i] = u1[i] + w01[i][j]*Y01[j];
        }
        
        Y12[i] = tanh(u1[i]);
    }

    for(i = 0; i < H2; i++){
        u2[i] = b2[i];
        for(j = 0; j < H1; j++){
            u2[i] = u2[i] + w12[i][j]*Y12[j];
        }
        if(isSigmoid == 1){
            Y23[i] = 1.0/(1.0+exp(-1.0*u2[i]));  
        }
        else{
            Y23[i] = u2[i];
        }
        
    }	

    for(i = 0; i < K; i++){
        u3[i]=0;
        for(j = 0; j < H1; j++){
            u3[i] = u3[i] + w23[i][j]*Y23[j];
        }
        u3[i] = u3[i] + b3[i];
        y[i] = 1.0/(1.0+exp(-1.0*u3[i]));
    }
}

void backprop(float *x, int *t){
    float y[K];
    float sum;
    int i,j;


    forward_pass(x,y);

    for(i = 0; i < K; i++){
        d3[i] = y[i]*(1.0-y[i])*(y[i]-(float)t[i]);
    }

    for(i = 0; i < K; i++){
        dEb3[i] += d3[i];
        for(j = 0; j < H2; j++){
            dEw23[i][j] += d3[i]*Y23[j];
        }
    }
    
    
    for(i = 0; i < H2; i++){
        sum = 0;
        for(j = 0;j < K; j++){
            sum += w23[j][i]*d3[j];
        }
        if(isSigmoid == 1){
            d2[i] = Y23[i]*(1.0-Y23[i])*sum;
        }
        else{
            d2[i] = sum;
        }
        
    }

    for(i = 0; i< H2; i++){
        dEb2[i] += d2[i];
        for(j = 0; j < H1; j++){
            dEw12[i][j] += d2[i]*Y12[j];
        }
    }
    
    for(i = 0; i < H1; i++){
        sum=0;
        for(j = 0; j < H2; j++){
            sum += w12[j][i]*d2[j];
        }
        d1[i]=(1.0 - tanh(u1[i])*tanh(u1[i]))*sum;
    }
 
    for(i = 0; i < H1; i++){
        dEb1[i] += d1[i];
        for(j = 0; j < d; j++){
            dEw01[i][j] += d1[i]*Y01[j];
        }
    }
}

void gradient_descent(){
    int epoch = 0;
    float y[K];
    float error, error0;
    int i, j, k;
    
    do{
        error0 = error;
        
        for(k = 0; k < N; k++){
            backprop(Dtrain[k],DtrainC[k]);
            if(k % B == 0){
                for(i = 0; i < H1; i++){
                    b1[i] -= n*dEb1[i];
                    for(j = 0; j < d; j++){
                        w01[i][j] -= n*dEw01[i][j];
                    }
                }

                for(i = 0; i < H2; i++){
                    b2[i] -= n*dEb2[i];
                    for(j = 0; j < H1; j++){
                        w12[i][j] -= n*dEw12[i][j];
                    }
                }

                for(i = 0; i < K; i++){
                    b3[i] -= n*dEb3[i];
                    for(j = 0; j < H2; j++){
                        w23[i][j] -= n*dEw23[i][j];
                    }
                }
                
                
                
                for(i = 0; i < H1; i++){
                    dEb1[i] = 0;
                    for(j = 0; j < d; j++){
                        dEw01[i][j] = 0;
                    }
                }

                for(i = 0; i < H2; i++){
                    dEb2[i] = 0;
                    for(j = 0; j < H1; j++){
                        dEw12[i][j] = 0;
                    }
                }

                for(i = 0; i < K; i++){
                    dEb3[i] = 0;
                    for(j = 0; j < H2; j++){
                        dEw23[i][j] = 0;
                    }
                }
            }
            
        }
    
        
        error = 0;
        for(i = 0; i < N; i++){
            forward_pass(Dtrain[i],y);
            
            for(j = 0; j < K; j++){
                error += (y[j] - (float)DtrainC[i][j])*(y[j] - (float)DtrainC[i][j]);
            }
        }
        error /= 2.0;
        
        epoch++;
        if(epoch >= 500 && fabs(error - error0) < 0.001)
                break;
        
        printf("epoch: %d  error: %f\n", epoch, error);
    }while(1);
}

void testMLP(){
    int i,j;
    float y[K];
    int c;
    int hit = 0;
    FILE *outfile1, *outfile2;
    float hitRatio;
    
    outfile1 = fopen("correct.txt","w");
    outfile2 = fopen("wrong.txt","w");
    
    for(i = 0; i < N; i++){
        forward_pass(Dtest[i],y);
        
        c = 0;
        for(j = 0; j < K; j++){
            if(y[c] < y[j]){
                c = j;
            }
        }
        
        if(DtestC[i][c] == 1){
            hit++;
            fprintf(outfile1,"%f %f\n", Dtest[i][0], Dtest[i][1]);
        }
        else{
            fprintf(outfile2,"%f %f\n", Dtest[i][0], Dtest[i][1]);
        }
    }
    
    hitRatio = 100*hit/(float)N;
    printf("Hit ratio = %f\n", hitRatio);
    if(isSigmoid == 1){
        printf("%d\t%d\t%d\tsigmoid\t%f\n", H1, H2, B, hitRatio);
    }
    else{
        printf("%d\t%d\t%d\tlinear\t%f\n", H1, H2, B, hitRatio);
    }
    
    
    fclose(outfile1);
    fclose(outfile2);
}