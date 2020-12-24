/*************************************************************************
	> File Name: red_black_tree.cpp
	> Author: David Fun 
	> Mail: david4work@qq.com 
	> Created Time: Thu 24 Dec 2020 01:53:10 PM CST
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
#define L(n) (n->lchild)
#define R(n) (n->rchild)
#define C(n) (n->color)

typedef struct Node {
    int key, color;
    struct Node *lchild, *rchild;
} Node;

Node __NIL;
#define NIL (&__NIL)
__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL->color = 1;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->color = 0;
    p->lchild = p->rchild = NIL;
    return p;
}

int has_red_child(Node *root) {
    return C(L(root)) == 0 || C(R(root)) == 0;
}

Node *left_rotate(Node *root) {
    Node *temp = R(root);
    R(root) = L(temp);
    L(temp) = root;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = L(root);
    L(root) = R(temp);
    R(temp) = root;
    return temp;
}

Node *insert_maintain(Node *root) {
    // root has no red child
    if (!has_red_child(root)) return root;
    // root has two red children
    if (C(L(root)) == 0 && C(R(root)) == 0) {
        if (has_red_child(L(root)) || has_red_child(R(root))) {
            C(root) = 0;
            C(L(root)) = C(R(root)) = 1;
        }
        return root;
    }
    // root has a red child and a black child
    int flag = 0;
    if (C(L(root)) == 0 && has_red_child(L(root))) flag = 1;
    if (C(R(root)) == 0 && has_red_child(R(root))) flag = 2;
    if (flag == 0) return root;
    if (flag == 1) {
        if (C(R(L(root))) == 0) {
            L(root) = left_rotate(L(root));
        }
        root = right_rotate(root);
    } else {
        if (C(L(R(root))) == 0) {
            R(root) = right_rotate(R(root));
        }
        root = left_rotate(root);
    }
    C(root) = 0;
    C(L(root)) = C(R(root)) = 1;
    return root;
}

Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (key == root->key) return root;
    if (key < root->key) {
        L(root) = __insert(L(root), key);
    } else {
        R(root) = __insert(R(root), key);
    }
    return insert_maintain(root);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    C(root) = 1;
    return root;
}

Node *predecessor(Node *root) {
    Node *temp = L(root);
    while (R(temp) != NIL) temp = R(temp);
    return temp;
}

Node *erase_maintain(Node *root) {
    // no DB child
    if (C(L(root)) != 2 && C(R(root)) != 2) return root;
    if (has_red_child(root)) {
        // DB has a brother of red
        C(root) = 0;
        int flag = 0;
        if (C(L(root)) == 2) {
            root = left_rotate(root);
            flag = 1;
        } else {
            root = right_rotate(root);
            flag = 2;
        }
        C(root) = 1;
        if (flag == 1) L(root) = erase_maintain(L(root));
        else R(root) = erase_maintain(R(root));
        return root;
    } else {
        // DB has a brother of black
        if ((C(L(root)) == 2 && !has_red_child(R(root))) || (C(R(root)) == 2 && !has_red_child(L(root)))) {
            // brother Node has no red child
            C(root) += 1;
            C(L(root)) -= 1;
            C(R(root)) -= 1;
            return root;
        }
        // brother Node has red child
        if (C(L(root)) == 2) {
            // left_rotate at last
            if (C(R(R(root))) != 0) {
                C(R(root)) = 0;
                R(root) = right_rotate(R(root));
                C(R(root)) = 1;
            }
            root = left_rotate(root);
            C(root) = C(L(root));
            C(L(L(root))) -= 1;
        } else {
            // right_rotate at last
            if (C(L(L(root))) != 0) {
                C(L(root)) = 0;
                L(root) = left_rotate(L(root));
                C(L(root)) = 1;
            }
            root = right_rotate(root);
            C(root) = C(R(root));
            C(R(R(root))) -= 1;
        }
    }
    C(L(root)) = C(R(root)) = 1;
    return root;
}

Node *__erase(Node *root, int key) {
    if (root == NIL) return root;
    if (key < root->key) {
        L(root) = __erase(L(root), key);
    } else if (key >root->key) {
        R(root) = __erase(R(root), key);
    } else {
        if (L(root) == NIL || R(root) == NIL) {
            Node *temp = L(root) != NIL ? L(root) : R(root);
            C(temp) += C(root);
            free(root);
            return temp;
        }
        Node *temp = predecessor(root);
        root->key = temp->key;
        L(root) = __erase(L(root), temp->key);
    }
    return erase_maintain(root);
}

Node *erase(Node *root, int key) {
    root = __erase(root, key);
    C(root) = 1;
    return root;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(L(root));
    clear(R(root));
    free(root);
    return ;
}

void print(Node *root) {
    printf("%d %d %d %d\n", root->key, C(root), L(root)->key, R(root)->key);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    output(L(root));
    print(root);
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
            case 3: output(root); break;
        }
    }
    clear(root);
    return 0;
}
