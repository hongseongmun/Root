#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <conio.h>

using namespace std;

constexpr const char* roma = "IVXLCDM"; //문자열을 roma변수 의 각 인덱스 마다 문자로 잘라서 저장해줌
constexpr int number[] = { 1, 5, 10, 50, 100,500, 1000 };

int numToNum(const char ch)
{
	for (int i = 0; i < 8; i++)
	{
		if (roma[i] == ch) {
			return number[i];
		}
	}
	return -1;
}

int main()
{
	//로마숫자를 아랍 숫자로 표시하는 코드
	char str[100]; // 로마 숫자를 저장할 변수
	int num = 0; // 종료할지 1번,2번할지 값을 입력 받을 변수

	// 수를 로마숫자로 변화하는 코드
	int num2, thous, hund, ten, one; // 수를 로마 숫자로 변환하기 위해 천,백,십,일 단위로 저장받을 변수
	int i; // 반복문때 쓰이는 변수

	while (true) {
		cout << '\n' << "1번 : 아랍 숫자를 로마 숫자로 변환 2번 : 로마 숫자를 아랍 숫자로 변환(종료 : ESC)" << '\n';
		num = _getch();
		if (num == 27) {
			cout << '\n' << "종료되었습니다." << '\n';
			break;
		}
		else if (num == 50) { // 2일때

			cout << '\n' << "1 ~ 3999사이의 로마 숫자를 입력하시오." << '\n';
			gets_s(str, sizeof(str));
			num = 0;
			for (int j = 0; str[j]; j++) {
				num += numToNum(str[j]);
			}
			if (num < 0 || num > 3999) {
				cout << '\n' << "범위 안에 있는 수가 아닙니다." << '\n';
				num = 0;
			}
			else {
				cout << num;
				num = 0;
			}
		}
		else if (num == 49) { // 1일떄
			num = 0;
			cout << '\n' << "1 ~ 3999사이의 아랍 숫자 를 입력하시오." << '\n';
			cin >> num;

			if (num > 0 && num <= 3999) {
				thous = num / 1000;
				hund = (num % 1000) / 100;
				ten = (num % 100) / 10;
				one = (num % 10);

				for (i = 0; i < thous; i++) {
					cout << "M";
				}
				if (hund < 4)
					for (i = 0; i < hund; i++) {
						cout << "C";
					}
				else if (hund == 4) {
					cout << "CD";
				}
				else if (hund >= 5 && hund < 9) {
					cout << "D";
					for (int i = 0; i < (hund - 5); i++) {
						cout << "C";
					}
				}
				else cout << "CM";

				if (ten < 4)
					for (i = 0; i < ten; i++)
						cout << "X";
				else if (ten == 4)
					cout << "XL";
				else if (ten >= 5 && ten < 9)
				{
					cout << "L";
					for (i = 0; i < (ten - 5); i++)
						cout << "X";
				}
				else cout << "XC";

				if (one < 4)
					for (i = 0; i < one; i++)
						cout << "I";
				else if (one == 4)
					cout << "IV";
				else if (one >= 5 && one < 9)
				{
					cout << "V";
					for (i = 0; i < (one - 5); i++)
						cout << "I";
				}
				else cout << "IX";
			}
			else {
				cout << '\n' << "범위 안에 있는 수가 아닙니다." << '\n';
				continue;
			}
			num = 0;
		}
	}
}
