#include <stdio.h>

using namespace std;
	class Node {
	public:
		int  thisValue; // 자기자신값
		Node* rightChild; // 자기자신의 오른쪽 자식노드 값
		Node* leftChild; // 자기자신의 왼쪽 자식노드 값

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