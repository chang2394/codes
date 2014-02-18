// To maintain duplicate elements maintain one more thing in Node (frequency) of that particular value.
// :) :) :) :) :) 

// ****************** START OF CODE FOR TREAP (BST + MAX HEAP) **********************

struct Node{
    int key,cnt,priority;
    Node *left, *right;

    Node():key(0),cnt(0),priority(0),left(NULL),right(NULL){}
    Node(int k):key(k), cnt(1), priority(rand()), left(NULL), right(NULL){}
};

struct Treap{
    Node *root;
    Treap():root(NULL){ /*srand(time(NULL));*/ }

    int Size(Node *T){
        return (T == NULL) ? 0 : T->cnt;
    }

    void UpdateCnt(Node *&T){
        if (T == NULL) return;
        T->cnt = Size(T->left) + Size(T->right) + 1;
    }

    void LeftRotate(Node *&T){
        Node *temp = T->right;
        T->right = temp->left;
        temp->left = T;
        T = temp;

        UpdateCnt(T->left);
        UpdateCnt(T);
    }

    void RightRotate(Node *&T){
        Node *temp = T->left;
        T->left = temp->right;
        temp->right = T;
        T = temp;

        UpdateCnt(T->right);
        UpdateCnt(T);
    }

    void Insert(Node *&T,int _key){
        if (T == NULL){
            T = new Node(_key);
            return;
        }

        if (T->key > _key){
            Insert(T->left,_key);
            if (T->priority < T->left->priority)
                RightRotate(T);
        }
        else if (T->key < _key){
            Insert(T->right,_key);
            if (T->priority < T->right->priority)
                LeftRotate(T);
        }
        UpdateCnt(T);
    }

    void Insert(int _key){
        Insert(root,_key);
    }

    void Erase(Node *&T,int _key){
        if (T == NULL)
            return;
        if (T->key > _key)
            Erase(T->left,_key);
        else if (T->key < _key)
            Erase(T->right,_key);
        else {
            if (T->left && T->right){
                if (T->left->priority > T->right->priority)
                    RightRotate(T);
                else
                    LeftRotate(T);
                Erase(T,_key);
            }
            else {
                Node *temp = T;
                if (T->left)
                    T = T->left;
                else
                    T = T->right;
                delete temp;
            }
        }
        UpdateCnt(T);
    }

    void Erase(int _key){
        Erase(root,_key);
    }

    int Count(Node *T,int bound){
        if (T == NULL)
            return 0;
        if (T->key < bound)
            return (Size(T->left)+ 1 + Count(T->right,bound));
        return Count(T->left,bound);
    }

    int Count(int bound){
        return (Count(root,bound));
    }

    int FindK(Node *T,int k){
        if (Size(T) < k)
            return INT_MIN;

        int sz = 1 + Size(T->left);
        if (sz == k)
            return T->key;
        if (sz < k)
            return (FindK(T->right,k-sz));
        return (FindK(T->left,k));
    }

    int FindK(int k){
        return (FindK(root,k));
    }
};
// ******************* END OF CODE FOR TREAP (BST + MAX HEAP) *********************
