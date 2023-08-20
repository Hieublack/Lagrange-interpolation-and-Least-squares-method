
#include "function.h"

// Driver code
int main()
{
    int node, n;
    FILE *FinalResult;
    printf("_____MENU_____ \n");
    printf("1. LAGRANGE POLYNOMIAL REGRESSION\n");
    printf("0. EXIT PROGRAMING\n");

    printf("Enter node corresponding to your function: ");
    scanf("%d", &node);
    FinalResult = fopen("result.txt", "w");
    fclose(FinalResult);
    if (node == 0)
        printf("You exit Menu \n");
    while (node != 0)
    {
        switch (node)
        {
        case 1:
            printf("Larange polynomial regression \n");
            polynomialLarange(FinalResult);
            break;
        
        default:
            printf("Not Found \n");
            break;
        }
        printf("\n");
        printf("\n_____MENU_____ \n");
        printf("1. LAGRANGE POLYNOMIAL REGRESSION\n");
        printf("0. EXIT PROGRAMING\n");
        printf("Enter node corresponding to your function: ");
        scanf("%d", &node);
        if (node == 0)
            printf("You exit Menu \n");
    }
}

void polynomialLarange()
{
    int size;
    int error = 0;
    int longresult;
    printf("\nNhap so chu so muon hien thi: ");
    scanf("%d", &longresult);
    printf("Nhap so cap (x, y) cua bo du lieu: ");
    scanf("%d", &size);
    double X[size], Y[size];
    do
    {
        error = 0;
        for (int i = 0; i < size; i++)
        {
            printf("Nhap cap (x, y) thu %d: ", i + 1);
            printf("\nX = ");
            scanf("%lf", &X[i]);
            printf("\nY = ");
            scanf("%lf", &Y[i]);
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (X[i] == X[j])
                {
                    error += 1;
                }
            }
        }
        if (error != 0)
            printf("\nMoc noi suy trung nhau!\nXin moi nhap lai\n");

    } while (error != 0);

    //double X[] = {1, 2, 3, 4, 7};
    //double Y[] = {17, 17.5, 76, 210.5, 1970};
    double *F;
    double **L = NULL;
    L = (double **)malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++)
    {
        L[i] = (double *)malloc(size * sizeof(double));
    }
    printf("\nHam co ban tu bang gia tri:\n");
    F = lagrange(X, Y, L, size);

    /* In đa thức nội suy ra màn hình */
    printf("\nHam noi suy tu bang gia tri:");
    printf("\nF = ");
    printPoly(F, size);
    horner(F, size, longresult);
    tinhGiaTriTaiMotDiem(F, L, size, longresult);
}

void printPoly(double poly[], int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        if (poly[i] != 0) // Chỉ in khi hệ số khác 0
        {
            // In hệ số
            if (poly[i] != 1 || i == 0)
                printf("%.3f", poly[i] > 0 ? poly[i] : -poly[i]);
            // In biến số
            if (i != 0)
                i > 1 ? printf("x^%d", i) : printf("x");
            // In dấu '+', '-'
            if (i != 0)
                poly[i - 1] > 0 ? printf(" + ") : printf(" - ");
        }
    }
    printf("\n");
}

double *multiPoly(double A[], double B[], int m, int n)
{
    FILE *FinalResult;

    double *prod = calloc(m + n - 1, sizeof(double));
    // Initialize the porduct polynomial
    for (int i = 0; i < m + n - 1; i++)
        prod[i] = 0;
    // Multiply two polynomials term by term
    // Take ever term of first polynomial
    for (int i = 0; i < m; i++)
    {
        // Multiply the current term of first polynomial
        // with every term of second polynomial.
        for (int j = 0; j < n; j++)
        {
            prod[i + j] += A[i] * B[j];
        }
    }
    return prod;
}

void tinhGiaTriTaiMotDiem(double F[], double **L, int size, int longresult)
{
    printf("\nNhap gia tri can tinh toan: ");
    double value;
    scanf("%lf", &value);
    double valuepoly = 0;

    for (int i = 1; i <= size; i++)
    {
        valuepoly += F[size - i] * pow(value, size - i);
    }
    printf("\nGia tri da thuc tai x = %f la: F(%f) = ", value, value);
    hienThiSoTP(valuepoly, longresult);
    for (int i = 0; i < size; i++)
    {
        valuepoly = 0;
        for (int j = 1; j <= size; j++)
        {
            valuepoly += L[i][size - j] * pow(value, size - j);
        }
        printf("\nGia tri da thuc co ban L[%d](%f): ", i + 1, value);
        hienThiSoTP(valuepoly, longresult);
    }
}

double *lagrange(double X[], double Y[], double **L, int size)
{
    double *F = calloc(size, sizeof(double));
    double poly[size][2]; // Các đa thức con cần dùng trong quá trình tính toán
    // Biến chạy vòng lặp for
    int i, j, k;
    // Biến tạm trong quá trình tính toán
    double *tempPoly;
    double temp;
    /* 1. Tim các đa thức Lagrange cơ bản và in ra màn hình */
    /* Khởi tạo các đa thức con từ mảng X */
    for (i = 0; i < size; i++)
    {
        poly[i][0] = -X[i];
        poly[i][1] = 1;
    }
    for (i = 0; i < size; i++)
    {
        /* Khởi tạo tempPoly để tính đa thức Lagrange cơ bản */
        if (i == 0)
            tempPoly = poly[1];
        else
            tempPoly = poly[0];

        /* Tính đa thức Lagrange cơ bản L[i] */

        // Tìm tử số của L[i] lưu vào biến tạm tempPoly
        k = 0;
        for (j = 0; j < size; j++)
        {
            if ((j != 0 && j != i && i != 0) || (i == 0 && j > 1))
            {
                tempPoly = multiPoly(tempPoly, poly[j], k + 2, 2);
                k++;
            }
        }

        // Tính mẫu số của L[i] lưu vào biến tạm temp
        temp = 1;
        for (j = 0; j < size; j++)
        {
            if (j != i)
                temp *= (poly[i][0] - poly[j][0])
        }

        /* Tính rồi lưu đa thức Lagrange cơ bản L[i] vào mảng L */
        for (j = 0; j < size; j++)
        {
            L[i][j] = tempPoly[j] / temp;
        }
        // In đa thức cơ bản vừa tìm được ra màn hình
     
        printf("L[%d] = ", i + 1);
        printPoly(L[i], size);
    }
    /* Giải phóng bộ nhớ cho tempPoly sau khi không còn sử dụng */
    //free(tempPoly);

    /* 2, Tìm các hệ số của đa thức nội suy thông qua các đa thức cơ bản */
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            F[i] += L[j][i] * Y[j];
        }
    }
    return F;
}

void horner(double poly[], int size, int longresult)
{
    FILE *FinalResult;
    FinalResult = fopen("result.txt", "a");
    double result = poly[size - 1]; // Initialize result
    double value;
    printf("Nhap gia tri can phai kiem tra: ");
    scanf("%lf", &value);
    // Evaluate value of polynomial using Horner's method

    printf("\n_______Kiem tra bang thuat toan Horner______");
    printf("\nx0 = %.3f", value);
    printf("\nKhoi tao gia tri ban dau bang he so cua x^%d:", size - 1);
    result = poly[size - 1];
    printf("\nresult = %.3f", result);
    for (int i = 1; i < size; i++)
    {
        result = result * value + poly[size - 1 - i];
        printf("\nresult = result*%.3f + %.3f", value, poly[size - 1 - i]);
        printf("\t=> result = ");
        hienThiSoTP(result, longresult);
    }
}

void PrintResult(double a[][M], int n)
{
    FILE *FinalResult;
    FinalResult = fopen("result.txt", "a");
    int i, j, k, c;
    float ratio;
    float x[M];
    /* Applying Gauss Jordan Elimination */
    for (i = 1; i <= n; i++)
    {
        if (a[i][i] == 0)
        {
            c = n - 2;
            while ((i + c) <= n && a[i + c][i] == 0)
                c++;
            if ((i + c) == n)
            {
                break;
            }
            for (j = i, k = 0; k <= n + 1; k++)
            {
                float temp = a[j][k];
                a[j][k] = a[j + c][k];
                a[j + c][k] = temp;
            }
        }
        for (j = 1; j <= n; j++)
        {
            if (i != j)
            {
                ratio = a[j][i] / a[i][i];
                for (k = 1; k <= n + 1; k++)
                {
                    a[j][k] = a[j][k] - ratio * a[i][k];
                }
            }
        }
    }
    /* Obtaining Solution */
    for (i = 1; i <= n; i++)
    {
        x[i] = a[i][n + 1] / a[i][i];
        printf("%f \n", x[i]);
        fprintf(FinalResult, "%f \n", x[i]);
    }
    /* Displaying function */
    printf("\nFunction:\n");
    fprintf(FinalResult, "\nFunction:\n");
    for (i = 1; i < n; i++)
    {
        printf("%fx^%d + ", x[i], n - i);
        fprintf(FinalResult, "%fx^%d + ", x[i], n - i);
    }
    printf("%f \n", x[n]);
    fprintf(FinalResult, "%f", x[1]);
    fclose(FinalResult);
    getch();
}

void hienThiSoTP(double num, int n)
{
    FILE *FinalResult;
    FinalResult = fopen("result.txt", "a");
    double k;
    int u = (int)num;
    if ((num < 0) && (num > -1))
    {
        printf("-0.");
        fprintf(FinalResult, "-0.");
    }
    else if ((num > 0) && (num < 1))
    {
        printf("0.");
        fprintf(FinalResult, "0.");
    }
    else
    {
        printf("%d.", u);
        fprintf(FinalResult, "%d.", u);
    }
    k = num - (int)num;
    for (int i = 1; i <= n; i++)
    {
        if (k == 0)
        {
            printf("0");
            fprintf(FinalResult, "0");
            break;
        }
        k *= 10;
        printf("%d", abs((int)k));
        fprintf(FinalResult, "%d", abs((int)k));
        k -= (int)k;
    }
    fclose(FinalResult);
}


