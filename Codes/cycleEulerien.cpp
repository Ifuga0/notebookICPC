
struct Arete
{
    int b,id;
    Arete(int i,int j){b=i; id=j;}
};
const int NMAX=1001;
const int MMAX=10001;
vector<Arete> adjacence[NMAX];
int idArete[NMAX];
bool vuArete[MMAX];
vector<int> cycle;


void parcours(int noeud)
{
    while(idArete[noeud]<adjacence[noeud].size())
    {
        Arete& a=adjacence[noeud][idArete[noeud]++];
        if(vuArete[a.id])continue;
        vuArete[a.id]=true;
        parcours(a.b);
        cycle.push_back(noeud);
    }
}
