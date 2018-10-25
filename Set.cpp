#include<iostream>
#define RED 0
#define BLACK 1
using namespace std;


struct node{
	int data;
	int color;
	node * left;
	node * right;
	node * parent;
};

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

void right_rotate(node * root, node * g_parent){
	node* new_parent = g_parent->left;
	if(g_parent==root)
		root=new_parent;
	if(g_parent->parent!=NULL){
		if(g_parent->left==g_parent){
			g_parent->parent->left=new_parent;
		}
		else{
			g_parent->parent->right=new_parent;
		}
	}
	new_parent->parent=g_parent;
	g_parent->parent=new_parent;
	g_parent->left = new_parent->right;
	if(new_parent->right!=NULL){
		new_parent->right->parent=g_parent;
	}
	new_parent->right=g_parent;

}


void correct_red_red(node * root, node * new_node){
	if(new_node==root) return;
	node * parent = new_node->parent;
	node * g_parent = parent->parent;
	node * uncle = get_uncle(new_node);

	if(parent->color==RED){
		if(uncle!=NULL && uncle->color==RED){
			parent->color=BLACK;
			uncle->color=BLACK;
			if(g_parent!=root){
				g_parent->color=RED;
				correct_red_red(root,g_parent);
			}
		}
		else{
			cout<<"h";
			if(uncle!=NULL && uncle->color==BLACK){
			if(g_parent->left==parent && parent->left==new_node){
				//LL
				//make g_parent and new_node RED and parent BLACK
				//same rotation as AVL
				int t = g_parent->color;
				g_parent->color=parent->color;
				parent->color=t;
				right_rotate(root,g_parent);

			}
			else if(g_parent->left==parent && parent->right==new_node){
				//LR
			}
			else if(g_parent->right==parent && parent->right==new_node){
				//RR
			}
			else if(g_parent->right==parent && parent->left==new_node){
				//LR
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
				correct_red_red(root,new_node);
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
	print(s1);
	return 0;
}