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
    int row;  // ���� ��ġ�� �� ��ȣ
    int col;  // ���� ��ġ�� �� ��ȣ
    Node* parent;  // �θ� ��� ������
    vector<Node*> children;  // �ڽ� ��� ������ ����

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
    Node* root;  // ��Ʈ ��� ������

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
    // �湮 ���θ� �����ϴ� �迭
    bool visited[ROW][COL] = { false };

    // �̵��� �� ����
    int dx[4] = { -1, 0, 1, 0 };
    int dy[4] = { 0, 1, 0, -1 };

    // ���� ���� ť�� ����
    queue<TreeNode*> q;
    TreeNode* start_node = new TreeNode(start_row, start_col, nullptr);
    q.push(start_node);
    visited[start_row][start_col] = true;

    // BFS Ž��
    while (!q.empty()) {
        TreeNode* current_node = q.front();
        int row = current_node->row;
        int col = current_node->col;
        q.pop();

        // ���� ��ġ�� �����ϸ� ��� ��ȯ
        if (row == end_row && col == end_col) {
            return current_node;
        }

        // �� �������� �̵� ������ ��ġ Ž��
        for (int j = 0; j < 4; j++) {
            int next_row = row + dx[j];
            int next_col = col + dy[j];
            if (next_row < 0 || next_row >= ROW || next_col < 0 || next_col >= COL) continue; // ���� ���� ���
            if (map[next_row][next_col] == '#') continue; // ���� ���
            if (visited[next_row][next_col]) continue; // �̹� �湮�� ���

            // Ž���� ��ġ�� Ʈ���� �߰�
            TreeNode* next_node = new TreeNode(next_row, next_col, current_node);
            current_node->children.push_back(next_node);
            q.push(next_node);
            visited[next_row][next_col] = true;
        }
    }

    // ���� ��ġ�� ������ �� ���� ���
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
        cout << "���� ������ ������ �� �����ϴ�." << endl;
        return 0;
    }

    // ��� ���
    cout << "���� ���������� ��� : ";
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

    // ��θ� Ʈ���� ����
    Tree tree(start_row, start_col);
    Node* root = tree.GetRoot();
    for (auto child : end_node->children) {
        Node* node = new Node(child->row, child->col, root);
        root->children.push_back(node);
    }
    DrawMap(end_node);
    cout << "�̵� �Ÿ� : " << move << endl;
    return 0;
}