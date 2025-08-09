#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct MParam {
    uint8_t row;
    uint8_t column;
    float **data;
} *Matrix;

// 创建矩阵，动态分配内存
Matrix createMatrix(uint8_t row, uint8_t column) {
    Matrix mat = (Matrix)malloc(sizeof(struct MParam));
    if (!mat) {
        printf("内存分配失败!\n");
        return NULL;
    }
    mat->row = row;
    mat->column = column;

    mat->data = (float **)malloc(row * sizeof(float *));
    if (!mat->data) {
        free(mat);
        printf("内存分配失败!\n");
        return NULL;
    }

    for (uint8_t i = 0; i < row; i++) {
        mat->data[i] = (float *)malloc(column * sizeof(float));
        if (!mat->data[i]) {
            // 释放已经分配的内存
            for (uint8_t j = 0; j < i; j++) free(mat->data[j]);
            free(mat->data);
            free(mat);
            printf("内存分配失败!\n");
            return NULL;
        }
    }
    return mat;
}

// 释放矩阵内存
void freeMatrix(Matrix mat) {
    if (mat) {
        for (uint8_t i = 0; i < mat->row; i++) {
            free(mat->data[i]);
        }
        free(mat->data);
        free(mat);
    }
}

// 输入矩阵元素
void inputMatrix(Matrix mat) {
    printf("请输入矩阵元素（共 %d 行 %d 列）：\n", mat->row, mat->column);
    for (uint8_t i = 0; i < mat->row; i++) {
        for (uint8_t j = 0; j < mat->column; j++) {
            printf("元素[%d][%d]: ", i, j);
            scanf("%f", &mat->data[i][j]);
        }
    }
}

// 输出矩阵元素
void printMatrix(Matrix mat) {
    for (uint8_t i = 0; i < mat->row; i++) {
        for (uint8_t j = 0; j < mat->column; j++) {
            printf("%8.2f ", mat->data[i][j]);
        }
        printf("\n");
    }
}

// 计算矩阵转置
Matrix transposeMatrix(Matrix mat) {
    Matrix trans = createMatrix(mat->column, mat->row);
    if (!trans) return NULL;

    for (uint8_t i = 0; i < mat->row; i++) {
        for (uint8_t j = 0; j < mat->column; j++) {
            trans->data[j][i] = mat->data[i][j];
        }
    }
    return trans;
}

// 矩阵乘法 mat1(row1 x col1) * mat2(row2 x col2)
// 返回新矩阵
Matrix multiplyMatrix(Matrix mat1, Matrix mat2) {
    if (mat1->column != mat2->row) {
        printf("矩阵维度不匹配，无法相乘!\n");
        return NULL;
    }

    Matrix result = createMatrix(mat1->row, mat2->column);
    if (!result) return NULL;

    for (uint8_t i = 0; i < result->row; i++) {
        for (uint8_t j = 0; j < result->column; j++) {
            float sum = 0;
            for (uint8_t k = 0; k < mat1->column; k++) {
                sum += mat1->data[i][k] * mat2->data[k][j];
            }
            result->data[i][j] = sum;
        }
    }
    return result;
}

int main() {
    uint8_t row, column;
    printf("请输入矩阵的行数: ");
    scanf("%hhu", &row);
    printf("请输入矩阵的列数: ");
    scanf("%hhu", &column);

    Matrix mat = createMatrix(row, column);
    if (!mat) return -1;

    inputMatrix(mat);

    printf("输入的矩阵是:\n");
    printMatrix(mat);

    Matrix trans = transposeMatrix(mat);
    if (!trans) {
        freeMatrix(mat);
        return -1;
    }

    printf("转置矩阵是:\n");
    printMatrix(trans);

    Matrix product = multiplyMatrix(mat, trans);
    if (!product) {
        freeMatrix(mat);
        freeMatrix(trans);
        return -1;
    }

    printf("矩阵与其转置的乘积是:\n");
    printMatrix(product);

    // 释放内存
    freeMatrix(mat);
    freeMatrix(trans);
    freeMatrix(product);

    return 0;
}
