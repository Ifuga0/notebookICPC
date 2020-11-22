
const int NMAX=1e5;

struct Node
{
	int nbFins=0;
	int nbSuffixes=1;
	map<char,Node*> fils;
	// on peut remplacer par un tableau si l'alphabet est petit
}

Node racine;
char s[NMAX];

void add(Node* u, int i)
{
	if(s[i]=='\0')
		u->nbFins++;
	else
	{
		auto it=u->fils.find(s[i]);
		if(it==u->fils.end())
		{
			u->fils[s[i]] = new Node;
			add(u->fils[s[i]],i+1);
		}
		else
		{
			add(it->second,i+1);
			u->nbSuffixes++;
		}
	}
}

int count(Node* u, int i)
{
	if(s[i]=='\0')
		return u->nbFins;
	else
	{
		auto it=u->fils.find(s[i]);
		if(it==u->fils.end())
		{
			return 0;
		}
		else
		{
			return count(it->second,i+1);
		}
	}
}
