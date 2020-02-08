
struct Situation
{
	int prof;
	// Paramètres
	
	void vu()
	{
		
	}
}

void BFS()
{
	queue<Situation> file;
	Situation dep;
	file.push(dep);
	dep.vu();
	
	while(!file.empty())
	{
		Situation cur=file.front();
		file.pop();
		cur.vu();
		//Boucler sur les transitions
		
	}
}