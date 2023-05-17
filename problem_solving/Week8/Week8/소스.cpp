#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>



//8주차
// 문자열로 표현할 데이터가 정수인지, 실수인지, 문자인지, 문자열인지 입력받아서 판단할것.
// 4개의 매개변수를 반드시 입력할것
// 모든 데이터 값을 넣고 엔터치기 전까지는 scanf가 종료되지 않을것
int hsm_Scanf(const char* ch, void* data1, void* data2, void* data3, void* data4) {

    // 몇번째 데이터에 값을 넣을지 판단할 변수
    int data_number = 1;
    // 문자열 입력할때 사용되는 변수
    int index = 0;
    // 입력 받은 값을 저장할 변수
    float temp_ch;
    // 정수나 실수 값을 넣을 변수
    float num = 0;
    //음수인지 아닌지 판단하는 변수
    bool negative_number = false;

    //입력한 문자에 %가 나올때까지 ++해줌
    while (*ch != '%' && *ch)
        ch++;

    // %가 나오면 키 입력을 받고 다음 버퍼로 넘어감
    while (*ch) {
        if (*ch == '%') {
            ch++;
            temp_ch = getc(stdin);

            // 엔터, 공백, \t일 경우 다음 버퍼로 넘어가서 계속 입력받음 
            while (temp_ch == ' ' || temp_ch == '\n' || temp_ch == '\t') {
                temp_ch = getc(stdin);
            }

            //입력 받을 변수 유형을 체크함
            switch (*ch)
            {
                //문자일때
            case 'c':
                if (data_number == 1) {
                    *((char*)data1) = (char)temp_ch;
                }
                else if (data_number == 2) {
                    *((char*)data2) = (char)temp_ch;
                }
                else if (data_number == 3) {
                    *((char*)data3) = (char)temp_ch;
                }
                else if (data_number == 4) {
                    *((char*)data4) = (char)temp_ch;
                }
                data_number++;
                break;
                //문자열일떄
            case 's':
                while (true) {
                    if (temp_ch == '\n' || temp_ch == '\0') {
                        if (data_number == 1) {
                            *((char*)data1 + index) = '\0';
                        }
                        else if (data_number == 2) {
                            *((char*)data2 + index) = '\0';
                        }
                        else if (data_number == 3) {
                            *((char*)data3 + index) = '\0';
                        }
                        else if (data_number == 4) {
                            *((char*)data4 + index) = '\0';
                        }
                        index = 0;
                        data_number++;
                        break;
                    }
                    else {
                        if (data_number == 1) {
                            *((char*)data1 + index) = (char)temp_ch;
                        }
                        else if (data_number == 2) {
                            *((char*)data2 + index) = (char)temp_ch;
                        }
                        else if (data_number == 3) {
                            *((char*)data3 + index) = (char)temp_ch;
                        }
                        else if (data_number == 4) {
                            *((char*)data4 + index) = (char)temp_ch;
                        }
                        index++;
                    }
                    temp_ch = getc(stdin);
                }
                data_number++;
                break;

                //정수일때
            case 'd':
                num = 0;

                if (temp_ch == '-') {
                    temp_ch = '0';
                }
               
                // 정수로 표현하고 그 사이 값이 0~ 9 사이 일경우
                while ((int)temp_ch >= '0' || (int)temp_ch <= sizeof(_CRT_INT_MAX)) {
                    //값을 num에다가 넣어주고 다시 문자를 읽어옴
                    num = (int)num * 10 + (int)temp_ch - '0';
                    temp_ch = getc(stdin);

                    if (temp_ch == ' ' || temp_ch == '\n') {
                        if (data_number == 1) {
                            *(int*)data1 = num;
                        }
                        else if (data_number == 2) {
                            *(int*)data2 = num;
                        }
                        else if (data_number == 3) {
                            *(int*)data3 = num;
                        }
                        else if (data_number == 4) {
                            *(int*)data4 = num;
                        }
                        data_number++;
                        break;
                    }
                }

                //실수일때
            case 'f':
                num = 0;

if (temp_ch == '-') {
    negative_number = true;
    temp_ch = '0';
}

while ((float)temp_ch >= '0' || (float)temp_ch <= sizeof(_CRT_INT_MAX)) {

    num = (float)num * 10 + (float)temp_ch - '0';
    temp_ch = getc(stdin);

    if (temp_ch == '.') {
        temp_ch = getc(stdin);
    }
    if (temp_ch == ' ' || temp_ch == '\n') {
        if (data_number == 1) {
            *(float*)data1 = num / 10;
        }
        else if (data_number == 2) {
            *(float*)data2 = num / 10;
        }
        else if (data_number == 3) {
            *(float*)data3 = num / 10;
        }
        else if (data_number == 4) {
            *(float*)data4 = num / 10;
        }
        data_number++;
        break;
    }
}
            }
        }
        ch++;
     }
     return 1;
}

//9주차
void hsm_File() {
    char* buf1, * buf2;
    int fileSize;
    int temp_ch = 0;

    FILE* file = fopen("test.txt", "r");

    if (file == NULL) {
        printf("Not Found File");
    }

    //파일 크기 구하기
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    //파일크기로 동적할당
    buf1 = (char*)malloc(fileSize * sizeof(char));
    buf2 = (char*)malloc(fileSize * sizeof(char));

    //file파일을 buf1에 읽어옴 sizeof길이의 fileSize 항목까지읽음
    fread(buf1, sizeof(char), fileSize, file);

    //줄바꿈을 기준으로 문자열을 2개로 나뉠 것이기 때문에 문자검색 함수strchr를 사용
    char* buf1Newline = strchr(buf1, '\n');
    if (buf1Newline != NULL) {
        *buf1Newline = '\0';
        buf1Newline++;

        char* buf2Dotline = strchr(buf1Newline, '.');
        if (buf2Dotline != NULL) {
            *(buf2Dotline + 1) = '\0';
        }
        strcpy(buf2, buf1Newline);
    }

    //wchar_t* sh = (wchar_t*)malloc(fileSize * sizeof(wchar_t));
    //fread(sh, sizeof(wchar_t), fileSize, file);

    //wchar_t* buf1Newline = strchr(buf1, '\n');
    //if (buf1Newline != NULL) {
    //    *buf1Newline = '\0';
    //    buf1Newline++;

    //    wchar_t* buf2Dotline = strchr(buf1Newline, '.');
    //    if (buf2Dotline != NULL) {
    //        *(buf2Dotline + 1) = '\0';
    //    }
    //    strcpy(buf2, buf1Newline);
    //}

    wchar_t sh1[1024];
    wchar_t sh2[1024];
    setlocale(LC_ALL, "Korean");
    mbstowcs(sh1, buf1, 1024);
    mbstowcs(sh2, buf2, 1024);

    for (int i = 0; sh1[i] != '\0'; i++) {
        if (sh1[i] == '%') {

            if (sh1[i + 1] == 'c') {
                int j;
                char* ch = (char*)malloc(1);
                for (j = i; sh1[i + 2] != sh2[j]; j++) {
                    *ch = sh2[j];
                }
                printf("\nchar(%d 개): %c", sizeof(char), *ch);
            }
            else if (sh1[i + 1] == 's') {
                int j, k = 0;

                wchar_t sh3[1024];

                for (j = i; ((sh1[i + 3] != sh2[j + 1])); j++) {
                    sh3[k] = sh2[j];
                    k++;
                }
                sh3[k] = L'\0';
                wprintf(L"\nstring(%d 개) : %s\n", sizeof(char), sh3);
            }
            else if (sh1[i + 1] == 'd') {
                int a[10];
                int  b[10];
                int k = i + 2;
                int k2 = i;
                int t = 2;
                int t2= 0;
                a[0] = sh1[i];
                a[1] = sh1[i + 1];

                int das[10];

                while (true) {
                    if ((int)sh1[k]>= '0' && (int)sh1[k] <= '9') {
                        a[t] = (int)sh1[k] - '0';
                        t++;
                        k++;
                    }
                    else {
                        k++;
                    }
                    if ((int)sh2[k2] >= '0' && (int)sh2[k2] <= '9') {
                        b[t2] = (int)sh2[k2] - '0';
                        t2++;
                        k2++;
                    }
                    else {
                        k2++;
                    }
                    if ((char)sh1[k] == '\0' || (char)sh2[k2] == '\0') {
                        break;
                    }
                }
                k2 = 0;

                for (int v = 0; v <= k; v++) {
                    if ((int)a[v] != (int)b[v]) {
                        das[k2] = (int)b[v];
                        k2++;
                    }
                    else {
                        break;
                    }
                }
                printf("\nint(%d 개) : ", k2);
                for (int v = 0; v < k2; v++) {
                    printf(" %d, ", das[v]);
                }
            }
        }
    }
    // 파일 닫기
    fclose(file);
    // 메모리 해제
    free(buf1);
    free(buf2);
}

int main() {

    hsm_File();

    return 0;
}