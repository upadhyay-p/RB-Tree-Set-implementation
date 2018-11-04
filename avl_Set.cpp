#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>
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
		h=1+max(height(root->left),height(root->right));
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
		vector<T> v;
		inOrder(root,&v);
		return v[0];
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
	}
	void printSet()
	{
		vector<T> v;
		inOrder(root,&v);
		for(int i=0;i<v.size();i++)
		{
			cout << v[i] << " ";
		}
		cout << endl;

	}

};

template <typename T>
Set<T> Union(Set<T> s,Set<T> s1)
{
	vector<T> v;
	inOrder(s.root,&v);
	vector<T> v1;
	inOrder(s1.root,&v1);
	Set<T> temp;

	int i=0,j=0;
	vector<T> v3;
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
		// cout << v3[h] << " ";
		temp.insert(v3[h]);
	}
	// cout << endl;
	return temp; 
}

template <typename T>
Set<T> intersection(Set<T> s,Set<T> s1)
{
	vector<T> v;
	inOrder(s.root,&v);
	vector<T> v1;
	inOrder(s1.root,&v1);
	int i=0,j=0;
	vector<T> v3;
	Set<T> temp;
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
		// cout << v3[h] << " ";
		temp.insert(v3[h]);
	}
	// cout << endl;
	return temp; 
}

template <typename T>
Set<T> difference(Set<T> s,Set<T> s1)
{
	vector<T> v;
	inOrder(s.root,&v);
	vector<T> v1;
	inOrder(s1.root,&v1);
	int i=0,j=0;
	vector<T> v3;
	Set<T> temp;
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
		temp.insert(v3[h]);
		// cout << v3[h] << " ";
	}
	// cout << endl;
	return temp; 

}
// int main()
// {
// 	Set<float> s;
// 	s.insert(-1.2);
// 	s.insert(1.3);
// 	s.insert(1.9);
// 	s.insert(2);
// 	s.insert(2.5);
// 	s.insert(3.7);
// 	s.insert(4.8);
// 	s.insert(5.7);
// 	s.insert(6.2);
// 	s.insert(7);
// 	s.insert(9.8);
// 	s.insert(10.3);
// 	s.insert(11.1);
// 	s.insert(18.9);
// 	s.erase(2.5);
// 	s.erase(8);
// 	s.printSet();

// 	Set<float> s1;
// 	s1.insert(2);
// 	s1.insert(2.5);
// 	s1.insert(3.7);
// 	s1.insert(4.8);
// 	s1.insert(5.7);
// 	s1.insert(6.2);
// 	s1.insert(2.9);
// 	s1.insert(3.12);
// 	s1.insert(4.18);
// 	s1.insert(5.17);
// 	s1.insert(6.12);
// 	s1.printSet();

// 	Set<float> s2=Union(s,s1);
// 	s2.printSet();

// 	Set<float> s3=intersection(s,s1);
// 	s3.printSet();

// 	Set<float> s4 = difference(s,s1);
// 	s4.printSet();



// }