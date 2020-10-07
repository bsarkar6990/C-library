#include<stdio.h>
#include <time.h> 
#include <stdlib.h> 
int main(){
    float  matrix[10][10];
	int mat[10][10];
	float ratio, det;
    int i, j, k, n;
    printf("Enter order of matrix: ");
    scanf("%d", &n);
    printf("matrix Elements:  \n");
	 srand (time(NULL));
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            mat[i][j] =  rand() % 255 ;
			matrix[i][j]=(float)mat[i][j]/255;
			printf("%.2f ",matrix[i][j]);
        }
		printf("\n");
    }
	printf("calculating determinant...\n");
	getchar();
    /* Conversion of matrix to upper triangular */
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(j>i){
                ratio = matrix[j][i]/matrix[i][i];
                for(k = 0; k < n; k++){
                    matrix[j][k] -= ratio * matrix[i][k];
                }
            }
        }
    }
    det = 1; //storage for determinant
    for(i = 0; i < n; i++)
        det *= matrix[i][i];
    printf("The determinant of matrix is: %.2f\n\n", det);
	getchar();
    return 0;
}