#include<iostream>
#include<vector>
#include<set>
#include<time.h>
#include <string.h>
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
//void print(Set s);

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
node<T2>* find(node<T2> * root, T2 x){
	if(root->data==x) { return root;}
	else if(root->data>x && root->left!=NULL) return find(root->left,x);
	else if(root->data>x && root->left==NULL) return root;
	else if(root->data<x && root->right!=NULL)return find(root->right,x);
	else if(root->data<x && root->right==NULL) return root;
	return root;
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
      	// cout<<temp->data<<"--found"<<n;
      	return temp;
        break; 
      } else { 
      	// cout<<temp->data<<"-->";
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

template <typename T2>
void right_rotate(node<T2> ** root, node<T2> * g_parent){
	node<T2>* new_parent = g_parent->left;
	if(g_parent == *root)
		*root=new_parent;
	if(g_parent->parent!=NULL){
		if(g_parent->parent->left==g_parent){
			g_parent->parent->left=new_parent;
		}
		else{
			g_parent->parent->right=new_parent;
		}
	}
	new_parent->parent=g_parent;//changed
	g_parent->parent=new_parent;	
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
	if(g_parent->parent!=NULL){
		if(g_parent->parent->right==g_parent){//changed
			g_parent->parent->right=new_parent;
		}
		else{
			g_parent->parent->left=new_parent;
		}
	}
	new_parent->parent=g_parent;//changed
	g_parent->parent=new_parent;	
	g_parent->right = new_parent->left;
	if(new_parent->left!=NULL){
		new_parent->left->parent=g_parent;
	}
	new_parent->left=g_parent;
}

template <typename T2>
void correct_red_red(node<T2> ** root, node<T2> * new_node){
	if(new_node==*root) return;
	node<T2> * parent = new_node->parent;
	node<T2> * g_parent = parent->parent;
	node<T2> * uncle = get_uncle(new_node);

	if(parent->color==RED){
		if(uncle!=NULL && uncle->color==RED){
			parent->color=BLACK;
			uncle->color=BLACK;
			if(g_parent!=*root){
				g_parent->color=RED;
				correct_red_red(root,g_parent);
			}
		}
		else{

			if(uncle==NULL || uncle->color==BLACK){
			if(g_parent->left==parent && parent->left==new_node){
				//LL
				//make g_parent and new_node RED and parent BLACK
				//same rotation as AVL
				right_rotate(root, g_parent);
				int t = g_parent->color;
				g_parent->color=parent->color;
				parent->color=t;
				

			}
			else if(g_parent->left==parent && parent->right==new_node){
				//LR
				left_rotate(root, parent);
				int t = g_parent->color;
				g_parent->color=new_node->color;
				new_node->color=t;
				right_rotate(root,g_parent);
			}
			else if(g_parent->right==parent && parent->right==new_node){
				//RR
				left_rotate(root, g_parent);
				int t = g_parent->color;
				g_parent->color=parent->color;
				parent->color=t;
			}
			else if(g_parent->right==parent && parent->left==new_node){
				//RL
				right_rotate(root, parent);
				int t = g_parent->color;
				g_parent->color=new_node->color;
				new_node->color=t;
				left_rotate(root,g_parent);

			}
		}
	}
	}


	// node*
}
template <typename T2>
void swap_node_data(node<T2> * dnode, node<T2>* replace_node){
	// cout<<"swap: "<<dnode->data<<" and "<<replace_node->data<<endl;
	T2 temp;
	temp = dnode->data;
	dnode->data=replace_node->data;
	replace_node->data = temp;
}


template <typename T2>
void doubleBlack(node<T2> ** root, node<T2> * x){
	// cout<<"DD"<<endl;
	if(*root==x) return;
	node<T2> * sibling;
	bool isLeft=false;
	if(x->parent->left==x){
		sibling=x->parent->right;
	} 
	else if(x->parent->right==x) {
		sibling=x->parent->left;
		isLeft=true;
	}
	//if sibling is black and atleast oneof sibling's children is red
	if(sibling!=NULL && sibling->color==BLACK){
		//left child
		if(sibling->left!=NULL && sibling->left->color==RED){
			if(isLeft){
				//Left left case
				sibling->left->color=BLACK;
				right_rotate(root,sibling->parent);
			}
			else{
				//right left case
				right_rotate(root,sibling);
				int t=sibling->color;
				sibling->color=sibling->left->color;
				sibling->left->color=t;
				left_rotate(root,x->parent);
			}
		}
		//right child case
		else if(sibling->right!=NULL && sibling->right->color==RED){
			if(isLeft){
				//left right case
				left_rotate(root,sibling);
				int t=sibling->color;
				sibling->color=sibling->right->color;
				sibling->right->color=t;
				right_rotate(root,x->parent);

			}
			else{
				//right right case
				sibling->right->color=BLACK;
				left_rotate(root, sibling->parent);
			}
		}
	}
	else if(sibling->color==BLACK && (sibling->left==NULL || sibling->right==NULL||sibling->left->color==BLACK || sibling->right->color==BLACK)){
		sibling->color=RED;
		if(x->parent->color==BLACK){
			doubleBlack(root, x->parent);
		}
	}
	//red sibling
	else if(sibling->color==RED){
		if(!isLeft){
			//left case
			right_rotate(root,x->parent);
		}
		else{
			//right case
			left_rotate(root,x->parent);
		}
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
void del_node(node<T2> * root, node<T2> * dnode){
		struct node<T2> * parent = (dnode)->parent;
		struct node<T2> * replace_node;

		//finding inorder successor
		replace_node = find_replacement(dnode);
		// if(dnode->left==NULL && dnode->right==NULL){
		// 	replace_node=NULL;
		// }
		// else if(dnode->left!=NULL && dnode->right!=NULL){
		// 	cout<<"nonleaf"<<endl;
		// 	struct node * right_subtree = dnode->right;
		// 	while(right_subtree->left!=NULL)
		// 		right_subtree=right_subtree->left;
		// 	replace_node = right_subtree;
		// }
		// else if(dnode->left!=NULL)
		// 	replace_node = dnode->left;
		// else replace_node = dnode->right;

		//if(replace_node!=NULL) cout<<"replace_node: "<<replace_node->data<<endl;
		bool r_color = (replace_node==NULL)||(replace_node->color==BLACK);
		bool d_color = ((dnode)->color==BLACK);
		bool bothBlack = r_color && d_color;
		if(replace_node==NULL){
			if((dnode)==root){
				root=NULL;
			}else{
			if(bothBlack){
				//fix double black
				doubleBlack(&root, (dnode));
			}
			else{
				// struct node* sibling=NULL;
				// if(parent==NULL) sibling = NULL;
				// else if(parent->left=(dnode)) sibling  = parent->right;
				// else if(parent->right=dnode)sibling = parent->left;
				if(get_sibling(dnode)!=NULL)
					{get_sibling(dnode)->color = RED;}
			}
			if (parent->left==dnode)
				{parent->left = NULL;}
			else
				{parent->right = NULL;}
			// cout<<"1deleting-->"<<(dnode)->data<<endl;

		}
			delete dnode;
			return;
		}
		if((dnode)->left == NULL || (dnode)->right == NULL){
			if(dnode==root){
				(dnode)->data = replace_node->data;
				(dnode)->left=NULL;
				(dnode)->right=NULL;
				// cout<<"deleting-->"<<replace_node->data<<endl;
				delete replace_node;
			}
			else{
				if(parent->left==dnode){
					parent->left=replace_node;
				}
				else{
					parent->right=replace_node;
				}
				// cout<<"deleting-->"<<(dnode)->data<<endl;
				delete dnode;
				replace_node->parent = parent;
				if(bothBlack){
					//fixDoubleBlack(replace_node);
					doubleBlack(&root,replace_node);
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
			node<T> * insert_at = find(root,x);
			if(insert_at->data ==x) return; //data already exists
			else{
				// cout<<"Insert at: "<<insert_at->data.first<<","<<insert_at->data.second<<endl;
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
		// cout<<"delete this: "<<x<<endl;
		if(root==NULL){
			cout<<"The set is empty.";
			return;
		}

		node<T> * dnode = search(&root,x);
		if(dnode->data!=x){
			// cout<<"Attempt to delete non-existing key."<<dnode->data<<endl;
			return;
		}
		if(dnode==root){
			delete dnode;
			root=NULL;
			return;
		}
		del_node(root,dnode);

	}

	bool empty(){
		if(root==NULL) return true;
		return false;
	}

	T begin(){
		vector<T> v;
		inorder(root, &v);
		return v[0];
	}

};

template <typename T2>
void printTree(node<T2>* root){
	if(root==NULL)  return;
	if(root->left!=NULL)
	printTree(root->left);
	cout<<root->data.first<<","<<root->data.second<<" ";
	//if(root->data<100 && root->data>0) exit(1);
	if(root->right!=NULL)
	printTree(root->right);
}

template <typename T2>
void print(Set<T2> s){
	printTree(s.root);
}

template <typename T2>
void inorder(struct node<T2> * root,vector<T2> *v){
	//vector<int> v;
	//code for inorder
	if(root==NULL)  return ;
	if(root->left!=NULL)
	inorder(root->left,v);
	v->push_back(root->data);
	if(root->right!=NULL)
	inorder(root->right,v);
	//return v;
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
	//code for merge;
	return v;
}

template <typename T2>
vector<T2> intersection_merge(vector<T2> v1, vector<T2> v2){
	vector<T2> v;
	//code for merge;
	int i=0,j=0;
	while(i<v1.size() && j<v2.size()){
		if(v1[i]==v2[j]){
			v.push_back(v1[i]);
			i++;
			j++;
		}
		else if(v1[i]>v2[j]){
			//v.push_back(v2[j]);
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
			// v.push_back(v2[j]);
			j++;
		}
		else{
			// v.push_back(v1[i]);
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
	// else if(j<v2.size()){
	// 	while(j<v2.size()){
	// 		v.push_back(v2[j]);
	// 		j++;
	// 	}
	// }
	//code for merge;
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

// vector <pair<int,int>> v[10];  //array ka index is the vertex pair x,y is index--x si the edge and y is its weight
// int dist[10];
// int vis[10];
// int nodes,edges;

// void shortest_path(){

// memset(vis,0, sizeof vis);
// dist[1]=0;
// Set<pair<int, int>> s;  //pair x,y where x is the weight and y is the destination
// s.insert({0,1});
// while(!s.empty()){
// 	pair <int,int> p =s.begin();
// 	s.erase(s.begin());
// 	int x = p.second;
// 	int wei = p.first;
// 	if(vis[x]==1) continue;
// 	for(int i=0;i<v[x].size();i++){
// 		int e=v[x][i].first;
// 		int w=v[x][i].second;
// 		if(dist[x]+w<dist[e]){
// 			dist[e]=dist[x]+w;
// 			cout<<"inserting: "<<dist[e]<<","<<e<<endl;
// 			s.insert(make_pair(dist[e],e));
// 			//print(s);
// 			cout<<"inserted!"<<endl;
// 		}
// 	}
// }
// }

// void intialize(){
// 	for(int i=1;i<=nodes;i++){
// 		dist[i]=1234;
// 	}
// }


// int main(){
// 	cin>>nodes>>edges;
// for(int i=1;i<=nodes;i++){
// 	int x,y,z;
// 	cin>>x>>y>>z;
// 	v[x].push_back({y,z});
// }
// intialize();
// shortest_path();
// for(int i=2;i<=nodes;i++){
// 	cout<<dist[i]<<" ";
// }
	
// 	return 0;
// }