#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>
using namespace std;
//struct defining avl tree node
template <typename T>
struct avl{
    T data;
    int bal_height;
    avl * left;
    avl * right;
};
int max_h(int x, int y)//give max value amongst x and y
{
	int max;
	if(x>=y)
		max=x;
	else
		max=y;
	return max;
}
template <typename T>
int height(avl<T>* root)//find height of tree
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
		hght=height(root->left)-height(root->right);//balance factor = height of left subtree - height of right subtree
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
	//LL case
	if(root->bal_height>1 && root->left->data>x)
	{
		root=right_rotation(root);
		return root;
	}

	//RR case
	if(root->bal_height<-1 && root->right->data<x )
	{
		root=left_rotation(root);
		return root;
	}

	//RL case
	if(root->bal_height<-1  && root->right->data>x )
	{
		root->right=right_rotation(root->right);
		root=left_rotation(root);
		return root;
	}

	//LR case
	if(root->bal_height>1 && root->left->data<x )
	{
		root->left=left_rotation(root->left);
		root=right_rotation(root);
		return root;
	}
	else 
		return root;

}


//find the inorder sequence and store it in a vector
template <typename T>
void inOrder(struct avl<T>* root, vector<T>* v)
{
	if(root==NULL)
		return;
	inOrder(root->left,v);
	v->push_back(root->data);
	inOrder(root->right,v);

}

template <class T>
class Set{
public:

	struct avl<T>* root;
	Set()
	{
		root=NULL;//initialize the set with empty tree
	}

	T begin()//return first element of the set
	{
		if(root->left==NULL && root->right==NULL)//if set has single element then return it
			return root->data;
		
		//else go to the left until you hit the leaf node (first node of inorder)
		else
		{
			avl<T>* t=new avl<T>;
			t=root;
			while(t->left!=NULL && t->right!=NULL)
			{
				t=t->left;
			}
			return t->data;//return that node's data
		}
	}

	avl<T>* insert_temp(avl<T>** root,T x)
	{
		
		if((*root) == NULL)//if root is null, then create a node having data as x and make it root
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
			if(x<(*root)->data)//if root data > x then x must be inserted in left subtree
			{
				(*root)->left=insert_temp(&((*root)->left),x); //insert in left subtree
				

				//check is insertion leads to violation of range of balance factor
				(*root)->bal_height=balfactor_cal(*root);
				(*root)->left->bal_height=balfactor_cal((*root)->left);

				//after every insertion check for rotation at the changed nodes
				(*root)=rotation((*root),x);
				(*root)->left=rotation((*root)->left,x);
				
				return (*root);//return the new tree
			}
			else if(x>(*root)->data)//if root data < x then x must be inserted in right subtree
			{
				(*root)->right=insert_temp(&((*root)->right), x);//insert in left subtree
				
				//check is insertion leads to violation of range of balance factor
				(*root)->bal_height=balfactor_cal((*root));
				(*root)->right->bal_height=balfactor_cal((*root)->right);

				//after every insertion check for rotation at the changed nodes
				(*root)=rotation((*root),x);
				(*root)->right=rotation((*root)->right,x);

				return (*root);//return the new tree
			}
			else
			{
				return (*root);//element already is in the set no need for inserting
			}
		}
		
	}
	void insert(T x)//insert data x into the set
	{
		root=insert_temp(&root,x);//get apt place for x and insert it there
	}
	avl<T>* delete_temp(avl<T>** root,T x)
	{
		//simple BST deletion
		if((*root)==NULL)//if root is NULL then x is not there => there is no meaning of deleting anything
			return NULL;
		else if((*root)->data>x)//if data of root is greater than x then x lies in left subtree
			(*root)->left=delete_temp(&((*root)->left),x);
		else if((*root)->data<x)//if data of root is less than x then x lies in right subtree
			(*root)->right= delete_temp(&((*root)->right),x);
		else{
			//if data of root is equal to x then check cases

			//case 1) node having x has no child 
			if((*root)->left==NULL && (*root)->right==NULL) 
			{
				struct avl<T>* temp=new avl<T>; 
				temp=*root;
				*root=NULL;
				delete(temp);//delete the node having x
				
			}


			//case 2) node having x has one child 

			//case 2.1) right child
			else if((*root)->left==NULL && (*root)->right!=NULL)
			{
				(*root)->data=(*root)->right->data;//replace the root data from the data of right child
				delete((*root)->right);//delete right child
				(*root)->right=NULL;
			}

			//case 2.2) left child
			else if((*root)->right==NULL && (*root)->left!=NULL)
			{
				(*root)->data=(*root)->left->data;//replace the root data from the data of left child
				delete((*root)->left);//delete left child
				(*root)->left=NULL;
			}


			//case 3) node having x has two children
			else if((*root)->left!=NULL && (*root)->right!=NULL)
			{
				//find inorder successor
				struct avl<T>* temp=new avl<T>;
				temp=(*root)->right;
				while(temp->left!=NULL)
					temp=temp->left;

				//replace the root data with the data of successor
				(*root)->data=temp->data;
				(*root)->right=delete_temp(&((*root)->right),temp->data);//delete the successor
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
	void erase(T x)//erase the element x from the set
	{
		root=delete_temp(&root,x);//go from the root to find exact position of x then erase it
	}
	bool empty()//check if the set is empty or not
	{
		if(root==NULL)
		{
			return true;
		}
		else
			return false;
	}
	void printSet()
	{
		vector<T> v;
		inOrder(root,&v);//take inorder traversal of the tree (because inorder gives elements in sorted order)
		for(int i=0;i<v.size();i++)
		{
			cout << v[i] << " ";//print the set elements
		}
		cout << endl;

	}

};

template <typename T>
Set<T> Union(Set<T> s,Set<T> s1)
{
	vector<T> v;
	inOrder(s.root,&v);//take inorder traversal of s
	vector<T> v1;
	inOrder(s1.root,&v1);//take inorder traversal of s1
	Set<T> temp;

	int i=0,j=0;
	vector<T> v3;
	while(i<v.size() && j<v1.size())
	{
			if(v[i]==v1[j]) //elements in common must be included only once
			{
				v3.push_back(v[i]);
				i++;
				j++;
			}
			//elements that are not in common must also be included
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
	if(i<v.size())//if elements are left in s then include them
	{
		while(i<v.size())
		{
			v3.push_back(v[i]);
			i++;
		}
	}
	else if(j<v1.size())//if elements are left in s1 then include them
	{
		while(j<v1.size())
		{
			v3.push_back(v1[j]);
			j++;
		}
	}

	for(int h=0;h<v3.size();h++)
	{

		temp.insert(v3[h]);//insert elements of v3 in temp
	}

	return temp; //return temp
}

template <typename T>
Set<T> intersection(Set<T> s,Set<T> s1)
{
	vector<T> v;
	inOrder(s.root,&v);//take inorder traversal of s
	vector<T> v1;
	inOrder(s1.root,&v1);//take inorder traversal of s1
	int i=0,j=0;
	vector<T> v3;
	Set<T> temp;
	while(i<v.size() && j<v1.size())
	{
			if(v[i]==v1[j])//if there is something in common between the 2 sets, then insert it into v3 
			{
				v3.push_back(v[i]);
				i++;
				j++;
			}
			//ignore those elements which are not in common
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

		temp.insert(v3[h]);//insert the elements of v3 into temp
	}

	return temp; //return temp
}

template <typename T>
Set<T> difference(Set<T> s,Set<T> s1)
{
	vector<T> v;
	inOrder(s.root,&v); //get inorder traversal of set s
	vector<T> v1;
	inOrder(s1.root,&v1);//get inorder traversal of set s1
	int i=0,j=0;
	vector<T> v3;
	Set<T> temp;
	while(i<v.size() && j<v1.size())
	{
			if(v[i]==v1[j]) //if something is in common in both the sets, then ignore that element
			{
				i++;
				j++;
			}
			else if(v[i]<v1[j])//if something is in s that is not in s1, then insert it into v3
			{
				v3.push_back(v[i]);
				i++;
			}
			else if(v[i]>v1[j])//everything that is in s1 and not in s should be ignored
			{
				j++;
			}
	}
	if(i<v.size()) //Those elements in s which left uncompared must be added to v3 as they are not in s1.
	{
		while(i<v.size())
		{
			v3.push_back(v[i]);
			i++;
		}
	}
	for(int h=0;h<v3.size();h++)//insert the elements of v3 to temp 
	{
		temp.insert(v3[h]);

	}

	return temp; //return temp

}
