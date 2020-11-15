
int n,m;
vector<int> listeAdj[NMAX];
bool vu[NMAX];
vector<pair<int,int> > ponts;
int profDecouverte[NMAX];
int parent[NMAX];

int dfsPont(int u,int prof)
{
    vu[u]=true;
    int profMin=prof;
    profDecouverte[u]=prof;
    for(int v : listeAdj[u])
    {
        if(!vu[v])
        {
            parent[v]=u;
            int profTrouvee=dfsPont(v,prof+1);
            if(profTrouvee>prof)
            {
                ponts.push_back({u,v});
            }
            profMin=min(profMin,profTrouvee);
        }
        else if(v!=parent[u])
        {
            profMin=min(profMin,profDecouverte[v]);
        }
    }
    return profMin;
}

