#include<iostream>
#include<iomanip>
#include<math.h>
#include<stdlib.h>

#define SIZE 10

using namespace std;

int determinant(float matrix[SIZE][SIZE], int n) {
    int det = 0;
    float submatrix[SIZE][SIZE];
    if (n == 2)
        return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
    else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
        }
    }
    return det;
}

void inverse(float matrix[SIZE][SIZE], int n) {
    float submatrix[SIZE][SIZE];
    float adj[SIZE][SIZE];
    float inv[SIZE][SIZE];

    if (n == 2) {
        inv[0][0] = matrix[1][1] / determinant(matrix, n);
        inv[0][1] = -matrix[1][0] / determinant(matrix, n);
        inv[1][0] = -matrix[0][1] / determinant(matrix, n);
        inv[1][1] = matrix[0][0] / determinant(matrix, n);
    }

    else {
        for (int k = 0; k < n; k++) {
            for (int x = 0; x < n; x++) {
                int subi = 0;
                for (int i = 0; i < n; i++) {
                    if (i == k) {
                        continue;
                    }
                    int subj = 0;
                    for (int j = 0; j < n; j++) {
                        if (j == x)
                            continue;
                        submatrix[subi][subj] = matrix[i][j];
                        subj++;
                    }
                    subi++;
                }
                adj[x][k] = pow(-1, x + k) * determinant(submatrix, n - 1);
            }
        }
        for (int x = 0; x < n; x++) {
            for (int i = 0; i < n; i++) {
                inv[x][i] = adj[x][i] / determinant(matrix, n);
            }
        }
    }

    cout << endl << "======= inverse matrix =======" << endl;
    for (int x = 0; x < n; x++) {
        for (int i = 0; i < n; i++) {
            cout << setw(10)<<setfill(' ')<<inv[x][i];
        }
        cout << endl;
    }
}

int main()
{
    float a[SIZE][SIZE];
    int i, j, n;

    int r, c;
    cout << "���� �������� �� ������ �Է��Ͻÿ� : ";
    cin >> r;
    cout << "���� ������ �Է��Ͻÿ� : ";
    cin >> c;

    if (r != c) {
        cout << "determinant�� ���� �� �����ϴ�." << endl;
        exit(1);
    }


    // ��� ����
    float** mat = new float* [r];
    for (i = 0; i < r; i++) {
        mat[i] = new float[c + 1];
    }

    // ��� �Է�
    cout << "Augmented ����� �� ���� ������ �Է��Ͻÿ�" << endl;
    for (i = 0; i < r; i++) {
        cout << i + 1 << "�� : ";
        for (j = 0; j <= c; j++) {
            cin >> mat[i][j];
        }
    }


    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            a[i][j] = mat[i][j];
        }
    }

    n = r;


    // �Ҽ��� ���ڸ����� �ݿø�
    cout << setprecision(3) << fixed;

    //determinant ���ϱ�
    cout << endl << "======= determinant =======" << endl;
    cout << setw(13)<<setfill(' ')<< determinant(a, n) << endl;

    if (determinant(a, n) == 0) {
        cout << endl << "   << ����� ��� �Ұ��� >>" << endl;
        exit(1);
    }

    cout << endl << "<< ����� ��� ���� >>" << endl;

    //inverse ���ϱ�
    inverse(a, n);
    return 0;
}