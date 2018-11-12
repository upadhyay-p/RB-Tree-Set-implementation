#include<iostream>
#include<vector>
#include<set>
#include<time.h>
#include <string.h>
#include<limits.h>
#include <time.h>
#define RED 0
#define BLACK 1
using namespace std;

template <typename T1>
struct node{
	T1 data;
	int color=BLACK;
	node * left;
	node * right;
	node * parent;
};
template <typename T>
void printTree(struct node<T>* root);


template <typename T2>
node<T2>* getNode(T2 x){
	node<T2> * new_node = new node<T2>;
	new_node->left=NULL;
	new_node->right=NULL;
	new_node->parent=NULL;
	new_node->data = x;
	new_node->color = RED;
	return new_node;
}

template <typename T2>
node<T2>* find(node<T2> ** root, T2 x){
	if((*root)->data==x) { return *root;}
	else if((*root)->data>x && (*root)->left!=NULL) return find(&((*root)->left),x);
	else if((*root)->data>x && (*root)->left==NULL) return *root;
	else if((*root)->data<x && (*root)->right!=NULL)return find(&((*root)->right),x);
	else if((*root)->data<x && (*root)->right==NULL) return *root;
	return *root;
}

template <typename T2>
 node<T2> *search(node<T2>** root,T2 n) { 
    node<T2> *temp = *root; 
    while (temp != NULL) { 
    	
      if (n < temp->data) { 
        if (temp->left == NULL) 
          break; 
        else
          temp = temp->left; 
      } else if (n == temp->data) { 
      	
        break; 
      } else { 
        if (temp->right == NULL) 
          break; 
        else
          temp = temp->right; 
      } 
    } 
  
    return temp; 
  } 

template <typename T2>
node<T2> * get_uncle(node<T2> * n){
	if(n->parent==NULL || n->parent->parent==NULL) return NULL;
	node<T2> * parent = n->parent;
	node<T2> * g_parent = parent->parent;
	if(g_parent->left == parent) return g_parent->right;
	else return g_parent->left;
}

template <typename T>
void moveDown(node<T>* x, node<T>* new_parent){
	if(x->parent!=NULL){
		if(x->parent->left==x){
			x->parent->left=new_parent;
		}
		else{
			x->parent->right=new_parent;
		}
	}
	new_parent->parent=x->parent;
	x->parent=new_parent;
}

template <typename T2>
void right_rotate(node<T2> ** root, node<T2> * g_parent){
	node<T2>* new_parent = g_parent->left;
	if(g_parent == *root)
		*root=new_parent;
	

	moveDown(g_parent, new_parent);
	
	g_parent->left = new_parent->right;
	if(new_parent->right!=NULL){
		new_parent->right->parent=g_parent;
	}
	new_parent->right=g_parent;
}

template <typename T2>
void left_rotate(node<T2> ** root, node<T2> * g_parent){
	node<T2>* new_parent = g_parent->right;
	if(g_parent == *root)
		*root=new_parent;
	

	moveDown(g_parent, new_parent);
	g_parent->right = new_parent->left;
	if(new_parent->left!=NULL){
		new_parent->left->parent=g_parent;
	}
	new_parent->left=g_parent;
}

template <typename T2>
void correct_red_red(node<T2> ** root, node<T2> * new_node){
	if(new_node==*root){
		new_node->color=BLACK;
	 return;}
	node<T2> * parent = new_node->parent;
	node<T2> * g_parent = parent->parent;
	node<T2> * uncle = get_uncle(new_node);

	if(parent->color!=BLACK){
		if(uncle!=NULL && uncle->color==RED){
			parent->color=BLACK;
			uncle->color=BLACK;
			
				g_parent->color=RED;
				correct_red_red(root,g_parent);
			
		}
		else{

			
			if(g_parent->left==parent && parent->left==new_node){
				
				int t = g_parent->color;
				g_parent->color=parent->color;
				parent->color=t;
				right_rotate(root, g_parent);

			}
			else if(g_parent->left==parent && parent->right==new_node){
				
				left_rotate(root, parent);
				int t = g_parent->color;
				g_parent->color=new_node->color;
				new_node->color=t;
				right_rotate(root,g_parent);
			}
			else if(g_parent->right==parent && parent->right==new_node){
				
				
				int t = g_parent->color;
				g_parent->color=parent->color;
				parent->color=t;
				left_rotate(root, g_parent);
			}
			else if(g_parent->right==parent && parent->left==new_node){
				
				right_rotate(root, parent);
				int t = g_parent->color;
				g_parent->color=new_node->color;
				new_node->color=t;
				left_rotate(root,g_parent);

			}
		}

	}



}
template <typename T2>
void swap_node_data(node<T2> * dnode, node<T2>* replace_node){
	
	T2 temp;
	temp = dnode->data;
	dnode->data=replace_node->data;
	replace_node->data = temp;
}


template <typename T2>
void doubleBlack(node<T2> ** root, node<T2> * x){
	
	
	if(x==*root) return;
	
	node<T2> * sibling;
	bool isLeft=false;
	if(x->parent->left==x){
		sibling=x->parent->right;
	} 
	else if(x->parent->right==x) {
		sibling=x->parent->left;
		isLeft=true;
	}
	if(sibling==NULL){
		doubleBlack(root,x->parent);
	}
	
	else if(sibling!=NULL && sibling->color==BLACK){
		
		if(sibling->left!=NULL && sibling->left->color==RED){
			if(isLeft){
				
				sibling->left->color=sibling->color;
				sibling->color=x->parent->color;
				right_rotate(root,sibling->parent);
			}
			else{
				
				sibling->left->color=x->parent->color;
				right_rotate(root,sibling);
				
				left_rotate(root,x->parent);
				
				
				
				
				
			}
			x->parent->color=BLACK;
		}
		
		else if(sibling->right!=NULL && sibling->right->color==RED){
			if(isLeft){
				
				sibling->right->color=x->parent->color;
				left_rotate(root,sibling);
				right_rotate(root,x->parent);
				
				
				
				
				

			}
			else{
				
				sibling->right->color=sibling->color;
				sibling->color=x->parent->color;
				left_rotate(root, sibling->parent);
			}
			x->parent->color=BLACK;
		}
	}
	
	else if(sibling->color==RED){
		x->parent->color=RED;
		sibling->color=BLACK;
		if(isLeft){
			
			right_rotate(root,x->parent);
		}
		else{
			
			left_rotate(root,x->parent);
		}
		doubleBlack(root,x);
	}
	else{
		sibling->color=RED;
		if(x->parent->color==BLACK){
			doubleBlack(root, x->parent);
		}
		else
			x->parent->color=BLACK;
	}


}

template <typename T2>
node<T2> * find_replacement(node<T2> * x){
	
	if(x->left!=NULL && x->right!=NULL) {
		node<T2> * t=x->right;
		while(t->left!=NULL)
			t=t->left;
		return t;
	}
	
	if(x->left==NULL && x->right==NULL) return NULL;
	
	if(x->left!=NULL)
		return x->left;
	else return x->right;
}

template <typename T2>
node<T2> * get_sibling(node<T2> * x){
	node<T2> * parent=x->parent;
	if(parent==NULL) return NULL;
	if(parent->left==x) return parent->right;
	return parent->left;
}

template <typename T2>
void del_node(node<T2> ** root, node<T2> * dnode){
		struct node<T2> * parent = (dnode)->parent;
		struct node<T2> * replace_node;

		
		replace_node = find_replacement(dnode);
		
		
		
		
		
		
		
		
		
		
		
		
		

		
		bool r_color = (replace_node==NULL)||(replace_node->color==BLACK);
		bool d_color = ((dnode)->color==BLACK);
		bool bothBlack = r_color && d_color;
		if(replace_node==NULL){
			if((dnode)==*root){
				*root=NULL;
			}
			else{
			if(bothBlack){
				
				doubleBlack(root, (dnode));
			}
			else{
				
				
				
				
				if(get_sibling(dnode)!=NULL)
					{get_sibling(dnode)->color = RED;}
			}

			if (parent!=NULL && parent->left==dnode)
				{parent->left = NULL;}
			else if(parent!=NULL && parent->right==dnode)
				{parent->right = NULL;}
			

		}
			delete dnode;
			return;
		}
		if((dnode)->left == NULL || (dnode)->right == NULL){
			if(dnode==*root){
				(dnode)->data = replace_node->data;
				(dnode)->left=NULL;
				(dnode)->right=NULL;
				
				delete replace_node;
			}
			else{
				if(parent->left==dnode){
					parent->left=replace_node;
				}
				else{
					parent->right=replace_node;
				}
				
				delete dnode;
				replace_node->parent = parent;
				if(bothBlack){
					
					doubleBlack(root,replace_node);
				}
				else{
					replace_node->color=BLACK;
				}
			}
			return;
		}

		swap_node_data(dnode,replace_node);
		del_node(root,replace_node);
	
}


template <class T>
class Set{
public:
	struct node<T> * root;
	Set(){
		root=NULL;
	}
	
	void insert(T x){
		if(root==NULL){
			root = getNode(x);
			root->color = BLACK;
		}
		else{
			node<T> * insert_at = search(&root,x);
			if(insert_at->data ==x) return; 
			else{
				
				node<T> * new_node = getNode(x);
				new_node->parent = insert_at;
				if(x < insert_at->data){
					insert_at->left = new_node;
				}
				else{
					insert_at->right = new_node;
				}
				correct_red_red(&root,new_node);
			}
		}
	}

	void erase(T x){
		
		if(root==NULL){
			
			
			return;
		}

		node<T> * dnode = search(&root,x);
		if(dnode->data!=x){
			
			return;
		}
		
		
		
		
		
		
		del_node(&root,dnode);

	}

	bool empty(){
		return (root==NULL);
	}

	T begin(){
		if(root!=NULL){
			node<T> * temp=root;
			while(temp->left!=NULL)
				temp=temp->left;
			return temp->data;
		}
	}

};

void printTree(node<pair<int,int>>* root){
	if(root==NULL)  return;
	if(root->left!=NULL)
	printTree(root->left);
	cout<<root->data.first<<","<<root->data.second<<" ";
	
	if(root->right!=NULL)
	printTree(root->right);
}

template <typename T2>
void printTree(node<T2>* root){
	if(root==NULL)  return;
	if(root->left!=NULL)
	printTree(root->left);
	cout<<root->data<<" ";
	
	if(root->right!=NULL)
	printTree(root->right);
}

template <typename T2>
void print(Set<T2> s){
	printTree(s.root);
}

template <typename T2>
void inorder(struct node<T2> * root,vector<T2> *v){
	
	
	if(root==NULL)  return ;
	if(root->left!=NULL)
	inorder(root->left,v);
	v->push_back(root->data);
	if(root->right!=NULL)
	inorder(root->right,v);
	
}

template <typename T2>
vector<T2> union_merge(vector<T2> v1, vector<T2> v2){
	vector<T2> v;
	int i=0,j=0;
	while(i<v1.size() && j<v2.size()){
		if(v1[i]<v2[j]){
			v.push_back(v1[i]);
			i++;
		}
		else if(v1[i]>v2[j]){
			v.push_back(v2[j]);
			j++;
		}
		else{
			v.push_back(v1[i]);
			i++;
			j++;
		}
	}
	if(i<v1.size()){
		while(i<v1.size()){
			v.push_back(v1[i]);
			i++;
		}
	}
	else if(j<v2.size()){
		while(j<v2.size()){
			v.push_back(v2[j]);
			j++;
		}
	}
	
	return v;
}

template <typename T2>
vector<T2> intersection_merge(vector<T2> v1, vector<T2> v2){
	vector<T2> v;
	
	int i=0,j=0;
	while(i<v1.size() && j<v2.size()){
		if(v1[i]==v2[j]){
			v.push_back(v1[i]);
			i++;
			j++;
		}
		else if(v1[i]>v2[j]){
			
			j++;
		}
		else{
			i++;
		}
	}
	return v;
}


template <typename T2>
vector<T2> difference_merge(vector<T2> v1, vector<T2> v2){
	vector<T2> v;
	int i=0,j=0;
	while(i<v1.size() && j<v2.size()){
		if(v1[i]<v2[j]){
			v.push_back(v1[i]);
			i++;
		}
		else if(v1[i]>v2[j]){
			
			j++;
		}
		else{
			
			i++;
			j++;
		}
	}
	if(i<v1.size()){
		while(i<v1.size()){
			v.push_back(v1[i]);
			i++;
		}
	}
	
	
	
	
	
	
	
	return v;
}

template <typename T2>
Set<T2> Union(Set<T2> s1,Set<T2> s2){
	vector<T2> v1;
	inorder(s1.root,&v1);
	vector<T2> v2;
	 inorder(s2.root,&v2);
	vector<T2> v3 = union_merge(v1,v2);
	Set<T2> s;
	for(int i=0;i<v3.size();i++){
		s.insert(v3[i]);
	}
	cout<<endl;
	return s;
}


template <typename T2>
Set<T2> Intersection(Set<T2> s1,Set<T2> s2){
	vector<T2> v1;
	inorder(s1.root,&v1);

	vector<T2> v2;
	inorder(s2.root,&v2);
	vector<T2> v3 = intersection_merge(v1,v2);
	Set<T2> s;
	for(int i=0;i<v3.size();i++){
		s.insert(v3[i]);
	}
	return s;
}

template <typename T2>
Set<T2> Difference(Set<T2> s1, Set<T2> s2){
	vector<T2> v1;
	inorder(s1.root,&v1);

	vector<T2> v2;
	inorder(s2.root,&v2);
	vector<T2> v3 = difference_merge(v1,v2);
	Set<T2> s;
	for(int i=0;i<v3.size();i++){
		s.insert(v3[i]);
	}
	return s;	
}


vector <pair<long long,long long>> v[1000000];  
long long dist[1000000];
bool vis[1000000];


void shortest_path(){


dist[1]=0;
Set<pair<long, long>> s;  
s.insert({0,1});
int i=0;
while(!s.empty()){
	
	pair <long long,long long> p =s.begin();
	
	s.erase(s.begin());
	
	
	
	int x = p.second;
	int wei = p.first;
	if(vis[x]==1) continue;
	vis[x]=1;
	
	for(int i=0;i<v[x].size();i++){
		int e=v[x][i].first;
		int w=v[x][i].second;
		
		if(vis[e]==0){
		if(dist[x]+w<dist[e]){
			dist[e]=dist[x]+w;
			
			s.insert(make_pair(dist[e],e));
			
			
		}}
	}
}
}

void intialize(long long nodes){
	for(int i=1;i<=nodes;i++){
		dist[i]=1000000000;
		vis[i]=0;
	}
}


int main(){
    long long nodes,edges;
	
	cin>>nodes>>edges;
	
	
	int c=0;
for(int i=1;i<=edges;i++){
	int x,y,z;
	cin>>x>>y>>z;
	v[x].push_back({y,z});

	
}

intialize(nodes);

clock_t t;
t=clock();
shortest_path();

for(int i=2;i<=nodes;i++){
	cout<<dist[i]<<" ";
}
	
	return 0;
}