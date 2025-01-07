#include <string>
#include <iostream >
#include "colour.hpp"

using namespace std;

#define black 'b'
#define red 'r'

class Treenode
{
public:
    int key;
    Treenode *left;
    Treenode *right;
    Treenode *parent;
    string value;
    char color;

    void print()
    {
        if (color == red)
        {
            cout << dye ::aqua_on_red(key) << dye::aqua_on_red("_") << dye ::aqua_on_red(value);
        }
        else
            cout << key << "_" << value;
    }
};

class Red_black_tree
{
    Treenode *root;

public:
    int size;

    Red_black_tree()
    {
        root = NULL;
        size = 0;
    }

    void print()
    {

        if (root == NULL)
        {
            cout << endl;
            return;
        }
        root->print();
        print(root);
        cout << endl;
    }

    void print(Treenode *&nd)
    {

        if (nd->left != NULL && nd->right != NULL)
        {
            cout << "(";
            nd->left->print();
            print(nd->left);
            cout << ",";
            nd->right->print();
            print(nd->right);
            cout << ")";
        }
        else if (nd->left != NULL && nd->right == NULL)
        {
            cout << "(";
            nd->left->print();
            print(nd->left);
            cout << ",)";
        }
        else if (nd->left == NULL && nd->right != NULL)
        {
            cout << "(,";
            nd->right->print();
            print(nd->right);
            cout << ")";
        }
    }

    void insert(pair<int, string> val)
    {
        size++;
        if (root == NULL)
        {
            root = new Treenode;
            root->left = NULL;
            root->right = NULL;
            root->key = val.first;
            root->value = val.second;
            root->parent = NULL;
            root->color = black;
        }
        else
        {
            inserthelp(root, val);
        }
        // inserthelp(root, val);
    }

    void inserthelp(Treenode *&nd, pair<int, string> val)
    {
        if (nd->key > val.first)
        {
            if (nd->left == NULL)
            {
                Treenode *temp = new Treenode;
                temp->left = NULL;
                temp->right = NULL;
                temp->color = red;
                temp->key = val.first;
                temp->value = val.second;
                nd->left = temp;
                temp->parent = nd;

                // print();
                // cout << nd->left->parent->key << endl;

                ReColouring(nd->left);
                // cout << "done";
            }
            else
            {
                inserthelp(nd->left, val);
            }
        }
        else if (nd->key < val.first)
        {
            if (nd->right == NULL)
            {
                Treenode *temp = new Treenode;
                temp->left = NULL;
                temp->right = NULL;
                temp->color = red;
                temp->key = val.first;
                temp->value = val.second;
                nd->right = temp;
                temp->parent = nd;

                ReColouring(nd->right);
            }
            else
            {
                inserthelp(nd->right, val);
            }
        }
    }

    void ReColouring(Treenode *&nd)
    {
        if (isRoot(nd))
        {
            nd->color = black;
           
            return;
        }
        else
        {
            if (nd->parent->color == black)
            {
                //  cout << "parent black " << nd->key << endl;
                // cout << nd->color << endl;
                return;
            }
            else
            {

                Treenode *uncle = Uncle(nd);
                if (uncle != NULL && uncle->color == red)
                {
                    // cout << "ekhane ashche ??" << endl;

                    nd->parent->color = black;
                    uncle->color = black;
                    nd->parent->parent->color = red;
                    ReColouring(nd->parent->parent);
                }
                else
                {

                    string config = whichConfig(nd);
                    // cout << "hey";
                    //  print ();

                    // cout << config << endl;
                    // cout << "hey";
                    if (config == "left_left")
                    {
                        // cout << "ekhance ashche" ;
                        // cout << nd->parent->key << endl;
                        //  print ();

                        right_rotation(nd->parent);

                        nd->parent->color = black;
                        nd->parent->right->color = red;
                        // print ();
                    }
                    else if (config == "left_right")
                    {
                        Treenode *temp = nd->parent;
                        //  cout << "temp key 1 "<<temp->key << endl;

                        left_rotation(nd);
                        //  cout<< "temp key 2 " << temp->key << " " << temp->parent->key << endl;
                        right_rotation(temp->parent);

                        //   cout << "temp key 3 " << temp->key << " " << temp->parent->key << " " << temp->parent->right->parent->key<< endl;
                        //   cout << "temp uncle" << temp->parent->parent->key << endl;
                        temp->parent->color = black;
                        temp->parent->right->color = red;
                        // print();
                    }
                    else if (config == "right_left")
                    {
                        Treenode *temp = nd->parent;
                        //    cout << " right left er output " << nd->key << endl;
                        right_rotation(nd);
                        left_rotation(temp->parent);
                        temp->parent->color = black;
                        temp->parent->left->color = red;
                    }
                    if (config == "right_right")
                    {

                        left_rotation(nd->parent);
                        // print();
                        nd->parent->color = black;
                        nd->parent->left->color = red;
                    }
                }
            }
        }
    }

    // which configuration

    string whichConfig(Treenode *&nd)
    {

        Treenode *parent = nd->parent;
        Treenode *grand_parent = parent->parent;
        if (grand_parent->left == parent)
        {
            if (parent->left == nd)
            {
                return "left_left";
            }
            else
            {
                return "left_right";
            }
        }
        else
        {
            if (parent->left == nd)
            {
                return "right_left";
            }
            else
            {
                return "right_right";
            }
        }
    }

    // rotation functions

    void left_rotation(Treenode *&nd)
    {
        Treenode *node = nd;
        Treenode *temp = nd->left;
        Treenode *nd_parent = nd->parent;
        Treenode *nd_grandparent = nd_parent->parent;

        nd_parent->right = temp;
        if (temp != NULL)
        {

            temp->parent = nd_parent;
        }

        node->left = nd_parent;
        nd_parent->parent = node;

        if (nd_grandparent == NULL)
        {
            // cout << "root setting";
            node->parent = NULL;
            root = node;
            // cout << "heelo";
        }

        else if (nd_grandparent != NULL && nd_grandparent->left == nd_parent)
        {
            nd_grandparent->left = node;
            node->parent = nd_grandparent;
        }

        else if (nd_grandparent != NULL && nd_grandparent->right == nd_parent)
        {
            nd_grandparent->right = node;
            node->parent = nd_grandparent;
        }
    }

    void right_rotation(Treenode *&nd)
    {

        Treenode *node = nd;
        Treenode *temp = nd->right;
        Treenode *nd_parent = nd->parent;
        Treenode *nd_grandparent = nd_parent->parent;

        nd_parent->left = temp;
        if (temp != NULL)
        {

            temp->parent = nd_parent;
        }

        node->right = nd_parent;
        nd_parent->parent = node;

        if (nd_grandparent == NULL)
        {
            node->parent = NULL;
            root = node;
        }

        if (nd_grandparent != NULL && nd_grandparent->left == nd_parent)
        {
            nd_grandparent->left = node;
            node->parent = nd_grandparent;
        }

        else if (nd_grandparent != NULL && nd_grandparent->right == nd_parent)
        {
            nd_grandparent->right = node;
            node->parent = nd_grandparent;
        }
    }

    // finding sibling
    Treenode *sibling(Treenode *&node)
    {
        Treenode *parent = node->parent;
        if (parent == NULL)
            return NULL;
        else
        {

            if (parent->left == node)
                return parent->right;
            else
            {
                return parent->left;
            }
        }
    }

    // finding uncle
    Treenode *Uncle(Treenode *&node)
    {
        Treenode *parent = node->parent;
        if (parent == NULL)
            return NULL;
        else
        {
            Treenode *grandparent = parent->parent;
            if (grandparent->left == parent)
                return grandparent->right;
            else
            {
                return grandparent->left;
            }
        }
    }

    // checking is the node or not
    bool isRoot(Treenode *nd)
    {
        if (nd->parent == nullptr)
            return true;
        return false;
    }

    bool find(int val)
    {
        return findhelp(root, val) != NULL;
    }

    Treenode *findhelp(Treenode *&nd, int val)
    {
        if (nd == NULL)
            return NULL;
        if (nd->key == val)
        {
            return nd;
        }
        if (nd->key > val)
            return findhelp(nd->left, val);

        else if (nd->key < val)
            return findhelp(nd->right, val);
    }

    Treenode *getmin(Treenode *&nd)
    {
        if (nd->left == NULL)
            return nd;

        return getmin(nd->left);
    }

    // fixing errors and all
    void fixing_error(Treenode *&nd)
    {
        Treenode *Sibling = sibling(nd);

        string Sibling_config = siblingConfig(Sibling);
        // cout << "Sibling config" << Sibling_config << endl;

        if (Sibling_config == "at_least_one_red")
        {
            if (Sibling->left != NULL)
            {
                string rotation_config = whichConfig(Sibling->left);
                //  cout << "which config" << rotation_config << endl;

                // cout << "right child " << Sibling->right->key << endl;

                if (rotation_config == "left_left")
                {

                    right_rotation(Sibling);

                    if (isRoot(Sibling))
                    {
                        Sibling->color = black;
                        Sibling->left->color = black;
                        Sibling->right->color = black;
                    }
                    else
                    {
                        Sibling->color = red;
                        Sibling->left->color = black;
                        Sibling->right->color = black;
                    }

                    //  cout << Sibling->key << " " << Sibling->left->key << " " << Sibling->right->key << endl;
                    delete nd;
                    nd = NULL;

                    return;
                }

                else if (rotation_config == "right_left" && Sibling->right == NULL)
                {
                    //   cout << "right left e ki asche" << endl;
                    Treenode *temp = Sibling;
                    right_rotation(Sibling->left);
                    left_rotation(temp->parent);

                    if (isRoot(temp->parent))
                    {

                        temp->parent->color = black;
                        temp->parent->left->color = black;
                        temp->parent->right->color = black;
                    }
                    else
                    {

                        temp->parent->color = red;
                        temp->parent->left->color = black;
                        temp->parent->right->color = black;
                    }
                    delete nd;
                    nd = NULL;

                    return;
                }
            }

            if (Sibling->right != NULL)
            {
                string rotation_config = whichConfig(Sibling->right);
                // cout << "which config" << rotation_config << endl;
                // cout << "right child " << Sibling->right->key << endl;

                if (rotation_config == "right_right")
                {
                    left_rotation(Sibling);
                    //   cout << Sibling->key << Sibling->left->key << Sibling->right->key << endl;

                    if (isRoot(Sibling))
                    {
                        Sibling->color = black;
                        Sibling->left->color = black;
                        Sibling->right->color = black;
                    }
                    else
                    {
                        Sibling->color = red;
                        Sibling->left->color = black;
                        Sibling->right->color = black;
                    }

                    delete nd;
                    nd = NULL;
                    return;
                }

                else if (rotation_config == "left_right" && Sibling->left == NULL)
                {
                    Treenode *temp = Sibling;
                    left_rotation(Sibling->right);
                    right_rotation(temp->parent);

                    if (isRoot(temp->parent))
                    {

                        temp->parent->color = black;
                        temp->parent->left->color = black;
                        temp->parent->right->color = black;
                    }
                    else
                    {

                        temp->parent->color = red;
                        temp->parent->left->color = black;
                        temp->parent->right->color = black;
                    }
                    //   cout << "temp key " << temp->parent->key << endl;
                    delete nd;
                    nd = NULL;
                    return;
                }
            }
        }
        else if (Sibling_config == "both_black")
        {
            Sibling->color = red;
            Sibling->parent->color = black;
            // cout << Sibling->key << Sibling->parent->key << endl;
            //  right_rotation (Sibling->parent);
            delete nd;
            nd = NULL;

            // if (!isRoot (nd->parent))
            // {
            //     fixing_error (nd->parent);
            // }

            //  return;
        }
        else if (Sibling_config == "sibling_red")
        {
            if (whichSideSibling(Sibling) == "left")
            {
                Sibling->right->color = red;
                right_rotation(Sibling);

                if (isRoot(Sibling))
                {
                    Sibling->color = black;
                }
                else
                {
                    Sibling->color = red;
                }
                delete nd;
                nd = NULL;
                return;
            }
            else
            {
                Sibling->left->color = red;
                left_rotation(Sibling);

                if (isRoot(Sibling))
                {
                    Sibling->color = black;
                }
                else
                {
                    Sibling->color = red;
                }
                delete nd;
                nd = NULL;
                return;
            }
        }
    }

    // sibling config

    string siblingConfig(Treenode *&nd)
    {
        if (nd->color == black)
        {

            if (nd->left == NULL && nd->right == NULL)
            {
                return "both_black";
            }
            else if (nd->left != NULL && nd->right != NULL)
            {
                if (nd->left->color == red || nd->right->color == red)
                {
                    return "at_least_one_red";
                }
                else
                {
                    return "both_black";
                }
            }
            else if (nd->left != NULL)
            {
                if (nd->left->color == red)
                    return "at_least_one_red";
                else
                    return "both_black";
            }
            else if (nd->right != NULL)
            {
                if (nd->right->color == red)
                    return "at_least_one_red";
                else
                    return "both_black";
            }
            else
            {
                return "";
            }
        }
        else
        {
            return "sibling_red";
        }
    }

    /// sibling in which child

    string whichSideSibling(Treenode *&nd)
    {
        Treenode *parent = nd->parent;
        if (parent->left == nd)
            return "left";
        return "right";
    }

    // inordre

    void inorder()
    {
        inorder(root);
    }

    void inorder(Treenode *&nd)
    {
        if (nd == NULL)
            return;
        inorder(nd->left);

        if (nd->color == red)
            cout << dye ::aqua_on_red(nd->key) << " => " << dye ::aqua_on_red(nd->value) << endl;
        else
            cout << nd->key 
                 << " => " << nd->value << endl;
        inorder(nd->right);
    }
    void setValue(pair<int, string> temp)
    {
        Treenode *nd = findhelp(root, temp.first);
        nd->value = temp.second;
    }

    void clear()
    {
        int s = size;
        while (root != NULL)
        {

            Delete(root->key);
        }
        // cout << root->key << endl;
        // Delete (root->key);
        // cout << root->key << endl;
        // print();
        // Delete (root->key);
        size = 0;
        // {
        //     Delete (root->key);
        // }
        // Delete (root->key);
    }

    void Delete(int val)
    {
        size--;
        Delete(root, val);
    }

    void Delete(Treenode *&nd, int val)
    {
        if (nd == NULL)
            return;

        if (nd->key == val)
        {
            if (nd->left != NULL && nd->right == NULL)
            {
                Treenode *temp = nd;

                if (temp->left->color == red)
                {
                    nd = nd->left;
                    nd->parent = temp->parent;
                    nd->color = black;
                    delete temp;
                    temp = NULL;
                }

                else
                {
                    // cout << "color not red " << endl;
                }
            }
            else if (nd->left == NULL && nd->right != NULL)
            {
                Treenode *temp = nd;

                if (temp->right->color == red)
                {
                    nd = nd->right;
                    nd->parent = temp->parent;
                    nd->color = black;
                    delete temp;
                    temp = NULL;
                }
                else
                {
                    // cout << "colornot red" << endl;
                }
            }
            else if (nd->left == NULL && nd->right == NULL)
            {
                if (nd->color == red)
                {
                    delete nd;
                    nd = NULL;
                }
                else if (isRoot(nd))
                {
                    root = NULL;
                }
                else
                {
                    fixing_error(nd);
                    // shob kahini
                }
            }
            else if (nd->left != NULL && nd->right != NULL)
            {
                Treenode *temp = getmin(nd->right);
                nd->key = temp->key;
                nd->value = temp->value;
                Delete(nd->right, temp->key);
            }
        }
        else if (nd->key > val)
        {
            Delete(nd->left, val);
        }
        else if (nd->key < val)
        {
            Delete(nd->right, val);
        }
    }
};

