#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 100; 

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
};

class MinHeap {
public:
    Node* heap[MAX];
    int size;

    MinHeap() {
        size = 0;
    }

    void swap(int i, int j) {
        Node* temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void insert(Node* newNode) {
        heap[size] = newNode;
        int i = size;
        size++;

        while (i > 0 && heap[i]->freq < heap[(i - 1) / 2]->freq) {
            swap(i, (i - 1) / 2);
            i = (i - 1) / 2;
        }
    }

    Node* extractMin() {
        if (size == 0) return nullptr;

        Node* minNode = heap[0];
        heap[0] = heap[size - 1];
        size--;

        int i = 0;
        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size && heap[left]->freq < heap[smallest]->freq)
                smallest = left;
            if (right < size && heap[right]->freq < heap[smallest]->freq)
                smallest = right;

            if (smallest == i) break;

            swap(i, smallest);
            i = smallest;
        }

        return minNode;
    }
};

void printCodes(Node* root, char* code, int depth) {
    if (!root) return;

    if (!root->left && !root->right && root->ch != '#') {
        code[depth] = '\0';
        cout << root->ch << ": " << code << endl;
    }

    code[depth] = '0';
    printCodes(root->left, code, depth + 1);

    code[depth] = '1';
    printCodes(root->right, code, depth + 1);
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    cin >> n;

    MinHeap mh;

    cout << "Enter character and frequency:\n";
    for (int i = 0; i < n; i++) {
        char c;
        int f;
        cin >> c >> f;

        Node* newNode = new Node;
        newNode->ch = c;
        newNode->freq = f;
        newNode->left = nullptr;
        newNode->right = nullptr;

        mh.insert(newNode);
    }

    while (mh.size > 1) {
        Node* left = mh.extractMin();
        Node* right = mh.extractMin();

        Node* merged = new Node;
        merged->ch = '#'; 
        merged->freq = left->freq + right->freq;
        merged->left = left;
        merged->right = right;

        mh.insert(merged);
    }

    Node* root = mh.extractMin();

    cout << "\nHuffman Codes:\n";
    char code[100];
    printCodes(root, code, 0);

    return 0;
}
