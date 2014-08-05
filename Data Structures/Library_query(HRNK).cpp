// Code for hackerrank Library query 
// Link :- https://www.hackerrank.com/contests/feb14/challenges/library-query

//Supports multiple insertions and deletion of same elements. :) :) 

#include <bits/stdc++.h>
using namespace std;

// ****************** START OF CODE FOR TREAP (BST + MAX HEAP) **********************
struct Node{
    int key,cnt,priority,fre;
    Node *left, *right;

    Node():key(0),cnt(1),priority(0),fre(1),left(NULL),right(NULL){}
    Node(int k):key(k), cnt(1),fre(1), priority(rand()), left(NULL), right(NULL){}
};

struct Treap{
    Node *root;
    Treap():root(NULL){ /*srand(time(NULL));*/ }

    int Size(Node *T){
        return (T == NULL) ? 0 : T->cnt;
    }

    void UpdateCnt(Node *&T){
        if (T == NULL) return;
        T->cnt = Size(T->left) + Size(T->right) + T->fre;
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
        if (T->key == _key){
            T->fre = T->fre+1;
            T->cnt = T->cnt+1;
            return;
        }
        if (T->key > _key){
            Insert(T->left,_key);
            if (T->priority < T->left->priority)
                RightRotate(T);
        }
        else {
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
            if (T->fre > 1){
                T->fre -= 1;
                T->cnt -= 1;
                return;
            }
            if (T->left != NULL && T->right != NULL){
                if (T->left->priority > T->right->priority)
                    RightRotate(T);
                else
                    LeftRotate(T);
                Erase(T,_key);
            }
            else {
                Node *temp = T;
                if (T->left != NULL)
                    T = T->left;
                else
                    T = T->right;
                delete temp;
                temp = NULL;
            }
        }
        UpdateCnt(T);
    }

    void Erase(int _key){
        Erase(root,_key);
    }

    int LessCount(Node *T,int bound){
        if (T == NULL)
            return 0;
        if (T->key <= bound)
            return (T->fre+Size(T->left)+ LessCount(T->right,bound));
        return LessCount(T->left,bound);
    }

    int LessCount(int bound){
        return LessCount(root,bound);
    }

    void Clear(Node *&T){
        if (T == NULL) return;
        Clear(T->left);
        Clear(T->right);
        delete T;
        T = NULL;
    }

    void Clear(){
        Clear(root);
    }

    void print(Node *T){
        if (T == NULL) return;
        print(T->left);
        cout << T->key << " ";
        print(T->right);
    }

    void print(){
        print(root);
        cout << endl;
    }
};
// ******************* END OF CODE FOR TREAP (BST + MAX HEAP) *********************

#define MAX (112345)
#define MID ((l+r) >> 1)
#define LT (node << 1)
#define RT ((node << 1) + 1)

struct SEG{
    Treap seg[3*MAX];
    int arr[MAX],N,M;
    int q[MAX],ct;

    SEG(){
        N = M = ct = 0;
    }

    void input(){
        cin >> N;
        for(int i = 0; i < N; ++i)
            cin >> arr[i];
        cin >> M;
        Build();
    }

    void Build(int node,int l,int r){
        seg[node].Clear();
        if (l == r)
            return;
        Build(LT,l,MID);
        Build(RT,MID+1,r);
    }

    void Build(){
        Build(1,0,N-1);
        for(int i = 0; i < N; ++i)
            Update(i,arr[i]);
    }

    void Update(int node,int l,int r,int id,int _key){
        seg[node].Insert(_key);
        if (l == r)
            return;
        if (id <= MID)
            Update(LT,l,MID,id,_key);
        else
            Update(RT,MID+1,r,id,_key);
    }

    void Update(int id,int _key){
        Update(1,0,N-1,id,_key);
    }

    void Delete(int node,int l,int r,int id,int _key){
        seg[node].Erase(_key);
        if (l == r)
            return;
        if (id <= MID)
            Delete(LT,l,MID,id,_key);
        else
            Delete(RT,MID+1,r,id,_key);
    }

    void Delete(int id,int _key){
        Delete(1,0,N-1,id,_key);
    }

    void Query(int node,int l,int r,int a,int b){
        if (l > b || r < a) return;
        if (l >= a && r <= b){
            q[ct++] = node;
            return;
        }

        Query(LT,l,MID,a,b);
        Query(RT,MID+1,r,a,b);
    }

    void Query(int x,int y){
        ct = 0;
        Query(1,0,N-1,x,y);
    }

    void Process(){
        int chk,x,y,k;
        cin >> chk >> x >> y;
        --x;
        if (chk == 1){
            Delete(x,arr[x]);
            arr[x] = y;
            Update(x,arr[x]);
            return;
        }
        --y;
        cin >> k;

        Query(x,y);
        int lt = 0, rt = 100000;
        while(lt < rt){
            int mid = (lt+rt) >> 1, res = 0;
            for(int i = 0; i < ct; ++i)
                res += seg[q[i]].LessCount(mid);
            if (res >= k)
                rt = mid;
            else
                lt = mid+1;
        }
        cout << rt << endl;
    }

    void Process_Queries(){
        for(int i = 0; i < M; ++i)
            Process();
    }
};

void solve(){
    SEG sg;
    sg.input();
    sg.Process_Queries();
}

int main()
{
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}
