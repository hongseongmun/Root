#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>



//8����
// ���ڿ��� ǥ���� �����Ͱ� ��������, �Ǽ�����, ��������, ���ڿ����� �Է¹޾Ƽ� �Ǵ��Ұ�.
// 4���� �Ű������� �ݵ�� �Է��Ұ�
// ��� ������ ���� �ְ� ����ġ�� �������� scanf�� ������� ������
int hsm_Scanf(const char* ch, void* data1, void* data2, void* data3, void* data4) {

    // ���° �����Ϳ� ���� ������ �Ǵ��� ����
    int data_number = 1;
    // ���ڿ� �Է��Ҷ� ���Ǵ� ����
    int index = 0;
    // �Է� ���� ���� ������ ����
    float temp_ch;
    // ������ �Ǽ� ���� ���� ����
    float num = 0;
    //�������� �ƴ��� �Ǵ��ϴ� ����
    bool negative_number = false;

    //�Է��� ���ڿ� %�� ���ö����� ++����
    while (*ch != '%' && *ch)
        ch++;

    // %�� ������ Ű �Է��� �ް� ���� ���۷� �Ѿ
    while (*ch) {
        if (*ch == '%') {
            ch++;
            temp_ch = getc(stdin);

            // ����, ����, \t�� ��� ���� ���۷� �Ѿ�� ��� �Է¹��� 
            while (temp_ch == ' ' || temp_ch == '\n' || temp_ch == '\t') {
                temp_ch = getc(stdin);
            }

            //�Է� ���� ���� ������ üũ��
            switch (*ch)
            {
                //�����϶�
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
                //���ڿ��ϋ�
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

                //�����϶�
            case 'd':
                num = 0;

                if (temp_ch == '-') {
                    temp_ch = '0';
                }
               
                // ������ ǥ���ϰ� �� ���� ���� 0~ 9 ���� �ϰ��
                while ((int)temp_ch >= '0' || (int)temp_ch <= sizeof(_CRT_INT_MAX)) {
                    //���� num���ٰ� �־��ְ� �ٽ� ���ڸ� �о��
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

                //�Ǽ��϶�
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

//9����
void hsm_File() {
    char* buf1, * buf2;
    int fileSize;
    int temp_ch = 0;

    FILE* file = fopen("test.txt", "r");

    if (file == NULL) {
        printf("Not Found File");
    }

    //���� ũ�� ���ϱ�
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    //����ũ��� �����Ҵ�
    buf1 = (char*)malloc(fileSize * sizeof(char));
    buf2 = (char*)malloc(fileSize * sizeof(char));

    //file������ buf1�� �о�� sizeof������ fileSize �׸��������
    fread(buf1, sizeof(char), fileSize, file);

    //�ٹٲ��� �������� ���ڿ��� 2���� ���� ���̱� ������ ���ڰ˻� �Լ�strchr�� ���
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
                printf("\nchar(%d ��): %c", sizeof(char), *ch);
            }
            else if (sh1[i + 1] == 's') {
                int j, k = 0;

                wchar_t sh3[1024];

                for (j = i; ((sh1[i + 3] != sh2[j + 1])); j++) {
                    sh3[k] = sh2[j];
                    k++;
                }
                sh3[k] = L'\0';
                wprintf(L"\nstring(%d ��) : %s\n", sizeof(char), sh3);
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
                printf("\nint(%d ��) : ", k2);
                for (int v = 0; v < k2; v++) {
                    printf(" %d, ", das[v]);
                }
            }
        }
    }
    // ���� �ݱ�
    fclose(file);
    // �޸� ����
    free(buf1);
    free(buf2);
}

int main() {

    hsm_File();

    return 0;
}