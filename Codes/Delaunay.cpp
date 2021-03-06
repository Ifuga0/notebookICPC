int idParcours=1;

struct Point {
    int x,y;
    bool operator < (const Point& other) const
    {
        return x<other.x || (x==other.x && y < other.y);
    }
    Point(int a,int b){ x=a; y=b;}
    Point operator - (const Point& other) const
    {
        return Point(x-other.x,y-other.y);
    }
    bool operator == (const Point& other) const
    {
        return x==other.x && y == other.y;
    }
};

vector<Point> points;

long long detCercle(const Point& a, const Point& b, const Point& c){
    return a.x*b.y*produitScalaire(c,c)+b.x*c.y*produitScalaire(a,a)+c.x*a.y*produitScalaire(b,b)
            - produitScalaire(a,a)*b.y*c.x - produitScalaire(b,b)*c.y*a.x - produitScalaire(c,c)*a.y*b.x ;
}
bool dansCercle(const Point& a, const Point& b, const Point& c, const Point& d)
{ /// On teste si d est dans le cercle de abc avec le signe du determinant d'une matrice
    if(a==d || b==d || c == d) /// On vérifie que d n'est pas un des points du triangle
        return false;
    else
        return (detCercle(a,b,c) - detCercle(a,b,d) + detCercle(a,c,d) - detCercle(b,c,d)) > 0 ;
}

struct AreteTriangulation //Semi-arêtes
{
    AreteTriangulation* suiv; /// arete suivante
    AreteTriangulation* rot; /// rotation (une seule nous envoie dans le dual (faces) )
    int idOrig; /// point d'origine de l'arete
    int idVu=0; /// Marqueur pour le parcours de la triangulation
    AreteTriangulation(AreteTriangulation* s,AreteTriangulation* r, int i){suiv=s; rot=r; idOrig=i;}
    AreteTriangulation* sym() /// renvoie l'arête symetrique
    { return rot->rot; }
    Point* orig(){ return &points[idOrig]; }
    int idDest() { return sym()->idOrig; }
    Point* dest() /// renvoie l'autre extremite de l'arete
    { return sym()->orig(); }
    AreteTriangulation* oPrec() { return rot->suiv->rot; }
    AreteTriangulation* gSuiv() /// sens horaire
    { return rot->sym()->suiv->rot; }
    AreteTriangulation* dPrec() /// sens trigo
    { return sym()->suiv; }
};

struct Triangulation
{
    AreteTriangulation* extremiteGauche;
    AreteTriangulation* extremiteDroite;
    Triangulation(AreteTriangulation* a,AreteTriangulation* b){extremiteGauche=a; extremiteDroite=b;}
};
bool aGauche(Point* p, AreteTriangulation* ar){
    return produitVectoriel(*(ar->orig())-*p,*(ar->dest())-*p) > 0;
}
bool aDroite(Point* p, AreteTriangulation* ar){
    return produitVectoriel(*(ar->dest())-*p,*(ar->orig())-*p) > 0;
}
AreteTriangulation* construitAreteTriangulation(int iDep, int iDest){
    AreteTriangulation* a0 = new AreteTriangulation(NULL, NULL, iDep);
    AreteTriangulation* a1 = new AreteTriangulation(NULL, NULL, -1);
    AreteTriangulation* a2 = new AreteTriangulation(NULL, NULL, iDest);
    AreteTriangulation* a3 = new AreteTriangulation(NULL, NULL, -1);
    /// Construction des rotations
    a0->rot = a1; a1->rot = a2;
    a2->rot = a3; a3->rot = a0;
    a0->suiv = a0; a2->suiv=a2; /// AreteTriangulation isolee donc elle est l'AreteTriangulation suivante
    a1->suiv = a3; a3->suiv=a1; /// On construit l'AreteTriangulation dans la représentation duale (faces)
    return a0;
}
void coller(AreteTriangulation* a, AreteTriangulation* b){
    AreteTriangulation* aa=a->suiv->rot;
    AreteTriangulation* bb=b->suiv->rot;
    swap(a->suiv, b->suiv);
    swap(aa->suiv,bb->suiv);
}
AreteTriangulation* relier(AreteTriangulation* a,AreteTriangulation* b){
    AreteTriangulation* q = construitAreteTriangulation(a->idDest(),b->idOrig);
    coller(q,a->gSuiv());
    coller(q->sym(),b);
    return q;
}
void supprimeAreteTriangulation(AreteTriangulation* q){
    coller(q,q->oPrec());
    coller(q->sym(),q->sym()->oPrec());
    delete q->rot;
    delete q->rot->sym();
    delete q->sym();
    delete q;
}
Triangulation diviserPourRegner(int a, int b) 
{ /// Gestion de l'intervalle de points d'indices [a,b[
    if(b-a<=3) {
        /// Cas de base
        if(b == a + 2) {
            /// On forme le segment qui relie les deux points
            AreteTriangulation* ar= construitAreteTriangulation(a,a+1);
            return Triangulation(ar,ar->sym());
        }
        else { /// b = a + 3
            /// On forme le triangle qui relie les trois points
            Point *pA=&points[a], *pB=&points[a+1], *pC=&points[a+2];
            AreteTriangulation* ab=construitAreteTriangulation(a,a+1);
            AreteTriangulation* bc=construitAreteTriangulation(a+1,a+2);
            coller(ab->sym(),bc);
            int orientation=produitVectoriel(*pB- *pA,*pC- *pA);
            if(orientation > 0) { /// A B C est l'ordre de parcours trigonometrique des points
                relier(bc,ab);
                return Triangulation(ab,bc->sym());
            }
            else if(orientation < 0) { /// A C B est l'ordre trigonometrique
                AreteTriangulation* ca = relier(bc,ab);
                return Triangulation(ca->sym(),ca);
            }
            else { /// Points alignés
                return Triangulation(ab,bc->sym());
            }
        }
    } else {
        Triangulation triangulationG = diviserPourRegner(a, a + (b-a)/2);
        Triangulation triangulationD = diviserPourRegner(a + (b-a)/2, b);
        AreteTriangulation* intG=triangulationG.extremiteDroite; /// Point interieur gauche
        AreteTriangulation* intD=triangulationD.extremiteGauche; /// Point interieur droit
        AreteTriangulation* extG=triangulationG.extremiteGauche; /// Point exterieur gauche
        AreteTriangulation* extD=triangulationD.extremiteDroite; /// Point exterieur droit
        /// Détermination de la "base" : tangente inférieure aux deux ensembles à fusionner
        while(true) {
            if(aGauche(intD->orig(),intG)){
                intG=intG->gSuiv();
            } else if(aDroite(intG->orig(),intD)) {
                intD=intD->dPrec();
            } else break;
        }
        AreteTriangulation* base = relier(intD->sym(),intG);
        if(*(intG->orig()) == *(extG->orig()))
            extG=base->sym();
        if(*(intD->orig()) == *(extD->orig()))
            extD=base;
        while(true) {
            //affiche(base);
            AreteTriangulation* candidatGauche=base->sym()->suiv;
            while(aDroite(candidatGauche->dest(),base) && 
			dansCercle(*(base->dest()),*(base->orig()),*(candidatGauche->dest()),
			*(candidatGauche->suiv->dest()))){
                AreteTriangulation* suivant=candidatGauche->suiv;
                supprimeAreteTriangulation(candidatGauche);
                candidatGauche=suivant;
            }
            AreteTriangulation* candidatDroit=base->oPrec();
            while(aDroite(candidatDroit->dest(),base) && 
			dansCercle(*(base->dest()),*(base->orig()),*(candidatDroit->dest()),
			*(candidatDroit->oPrec()->dest())))
            {
                AreteTriangulation* suivant=candidatDroit->oPrec();
                supprimeAreteTriangulation(candidatDroit);
                candidatDroit=suivant;
            }
            bool gaucheValide = aDroite(candidatGauche->dest(),base), droiteValide = aDroite(candidatDroit->dest(),base);
            if( !(gaucheValide) && !(droiteValide) ) /// S'il n'y a plus de candidat, on est arrivé en haut
                break;
            /// Choix du candidat final
            if( !(gaucheValide) || ( droiteValide && dansCercle(*(candidatGauche->dest()),*(candidatGauche->orig()),*(candidatDroit->orig()),*(candidatDroit->dest()))) )
                base=relier(candidatDroit,base->sym());
            else
                base=relier(base->sym(),candidatGauche->sym());
        }
        return Triangulation(extG,extD);
    }
}

vector<int> adj[NMAX];

void construitAdjacence(AreteTriangulation* ar)
{
    vector<AreteTriangulation*> pile;
    pile.push_back(ar);
    ar->idVu=idParcours;
    while(!pile.empty())
    {
        ar=pile.back(); pile.pop_back();
        adj[ar->idOrig].push_back(Arete(ar->idOrig,ar->idDest(),normeEucli(*(ar->orig())- *(ar->dest()))));
        if( ar->sym()->idVu < idParcours )
        {
            pile.push_back(ar->sym());
            ar->sym()->idVu=idParcours;
        }
        if( ar->gSuiv()->idVu < idParcours )
        {
            pile.push_back(ar->gSuiv());
            ar->gSuiv()->idVu=idParcours;
        }
    }
}

int main()
{
	// lire points
    int n=points.size();
    sort(points.begin(),points.end());
    Triangulation delaunay=diviserPourRegner(0,n);
    construitAdjacence(delaunay.extremiteGauche); idParcours++;
    
}
