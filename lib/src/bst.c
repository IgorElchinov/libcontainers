#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void 
bst_check(BSTree *tree, const char func_name[]) {
    if (tree == NULL) {
        fprintf(stderr, "%s: tree is NULL\n", func_name);
        fflush(stderr);
        exit(1);
    }
    return;
}

static void
free_tree_node(BSTreeNode *node) {
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
bst_free(BSTree *tree) {
    bst_check(tree, __func__);
    if (tree->root != NULL) {
        free_tree_node(tree->root);
    }
    tree->root = NULL;
    return;
}

static void
print_node(BSTreeNode *node, size_t depth) {
    for (int i = 0; i < depth; ++i) {
        printf("  ");
    }
    printf("ptr: %p; data: %d; parent: %p; left: %p; right: %p\n", 
            node, node->data, node->parent, node->left, node->right);
    return;
}

void
print_tree_helper(BSTreeNode *node, size_t depth) {
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
bst_print(BSTree *tree) {
    bst_check(tree, __func__);
    if (tree->root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    print_tree_helper(tree->root, 0);
    return;
}

static BSTreeNode *
add_node(int elem, BSTreeNode *par) {
    BSTreeNode *node = calloc(1, sizeof(*node));
    if (node == NULL) {
        fprintf(stderr, "%s: Memory allocation problem\n", __func__);
        fflush(stderr);
        exit(1);
    }
    node->data = elem;
    node->left = NULL;
    node->right = NULL;
    node->parent = par;
    return node;
}


void
bst_insert(BSTree *tree, int elem) {
    bst_check(tree, __func__);
    if (tree->root == NULL) {
        tree->root = add_node(elem, NULL);
        return;
    }
    BSTreeNode *cur = tree->root;
    while (cur != NULL) {
        if (elem < cur->data) {
            if (cur->left == NULL) {
                cur->left = add_node(elem, cur);
                break;
            }
            cur = cur->left;
        } else {
            if (cur->right == NULL) {
                cur->right = add_node(elem, cur);
                break;
            }
            cur = cur->right;
        }
    }
    return;
}

BSTreeNode *
bst_find_min(BSTreeNode *node) {
    BSTreeNode *cur = node;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}

void
bst_erase_raise_error(BSTree *tree, int elem) {
    fprintf(stderr, "bst_erase: %d is not in tree\n", elem);
    fflush(stderr);
    bst_free(tree);
    exit(1);
    return;
}

void
bst_delete_nonroot_node(BSTreeNode *node) {
    if (node == NULL || node->parent == NULL) {
        fprintf(stderr, "%s: node or is's parent is null\n", __func__);
    }
    if (node->left == NULL && node->right == NULL) {
        if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
        free(node);
    } else if (node->left == NULL && node->right != NULL) {
        if (node == node->parent->left) {
            node->parent->left = node->right;
            node->right->parent = node->parent;
        } else {
            node->parent->right = node->right;
            node->right->parent = node->parent;
        }
        free(node);
    } else if (node->left != NULL && node->right == NULL) {
        if (node == node->parent->left) {
            node->parent->left = node->left;
            node->left->parent = node->parent;
        } else {
            node->parent->right = node->left;
            node->left->parent = node->parent;
        }
        free(node);
    } else {
        BSTreeNode *replacement = bst_find_min(node->right);
        node->data = replacement->data;
        bst_delete_nonroot_node(replacement);
    }
    return;
}

void
bst_erase(BSTree *tree, int elem) {
    bst_check(tree, __func__);
    if (tree->root == NULL) {
        bst_erase_raise_error(tree, elem);
    }
    BSTreeNode *cur = tree->root;
    while (cur != NULL && cur->data != elem) {
        if (elem < cur->data) {
            if (cur->left == NULL) {
                bst_erase_raise_error(tree, elem);
            }
            cur = cur->left;
        } else if (elem > cur->data) {
            if (cur->right == NULL) {
                bst_erase_raise_error(tree, elem);
            }
            cur = cur->right;
        }
    }
    if (cur == tree->root) {
        if (cur->left == NULL && cur->right == NULL) {
            free(cur);
            tree->root = NULL;
        } else if (cur->left == NULL && cur->right != NULL) {
            free(cur);
            tree->root = cur->right;
            cur->right->parent = NULL;
        } else if (cur->left != NULL && cur->right == NULL) {
            free(cur);
            tree->root = cur->right;
            cur->right->parent = NULL;
        } else {
            BSTreeNode *replacement = bst_find_min(cur->right);
            cur->data = replacement->data;
            bst_delete_nonroot_node(replacement);
        } 
    } else {
        bst_delete_nonroot_node(cur);
    }
    return;
}

int
bst_find_helper(BSTreeNode *node, int elem) {
    if (node == NULL) {
        return 0;
    }
    if (node->data == elem) {
        return 1;
    }
    if (node->data > elem) {
        return bst_find_helper(node->left, elem);
    }
    return bst_find_helper(node->right, elem);
}

inline int
bst_find(BSTree *tree, int elem) {
    bst_check(tree, __func__);
    return bst_find_helper(tree->root, elem);
}

void
bst_to_vector_add_node(BSTreeNode *node, Vector *vector) {
    if (node == NULL) {
        return;
    }
    if (node->left != NULL) {
        bst_to_vector_add_node(node->left, vector);
    }
    v_push_back(vector, node->data);
    if (node->right != NULL) {
        bst_to_vector_add_node(node->right, vector);
    }
    return;
}

Vector
bst_to_vector(BSTree *tree) {
    bst_check(tree, __func__);
    Vector vector = v_init(0);
    if (tree->root != NULL) {
        bst_to_vector_add_node(tree->root, &vector);
    }
    return vector;
}
