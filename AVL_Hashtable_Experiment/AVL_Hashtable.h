#pragma once
#ifndef AVL_HASH_H
#define AVL_HASH_H
#include <iostream>
template<typename Type>
struct NODE
{
	Type Key;
	NODE * left;
	NODE * right;
	NODE * Parent;
	int height;

	NODE(Type K)
	{
		Key = K;
		left = nullptr;
		right = nullptr;
		Parent = nullptr;  //will implement if time allows
	}
};
template<typename Type>
class BST
{
public:
	void max()
	{
		int max(int a, int b);
	}
	BST()
	{
		root == nullptr;
	}

	//public call for inorder private method
	void inorder()
	{

		inorder(root);

	}
	//public call for private Delete Method
	void Delete_Node(Type K)
	{
		Delete_Node(K, root);
	}
	//public call for private insert.  This creates the first NODE int the tree and establishes root.
	NODE<Type> * insert(Type K)
	{
		//first insertion operation, setting root value on first insertion call
		if (root == nullptr)
		{
			//declaring a new node for root with k value for the key
			root = new NODE<Type>(K);
			root->height = 0;
			std::cout << "root created!" << std::endl;
			std::cout << "Root Value: " << root->Key << std::endl;
			std::cout << "Tree Height: " << root->height << std::endl;
			return root;
		}
		else
		{
			//testing the fundamental structure of the binary search tree
			std::cout << "Root: " << root->Key << std::endl;
			if (root->left != nullptr)
			{
				//displays left child value to show successful creation of left child for the root node
				std::cout << "Left Child: " << root->left->Key << std::endl;
				//displays the parent Node Value to show successful parent creation
				std::cout << "Left Parent: " << root->left->Parent->Key << std::endl;
			}
			if (root->right != nullptr)
			{
				//displays right child value to show successful creation of right child for the root node
				std::cout << "Right Child: " << root->right->Key << std::endl;
				//displays the parent Node Value to show successful parent creation
				std::cout << "Right Parent: " << root->right->Parent->Key << std::endl;
			}
			//recursive call function takes user input k value and root from BST class returns a pointer
			return insert(K, root);
		}


	}
	//recursive call to Maximum private function.  Instert root as node.  Allows user public access to private method.
	NODE<Type>* Maximum()
	{
		//store the Node as a temp variable.
		NODE<Type> * Value = Maximum(root);
		std::cout << "Maximum Value: " << Value->Key << std::endl;
		return Value;
	}


	~BST()
	{
		Delete_Tree(root);
	}

private:



	NODE<Type>* root = nullptr;
	//private Methods used for recursion
	NODE<Type> * insert(Type K, NODE<Type>* node)
	{
		if (node == nullptr)
		{
			node = new NODE<Type>(K);
			node->height = 1;
			std::cout << "Node Successfully inserted: " << node->Key << std::endl;
			return node;

		}
		else if (K < node->Key)
		{
			//all functions must be performed in order
			//create a temporary variable left_child to assign the value of node to maintain pointer integrity
			NODE<Type>* left_child = insert(K, node->left);
			//set the value of node-> left to the value of the temporary variable left_child
			node->left = left_child;
			//set the left child to the value of node connecting the parent
			left_child->Parent = node;
			//this is a test function that informs the user of a successful connection of the Parent value
			if (node->Parent != nullptr)
			{
				std::cout << "Parent: " << node->Parent->Key << std::endl;
			}
			//return the node value after all functions are complete
			return node;
		}
		else if (K > node->Key)
		{
			//all functions must be performed in order
			//create a temporary variable right_child to assign the value of node to maintain pointer integrity
			NODE<Type>* right_child = insert(K, node->right);
			//set the value of node->right to the value of the temporary variable right_child
			node->right = right_child;
			//set the right child to the value of node connecting the parent
			right_child->Parent = node;
			//this is a test function that informs the user of a successful connection of the Parent value
			if (node->Parent != nullptr)
			{
				std::cout << "Parent: " << node->Parent->Key << std::endl;
			}
			//return the node value after all functions are complete
			return node;
		}

	}
	int max(int a, int b)
	{
		return (a > b) ? a : b;
	}
	NODE<Type>* Minimum(NODE<Type>*node)
	{
		//move left to locate the minimum value of the tree
		if (node->left == nullptr)
		{
			return node;
		}
		if (node == nullptr)
		{
			return nullptr;
		}
		return Minimum(node->left);

	}
	NODE<Type> * Maximum(NODE<Type>* node)
	{
		//move right to locate the minimum value of the tree
		if (node->right == nullptr)
		{
			return node;
		}
		if (node == nullptr)
		{
			return nullptr;
		}
		return Maximum(node->right);
	}

	void Delete_Node(Type K, NODE<Type>* node)
	{

		if (K < node->Key)
		{
			Delete_Node(K, node->left);
		}
		else if (K > node->Key)
		{
			Delete_Node(K, node->right);
		}
		else
		{
			//if the root Node is the only node in the list
			if (node == root && node->left == nullptr && node->right == nullptr)
			{

				//this is an error handling function
				//when deleting the final node, the program crashes. 
				//Instead, the program will now exit and inform the user of the exit.
				root = nullptr;
				delete node;
				system("cls");
				std::cout << "\n\nAll Nodes in the tree have been deleted.  The program will now exit.\n\n" << std::endl;
				system("pause");
				exit(0);
			}
			//Two Children
			if (node->left != nullptr && node->right != nullptr)
			{
				//create a successor Node that stores the minimum value of the tree as a copy
				NODE<Type>*successor = Minimum(node->right);
				//this function tests whether the node has a remaining left or right node tree and assigns a nullptr value to the previous nodes children that the node is being deleted from
				successor->Key > successor->Parent->Key ? successor->Parent->right = nullptr : successor->Parent->left = nullptr;
				//this function reassigns the key value of the minimum node to the node being replaced
				//this maintains the integrity of the tree and prevents the need to reassign pointer values of the node
				node->Key = successor->Key;
				//finally, we delete the successor node that is storing the minimum value
				delete successor;
			}
			//Node with one child
			//condition one performs a double check to verify that there is a nullptr for right and the the left is not a null value
			else if (node->right == nullptr && node->left != nullptr)
			{
				//These next two operations can be performed in any order
				//This line assigns the child of the node to be deleted to the nodes parent
				node->left->Parent = node->Parent;
				//this line assigns the nodes parent as the left child
				node->Parent->left = node->left;
				//delete the node after all ptr values are reassigned
				delete node;
			}
			//condition one performs a double check to verify that there is a nullptr for left and the the right is not a null value
			else if (node->left == nullptr && node->right != nullptr)
			{
				//These next two operations can be performed in any order
				//this line assigns the nodes parent as the right child
				node->Parent->right = node->right;
				//This line assigns the child of the node to be deleted to the nodes parent
				node->right->Parent = node->Parent;
				//delete the node after all ptr values are reassigned
				delete node;
			}
			//no children
			else if (node->left == nullptr && node->right == nullptr)
			{
				//these functions must be performed in this order
				//this function tests whether the node has a remaining left or right node tree and assigns a nullptr value to the parents children
				node->Key > node->Parent->Key ? node->Parent->right = nullptr : node->Parent->left = nullptr;
				//after the nodes parents children have been assigned their nullptr values, assign a nullptr value to the nodes parent
				node->Parent = nullptr;
				//the node is ready for deletion
				delete node;
			}
		}
		//if value does not exist, return.
		return;

	}
	void Delete_Tree(NODE<Type>* node)
	{
		if (node != nullptr)
		{
			Delete_Tree(node->left);
			Delete_Tree(node->right);
			delete node;
		}
		node = nullptr;
	}
	void inorder(NODE<Type>*node)
	{
		if (node != nullptr)
		{
			inorder(node->left);
			std::cout << node->Key << std::endl;
			if (node->Parent != nullptr)
			{
				std::cout << "Parent: " << node->Parent->Key << std::endl;
			}

			inorder(node->right);
		}

	}


};
#endif


