//Code for spoj ORDERSET
//Code By SNIGGA :)

#include <bits/stdc++.h>
using namespace std;

struct Node{
    int key,cnt,pr;
    Node *left,*right;
    Node(){key = cnt = pr = 0, left= right = NULL;}
    Node(int _key):key(_key),cnt(1),pr(rand()),left(NULL),right(NULL){}
    Node(int _key,int _pr):key(_key),cnt(1),pr(_pr),left(NULL),right(NULL){}
};

typedef Node * pNode;
struct Treap{
    pNode root;
    Treap():root(NULL){}

    int Cnt(pNode T){
        if (!T) return 0;
        return (T->cnt);
    }

    void Update(pNode T){
        if (!T) return;
        T->cnt = Cnt(T->left) + Cnt(T->right) + 1;
    }

    void Split(pNode T,int _key,pNode &L,pNode &R){
        if (T == NULL){ L = R = NULL; return; }
        if (T->key > _key)
            Split(T->left,_key,L,T->left), R = T, Update(R);
        else
            Split(T->right,_key,T->right,R), L = T, Update(L);
        Update(T);
    }

    void Merge(pNode &T,pNode L,pNode R){
        if (!L || !R){ (T = (L) ? L : R) ; return; }
        if (L->pr > R->pr)
            Merge(L->right,L->right,R), T = L;
        else
            Merge(R->left,L,R->left), T = R;
        Update(T);
    }

    void Insert(pNode &T,int _key,int _pr){
        if (!T){ T = new Node(_key,_pr); return; }
        if (T->pr < _pr){
            pNode res = new Node(_key,_pr);
            Split(T,_key,res->left,res->right);
            T = res;
            Update(T);
            return;
        }
        if (T->key < _key)
            Insert(T->right,_key,_pr);
        else
            Insert(T->left,_key,_pr);
        Update(T);
    }

    void Insert(int _key){
        int _pr = rand();
        Insert(root,_key,_pr);
    }

    void Erase(pNode &T,int _key){
        if (!T) return;
        if (T->key == _key){
            Merge(T,T->left,T->right);
            Update(T);
            return;
        }
        if (T->key < _key)
            Erase(T->right,_key);
        else
            Erase(T->left,_key);
        Update(T);
    }

    void Erase(int _key){
        Erase(root,_key);
    }

    bool IsPresent(pNode T,int _key){
        if (!T) return false;
        if (T->key == _key)
            return true;
        if (T->key < _key)
            return IsPresent(T->right,_key);
        return IsPresent(T->left,_key);
    }

    void Insert_unq(int _key){
        if (IsPresent(root,_key))
            return;
        Insert(_key);
    }

    int Count(pNode T,int bound){
        if (!T) return 0;
        if (T->key < bound)
            return (1 + Cnt(T->left) + Count(T->right,bound));
        else
            return (Count(T->left,bound));
    }

    int Count(int bound){
        return Count(root,bound);
    }

    int Kth(pNode T,int k){
        if (Cnt(T) < k) return INT_MIN;
        int sz = Cnt(T->left) + 1;
        if (sz == k)
            return T->key;
        if (sz < k)
            return (Kth(T->right,k-sz));
        return (Kth(T->left,k));
    }

    int Kth(int k){
        return (Kth(root,k));
    }

    void print(pNode T,int p){
        if (!T) return;
        cout << T->key << " PAR IS " << p << endl;
        print(T->left,T->key);
        print(T->right,T->key);
    }

    void print(){
        cout << endl << "printing TREE\n";
        print(root,-1);
    }
};

void solve(){
    int N,X;
    char ch[5];
    scanf("%d",&N);

    Treap root;
    while(N--){
        scanf("%s%d",ch,&X);
        if (ch[0] == 'I')
            root.Insert_unq(X);//, root.print();
        else if (ch[0] == 'D')
            root.Erase(X);
        else if (ch[0] == 'C'){
            int res = root.Count(X);
            printf("%d\n",res);
        } else {
            int res = root.Kth(X);
            if (res == INT_MIN)
                printf("invalid\n");
            else
                printf("%d\n",res);
        }
    }
}

int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("op2.txt","w",stdout);
    solve();
    return 0;
}

