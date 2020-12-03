#define card(u) (u==NULL?0:u->size)

struct Node
{
    int val,rank,id;
    int size;
    Node *left, *right;
    Node(int v,int r,int i) { val=v; rank=r; id=i; size=1; left=NULL; right=NULL; }
};


// Trouver le Kieme élément dans l'ordre croissant des valeurs (numerotation à partir de 0)
int findKth(Node* u,int k)
{
    assert(k>=0 && k<u->size);
    int leftSz=card(u->left);
    if(k<leftSz)
        return findKth(u->left,k);
    else if(k==leftSz)
        return u->id;
    else
        return findKth(u->right,k-leftSz-1);
}


// Couper par rapport à la valeur x
pair<Node*,Node*> cut(Node* u,int x)
{
    if(u==NULL)
        return {NULL,NULL};
    if(u->val<x)
    {
        pair<Node*,Node*> rc=cut(u->right,x);
        u->right = rc.first;
        u->size -= card(rc.second);
        return {u,rc.second};
    }
    else
    {
        pair<Node*,Node*> lc=cut(u->left,x);
        u->left = lc.second;
        u->size -= card(lc.first);
        return {lc.first,u};
    }
}


// Fusion de deux arbres cartésiens u et v tels que toute valeur de u est plus petite
// que toute valeur de v
Node* merge(Node* u, Node* v)
{
    if(u==NULL)
        return v;
    if(v==NULL)
        return u;
    if(u->rank<v->rank)
    {   
        u->size+=v->size;
        u->right=merge(u->right,v);
        return u;
    }
    else
    {
        v->size+=u->size;
        v->left=merge(u,v->left);
        return v;
    }
}

// Renvoie un pointeur sur un noeud ayant la valeur x cherchée ou NULL s'il n'y en a pas
Node* find(Node* u,int x)
{
    if(u==NULL || u->val==x)
    {
        return u;
    }
    else if(u->val<x)
    {
        return find(u->right,x);
    }
    else
        return find(u->left,x);
}

Node* insert(Node* u, Node* v)
{
    pair<Node*,Node*> cuts=cut(u,v->val);
    return merge(cuts.first,merge(v,cuts.second));
}