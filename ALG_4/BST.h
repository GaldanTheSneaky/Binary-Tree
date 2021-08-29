#pragma once

#include <iostream>
#include <string>
#include <memory> 

template <typename T>
class BSTree
{
public:
    BSTree() : root(nullptr) {}

    void Print() const;
    void Insert(T val);
    bool Contains(T val) const;
    void Remove(T val);
    int FindPath(T val) const;
    void preorderTraversal() const;
    void inorderTraversal() const;
    void postorderTraversal() const;

private:

    struct TreeNode
    {
        T data;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;

        TreeNode(T data) : data(data), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<TreeNode> root;
    void PrintTree(const std::unique_ptr<TreeNode>& node, int margin = 0) const;  
    void Insert(T val, std::unique_ptr<TreeNode>& node); 
    bool Contains(T val, std::unique_ptr<TreeNode>const& node) const;  
    int FindPath(T val, std::unique_ptr<TreeNode>const& node, int counter = 0) const;  
    void Remove(T val, std::unique_ptr<TreeNode>& node);  
    void preorderTraversal(std::unique_ptr<TreeNode>const& node) const;
    void inorderTraversal(std::unique_ptr<TreeNode>const& node) const;
    void postorderTraversal(std::unique_ptr<TreeNode>const& node) const;
    std::unique_ptr<TreeNode>& FindMin(std::unique_ptr<TreeNode>& node); 
};

template <typename T>
void BSTree<T>::Print() const
{
    PrintTree(this->root);
}


template <typename T>
void BSTree<T>::PrintTree(const std::unique_ptr<TreeNode>& node, int margin) const
{

    if (node != nullptr)
    {
        PrintTree(node->right, margin + 1);
        for (int i = 0; i < margin; i++) std::cout << " ";
        std::cout << node->data << std::endl;
        PrintTree(node->left, margin + 1);
    }

}

template <typename T>
void BSTree<T>::Insert(T val) 
{
    this->Insert(val, this->root);
}

template <typename T>
void BSTree<T>::Insert(T val, std::unique_ptr<TreeNode>& node) 
{

    if (node == nullptr)
    {
        node = std::make_unique<TreeNode>(val);
    }
    else
    {
        if (val < node->data)
        {
            this->Insert(val, node->left);
        }
        else if (val > node->data)
        {
            this->Insert(val, node->right);
        }
        else
        {
            std::cout << "Warning: Value already exists, so nothing will be done." << std::endl;
        }
    }
}

template <typename T>
bool BSTree<T>::Contains(T val) const 
{
    return Contains(val, this->root);
}

template <typename T>
bool BSTree<T>::Contains(T val, std::unique_ptr<TreeNode>const& node) const 
{
    if (node == nullptr)
    {
        return false;
    }
    else if (val == node->data)
    {
        return true;
    }
    else if (val < node->data) 
    {
        return this->Contains(val, node->left);
    }
    else
    {
        return this -> Contains(val, node->right);
    }
}

template <typename T>
int BSTree<T>::FindPath(T val) const 
{
    return FindPath(val, this->root);
}

template <typename T>
int BSTree<T>::FindPath(T val, std::unique_ptr<TreeNode>const& node, int counter) const
{
    if (node == nullptr)
    {
        return -1;
    }
    else if (val == node->data)
    {
        return counter;
    }
    else if (val < node->data) 
    {
        counter++;
        std::cout << node->data << " ";
        return this->FindPath(val, node->left, counter);
    }
    else 
    {
        counter++;
        std::cout << node->data << " ";
        return this -> FindPath(val, node->right, counter);
    }
}

template <typename T>
void BSTree<T>::Remove(T val)
{
    this->Remove(val, this->root);
}

template <typename T>
void BSTree<T>::Remove(T val, std::unique_ptr<TreeNode>& node)
{
    if (node == nullptr)
    {
        std::cout << "val not found in tree" << std::endl;
    }
    else if (val == node->data)
    {
        if (node->left == nullptr && node->right == nullptr) 
        {
            node = nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr)
        {
            node = std::move(node->left);

        }
        else if (node->left == nullptr && node->right != nullptr)
        {
            node = std::move(node->right);
        }
        else
        {
            std::unique_ptr<TreeNode>& minNode = this->FindMin(node->right); 
            node->data = minNode->data;
            this->Remove(minNode->data, minNode);
        }

    }
    else if (val < node->data)
    {
        this->Remove(val, node->left);
    }
    else 
    {
        this->Remove(val, node->right);
    }
}


template <typename T>
std::unique_ptr<typename BSTree<T>::TreeNode>& BSTree<T>::FindMin(std::unique_ptr<TreeNode>& node)
{
    if (node == nullptr) 
    {
        throw "Min value not found";
    }
    else if (node->left == nullptr)
    {
        return node;
    }
    else
    {
        return this->FindMin(node->left);
    }
}

template <typename T>
void BSTree<T>::postorderTraversal() const
{
     this->postorderTraversal(this->root);
}

template <typename T>
void BSTree<T>::postorderTraversal(std::unique_ptr<TreeNode>const& node) const
{
    if (node == nullptr)
        return;
  
        this->postorderTraversal(node->left);
   
        this->postorderTraversal(node->right);
    
        std::cout << node->data << " ";
}

template <typename T>
void BSTree<T>::inorderTraversal() const
{
    this->inorderTraversal(this->root);
}

template <typename T>
void BSTree<T>::inorderTraversal(std::unique_ptr<TreeNode>const& node) const
{
    if (node == nullptr)
        return;

    this->inorderTraversal(node->left);

    std::cout << node->data << " ";

    this->inorderTraversal(node->right);

}

template <typename T>
void BSTree<T>::preorderTraversal() const
{
    this->preorderTraversal(this->root);
}

template <typename T>
void BSTree<T>::preorderTraversal(std::unique_ptr<TreeNode>const& node) const
{
    if (node == nullptr)
        return;

    std::cout << node->data << " ";

    this->preorderTraversal(node->left);

    this->preorderTraversal(node->right);

}