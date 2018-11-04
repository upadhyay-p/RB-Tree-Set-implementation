#include <iostream>
#include <vector>
#include <limits.h>
// #include <bits/stdc++.h> 
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
			// cout<<"for loop of list "<<i+1<<endl;
			if(visited[g[e][i].first]==0)
			{				
				if(dist[e]+g[e][i].second<dist[g[e][i].first])
				{
					cout<<"g[e][i].second="<<g[e][i].second<<endl;
					cout<<endl;
					cout << "pair pushed: "<< dist[g[e][i].first] << "---" << g[e][i].first<<"---original: "<<dist[g[e][i].first] <<endl;
					cout<<endl;
					dist[g[e][i].first]=dist[e]+g[e][i].second;
					cout << "after pair pushed: "<< dist[g[e][i].first] << "---" << g[e][i].first<<endl;
					cout<<endl;
					s.insert({dist[g[e][i].first],g[e][i].first});
					
				}
			}
			
		}
	}

}

int main(){
	int n,e;
	cin >>n>>e;
	for(int i=1;i<=e;i++)
	{
		int x,y,z;
		cin >> x>>y>>z;
		
		g[y].push_back({x,z});
		g[x].push_back({y,z});
	}
	dist[1]=0;
	for(int i=2;i<=n;i++)
	{
		dist[i]=INT_MAX;
	}
	for(int i=1;i<=n;i++)
	{
		visited[i]=0;
	}
	shortest_path();
	for(int i=1;i<=n;i++)
	{
		cout << dist[i] << " ";
	}
	cout << endl;

}