#include <stdio.h>

using namespace std;
	class Node {
	public:
		int  thisValue; // �ڱ��ڽŰ�
		Node* rightChild; // �ڱ��ڽ��� ������ �ڽĳ�� ��
		Node* leftChild; // �ڱ��ڽ��� ���� �ڽĳ�� ��

		Node(int  value) {
			thisValue = value;
			rightChild = NULL;
			leftChild = NULL;
		}
	};


int main() {
	int k;
	
	
	Node* nd = new Node(10);

	nd->rightChild = new Node(5);

	return 0;
}