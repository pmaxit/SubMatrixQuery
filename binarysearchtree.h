#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <QObject>
#include <iostream>
#include <QPoint>

template<class T>
struct Node{
    T value;
    T minval;
    Node *left;
    Node *right;

    Node(T val){
        this->value = val;
        this->minval = val;
        this->left = NULL;
        this->right = NULL;
    }

    Node(T val, Node<T> *left, Node<T> *right){
        this->value = val;
        this->left = left;
        this->right = right;
    }
};

template<class T>
class BinarySearchTree : public QObject
{

public:
    explicit BinarySearchTree(QObject *parent = 0):QObject(parent){
        root = NULL;
    }

    template<class comp>
    void add(T val, comp com){
        std::cout<<"adding node"<<std::endl;
        if(root)
            this->addHelper(root ,val,com);
        else{
            std::cout<<"creating node "<<std::endl;
            root = new Node<T>(val);
        }
    }

    void print(){
        printHelper(this->root);
    }

private:
    Node<T> *root;

    template<class comp>
    T& addHelper(Node<T> *root, T val, comp com){
        if(com(root->value, val)){
            if(!root->left){
                root->left = new Node<T>(val);
                return root->left->minval;
            }
            else{
                T minval = addHelper(root->left, val, com);
                if(minval.x() < root->minval.x())
                    root->minval = minval;
            }
        }else{
            if(!root->right){
                root->right = new Node<T>(val);
                std::cout<<"inserting to right "<<val<<std::endl;
                return root->right->minval;
            }else{
                T minval = addHelper(root->right, val, com);
                if (minval.x() < root->minval.x())
                    root->minval = minval;
            }
        }
    }

    void printHelper(Node<T>* root){
        if(!root) return;
        printHelper(root->left);
        std::cout<<root->value<<" ---- MIN:  "<<root->minval<<"  "<<std::endl;
        printHelper(root->right);
    }
};

#endif // BINARYSEARCHTREE_H
