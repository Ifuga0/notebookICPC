struct Edge {
    int from, to, index;
    long long cap,flow;
    Edge(int from, int to, long long cap, long long flow, int index) :
        from(from), to(to), index(index), cap(cap), flow(flow) {}
    long long rcap() { return cap - flow;}
};

struct Dinic {
    int N;
    vector<vector<Edge> > G;
    vector<vector<Edge*>> Lf;
    vector<int> layer,Q;
    Dinic(int N) : N(N), G(N), layer(N), Q(N) {}
    void AddEdge(int from, int to, long long cap) {
        if(from == to) return;
        G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
        G[to].push_back(Edge(to,from,0,0,G[from].size()-1));
    }

    long long BlockingFlow(int s,int t) {
        fill(layer.begin(),layer.end(),-1);
        layer[s]=0;
        Lf.clear(); Lf.resize(N);
        int head=0, tail=0;
        Q[tail++]=s;
        while(head<tail) {
            int x = Q[head++];
            for(int i=0;i<G[x].size();++i)
            {
                Edge &e = G[x][i]; if(e.rcap() <= 0) continue;
                if(layer[e.to] ==-1) {
                    layer[e.to] = layer[e.from] + 1;
                    Q[tail++]=e.to;
                }
                if(layer[e.to] > layer[e.from])
                {
                    Lf[e.from].push_back(&e);
                }
            }
        }
        if(layer[t]==-1) return 0;

        long long totflow = 0;
        vector<Edge*> P;
        while(!Lf[s].empty()) {
            int curr= P.empty() ? s : P.back()->to;
            if(curr==t) { // Augment
                long long amt = P.front()->rcap();
                for(int i=0;i<P.size();++i) {
                    amt = min(amt, P[i]->rcap());
                }
                totflow += amt;
                for(int i=P.size()-1;i>=0;--i) {
                    P[i]->flow += amt;
                    G[P[i]->to][P[i]->index].flow -= amt;
                    if(P[i]->rcap() <= 0) {
                        Lf[P[i]->from].pop_back();
                        P.resize(i);
                    }
                }
            } else if(Lf[curr].empty()) { // Retreat
                P.pop_back();
                for(int i=0;i<N;++i)
                    for(int j=0;j<Lf[i].size(); ++j)
                        if(Lf[i][j]->to == curr)
                            Lf[i].erase(Lf[i].begin() + j);
            } else { // Advance
                P.push_back(Lf[curr].back());
            }
        }
        return totflow;
    }

    long long GetMaxFlow(int s,int t) {
        long long totflow = 0;
        while( long long flow = BlockingFlow(s,t))
            totflow += flow;
        return totflow;
    }
    
    // GetMaxFlow must be called before calling this function
    vector<pair<int,int> > GetMinCut() {
        vector<pair<int,int> > cut;
        for(int i=0;i<N;i++) {
            if(layer[i]!=-1)
                for(Edge &e : G[i])
                {
                    if(layer[e.to]==-1)
                        cut.push_back({i,e.to});
                }
        }
        return cut;
    }
};
