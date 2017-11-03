//
//  main.c
//  Perceptron
//
//  Created by MacBook Pro on 11/3/17.
//  Copyright © 2017 mstapha. All rights reserved.
//

#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <math.h>

#define nombre_ligne 10
#define nombre_entree 8
#define taux_apprentissage 0.1
#define nombre_iteration 1000

float getRandom()
{
    return (float)rand()/RAND_MAX;
}

int CalculerSortie(float poids[],int x[])
{
    int i;
    float somme_ponderee=0;
    for(i=0; i<nombre_entree; i++)
        somme_ponderee += x[i] * poids[i];

    return (somme_ponderee>=0) ? 1 : 0 ;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    //
    char* file_path = "path_to_file";
    FILE* fp ;
    if((fp = fopen(file_path,"r"))==NULL){
        printf("Impossible ouvrir le fichier ");
        exit(1);
    }
    int d[nombre_ligne];
    int x[nombre_ligne][nombre_entree] ;
    
    for(int i=0;i<nombre_ligne;i++){
        for(int j=0;j<=nombre_entree;j++){
            int entree ;
            fscanf(fp,"%d",&entree);
            if(j == nombre_entree){
                d[i] = entree ;
            }else{
                x[i][j] =entree ;
            }
        }
    }
    for(int i=0;i<nombre_ligne;i++){
        printf("\n");
        for(int j=0;j<nombre_entree;j++){
            printf("%d \t",x[i][j]);
        }
        
    }
    float poids[nombre_entree];
    for(int k=0;k<nombre_entree;k++){
        poids[k] = getRandom();
    }
    int iteration = 0;
    float global_error;
    do{
        global_error = 0;
        for(int p = 0;p<nombre_ligne;p++){
            int sortie = CalculerSortie(poids,x[p]);
            printf("%d \n",sortie);
            int local_error = d[p] - sortie;
            for(int k = 0;k<nombre_entree;k++){
                poids[k] = poids[k] + taux_apprentissage* local_error * x[p][k];
               
            }
            global_error += local_error*local_error ;
        }
        
        
        iteration++;
        printf("epoque %d : global_error  = %f RMSE = %f\n",iteration,global_error,sqrt(global_error/nombre_ligne)) ;
    }while(iteration<nombre_iteration && global_error != 0);
    for(int i=0;i<nombre_entree;i++){
        printf("%f \n",poids[i]);
    }
    return 0;
}
