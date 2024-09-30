#include <iostream>
#include <vector>

using namespace std;

class BinarySearchTreeNode;
class BinarySearchTree;
bool isSortedAscending(vector<BinarySearchTreeNode*> data);

class BinarySearchTreeNode {
 public:
    BinarySearchTreeNode* parent;
    BinarySearchTreeNode* leftChild;
    BinarySearchTreeNode* rightChild;
    int key;

    BinarySearchTreeNode(
        BinarySearchTreeNode* parent,
        BinarySearchTreeNode* leftChild,
        BinarySearchTreeNode* rightChild,
        int key
    ) {
        this->parent = parent;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->key = key;
    }
};

class BinarySearchTree {
 public:
    BinarySearchTreeNode* root;

    explicit BinarySearchTree(BinarySearchTreeNode* root = nullptr) {
        this->root = root;
    }

    BinarySearchTreeNode* minNode(BinarySearchTreeNode* treeNode) {
        while (treeNode->leftChild != nullptr) {
            treeNode = treeNode->leftChild;
        }
        return treeNode;
    }

    BinarySearchTreeNode* maxNode(BinarySearchTreeNode* treeNode) {
        while (treeNode->rightChild != nullptr) {
            treeNode = treeNode->rightChild;
        }
        return treeNode;
    }

    void preorderWalk(BinarySearchTreeNode* treeNode) {
        if (treeNode != nullptr) {
            cout << treeNode->key << " ";
            preorderWalk(treeNode->leftChild);
            preorderWalk(treeNode->rightChild);
        }
    }

    void inorderWalk(BinarySearchTreeNode* treeNode) {
        if (treeNode != nullptr) {
            inorderWalk(treeNode->leftChild);
            cout << treeNode->key << " ";
            inorderWalk(treeNode->rightChild);
        }
    }

    void postorderWalk(BinarySearchTreeNode* treeNode) {
        if (treeNode != nullptr) {
            postorderWalk(treeNode->leftChild);
            postorderWalk(treeNode->rightChild);
            cout << treeNode->key << " ";
        }
    }

    void inorderExplorationUtility(
        BinarySearchTreeNode* treeNode,
        vector<BinarySearchTreeNode*>& exploredVertices
    ) {
        if (treeNode != nullptr) {
            inorderExplorationUtility(treeNode->leftChild, exploredVertices);
            exploredVertices.push_back(treeNode);
            inorderExplorationUtility(treeNode->rightChild, exploredVertices);
        }
    }

    vector<BinarySearchTreeNode*> inorderExploration(BinarySearchTreeNode* treeNode) {
        vector<BinarySearchTreeNode*> exploredVertices;
        if (treeNode != nullptr) {
            inorderExplorationUtility(treeNode, exploredVertices);
        }

        return exploredVertices;
    }

    BinarySearchTreeNode* treeSearch(BinarySearchTreeNode* treeNode, int key) {
        while (treeNode != nullptr && key != treeNode->key) {
            if (key < treeNode->key) {
                treeNode = treeNode->leftChild;
            } else {
                treeNode = treeNode->rightChild;
            }
        }
        return treeNode;
    }

    BinarySearchTreeNode* successor(BinarySearchTreeNode* treeNode) {
        if (treeNode->rightChild != nullptr) {
            return minNode(treeNode->rightChild);
        }

        BinarySearchTreeNode* treeNodeParent = treeNode->parent;
        while (treeNodeParent != nullptr && treeNode == treeNodeParent->rightChild) {
            treeNode = treeNodeParent;
            treeNodeParent = treeNodeParent->parent;
        }

        return treeNodeParent;
    }

    BinarySearchTreeNode* predecessor(BinarySearchTreeNode* treeNode) {
        if (treeNode->leftChild != nullptr) {
            return minNode(treeNode->leftChild);
        }

        BinarySearchTreeNode* treeNodeParent = treeNode->parent;
        while (treeNodeParent != nullptr && treeNode == treeNodeParent->leftChild) {
            treeNode = treeNodeParent;
            treeNodeParent = treeNodeParent->parent;
        }

        return treeNodeParent;
    }

    void insert(int treeNodeKey) {
        BinarySearchTreeNode* treeNode = new BinarySearchTreeNode(
            nullptr,
            nullptr,
            nullptr,
            treeNodeKey
        );

        if (this->root == nullptr) {
            this->root = treeNode;
            return;
        }

        BinarySearchTreeNode* targetVertex = this->root;
        BinarySearchTreeNode* savedParent = nullptr;
        while (targetVertex != nullptr) {
            savedParent = targetVertex;
            if (treeNodeKey < targetVertex->key) {
                targetVertex = targetVertex->leftChild;
            } else {
                targetVertex = targetVertex->rightChild;
            }
        }

        treeNode->parent = savedParent;
        if (treeNodeKey < savedParent->key) {
            savedParent->leftChild = treeNode;
        } else {
            savedParent->rightChild = treeNode;
        }
    }

    void deleteVertex(BinarySearchTreeNode* target) {
        if (target->leftChild == nullptr) {
            transplant(target, target->rightChild);
        } else {
            if (target->rightChild == nullptr) {
                transplant(target, target->leftChild);
            } else {
                BinarySearchTreeNode* targetSuccessor = successor(target);
                if (targetSuccessor != target->rightChild) {
                    transplant(targetSuccessor, targetSuccessor->rightChild);
                    targetSuccessor->rightChild = target->rightChild;
                    targetSuccessor->rightChild->parent = targetSuccessor;
                }
                transplant(target, targetSuccessor);
                targetSuccessor->leftChild = target->leftChild;
                targetSuccessor->leftChild->parent = targetSuccessor;
            }
        }
    }
 private:
    void transplant(BinarySearchTreeNode* parentSubtree, BinarySearchTreeNode* childSubtree) {
        if (parentSubtree->parent == nullptr) {
            this->root = childSubtree;
        } else {
            if (parentSubtree == parentSubtree->parent->rightChild) {
                parentSubtree->parent->leftChild = childSubtree;
            } else {
                parentSubtree->parent->rightChild = childSubtree;
            }
        }

        if (childSubtree != nullptr) {
            childSubtree->parent = parentSubtree->parent;
        }
    }
};

bool isSortedAscending(vector<BinarySearchTreeNode*> data) {
    for (int i = 0; i < data.size() - 1; i++) {
        if (data[i]->key > data[i+1]->key) {
            return false;
        }
    }

    return true;
}

int main() {
    BinarySearchTree binarySearchTree;
    vector<int> vertices;
    
    binarySearchTree.insert(3);
    binarySearchTree.insert(25);
    binarySearchTree.insert(10);
    binarySearchTree.insert(30);
    binarySearchTree.insert(8);
    binarySearchTree.insert(6);
    binarySearchTree.insert(20);
    binarySearchTree.insert(4);
    binarySearchTree.insert(7);

    binarySearchTree.inorderWalk(binarySearchTree.root);
    cout << endl;
    binarySearchTree.preorderWalk(binarySearchTree.root);
    cout << endl;
    binarySearchTree.postorderWalk(binarySearchTree.root);
    cout << endl;

    // Check if BST is correct
    vector<BinarySearchTreeNode*> inorderResult = binarySearchTree.inorderExploration(binarySearchTree.root);
    if (isSortedAscending(inorderResult)) {
        cout << "CORRECT" << endl;
    } else {
        cout << "INCORRECT" << endl;
    }

}
