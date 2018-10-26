#include<iostream>
#include<vector>
#define RED 0
#define BLACK 1
using namespace std;



struct node{
	int data;
	int color=BLACK;
	node * left;
	node * right;
	node * parent;
};

void printTree(node* root);
//void print(Set s);

node* getNode(int x){
	node * new_node = new node;
	new_node->left=NULL;
	new_node->right=NULL;
	new_node->parent=NULL;
	new_node->data = x;
	new_node->color = RED;
	return new_node;
}

node* find(node * root, int x){
	if(root->data==x) return root;
	else if(root->data>x && root->left!=NULL) return find(root->left,x);
	else if(root->data>x && root->left==NULL) return root;
	else if(root->data<x && root->right!=NULL)return find(root->right,x);
	else if(root->data<x && root->right==NULL) return root;
	return root;
}

node * get_uncle(node * n){
	if(n->parent==NULL || n->parent->parent==NULL) return NULL;
	node * parent = n->parent;
	node * g_parent = parent->parent;
	if(g_parent->left == parent) return g_parent->right;
	else return g_parent->left;
}

void right_rotate(node ** root, node * g_parent){
	node* new_parent = g_parent->left;
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

void left_rotate(node ** root, node * g_parent){
	node* new_parent = g_parent->right;
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

void correct_red_red(node ** root, node * new_node){
	if(new_node==*root) return;
	node * parent = new_node->parent;
	node * g_parent = parent->parent;
	node * uncle = get_uncle(new_node);

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




class Set{
public:
	struct node * root;
	Set(){
		root=NULL;
	}
	
	void insert(int x){
		if(root==NULL){
			root = getNode(x);
			root->color = BLACK;
		}
		else{
			node * insert_at = find(root,x);
			if(insert_at->data ==x) return; //data already exists
			else{
				node * new_node = getNode(x);
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

};


void printTree(node* root){
	if(root==NULL)  return;
	if(root->left!=NULL)
	printTree(root->left);
	cout<<root->data<<" ";
	if(root->right!=NULL)
	printTree(root->right);
}


void print(Set s){
	printTree(s.root);
}

void inorder(struct node * root,vector<int> *v){
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
vector<int> union_merge(vector<int> v1, vector<int> v2){
	vector<int> v;
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

vector<int> intersection_merge(vector<int> v1, vector<int> v2){
	vector<int> v;
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

vector<int> difference_merge(vector<int> v1, vector<int> v2){
	vector<int> v;
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

Set Union(Set s1,Set s2){
	vector<int> v1;
	inorder(s1.root,&v1);
	vector<int> v2;
	 inorder(s2.root,&v2);
	vector<int> v3 = union_merge(v1,v2);
	Set s;
	for(int i=0;i<v3.size();i++){
		s.insert(v3[i]);
	}
	cout<<endl;
	return s;
}

Set Intersection(Set s1,Set s2){
	vector<int> v1;
	inorder(s1.root,&v1);

	vector<int> v2;
	inorder(s2.root,&v2);
	vector<int> v3 = intersection_merge(v1,v2);
	Set s;
	for(int i=0;i<v3.size();i++){
		s.insert(v3[i]);
	}
	return s;
}

Set Difference(Set s1, Set s2){
	vector<int> v1;
	inorder(s1.root,&v1);

	vector<int> v2;
	inorder(s2.root,&v2);
	vector<int> v3 = difference_merge(v1,v2);
	Set s;
	for(int i=0;i<v3.size();i++){
		s.insert(v3[i]);
	}
	return s;	
}



int main(){
	Set s;
	s.insert(7);
	s.insert(3);
	s.insert(18);
	s.insert(10);
	print(s);
	cout<<"\n";
	Set s1;
	s1.insert(97);
	s1.insert(30);
	s1.insert(8);
	s1.insert(100);
	// print(s1);

	Set tree;
	// s2.insert(8);
	// s2.insert(30);
	// s2.insert(78);
	// // s2.insert(7);
	// s1.insert(100);
	// print(s2);
	tree.insert(7); 
  tree.insert(3); 
  tree.insert(18); 
  tree.insert(10); 
  tree.insert(22); 
  tree.insert(8); 
  tree.insert(11); 
  tree.insert(26); 
  tree.insert(2); 
  tree.insert(6); 
  tree.insert(13);
  print(tree); 

  Set su = Union(tree,s);
  cout<<endl;
  print(su);

  cout<<endl;

  Set tree1;
  tree1.insert(2); 
  // print(tree1); cout<<endl;
  tree1.insert(3); 
  // print(tree1); cout<<endl;

  tree1.insert(6); 
  // print(tree1); cout<<endl;

  tree1.insert(7); 
  // print(tree1); cout<<endl;

  tree1.insert(8); 
  // tree1.insert(10); 
  // tree1.insert(11); 
  // tree1.insert(13); 
  // tree1.insert(18); 
  // tree1.insert(22); 
  tree1.insert(26);
  print(tree1);

  Set t = Difference(tree,tree1);
  cout<<endl;
  print(t);
	return 0;
}