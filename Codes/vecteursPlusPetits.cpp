#include <bits/stdc++.h>

using namespace std;

const int DIM=3;

int dimcmp;

int mask=0; 


struct Point
{
	int coord[DIM];
	int id;
	int nbPlusPetits;
	int cote;
	Point(){}
	Point(vector<int> t,int i)
	{
		id=i;
		for(int i=0;i<DIM;i++)
		{
			coord[i]=t[i];
		}
		nbPlusPetits=0;
		cote=0;
	}
};

bool cmpPoint(Point* a,Point* b)
{
	for(int i=dimcmp-1;i>=0;i--)
	{
		if(a->coord[i]<b->coord[i])
			return true;
		else if(a->coord[i]>b->coord[i])
			return false;
	}
	return false;
}

void triPoints(vector<Point*>& T,int dim)
{
	dimcmp=dim;
	sort(T.begin(),T.end(),cmpPoint);
}

void ajouterPetit(vector<Point*>& T, Point* e,int& cnt)
{
	if(e->cote == mask)
		cnt++;
	T.push_back(e);
}

void ajouterGrand(vector<Point*>& T,Point* e,int& cnt)
{
	if(!e->cote)
		e->nbPlusPetits+=cnt;
	T.push_back(e);
}

vector<Point*> DPR(int,vector<Point*>&);

vector<Point*> fusion(int i,vector<Point*> A,vector<Point*> B)
{
	if(i>1)
	{
		for(Point* a : A)
			a->cote |= (1<<i);
		for(Point* b : B)
			b->cote &= (~(1<<i));
		A.insert(A.end(),B.begin(),B.end());
		triPoints(A,i);
		return DPR(i,A);
	}
	else
	{
		vector<Point*> T;
		int cnt=0, iA=0, iB=0, sA=A.size(), sB=B.size();
		while(iA<sA && iB<sB)
		{
			if(A[iA]->coord[0]<=B[iB]->coord[0])
			{
				ajouterPetit(T,A[iA],cnt);
				iA++;
			}
			else
			{
				ajouterGrand(T,B[iB],cnt);
				iB++;
			}
		}
		while(iA<sA)
		{
			ajouterPetit(T,A[iA],cnt);
			iA++;
		}
		while(iB<sB)
		{
			ajouterGrand(T,B[iB],cnt);
			iB++;
		}
		return T;
	}
	
}

pair<vector<Point*>,vector<Point*> > diviser(vector<Point*>& T)
{
	pair<vector<Point*>,vector<Point*> > p;
	int sT=T.size();
	p.first.resize(sT/2);
	p.second.resize(sT-sT/2);
	for(int i=0;i<sT/2;i++)
	{
		p.first[i]=T[i];
	}
	for(int i=sT/2;i<sT;i++)
	{
		p.second[i-sT/2]=T[i];
	}
	return p;
}

vector<Point*> DPR(int i,vector<Point*>& T)
{
	if(T.size()==1)
		return T;
	pair<vector<Point*>,vector<Point*> > p=diviser(T);
	return fusion(i-1,DPR(i,p.first),DPR(i,p.second));
}

void algo(vector<Point*> T)
{
	for(int i=1;i<DIM;i++)
		mask|=(1<<i);
	triPoints(T,DIM);
	DPR(DIM,T);
}

int main()
{

}