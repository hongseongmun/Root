#include <iostream>
#include <queue>
#include <utility>

using namespace std;

const int ROW = 10;
const int COL = 10;

const char MAP[ROW][COL] = {
    {'#','#','#','#','#','#','#','#','#','#'},
    {'#','#','P','0','0','0','0','0','#','#'},
    {'#','#','#','#','#','0','0','0','#','#'},
    {'#','#','#','0','0','0','0','0','#','#'},
    {'#','0','0','0','0','#','#','#','#','#'},
    {'#','0','0','#','#','#','0','0','#','#'},
    {'#','0','0','0','0','#','0','0','#','#'},
    {'#','#','#','0','0','#','0','0','#','#'},
    {'#','#','#','0','0','0','E','#','#','#'},
    {'#','#','#','#','#','#','#','#','#','#'}
};

struct Node {
    int row;  // 현재 위치의 행 번호
    int col;  // 현재 위치의 열 번호
    Node* parent;  // 부모 노드 포인터
    vector<Node*> children;  // 자식 노드 포인터 벡터

    Node(int r, int c, Node* p) : row(r), col(c), parent(p) {}

    Node* find(int r, int c) {
        if (row == r && col == c) {
            return this;
        }
        for (auto child : children) {
            Node* found = child->find(r, c);
            if (found != nullptr) {
                return found;
            }
        }
        return nullptr;
    }
};

class Tree {
private:
    Node* root;  // 루트 노드 포인터

public:
    Tree(int start_row, int start_col) {
        root = new Node{ start_row, start_col, nullptr };
    }

    ~Tree() {
        DeleteTree(root);
    }

    Node* GetRoot() const {
        return root;
    }

    void DeleteTree(Node* node) {
        for (auto child : node->children) {
            DeleteTree(child);
        }
        delete node;
    }
};

class TreeNode {
public:
    int row;
    int col;
    TreeNode* parent;
    vector<TreeNode*> children;

    TreeNode(int r, int c, TreeNode* p) {
        row = r;
        col = c;
        parent = p;
    }
};


TreeNode* bfs(const char map[][COL], int start_row, int start_col, int end_row, int end_col) {
    // 방문 여부를 저장하는 배열
    bool visited[ROW][COL] = { false };

    // 이동할 네 방향
    int dx[4] = { -1, 0, 1, 0 };
    int dy[4] = { 0, 1, 0, -1 };

    // 시작 지점 큐에 삽입
    queue<TreeNode*> q;
    TreeNode* start_node = new TreeNode(start_row, start_col, nullptr);
    q.push(start_node);
    visited[start_row][start_col] = true;

    // BFS 탐색
    while (!q.empty()) {
        TreeNode* current_node = q.front();
        int row = current_node->row;
        int col = current_node->col;
        q.pop();

        // 도착 위치에 도달하면 경로 반환
        if (row == end_row && col == end_col) {
            return current_node;
        }

        // 네 방향으로 이동 가능한 위치 탐색
        for (int j = 0; j < 4; j++) {
            int next_row = row + dx[j];
            int next_col = col + dy[j];
            if (next_row < 0 || next_row >= ROW || next_col < 0 || next_col >= COL) continue; // 범위 밖인 경우
            if (map[next_row][next_col] == '#') continue; // 벽인 경우
            if (visited[next_row][next_col]) continue; // 이미 방문한 경우

            // 탐색한 위치를 트리에 추가
            TreeNode* next_node = new TreeNode(next_row, next_col, current_node);
            current_node->children.push_back(next_node);
            q.push(next_node);
            visited[next_row][next_col] = true;
        }
    }

    // 도착 위치에 도달할 수 없는 경우
    return nullptr;
}

void DrawMap(TreeNode* end_node) {
    queue<char> q;

    for (int h = 0; h < ROW; h++) {
        for (int v = 0; v < COL; v++) {
            char mapTemp = MAP[h][v];
            if (mapTemp == '0') {
                bool is_path = false;
                TreeNode* current_node = end_node;
                while (current_node != nullptr) {
                    if (current_node->row == h && current_node->col == v) {
                        is_path = true;
                        break;
                    }
                    current_node = current_node->parent;
                }
                if (is_path) {
                    cout << "\033[1;31m" << "X" << "\033[0m";
                }
                else {
                    cout << " ";
                }
            }
            else if (mapTemp == '#') {
                cout << "#";
            }
            else if (mapTemp == 'P') {
                cout <<  "\033[1;34m" << "P" << "\033[0m";
            }
            else if (mapTemp == 'E') {
                cout <<"\033[1;31m" <<  "E" << "\033[0m";
            }
        }
        cout << endl;
    }
};

int main() {
    int start_row, start_col, end_row, end_col;
    start_row = 1;
    start_col = 2;
    end_row = 8;
    end_col = 6;
    int move = 0;

    TreeNode* end_node = bfs(MAP, start_row, start_col, end_row, end_col);

    if (end_node == nullptr) {
        cout << "도착 지점에 도달할 수 없습니다." << endl;
        return 0;
    }

    // 경로 출력
    cout << "도착 지점까지의 경로 : ";
    TreeNode* current_node = end_node;
    while (current_node != nullptr) {
        cout << "(" << current_node->row << ", " << current_node->col << ")";
        current_node = current_node->parent;
        move++;
        if (current_node != nullptr) {
            cout << " -> ";
        }
    }
    cout << endl;

    // 경로를 트리로 구성
    Tree tree(start_row, start_col);
    Node* root = tree.GetRoot();
    for (auto child : end_node->children) {
        Node* node = new Node(child->row, child->col, root);
        root->children.push_back(node);
    }
    DrawMap(end_node);
    cout << "이동 거리 : " << move << endl;
    return 0;
}