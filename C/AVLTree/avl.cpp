/*************************************************************************
	> File Name: avl.cpp
	> Author: David Fun 
	> Mail: david4work@qq.com 
	> Created Time: Thu 24 Dec 2020 10:19:59 AM CST
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
#define L(n) (n->lchild)
#define R(n) (n->rchild)
#define H(n) (n->h)

typedef struct Node {
    int key, h;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = NIL->h = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->h = 1;
    p->lchild = p->rchild = NIL;
    return p;
}

void update_height(Node *root) {
    H(root) = (H(L(root)) > H(R(root)) ? H(L(root)) : H(R(root))) + 1;
    return ;
}

Node *left_rotate(Node *root) {
    Node *temp = R(root);
    R(root) = L(temp);
    update_height(root);
    L(temp) = root;
    update_height(temp);
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = L(root);
    L(root) = R(temp);
    update_height(root);
    R(temp) = root;
    update_height(temp);
    return temp;
}

Node *maintain(Node *root) {
    if (abs(H(L(root)) - H(R(root))) <= 1) return root;
    if (H(L(root)) > H(R(root))) {
        if (H(R(L(root))) > H(L(L(root)))) {
            L(root) = left_rotate(L(root));
        }
        root = right_rotate(root);
    } else {
        if (H(L(R(root))) > H(R(R(root)))) {
            R(root) = right_rotate(R(root));
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (key == root->key) return root;
    if (key < root->key) {
        L(root) = insert(L(root), key);
    } else {
        R(root) = insert(R(root), key);
    }
    update_height(root);
    return maintain(root);
}

Node *predecessor(Node *root) {
    Node *temp = L(root);
    while (R(temp) != NIL) temp = R(temp);
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (key < root->key) {
        L(root) = erase(L(root), key);
    } else if (key > root->key) {
        R(root) = erase(R(root), key);
    } else {
        if (L(root) == NIL || R(root) == NIL) {
            Node *temp = L(root) != NIL ? L(root) : R(root);
            free(root);
            return temp;
        }
        Node *temp = predecessor(root);
        root->key = temp->key;
        L(root) = erase(L(root), temp->key);
    }
    update_height(root);
    return maintain(root);
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(L(root));
    clear(R(root));
    free(root);
    return ;
}

void print(Node *root) {
    printf("(%d[%d], %d, %d)\n", root->key, H(root), L(root)->key, R(root)->key);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    print(root);
    output(L(root));
    output(R(root));
    return ;
}

int main() {
    Node *root = NIL;
    int op, val;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
        }
        output(root);
        printf("----------\n");
    }
    clear(root);
    return 0;
}
