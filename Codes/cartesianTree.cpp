
#define card(u) (u==NULL?0:u->size)

struct Node
{
	int val,rank;
	int size;
	Node* left,right;
	Node(int v,int r){val=v; rank=r; left=NULL; right=NULL;}
};


// Trouver le Kieme élément dans l'ordre croissant des valeurs (numerotation à partir de 0)
int findKth(Node* u,int k)
{
	assert(k<u->size);
	int leftSz=card(u->left);
	if(k<leftSz)
		return findKth(u->left,k);
	else if(k==leftSz)
		return u->val;
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
		u->right=rc.first;
		u->size=1+card(u->left)+card(u->right);
		rc.second->size=1+card(rc.second->left)+card(rc.second->right);
		return {u,rc.second};
	}
	else
	{
		pair<Node*,Node*> lc=cur(u->left,x);
		u->left=lc.second;
		u->size=1+card(u->left)+card(u->right);
		lc.first->size=1+card(lc.first->left)+card(lc.first->right);
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
		u->right=merge(u->right,v);
	}
	else
	{
		v->left=merge(u,v->left);
	}
	u->size=1+card(u->left)+card(u->right);
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

Node* insert(Node* u,int x)
{
	pair<Node*,Node*> cuts=cut(u,x);
	return merge(cuts.first,merge(Node(x,rand()),cuts.second));
}