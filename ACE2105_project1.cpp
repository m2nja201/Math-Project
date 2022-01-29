#include <iostream>
#include <vector>
// vector 개체 사용하기 위해 "vector" header 추가 (행렬 정의할 때 용이)
using namespace std;

#define matrix vector<vector<double>>
// 원소가 double형식인 2차원 vector "matrix" define
#define row vector<double> // 각 행의 원소들을 넣어줄 "r" 정의

// 함수 선언(설명은 밑에 표 참고)
void MUL(matrix& mat, int i, double k);
void SUM(matrix& mat, int n, double k, int j);
int findL1(row& r);
void echelon(matrix& mat);
void rEchelon(matrix& mat);

int main() {
    int r, c;
    cout << "연립 방정식의 식 개수를 입력하시오 : ";
    cin >> r;  // 식 개수(행 개수) 입력
    cout << "변수 개수를 입력하시오 : ";
    cin >> c;  // 변수 개수(열 개수-1) 입력

    cout << "Augmented 행렬의 각 행의 내용을 입력하시오" << endl;

    //행렬 입력
    matrix myMAT;  // matrix 형식의 myMAT 선언
    for (int i = 0; i < r; ++i) {  // 각 행 원소 입력
        row r;  // 하나의 행을 뜻하는 변수 r 선언
        cout << i + 1 << "행 : ";
        for (int j = 0; j <= c; ++j) { 
            double element;  // 행렬 원소의 값을 받은 변수 element 선언
            cin >> element;
            r.push_back(element); // push_back() 함수로 element 데이터를 r에 삽입
        }
        myMAT.push_back(r);  // 행의 element가 담긴 r을 myMAT에 삽입
    }

    //가우스 소거법
    rEchelon(myMAT);  // 입력해준 myMAT 행렬에서 가우스 소거법 실행
    //해당 case출력
    int a = 0;  // case를 분류하기 위한 int형 변수 a 선언 및 초기화
    if (r < c) {  // r<c인 경우, 무조건 무수히 많은 해 혹은 해가 없는 경우이므로
        a = 1;     // a에 1을 저장함 for문에서 해가 없는 경우로 판단 시 a에 2 저장
    }
    if (r > c) {  // 식의 개수가 미지수 개수보다 많을 때
        for (int i = 0; i < r - c; i++) {  // (r-c)개의 0인 행을 제외하고 case 검사
            for (int j = 0; j <= c; j++) {
                if (myMAT[i][j] == 0) {  // myMAT[i][j]==0일시 아래 내용 실행
                    if (j == c)  // 0인 원소가 마지막 열이면 a에 1을 저장
                        a = 1;
                }
                else if (j == c) {  // myMAT[i][j]이 0이 아닌 마지막 열이면 a에 2 저장
                    a = 2;
                    cout << endl << "해가 존재하지 않음" << endl;
                    system("pause");
                    return 0;  // 아래 코드 무시하고 프로그램 종료
                }
                else {  // 위 조건에 모두 해당하지 않을 시 해당 행을 건너뜀
                    break;
                }
            }
        }
    }
    else {  // r <= c인 경우 모든 행과 열에 대해 case 검사
        for (int i = 0; i < r; i++) {
            for (int j = 0; j <= c; j++) {
                if (myMAT[i][j] == 0) {
                    if (j == c)
                        a = 1;
                }
                else if (j == c) {
                    a = 2;
                    cout << endl << "해가 존재하지 않음" << endl;
                    system("pause");
                    return 0;
                }
                else {
                    break;
                }
            }
        }
    }
 cout << endl;
    switch (a) {   // a 값에 따른 case 분류를 위한 switch 사용
    case 1:  // a==1
        cout << endl << "무수히 많은 해 존재" << endl;
        break;  // 그 외 case가 실행되지 않도록 break를 이용해 switch 빠져나가기
    case 2:  // a==2
        cout << endl << "해가 존재하지 않음" << endl;
        break;
    default:  // a가 1, 2가 아니면 “유일해 존재” 출력
        cout << endl << "유일해 존재" << endl;
    }

    //해 출력
    cout << "- leading variable -" << endl;
    int s[10] = { 0 };  // 임시로 leading-1의 위치를 저장할 배열을 선언
    float freeV[100] = { 0 };  // Free Variable을 출력하기 위한 수를 저장할 배열 선언
    for (int i = 0; i < r; i++) {  // 각 행 검사
        for (int j = 0; j < c; j++) {  // 각 열 검사
            if (myMAT[i][j] == 1) {  // myMAT[i][j]가 leading-1일 때
                cout << "x" << j + 1 << " = " << myMAT[i][c];
                // j+1 해주는 이유 : 행렬의 번호가 0으로 시작하기 때문 
                s[i] = j;  // s[i]에 leading-1의 위치를 저장
                break;
            }
        }
        for (int j = 0; j < c; j++) {  // 해당 i에 대해서 다시 한 번 열을 검사
            if (j == s[i]) {  
                continue;
            }  // j가 s[i]인 경우, continue
            else if (myMAT[i][j] == 0) {  // myMAT[i][j]==0이면 공백을 출력
                cout << "";
            }
            else {
                freeV[j] = j;  // 위 조건을 만족하지 않을 시, free variable임
                if (myMAT[i][j] < 0) {  // 해당 값의 음수, 양수를 판단하여 부호 출력
                    printf(" + %.1f%c ", -myMAT[i][j], 115 + j);
                }
                else {
                    printf(" - %.1f%c ", myMAT[i][j], 115 + j);
                }
            }
        }
        cout << endl;
    }
    //Free Variable 존재 유무
    int num = 0;  // Free Variable 존재시, num에 1을 저장하기 위해 num값을 초기화
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (myMAT[i][j] != 0 && s[i] != j) { 
            // 검사하는 행, 열에 대해 원소가 0과 leading-1이 아닐 시
                num = 1;   // num==1이면 free variable이 존재함을 나타냄
                break;  // j에 대한 for문에서 나가고 새로운 행에 대해 반복문 실행
            }
        }
    }

    //Free Variable이 있을 시 출력
    if (num == 1) {  // num==1이면 free variable 존재. 즉, free variable 존재시 실행
        cout << "- free variable -" << endl;
    }
    int doublef[10] = { 0 };  // freev 배열과 비교할 doublef배열을 초기화
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (myMAT[i][j] != 0 && s[i] != j) {
            // 검사하는 행, 열에 대해 원소가 0과 leading-1이 아닐 시
                if (freeV[j] == doublef[j]) { // freeV[j]와 doublef[j] 비교
                // freeV[j]==0 이라면 해당 원소는 Free Variable에 해당하지 않음
                    continue;
                }
                else {  // free varialble일 경우
                    printf("x%.f = %c", freeV[j] + 1, 115 + j);
                    // x(특수해미지수) = (매개변수)의 형태로 출력
                    doublef[j] = freeV[j];  // continue와 동일
                    cout << endl;
                }
            }
        }
    }
    system("pause");
}

//함수 정의 (자세한 기능은 하단 표 참고)
void MUL(matrix& mat, int i, double k) {
    for (auto& iter : mat[i]) {  // 행 개수(i)만큼 반복
        iter = k * iter;  // 각 원소에 상수배(iter : 원소)
    } // auto : 초기화 값에 따라 알아서 데이터 타입 정해주는 키워드 (& : 주소 사용)
} // 반복자 iter 선언 : 저장된 모든 원소들을 전체적으로 훑을 때 사용, 일종의 포인터와 비슷한 객체
void SUM(matrix& mat, int n, double k, int j) {
    for (int i = 0; i < mat[0].size(); ++i) {  // 각 행의 열 개수만큼 반복
        mat[j][i] = mat[j][i] + k * mat[n][i];  // n행에서 k배한 후 j행에 더하기
    }
}

int findL1(row& r) {
    for (int i = 0; i < r.size(); ++i) {  // 행 개수만큼 반복
        if (r[i] != 0) return i;  // r[i]가 0이 아니라면 i 그대로 반환
        continue;  // r[i] == 0 -> continue;
    }
    return –1;  // 검사한 원소가 모두 0인 경우 -1 반환
}

void echelon(matrix& mat) {
    for (int i = 0; i < mat.size() - 1; ++i) {
    // 마지막행까지 검사할 필요 없으므로 마지막 행 검사 생략(-1)
        int j = findL1(mat[i]);  // 각 행의 leading 1 위치 반환해주는 변수 j 선언
        if (j == -1) continue;  // 모두 0이면(j == -1) continue;
        else {  // j != -1
            for (int k = 0; k < mat.size() - 1 - i; ++k) {
                SUM(mat, i, (-1) * mat[1 + i + k][j] / mat[i][j], 1 + i + k);
            // i+1행부터 순서대로 mat[i+1][j]==0 되도록 i행에 mat[1 + i + k][j]을 빼줌
      // mat[i][j]을 나눠준 이유 : SUM 함수에서 k배에 mat[n][i]을 곱하여 더해주기 때문
            }
        }
    }
}

void rEchelon(matrix& mat) {
    echelon(mat);  // echelon 함수 실행
    for (int i = 0; i < mat.size(); ++i) {  // leading 1 만들기
        int j = findL1(mat[i]);  // 각 행의 leading 1 위치 반환해주는 변수 j 선언
        if (j == -1) continue;  // 모두 0이면(j == -1) continue;
        else {
            MUL(mat, i, 1 / mat[i][j]); // mat[i][i]==1 이 되도록 각 열에 1/mat[i][j]배
        }
    }
    for (int i = mat.size() - 1; i >= 0; --i) {
        int j = findL1(mat[i]);  // 각 행의 leading 1 위치 반환해주는 변수 j 선언
        if (j == -1) continue;  // 모두 0이면(j == -1) continue;
            for (int k = 0; k < i; ++k) {
                SUM(mat, i, (-1) * mat[i - 1 - k][j], i - 1 – k);
            // i-1행부터 거꾸로 각 열마다 0이 되도록 (-1) * mat[i - 1 - k][j]을 더해줌
 
            // (∵ mat[n][i]==1)

            }
        }
    }
}
