#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
/*构建一个结构体*/
typedef struct  Mparam
{
    uint8_t row ;
    uint8_t column ;
    float **data ;
}*Matrix;
/*构建一个矩阵,并分配动态内存*/
Matrix creatmatrix(uint8_t row ,uint8_t column ){
    Matrix mat =(Matrix)malloc(sizeof(struct Mparam));
    if(!mat){
        printf("分配动态内存失败;");
        return NULL ;
    }
    mat->row=row;
    mat->column=column;
    mat->data =(float**)malloc(row*sizeof(float*));
    if(!mat->data){
        free(mat);
        printf("分配动态内存失败:");
        return NULL;
    }
    for(int i=0;i<row;i++){
        mat->data[i]=(float*)malloc(column*sizeof(float));
        if(!mat->data[i]){
            free(mat);
            printf("分配动态内存失败:");
            return NULL;
        }
    }
    return mat;
}
/*释放矩阵内存*/
void freematrix(Matrix mat){
    if(mat){
        for(uint8_t i=0;i<mat->row;i++){
            free(mat->data[i] );
        }
        free(mat->data);
        free(mat);
    }
}
/*输入矩阵元素*/
void inputmatrix(Matrix mat){
    printf("请输入矩阵元素(共%d行%d列):\n",mat->row,mat->column);
    for(int i=0;i<mat->row;i++){
        for(int j=0;j<mat->column;j++){
            printf("请输入元素[%d][%d]:",i,j);
            scanf("%f",&mat->data[i][j]);
        }
    }
}
/*输出矩阵元素*/
void printmatrix(Matrix mat){
    for(uint8_t i=0;i<mat->row;i++){
        for(uint8_t j=0;j<mat->column;j++){
            printf("%8.2f ",mat->data[i][j]);
        }
        printf("\n");
    }
}
/*计算矩阵转置*/
Matrix transposematrix(Matrix mat ){
    Matrix trans=creatmatrix(mat->column,mat->row);
    if (!trans){
        return NULL;
    }
    else{
        for(uint8_t i=0;i<mat->row;i++){
            for(uint8_t j=0;j<mat->column;j++){
                trans->data[i][j]=mat->data[j][i];
            }
        }
    }
    return trans;
}
/*矩阵的乘法*/
Matrix multplymatrix(Matrix mat1,Matrix mat2){
    uint8_t sum=0;
    Matrix mult=creatmatrix(mat1->row,mat2->column);
    if (mat1->row!=mat2->column)
    {
        printf("两个矩阵维度不匹配,无法相乘:\n");
        return NULL;
    }
    else{
        if(!mult){
            return NULL;
        }
        for (uint8_t i=0; i<mat1->row;i++) 
        {
            for(uint8_t j=0;j<mat2->column;j++){
                sum=0;
                for (uint8_t z = 0; z < mat1->row; z++)
                {
                    sum+=mat1->data[i][z]*mat2->data[z][j];
                }
                mult->data[i][j]=sum;
            }
        }
        
    }
    return mult;
}
int main(){
    Matrix mytype,mytran,mymult;
    int row,column;
    printf("请输入行数:");
    scanf("%d",&row);
    printf("请输入列数:");
    scanf("%d",&column);
    mytype=creatmatrix(row,column);
    inputmatrix(mytype);
    mytran=transposematrix(mytype);
    mymult=multplymatrix(mytype,mytran);
    printf("这是原来的矩阵:\n");
    printmatrix(mytype);
    printf("这是转置后的矩阵:\n");
    printmatrix(mytran);
    printf("这是矩阵与转置矩阵相乘后的矩阵:\n");
    printmatrix(mymult);
    return 0;
}