#include <iostream>
#include <vector>
#include <limits.h>
#include "avl_Set.cpp"

using namespace std;
vector <pair<int,int>> g[1000];
int dist[1000];
int visited[1000];
void shortest_path()
{
	
	Set<pair<int,int>> s;
	s.insert({0,1}); //from 1 to 1 dist=0 ({0=dist and 1=destination})
	while(!s.empty())
	{
		pair<int,int> x=s.begin();
		s.erase(s.begin());
		int e=x.second;
		if(visited[e]==1)
			continue;

		visited[e]=1;
		for(int i=0;i<g[e].size();i++)
		{
			if(visited[g[e][i].first]==0)
			{				
				if(dist[e]+g[e][i].second<dist[g[e][i].first]) //if newly found distance is less 
															  //then already know distance then update distance[]
				{
					
					dist[g[e][i].first]=dist[e]+g[e][i].second;
					
					s.insert({dist[g[e][i].first],g[e][i].first});//insert the new pair to set
					
				}
			}
			
		}
	}

}

int main(){
	int n,e;
	
	cin >>n;//nodes
	
	cin>>e;//edges
	
	for(int i=1;i<=e;i++)
	{
		int x,y,z; //from vertex x to vertex y edge has weight=z
		cin >> x >> y >> z;
		
		g[y].push_back({x,z});
		g[x].push_back({y,z});
	}
	//assume source vertex to be 1
	dist[1]=0;//from source to source distance=0 
	for(int i=2;i<=n;i++)
	{
		dist[i]=INT_MAX;//initialize all other distances to infinity
	}
	for(int i=1;i<=n;i++)
	{
		visited[i]=0;//initialize visited of every vertex to zero
	}
	shortest_path();
	// cout << "output"<<endl;
	for(int i=2;i<=n;i++)
	{
		cout << dist[i] << " ";
	}
	cout << endl;

}