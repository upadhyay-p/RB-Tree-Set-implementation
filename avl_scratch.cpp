#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>
using namespace std;
struct avl{
    long data;
    long bal_height;
    // long child;
    avl * left;
    avl * right;
    // avl* parent;
};
long max(long x, long y)
{
	long max;
	if(x>=y)
		max=x;
	else
		max=y;
	return max;
}
long height(avl* root)
{
	long h=0;
	if(root==NULL)
		h=0;
	else
		h=1+max(height(root->left),height(root->right));
	return h;
}
long balfactor_cal(avl* root){
	long hght;
	hght=height(root->left)-height(root->right);
	return hght;
}
avl* right_rotation(avl* root)
{
	avl* p=root->left;
	avl* x=p->right;
	p->right=root;
	root->left=x;
	root->bal_height=balfactor_cal(root);
	p->bal_height=balfactor_cal(p);
	return p;
}
avl* left_rotation(avl* root)
{
	avl* p=root->right;
	avl* x=p->left;

	p->left=root;
	root->right=x;

	root->bal_height=balfactor_cal(root);
	p->bal_height=balfactor_cal(p);

	return p;
}
avl* rotation(avl* root,long x)
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
avl* insert(avl* root,long x)
{
	
	if(root == NULL)
	{
		avl* t=new avl;
		t->data=x;
		t->bal_height=0;
		t->left=NULL;
		t->right=NULL;
		root=t;
		return root;
	}
	else 
	{
		if(x<root->data)
		{
			root->left=insert(root->left,x);
			
			root->bal_height=balfactor_cal(root);
			root->left->bal_height=balfactor_cal(root->left);
			//after every insertion check for rotation at the changed nodes
			root=rotation(root,x);
			root->left=rotation(root->left,x);
			
			return root;
		}
		else if(x>root->data)
		{
			root->right=insert(root->right, x);
			
			root->bal_height=balfactor_cal(root);
			root->right->bal_height=balfactor_cal(root->right);
			//after every insertion check for rotation at the changed nodes
			root=rotation(root,x);
			root->right=rotation(root->right,x);
			return root;
		}
		else
		{
			return root;
		}
	}
	
}

avl* delete_node(avl* root,long x)
{
	//simple BST deletion
	if(root==NULL)
		return NULL;
	if(root->data>x)
		root->left=delete_node(root->left,x);
	if(root->data<x)
		root->right= delete_node(root->right,x);
	else{
		if(root->left==NULL && root->right==NULL) //no child case
		{
			struct avl* temp=new avl;
			temp=root;
			root=NULL;
			delete(temp);
			
		}
		//one child case
		if(root->left==NULL && root->right!=NULL)
		{
			root->data=root->right->data;
			delete(root->right);
			root->right=NULL;
		}
		if(root->right==NULL && root->left!=NULL)
		{
			root->data=root->left->data;
			delete(root->left);
			root->left=NULL;
		}
		//two children
		if(root->left!=NULL && root->right!=NULL)
		{
			//find inorder successor
			struct avl* temp=new avl;
			temp=root->right;
			while(temp->left!=NULL)
				temp=temp->left;
			root->data=temp->data;
			root->right=delete_node(root->right,temp->data);
		}
		
	}	
	//after deleting check if the node is unbalanced if yes rotate 
	if(root==NULL)
		return root;

	else{
		root->bal_height=balfactor_cal(root);
		if(root->bal_height>1 && root->left->bal_height<0)
		{
			root->left=left_rotation(root->left);
			return right_rotation(root);
		}
		if(root->bal_height<-1 && root->right->bal_height<=0)
		{
			return left_rotation(root);
		}
		if(root->bal_height<-1 && root->right->bal_height>0)
		{
			root->right=right_rotation(root->right);
			return left_rotation(root);
		}
		if(root->bal_height>1 && root->left->bal_height>=0)
		{
			return right_rotation(root);
		}
		return root;
	}
}
void inOrder(struct avl *root,vector<long>* v) 
{ 
	if(root==NULL)
		return;
	
    inOrder(root->left,v);
    v->push_back(root->data);
    inOrder(root->right,v); 
 } 
void Union(struct avl* root,struct avl* root1)
{
	vector<long> v;
	inOrder(root,&v);
	vector<long> v1;
	inOrder(root1,&v1);
	

	long i=0,j=0;
	vector<long> v3;
	while(i<v.size() && j<v1.size())
	{
			if(v[i]==v1[j])
			{
				v3.push_back(v[i]);
				i++;
				j++;
			}
			else if(v[i]<v1[j])
			{
				v3.push_back(v[i]);
				i++;
			}
			else if(v[i]>v1[j])
			{
				v3.push_back(v1[j]);
				j++;
			}
	}
	if(i<v.size())
	{
		while(i<v.size())
		{
			v3.push_back(v[i]);
			i++;
		}
	}
	else if(j<v1.size())
	{
		while(j<v1.size())
		{
			v3.push_back(v1[j]);
			j++;
		}
	}
	// cout << "union: "<<endl;
	for(int h=0;h<v3.size();h++)
	{
		cout << v3[h] << " ";
	}
	cout << endl;
	return; 
}

void intersection(struct avl* root,struct avl* root1)
{
	vector<long> v;
	inOrder(root,&v);
	vector<long> v1;
	inOrder(root1,&v1);
	long i=0,j=0;
	vector<long> v3;
	while(i<v.size() && j<v1.size())
	{
			if(v[i]==v1[j])
			{
				v3.push_back(v[i]);
				i++;
				j++;
			}
			else if(v[i]<v1[j])
			{
				i++;
			}
			else if(v[i]>v1[j])
			{
				j++;
			}
	}
	for(int h=0;h<v3.size();h++)
	{
		cout << v3[h] << " ";
	}
	cout << endl;
	return; 
}
void difference(struct avl* root,struct avl* root1)
{
	vector<long> v;
	inOrder(root,&v);
	vector<long> v1;
	inOrder(root1,&v1);
	long i=0,j=0;
	vector<long> v3;
	while(i<v.size() && j<v1.size())
	{
			if(v[i]==v1[j])
			{
				//v3.push_back(v[i]);
				i++;
				j++;
			}
			else if(v[i]<v1[j])
			{
				v3.push_back(v[i]);
				i++;
			}
			else if(v[i]>v1[j])
			{
				j++;
			}
	}
	if(i<v.size())
	{
		while(i<v.size())
		{
			v3.push_back(v[i]);
			i++;
		}
	}
	for(int h=0;h<v3.size();h++)
	{
		cout << v3[h] << " ";
	}
	cout << endl;
	return; 

}
int main() {
    // long n;
    // cout << "enter the no. of nodes to be inserted:"; 
    // cin >> n;
    // long m;
    // cin >> m;
    // time_t b=clock();
    struct avl *root=NULL;
    // cout << "Enter values:";
    // for(long i=0;i<n;i++)
    // {
    // 	long x;
    // 	cin >> x;
    // 	root=insert(root,x);
    // }
    root=insert(root,7);
    root=insert(root,3);
    root=insert(root,18);
    root=insert(root,10);
    root=insert(root,6);
    root=insert(root,11);
    root=insert(root,-1);
    root=insert(root,1);
    root=insert(root,2);
    
    // cout << "preorder after insertion: "<<endl;
    // preOrder(root,v);
    // cout << endl;
    // root=delete_node(root,10);
    // cout << "preorder after deletion of 10: "<<endl;
    // inOrder(root,v);
    // cout << endl;
    struct avl *root1=NULL;
    root1=insert(root1,2);
    root1=insert(root1,1);
    root1=insert(root1,4);
    root1=insert(root1,5);
    root1=insert(root1,9);
    root1=insert(root1,3);
    root1=insert(root1,6);
    root1=insert(root1,7);
    // root=insert(root,2);
    // root=insert(root,6);
    // root=insert(root,13);
    

    Union(root,root1);
  
    intersection(root,root1);
    
    difference(root,root1);
    // time_t sp=clock()-b;
    // cout << "time taken by AVL="<<sp<<endl;

    // time_t b1=clock();
    // set<int> s;
    // s.insert(2);
    // s.insert(1);
    // s.insert(4);
    // s.insert(5);
    // s.insert(9);
    // s.insert(3);
    // s.insert(6);
    // s.insert(7);

    // time_t s1=clock()-b1;
    // cout << "time taken by set="<<s1<<endl;
    return 0;
}