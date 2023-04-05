#include <iostream>
#include <queue>
#include <utility>

using namespace std;

const int ROW = 14;
const int COL = 56;

const char MAP[ROW][COL] = { // 입력된 맵
    // 여기에 맵을 입력해주세요
{"#######################################################"},
{"#00000000000000000000000000000000000000000000000000000#"},
{"#00000000000000000000000000000000000000000000000000000#"},
{"#00000000000000000000000000000000000000000000000000000#"},
{"#00000000####00000000000000000000000000000000000000000#"},
{"#00000000####00000000000000000000000000000000000000000#"},
{"#00000000########0000000000000000000000000000000000000#"},
{"#00000000############000000000000000000000000000000000#"},
{"#00000000########0000000000000000000000000000000000000#"},
{"#00000000########0000000000000000000000000000000000000#"},
{"#00000000####0000000000000000000000000000000###########"},
{"#00000000####0000000000000000000000000000000###########"},
{"#0P000000####00000000000000000000000000E0000###########"},
{"#######################################################"}
};

class Node {
public:
    int x, y; // 노드의 좌표
    vector<Node*> adj_list; // 인접 리스트
    bool visited;

    Node(int x, int y) {
        this->x = x;
        this->y = y;
        visited = false;
    }
};

Node* createNode(int x, int y) {
    if (MAP[x][y] != '0') { // P 또는 E가 있는 칸인 경우
        return new Node(x, y);
    }
    return NULL;
}

void buildGraph(vector<Node*>& graph) {
    // 각 칸에 대해 노드 생성 및 인접 리스트 구성
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            Node* node = createNode(i, j);
            if (node != NULL) {
                if (i > 0) {
                    Node* top = createNode(i - 1, j);
                    if (top != NULL) {
                        node->adj_list.push_back(top);
                        top->adj_list.push_back(node);
                    }
                }
                if (j > 0) {
                    Node* left = createNode(i, j - 1);
                    if (left != NULL) {
                        node->adj_list.push_back(left);
                        left->adj_list.push_back(node);
                    }
                }
                graph.push_back(node);
            }
        }
    }
}

void printNode(Node* node) {
    cout << "(" << node->x << ", " << node->y << "): ";
    for (int i = 0; i < node->adj_list.size(); i++) {
        Node* adj_node = node->adj_list[i];
        cout << "(" << adj_node->x << ", " << adj_node->y << ") ";
    }
    cout << endl;
}

void BFS(vector<Node*>& graph, Node* start) {
    queue<Node*> q;
    q.push(start);
    start->visited = true;
    while (!q.empty()) {
        Node* cur_node = q.front();
        q.pop();
        printNode(cur_node);
        for (int i = 0; i < cur_node->adj_list.size(); i++) {
            Node* adj_node = cur_node->adj_list[i];
            if (!adj_node->visited) {
                adj_node->visited = true;
                q.push(adj_node);
            }
        }
    }
}

void DrawMap() {
	queue<char> q;

	for (int h = 0; h < 14; h++) {
		for (int v = 0; v < 56; v++) {
			char mapTemp = MAP[h][v];
			if (mapTemp == '0') {
				cout << " ";
			}
			else if (mapTemp == '#') {
				cout << "#";
			}
			else if (mapTemp == 'P') {
				cout << "P";
			}
			else if (mapTemp == 'E') {
				cout << "E";
			}
		}
		cout << endl;
	};
}


int main() {
	DrawMap();
    vector<Node*> graph;
    buildGraph(graph);
    Node* start = NULL;
    for (int i = 0; i < graph.size(); i++) {
        if (MAP[graph[i]->x][graph[i]->y] == 'P') {
            start = graph[i];
            break;
        }
    }
    BFS(graph, start);
    return 0;
}