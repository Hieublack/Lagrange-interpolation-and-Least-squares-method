#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#define M 100
#define MAX_VAL 100
void printPoly(double poly[], int n);

void hienThiSoTP(double num, int n);

double *multiPoly(double A[], double B[], int m, int n);

double *lagrange(double X[], double Y[], double **L, int size);

void horner(double poly[], int size, int longresult);

void tinhGiaTriTaiMotDiem(double X[], double **L, int size, int longresult);

void polynomialLarange();

void MakeMatrix(int n);

void PrintMatrix(double a[][M], int n);

void PrintResult(double a[][M], int n);

void SolveMatrix();


