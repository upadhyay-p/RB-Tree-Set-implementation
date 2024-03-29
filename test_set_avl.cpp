#include <iostream>
#include <string.h>
#include <vector>

#include <limits.h>

using namespace std;
template <typename T>
struct avl{
    T data;
    int bal_height;
    avl * left;
    avl * right;
};
int max_h(int x, int y)
{
	int max;
	if(x>=y)
		max=x;
	else
		max=y;
	return max;
}
template <typename T>
int height(avl<T>* root)
{
	int h=0;
	if(root==NULL)
		h=0;
	else
		h=1+max_h(height(root->left),height(root->right));
	return h;
}
template <typename T>
int balfactor_cal(avl<T>* root){
	int hght=0;
	if(root!=NULL)
		hght=height(root->left)-height(root->right);
	return hght;
}
template <typename T>
avl<T>* right_rotation(avl<T>* root)
{
	avl<T>* p=root->left;
	avl<T>* x=p->right;
	p->right=root;
	root->left=x;
	root->bal_height=balfactor_cal(root);
	p->bal_height=balfactor_cal(p);
	return p;
}
template <typename T>
avl<T>* left_rotation(avl<T>* root)
{
	avl<T>* p=root->right;
	avl<T>* x=p->left;

	p->left=root;
	root->right=x;

	root->bal_height=balfactor_cal(root);
	p->bal_height=balfactor_cal(p);

	return p;
}
template <typename T>
avl<T>* rotation(avl<T>* root,T x)
{
	if(root->bal_height>1 && root->left->data>x)
	{
		root=right_rotation(root);
		return root;
	}
	if(root->bal_height<-1 && root->right->data<x )
	{
		root=left_rotation(root);
		return root;
	}
	if(root->bal_height<-1  && root->right->data>x )
	{
		root->right=right_rotation(root->right);
		root=left_rotation(root);
		return root;
	}
	if(root->bal_height>1 && root->left->data<x )
	{
		root->left=left_rotation(root->left);
		root=right_rotation(root);
		return root;
	}
	else 
		return root;

}
template <typename T>
void inOrder(struct avl<T>* root, vector<T>* v)
{
	if(root==NULL)
		return;
	inOrder(root->left,v);//original did not have &
	v->push_back(root->data);
	inOrder(root->right,v);//original did not have &

}

template <class T>
class Set{
public:

	struct avl<T>* root;
	Set()
	{
		root=NULL;
	}
	T begin()
	{
		// if(root==NULL) this case is not handled

		if(root->left==NULL && root->right==NULL)
			return root->data;
		else
		{
			avl<T>* t=new avl<T>;
			t=root;
			while(t->left!=NULL && t->right!=NULL)
			{
				t=t->left;
			}
			return t->data;
		}
	}

	avl<T>* insert_temp(avl<T>** root,T x)
	{
		
		if((*root) == NULL)
		{
			avl<T>* t=new avl<T>;
			t->data=x;
			t->bal_height=0;
			t->left=NULL;
			t->right=NULL;
			*root=t;
			return (*root);
		}
		else 
		{
			if(x<(*root)->data)
			{
				(*root)->left=insert_temp(&((*root)->left),x);
				
				(*root)->bal_height=balfactor_cal(*root);
				(*root)->left->bal_height=balfactor_cal((*root)->left);
				//after every insertion check for rotation at the changed nodes
				(*root)=rotation((*root),x);
				(*root)->left=rotation((*root)->left,x); 
				
				return (*root);
			}
			else if(x>(*root)->data)
			{
				(*root)->right=insert_temp(&((*root)->right), x);
				
				(*root)->bal_height=balfactor_cal((*root));
				(*root)->right->bal_height=balfactor_cal((*root)->right);
				//after every insertion check for rotation at the changed nodes
				(*root)=rotation((*root),x);
				(*root)->right=rotation((*root)->right,x);
				return (*root);
			}
			else
			{
				return (*root);
			}
		}
		
	}
	void insert(T x)
	{
		root=insert_temp(&root,x);
	}
	avl<T>* delete_temp(avl<T>** root,T x)
	{
			//simple BST deletion
		if((*root)==NULL)
			return NULL;
		else if((*root)->data>x)
			(*root)->left=delete_temp(&((*root)->left),x);
		else if((*root)->data<x)
			(*root)->right= delete_temp(&((*root)->right),x);
		else{
			if((*root)->left==NULL && (*root)->right==NULL) //no child case
			{
				struct avl<T>* temp=new avl<T>;
				temp=*root;
				*root=NULL;
				delete(temp);
				
			}
			//one child case
			else if((*root)->left==NULL && (*root)->right!=NULL)
			{
				(*root)->data=(*root)->right->data;
				delete((*root)->right);
				(*root)->right=NULL;
			}
			else if((*root)->right==NULL && (*root)->left!=NULL)
			{
				(*root)->data=(*root)->left->data;
				delete((*root)->left);
				(*root)->left=NULL;
			}
			//two children
			else if((*root)->left!=NULL && (*root)->right!=NULL)
			{
				//find inorder successor
				struct avl<T>* temp=new avl<T>;
				temp=(*root)->right;
				while(temp->left!=NULL)
					temp=temp->left;
				(*root)->data=temp->data;
				(*root)->right=delete_temp(&((*root)->right),temp->data);
			}
			
		}	
		//after deleting check if the node is unbalanced if yes rotate 
		if((*root)==NULL)
			return (*root);

		else{
			(*root)->bal_height=balfactor_cal((*root));
			if((*root)->bal_height>1 && (*root)->left->bal_height<0)
			{
				(*root)->left=left_rotation((*root)->left);
				return right_rotation((*root));
			}
			if((*root)->bal_height<-1 && (*root)->right->bal_height<=0)
			{
				return left_rotation((*root));
			}
			if((*root)->bal_height<-1 && (*root)->right->bal_height>0)
			{
				(*root)->right=right_rotation((*root)->right);
				return left_rotation((*root));
			}
			if((*root)->bal_height>1 && (*root)->left->bal_height>=0)
			{
				return right_rotation((*root));
			}
			return (*root);
	}

	}
	void erase(T x)
	{
		root=delete_temp(&root,x);
	}
	bool empty()
	{
		if(root==NULL)
		{
			return true;
		}
		else
		    return false;
	}
// 	void printSet()
// 	{
// 		vector<T> v;
// 		inOrder(root,&v);
// 		for(int i=0;i<v.size();i++)
// 		{
// 			cout << v[i] << " ";
// 		}
// 		cout << endl;

// 	}

};



vector <pair<long,long>> g[100000];
long dist[100000];
long visited[100000];
void shortest_path()
{

	Set<pair<long,long>> s;
	s.insert({0,1}); //from 1 to 1 dist=0 ({0=dist and 1=destination})

	while(!s.empty())
	{

		pair<long,long> x=s.begin();
		s.erase(s.begin());
		long e=x.second;
		if(visited[e]==1)
			continue;

		visited[e]=1;
		for(unsigned long i=0;i<g[e].size();i++)
		{

			if(visited[g[e][i].first]==0)
			{				

				if(dist[e]+g[e][i].second<dist[g[e][i].first])
				{
					
					dist[g[e][i].first]=dist[e]+g[e][i].second;
					
					s.insert({dist[g[e][i].first],g[e][i].first});
					
				}
			}
			
		}
	}

}

int main(){
	long n,e;

	cin >>n;

	cin>>e;

	for(long i=1;i<=e;i++)
	{
		long x,y,z;
		cin >> x >> y >> z;
		g[x].push_back({y,z});
	}
	dist[1]=0;
	for(long i=2;i<=n;i++)
	{
		dist[i]=INT_MAX;
	}
	for(long i=1;i<=n;i++)
	{
		visited[i]=0;
	}
	shortest_path();

	for(long i=2;i<=n;i++)
	{
		cout << dist[i] << " ";
	}
	cout << endl;

}
