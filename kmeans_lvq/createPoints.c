#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 3000
#define N 150

void pointsS1(){
    float points[M][2];
    int i, j;
    FILE *outfile;
    int category;
    float r;
    outfile = fopen("trainS1.txt", "w");
    
    for(i = 0; i < 3000; i++){
        do{
            
            points[i][0] = (rand()/(float)RAND_MAX)*2 - 1;
            points[i][1] = (rand()/(float)RAND_MAX)*2 - 1;
            
            for(j = 0; j < i; j++){
                if(points[i][0] == points[j][0] && points[i][0] == points[j][1]){
                    break;
                }
            }
        }while(i > j);
        
        if(points[i][0]*points[i][0] + points[i][1]*points[i][1] < 0.25){
            category = 1;
            r = (rand()/(float)RAND_MAX);
            if(r <= 0.1){
                category = 4;
            }
        }
        else if((points[i][0] >= -1 && points[i][0] <= -0.4 && points[i][1] >= -1 && points[i][1] <= -0.4) || (points[i][0] >= 0.4 && points[i][0] <= 1 && points[i][1] >= 0.4 && points[i][1] <= 1)){
            category = 2;
            r = (rand()/(float)RAND_MAX);
            if(r <= 0.1){
                category = 4;
            }
        }
        else if((points[i][0] >= -1 && points[i][0] <= -0.4 && points[i][1] >= 0.4 && points[i][1] <= 1) || (points[i][0] >= 0.4 && points[i][0] <= 1 && points[i][1] >= -1 && points[i][1] <= -0.4)){
            category = 3;
            r = (rand()/(float)RAND_MAX);
            if(r <= 0.1){
                category = 4;
            }
        }
        else{
            category = 4;
        }
        if(category == 1){
            fprintf(outfile, "%f %f 1 0 0 0\n", points[i][0], points[i][1]);
        }
        else if(category == 2){
            fprintf(outfile, "%f %f 0 1 0 0\n", points[i][0], points[i][1]);
        }
        else if(category == 3){
            fprintf(outfile, "%f %f 0 0 1 0\n", points[i][0], points[i][1]);
        }
        else if(category == 4){
            fprintf(outfile, "%f %f 0 0 0 1\n", points[i][0], points[i][1]);
        }
    }
    fclose(outfile);

    outfile = fopen("testS1.txt", "w");
    for(i = 0; i < 3000; i++){
        do{
            
            points[i][0] = (rand()/(float)RAND_MAX)*2 - 1;
            points[i][1] = (rand()/(float)RAND_MAX)*2 - 1;
            
            for(j = 0; j < i; j++){
                if(points[i][0] == points[j][0] && points[i][0] == points[j][1]){
                    break;
                }
            }
        }while(i > j);
        
        if(points[i][0]*points[i][0] + points[i][1]*points[i][1] < 0.25){
            category = 1;
        }
        else if((points[i][0] >= -1 && points[i][0] <= -0.4 && points[i][1] >= -1 && points[i][1] <= -0.4) || (points[i][0] >= 0.4 && points[i][0] <= 1 && points[i][1] >= 0.4 && points[i][1] <= 1)){
            category = 2;
        }
        else if((points[i][0] >= -1 && points[i][0] <= -0.4 && points[i][1] >= 0.4 && points[i][1] <= 1) || (points[i][0] >= 0.4 && points[i][0] <= 1 && points[i][1] >= -1 && points[i][1] <= -0.4)){
            
        }
        else{
            category = 4;
        }
        if(category == 1){
            fprintf(outfile, "%f %f 1 0 0 0\n", points[i][0], points[i][1]);
        }
        else if(category == 2){
            fprintf(outfile, "%f %f 0 1 0 0\n", points[i][0], points[i][1]);
        }
        else if(category == 3){
            fprintf(outfile, "%f %f 0 0 1 0\n", points[i][0], points[i][1]);
        }
        else if(category == 4){
            fprintf(outfile, "%f %f 0 0 0 1\n", points[i][0], points[i][1]);
        }
    }
    fclose(outfile);
}


void S2(){
    float points[N][2];
    int i, j;
    FILE *outfile;
    outfile = fopen("s2.txt", "w");
    
    for(i = 0; i < 150; i++){
        do{
            
            points[i][0] = (rand()/(float)RAND_MAX)*0.5 + 0.75;
            points[i][1] = (rand()/(float)RAND_MAX)*0.5 + 0.75;
            
            for(j = 0; j < i; j++){
                if(points[i][0] == points[j][0] && points[i][0] == points[j][1]){
                    break;
                }
            }
        }while(i > j);
        
        fprintf(outfile, "%f %f\n", points[i][0], points[i][1]);
    }
    
    
    for(i = 0; i < 150; i++){
        do{
            
            points[i][0] = (rand()/(float)RAND_MAX)*0.5;
            points[i][1] = (rand()/(float)RAND_MAX)*0.5;
            for(j = 0; j < i; j++){
                if(points[i][0] == points[j][0] && points[i][0] == points[j][1]){
                    break;
                }
            }
        }while(i > j);
        
        
        fprintf(outfile, "%f %f\n", points[i][0], points[i][1]);
    }
    
    for(i = 0; i < 150; i++){
        do{
            
            points[i][0] = (rand()/(float)RAND_MAX)*0.5;
            points[i][1] = (rand()/(float)RAND_MAX)*0.5 + 1.5;
            
            for(j = 0; j < i; j++){
                if(points[i][0] == points[j][0] && points[i][0] == points[j][1]){
                    break;
                }
            }
        }while(i > j);
        
        fprintf(outfile, "%f %f\n", points[i][0], points[i][1]);
    }
    
    for(i = 0; i < 150; i++){
        do{
            
            points[i][0] = (rand()/(float)RAND_MAX)*0.5 + 1.5;
            points[i][1] = (rand()/(float)RAND_MAX)*0.5;
            
            for(j = 0; j < i; j++){
                if(points[i][0] == points[j][0] && points[i][0] == points[j][1]){
                    break;
                }
            }
        }while(i > j);
        
        fprintf(outfile, "%f %f\n", points[i][0], points[i][1]);
    }
    
    for(i = 0; i < 150; i++){
        do{
            
            points[i][0] = (rand()/(float)RAND_MAX)*0.5 + 1.5;
            points[i][1] = (rand()/(float)RAND_MAX)*0.5 + 1.5;
            
            for(j = 0; j < i; j++){
                if(points[i][0] == points[j][0] && points[i][0] == points[j][1]){
                    break;
                }
            }
        }while(i > j);
        
        fprintf(outfile, "%f %f\n", points[i][0], points[i][1]);
    }
    
    for(i = 0; i < 150; i++){
        do{
            
            points[i][0] = (rand()/(float)RAND_MAX)*2;
            points[i][1] = (rand()/(float)RAND_MAX)*2;
            
            for(j = 0; j < i; j++){
                if(points[i][0] == points[j][0] && points[i][0] == points[j][1]){
                    break;
                }
            }
        }while(i > j);
        
        fprintf(outfile, "%f %f\n", points[i][0], points[i][1]);
    }
    fclose(outfile);
}

int main(){
    srand(time(NULL));
    pointsS1();
    S2();
}