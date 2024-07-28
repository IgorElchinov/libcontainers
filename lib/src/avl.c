#include "avl.h"
#include <stdlib.h>
#include <stdio.h>

static inline int
max(int a, int b) {
    return a > b ? a : b;
}

void
avl_check(AVLTree *tree, const char func_name[]) {
    if (tree == NULL) {
        fprintf(stderr, "%s: tree is NULL\n", func_name);
        fflush(stderr);
        exit(1);
    }
    return;
}

static void
free_tree_node(AVLNode *node) {
    if (node == NULL) {
        return;
    }
    if (node->left != NULL) {
        free_tree_node(node->left);
    }
    if (node->right != NULL) {
        free_tree_node(node->right);
    }
    free(node);
    return;
}

void
avl_free(AVLTree *tree) {
    avl_check(tree, __func__);
    if (tree->root != NULL) {
        free_tree_node(tree->root);
    }
    tree->root = NULL;
    return;
}

static void
print_node(AVLNode *node, size_t depth) {
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }
    printf("ptr: %p; data: %d; parent: %p; left: %p; right: %p; cnt: %lu; h: %lu\n",
            node, node->data, node->parent, node->left, node->right, node->counter, node->height);
    return;
}

static void
print_tree_helper(AVLNode *node, size_t depth) {
    print_node(node, depth);
    if (node->left != NULL) {
        print_tree_helper(node->left, depth + 1);
    }
    if (node->right != NULL) {
        print_tree_helper(node->right, depth + 1);
    }
    return;
}

void
avl_print(AVLTree *tree) {
    avl_check(tree, __func__);
    if (tree->root == NULL) {
        printf("AVL tree: empty\n");
        return;
    }
    printf("AVL tree; height: %lu\n", tree->root->height);
    print_tree_helper(tree->root, 0);
    return;
}

static AVLNode *
add_node(int elem, AVLNode *par) {
    AVLNode *node = calloc(1, sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "%s: Memory allocation problem\n", __func__);
        fflush(stderr);
        exit(1);
    }
    node->data = elem;
    node->left = NULL;
    node->right = NULL;
    node->parent = par;
    node->counter = 1;
    node->height = 1;
    return node;
}

static inline int
h(AVLNode *node) {
    if (node == NULL) {
        return 0;
    } else {
        return node->height;
    }
}

static inline int
diff(AVLNode *node) {
    return h(node->left) - h(node->right);
}

AVLNode *
small_rotate_left(AVLNode *root) {
    AVLNode *res = root->right;
    AVLNode *right_left_son = root->right->left;
    res->left = root;
    res->left->right = right_left_son;
    res->parent = root->parent;
    root->parent = res;
    if (right_left_son != NULL) {
        right_left_son->parent = root;
    }
    res->left->height = max(h(res->left->left), h(res->left->right)) + 1;
    res->height = max(h(res->left), h(res->right)) + 1;
    return res;
}

AVLNode *
small_rotate_right(AVLNode *root) {
    AVLNode *res = root->left;
    AVLNode *left_right_son = root->left->right;
    res->right = root;
    res->right->left = left_right_son;
    res->parent = root->parent;
    root->parent = res;
    if (left_right_son != NULL) {
        left_right_son->parent = root;
    }
    res->right->height = max(h(res->right->right), h(res->right->left)) + 1;
    res->height = max(h(res->right), h(res->left)) + 1;
    return res;
}

AVLNode *
big_rotate_left(AVLNode *root) {
    root->right = small_rotate_right(root->right);
    return small_rotate_left(root);
}

AVLNode *
big_rotate_right(AVLNode *root) {
   root->left = small_rotate_left(root->left);
   return small_rotate_right(root);
}

void
balance_tree(AVLTree *tree, AVLNode *start_node) {
    AVLNode *cur = start_node; 
    while (cur != NULL) {
        cur->height = max(h(cur->left), h(cur->right)) + 1;
        NodeType type = ROOT;
        AVLNode *par = NULL;
        if (cur->parent != NULL) {
            par = cur->parent;
            if (cur == cur->parent->left) {
                type = LEFT_CHILD;
            } else {
                type = RIGHT_CHILD;
            }
        }
        AVLNode *res = cur;
        if (diff(cur) < -1) {
            if (diff(cur->right) == 1) {
                res = big_rotate_left(cur);
            } else {
                res = small_rotate_left(cur);
            }
        } else if (diff(cur) > 1) {
            if (diff(cur->left) == -1) {
                res = big_rotate_right(cur);
            } else {
                res = small_rotate_right(cur);
            }
        }
        switch (type) {
            case LEFT_CHILD:
                par->left = res;
                break;
            case ROOT:
                tree->root = res;
                break;
            case RIGHT_CHILD:
                par->right = res;
                break;
            default:
                fprintf(stderr, "%s: library error\n", __func__);
                fflush(stderr);
                avl_free(tree);
                exit(1);
        }
        cur = par;
    }
    return;
}

void
avl_insert(AVLTree *tree, int elem) {
    avl_check(tree, __func__);
    if (tree->root == NULL) {
        tree->root = add_node(elem, NULL);
        return;
    }
    AVLNode *cur = tree->root;
    int added = 1;
    while (cur != NULL) {
        if (elem < cur->data) {
            if (cur->left == NULL) {
                cur->left = add_node(elem, cur);
                break;
            }
            cur = cur->left;
        } else if (elem > cur->data) {
            if (cur->right == NULL) {
                cur->right = add_node(elem, cur);
                break;
            }
            cur = cur->right;
        } else {
            cur->counter++;
            added = 0;
            break;
        }
    }
    if (!added) {
        return;
    }
    balance_tree(tree, cur);
    return;
}

AVLNode *
avl_find_min(AVLNode *node) {
    AVLNode *cur = node;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

void
avl_erase_raise_error(AVLTree *tree, int elem) {
    fprintf(stderr, "avl_erase: %d is not in tree\n", elem);
    fflush(stderr);
    avl_free(tree);
    exit(1);
    return;
}

void
avl_delete_nonroot_node(AVLNode *node, AVLTree *tree) {
    if (node == NULL || node->parent == NULL) {
        fprintf(stderr, "%s: node or is's parent is null\n", __func__);
    }
    if (node->left == NULL && node->right == NULL) {
        if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
    } else if (node->left == NULL && node->right != NULL) {
        if (node == node->parent->left) {
            node->parent->left = node->right;
            node->right->parent = node->parent;
        } else {
            node->parent->right = node->right;
            node->right->parent = node->parent;
        }
    } else if (node->left != NULL && node->right == NULL) {
        if (node == node->parent->left) {
            node->parent->left = node->left;
            node->left->parent = node->parent;
        } else {
            node->parent->right = node->left;
            node->left->parent = node->parent;
        }
    } else {
        AVLNode *replacement = avl_find_min(node->right);
        node->data = replacement->data;
        node->counter = replacement->counter;
        avl_delete_nonroot_node(replacement, tree);
        return;
    }
    balance_tree(tree, node->parent);
    free(node);
    return;
}

void
avl_erase(AVLTree *tree, int elem) {
    avl_check(tree, __func__);
    if (tree->root == NULL) {
        avl_erase_raise_error(tree, elem);
    }
    AVLNode *cur = tree->root;
    while (cur != NULL && cur->data != elem) {
        if (elem < cur->data) {
            if (cur->left == NULL) {
                avl_erase_raise_error(tree, elem);
            }
            cur = cur->left;
        } else if (elem > cur->data) {
            if (cur->right == NULL) {
                avl_erase_raise_error(tree, elem);
            }
            cur = cur->right;
        }
    }
    if (cur == NULL) {
        return;
    }
    cur->counter--;
    if (cur->counter > 0) {
        return;
    }
    if (cur == tree->root) {
        if (cur->left == NULL && cur->right == NULL) {
            tree->root = NULL;
        } else if (cur->left == NULL && cur->right != NULL) {
            tree->root = cur->right;
            cur->right->parent = NULL;
        } else if (cur->left != NULL && cur->right == NULL) {
            tree->root = cur->right;
            cur->right->parent = NULL;
        } else {
            AVLNode *replacement = avl_find_min(cur->right);
            cur->data = replacement->data;
            cur->counter = replacement->counter;
            avl_delete_nonroot_node(replacement, tree);
            return;
        }
        free(cur);
    } else {
        avl_delete_nonroot_node(cur, tree);
    }
    return;
}

int
avl_find_helper(AVLNode *node, int elem) {
    if (node == NULL) {
        return 0;
    }
    if (node->data == elem) {
        return 1;
    }
    if (node->data > elem) {
        return avl_find_helper(node->left, elem);
    }
    return avl_find_helper(node->right, elem);
}

inline int
avl_find(AVLTree *tree, int elem) {
    avl_check(tree, __func__);
    return avl_find_helper(tree->root, elem);
}

void
avl_to_vector_add_node(AVLNode *node, Vector *vector) {
    if (node == NULL) {
        return;
    }
    if (node->left != NULL) {
        avl_to_vector_add_node(node->left, vector);
    }
    for (size_t i = 0; i <  node->counter; ++i) {
        v_push_back(vector, node->data);
    }
    if (node->right != NULL) {
        avl_to_vector_add_node(node->right, vector);
    }
    return;
}

Vector
avl_to_vector(AVLTree *tree) {
    avl_check(tree, __func__);
    Vector vector = v_init(0);
    if (tree->root != NULL) {
        avl_to_vector_add_node(tree->root, &vector);
    }
    return vector;
}


