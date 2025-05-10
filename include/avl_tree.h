#pragma once
#include <utility>

using std::size_t;

template<typename T>
class Node
{
	std::pair<size_t, T> data;
	Node<T>* left;
	Node<T>* right;
	Node<T>* prev;
	size_t _height;
	Node(size_t key = 1, const T& dat = T(), Node<T>* _prev = nullptr) :
		data(std::make_pair(key, dat)), left(nullptr), right(nullptr), prev(_prev), _height(1) {}
	~Node()
	{
		left = nullptr;
		right = nullptr;
		prev = nullptr;
		_height = 0;
	}
	template <typename T>
	friend class AvlTree;
};

template<typename T>
class AvlTree
{
	Node<T>* root;
	Node<T>* find_node(size_t key, Node<T>* node)
	{
		if (node == nullptr) return nullptr;
		if (key < node->data.first)
			node = find_node(key, node->left);
		else if (key > node->data.first)
			node = find_node(key, node->right);
		return node;
	}
	int get_height(Node<T>* node) 
	{
		if (node == nullptr)
			return 0;
		return node->_height;
	}
	Node<T>* rotate_right(Node<T>* node) 
	{
		Node<T>* newRoot = node->left;
		node->left = newRoot->right;
		newRoot->right = node;
		node->_height = std::max(get_height(node->left), get_height(node->right)) + 1;
		newRoot->_height = std::max(get_height(newRoot->left), get_height(newRoot->right)) + 1;
		return newRoot;
	}
	Node<T>* rotate_left(Node<T>* node)
	{
		Node<T>* newRoot = node->right;
		node->right = newRoot->left;
		newRoot->left = node;
		node->_height = 1 + std::max(get_height(node->left), get_height(node->right));
		newRoot->_height = 1 + std::max(get_height(newRoot->left), get_height(newRoot->right));
		return newRoot;
	}
	Node<T>* insert_node(size_t key, T dat, Node<T>* node, Node<T>* _prev = nullptr)
	{
		if (node == nullptr)
		{
			Node<T>* newNode = new Node<T>(key, dat, _prev);
			if (_prev != nullptr)
			{
				if (key < _prev->left->data.first)
					_prev->left = newNode;
				else _prev->right = newNode;
			}
			return newNode;
		}
		if (key < node->data.first)
			node->left = insert_node(key, dat, node->left, node);
		else if (key > node->data.first) 
			node-> right = insert_node(key, dat, node->right, node);
		else return nullptr;	
		node->_height = std::max(get_height(node->left), get_height(node->right)) + 1;
		int balance = get_height(node->left) - get_height(node->right);
		if (balance > 1)
		{
			if (key > node->left->data.first)
			{
				node->left = rotate_left(node->left);
				return rotate_right(node);
			}
			else return rotate_right(node);
		}
		else if (balance < -1) 
		{
			if (key > node->right->data.first) return rotate_left(node);
			else
			{
				node->right = rotate_right(node->right);
				return rotate_left(node);
			}
		}
		return node;
	};
	Node<T>* find_max_node(Node<T>* node)
	{
		Node<T>* current = node;
		while (current->right != nullptr)
			current = current->right;
		return current;
	}
	Node<T>* erase_node(size_t key, Node<T>* node)
	{
		if (node == nullptr) return nullptr;
		if (key < node->data.first) 
		{
			node->left = erase_node(key, node->left);
		}
		else if (key > node->data.first) 
		{
			node->right = erase_node(key, node->right);
		}
		else
		{
			if (node->left == nullptr)
			{
				Node<T>* tmp_left = node->left;
				delete node;
				return tmp_left;
			}
			else if (node->right == nullptr)
			{
				Node<T>* tmp_right = node->right;
				delete node;
				return tmp_right;
			}
			else
			{
				Node<T>* newRoot = find_max_node(node->left);
				node->data = newRoot->data;
				node->left = erase_node(newRoot->data.first, node->left);
			}

			if (node == nullptr) return node;
			node->_height = std::max(get_height(node->left), get_height(node->right)) + 1;
			int balance = get_height(node->left) - get_height(node->right);
			if (balance > 1)
			{
				if (get_height(node->left->left) < get_height(node->left->right))
				{
					node->left = rotate_left(node->left);
					return rotate_right(node);
				}
				else return rotate_right(node);
			}
			else if (balance < -1)
			{
				if (get_height(node->right->left) > get_height(node->right->right))
				{
					node->right = rotate_right(node->right);
					return rotate_left(node);
				}
				else return rotate_left(node);
			}
		}
		return node;
	}
public:
	AvlTree(size_t key = 1, const T& dat = T())
	{
		root = new Node<T>(key, dat);
	}
	T* find(size_t key)
	{
		Node<T>* pNode = find_node(key, root);
		if (pNode == nullptr) return nullptr;
		return &(pNode->data.second);
	};
	bool insert(size_t key, T dat)
	{
		Node<T>* pNode = insert_node(key, dat, root);
		if (pNode == nullptr) return false;
		return true;
	}
	bool erase(size_t key)
	{
		if (erase_node(key, root) != nullptr) return true;
		return false;
	}
};