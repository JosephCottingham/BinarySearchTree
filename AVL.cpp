 #include <iostream>

class AVLTree {
    
    struct Node {
        int key;
        char val;
        Node *left;
        Node *right;
        int height;
        Node(): key(0), val(0), left(nullptr), right(nullptr), height(0) {}
        Node(int key, char val) : key(key), val(val), left(nullptr), right(nullptr), height(0) {}
    };

    public:
        AVLTree() {
            size=0;
            root= new Node();
        }

        int getSize() {
            return size;
        }

        int print() {
            printTree(root, nullptr, false);
            return 1;
        }

        // Get Val of node with key
        char search(int key) {
            if (size == 0) {
                return -1;
            }
            Node* node = searchRecursive(root, key);
            if (node->key==key) return node->val;
            return -1;
        }

        // Insert new key with value into AVL tree
        char insert(int key, char val) {
            // Base case, root not created yet
            if (size == 0) {
                root = new Node(key, val);
                size++;
                return -1;
            }
            root = insertRecursive(root, key, val);
            return 1;
        }


    private:
        Node* root;
        int size;
        

        // Tree Rotates
        Node* leftRotate(Node* node) {
            // hold affected subtrees
            Node* newParent = node->right;
            Node* newParentOldLeft = newParent->left;

            // move affected subtrees
            newParent->left = node;
            node->right = newParentOldLeft;

            setHeight(node);
            setHeight(newParent);

            return newParent;
        }

        Node* rightRotate(Node* node) {
            // hold affected subtrees
            Node* newParent = node->left;
            Node* newParentOldRight = newParent->right;

            // move affected subtrees
            newParent->right = node;
            node->left = newParentOldRight;

            setHeight(node);
            setHeight(newParent);

            return newParent;
        }

        // Helpers
        int getBalanceFactor(Node* node) {
            if (node == nullptr) return 0;
            int rightHeight = getHeight(node->right);
            int leftHeight = getHeight(node->left);
            return leftHeight - rightHeight;
        }
        
        int getHeight(Node* node) {
            if (node == nullptr) return -1;
            return node->height;
        }

        void setHeight(Node* node) {
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);
            node->height = ((leftHeight > rightHeight) ? leftHeight+1 : rightHeight+1);
        }

        // Recursive

        Node* searchRecursive(Node* node, int key) {
            if (node->key > key && node->left) {
                return searchRecursive(node->left, key);
            } else if (node->key < key && node->right) {
                return searchRecursive(node->right, key);
            }
            return node;
        }
        
        Node* insertRecursive(Node* node, int key, char val) {
            if (node == nullptr) {
                size++;
                return new Node(key, val);
            } else if (node->key > key) {
                node->left = insertRecursive(node->left, key, val);
            } else if (node->key < key) {
                node->right = insertRecursive(node->right, key, val);
            } else {
                return node;
            }
            return balanceNode(node, key);
        }

        Node* balanceNode(Node* node, int insertedKey){
            setHeight(node);
            int weight = getBalanceFactor(node);

            if (weight > 1 && node->left && insertedKey < node->left->key) {
                // Right Rotation
                node = rightRotate(node);
            } else if (weight < -1 && node->right && insertedKey > node->right->key) {
                // Left Rotation
                node = leftRotate(node);
            } else if (weight > 1 && node->left && insertedKey > node->left->key) {
                // LeftRight Rotation
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            } else if (weight < -1 && node->right && insertedKey < node->right->key) {
                // RightLeft Rotation
                node->right = rightRotate(node->right);
                node = leftRotate(node);
            }

            return node;            
        }


        // Printing Functions

        struct Trunk {
            Trunk *prev;
            std::string str;
        
            Trunk(Trunk *prev, std::string str)
            {
                this->prev = prev;
                this->str = str;
            }
        };
    
        // Helper function to print branches of the binary tree
        void showTrunks(Trunk *p)
        {
            if (p == nullptr) {
                return;
            }
        
            showTrunks(p->prev);
            std::cout << p->str;
        }
        
        // Recursive function to print a binary tree.
        // It uses the inorder traversal.
        void printTree(Node* root, Trunk *prev, bool isLeft)
        {
            if (root == nullptr) {
                return;
            }
        
            std::string prev_str = "    ";
            Trunk *trunk = new Trunk(prev, prev_str);
        
            printTree(root->right, trunk, true);
        
            if (!prev) {
                trunk->str = "———";
            }
            else if (isLeft)
            {
                trunk->str = ".———";
                prev_str = "   |";
            }
            else {
                trunk->str = "`———";
                prev->str = prev_str;
            }
        
            showTrunks(trunk);
            std::cout << root->val << std::endl;
        
            if (prev) {
                prev->str = prev_str;
            }
            trunk->str = "   |";
        
            printTree(root->left, trunk, false);
        }

};


int main() {
    std::cout << "Written to Test AVL Tree" << "\n";
    AVLTree avl = AVLTree();
    avl.insert(2, 'b');
    avl.insert(5, 'e');
    avl.insert(5, 'e');
    avl.insert(4, 'd');
    avl.insert(3, 'c');
    avl.insert(6, 'f');
    avl.insert(1, 'a');
    avl.insert(5, 'r');
    avl.insert(9, 'i');
    avl.insert(7, 'g');
    avl.print();
    std::cout << avl.search(5) << "\n";

    AVLTree avltwo = AVLTree();
    int key;
    while (avltwo.getSize()<50) {
        key = (std::rand() % 94)+33;
        avltwo.insert(key, (char)key);
    }
    avltwo.print();
    return 0;
} 

