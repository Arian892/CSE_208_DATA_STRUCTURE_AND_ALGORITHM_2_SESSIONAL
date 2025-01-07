#include <iostream>
#include <vector>
using namespace std;

class node
{
public:
    int key;
    int value;
    node *parent;
    node *child;
    node *left;
    node *right;
    bool mark;
    int rank;

    node(int key, int value)
    {
        this->key = key;
        this->value = value;
        mark = false;
        rank = 0;
    }
    void print()
    {
        cout << "(" << key << "," << value <<")";
    }
};

class Fibonacci_heap
{
    node *max;
    int size;
    int tree_size;
    vector <node*> value_node ; 
    

public:
    Fibonacci_heap()
    {
        max = NULL;
        size = 0;
        tree_size = 0;
        value_node.resize(100001,nullptr);
      
    }

    void insert(int key, int value)
    {
        node *temp = new node(key, value);
        temp->parent = NULL;
        temp->child = NULL;
        temp->left = temp;
        temp->right = temp;

        if (max == NULL)
        {

            max = temp;
        }
        else
        {
            temp->right = max;
            temp->left = (max->left);
            max->left->right = temp;
            max->left = temp;

            if (temp->key > max->key)
            {
                max = temp;
            }
        }
        size++;
        tree_size++;
        value_node[value] = temp ;
    }

    void addToRootList(node *&temp)
    {
        temp->parent = NULL;
        temp->left = temp;
        temp->right = temp;

        if (max == NULL)
        {

            max = temp;
        }
        else
        {
            temp->right = max;
            temp->left = (max->left);
            max->left->right = temp;
            max->left = temp;
            if (temp->key > max->key)
            {
                max = temp;
            }
        }
        tree_size++;
    }

    void extract_max()
    {
       // max->print();
      // cout << tree_size << endl ;
        if (tree_size == 0)
        {
            return;
        }
        if (tree_size == 1 && max->child == NULL)
        {
            tree_size = 0;
            delete max;
            max = NULL;
            return;
        }
        //     max->print();
        //     max->right->print();
        node *ret = max;
        //   max->print();

        if (ret != NULL)
        {
            node *root_child = ret->child;
            node *root_child_right;
            //   cout << "heelo" ;
            for (int i = 1; i <= ret->rank; i++)
            {

                if (i < ret->rank)
                {
                    root_child_right = root_child->right;
                }

                //  root_child->print();
                addToRootList(root_child);
                root_child = root_child_right;
            }
            //  ret->left->print();
            //  ret->print();
            //  ret->right->print();
            //  ret->right->right->print();
            //  ret->right->right->right->print();

            ret->left->right = ret->right;
            ret->right->left = ret->left;
            max = ret->right;
             value_node[ret->value]= nullptr ;
            delete ret ;
            ret = NULL ;
           
            //  max->print();
            //  max->right->print();
           // max->right->right->right->print();
            tree_size--;
            //  print();

            //  max->print ();

       //     cout << "treesize " << tree_size << endl;
          //  print();
            Consolidate();

            // delete ret ;
            // delete ret ;
        }
        else
        {
            // return NULL ;
        }
    }
    void swapPointers(node *&pointer1, node *&pointer2)
    {
        node *temp = pointer1;
        pointer1 = pointer2;
        pointer2 = temp;
    }

    void Consolidate()
    {
        //  max->print();
        // Adjust the size of rank_list if needed
        //  cout << tree_size << endl;
        vector<node *> rank_list;
        rank_list.resize(2 * 50, nullptr);

        vector<node *> roots;
        //  cout << tree_size << endl;
        // max->print();
        // max->right->print();

        node *current = max;
        do
        {
            roots.push_back(current);
            current = current->right;
        } while (current != max);

       /// cout << "root size : " << roots.size() << endl;

        for (node *root : roots)
        {
            int rank = root->rank;
            //   cout << rank << endl;

            while (rank_list[rank] != nullptr)
            {
                node *other = rank_list[rank];
                // cout << "rank" << rank  << endl ;

                if (root->key < other->key)
                {

                    swapPointers(root, other);
                }

                // cout << "root and child " ;
                // root->print();
                // other->print();

                // Link other as a child of root
                other->left->right = other->right;
                other->right->left = other->left;
                other->left = other->right = other;
                other->parent = root;

                // Update root's child pointers
                if (root->child == nullptr)
                {
                    root->child = other;
                }
                else
                {
                    other->right = root->child;
                    other->left = root->child->left;
                    root->child->left->right = other;
                    root->child->left = other;
                }

                rank_list[rank] = nullptr;
                root->rank++;
                rank = root->rank;
                tree_size--;
            }

            rank_list[rank] = root;
        }

        // Update max pointer
        max = nullptr;
        for (node *root : rank_list)
        {
            if (root != nullptr)
            {
                if (max == nullptr || root->key > max->key)
                {
                    max = root;
                }
            }
        }
        // max->child->right->print();
    }

    void traverse(Fibonacci_heap f)
    {
        node *root_list = f.max;
        for (int j = 1; j <= f.tree_size; j++)
        {
            value_node[root_list->value] = root_list;
             traverse_help(root_list);
            

            root_list = root_list->right;
        }
        
    }

    void traverse_help(node *&temp)
    {
        node *child = temp->child;

        for (int i = 1; i <= temp->rank; i++)
        {
            value_node[child->value] = child ;
            

            traverse_help (child);

            child = child->right ;
        }

        
    }

    void Delete(int key)
    {
      //  max->print();
       // cout << "he";
        increaseKey(key, 99999999);
      //  print();
        // max->print();

       // cout << tree_size << endl;
        // max->right->print();
        extract_max();
    }
    void fixViolation(node *temp)
    {
        //temp->print();
        if (temp->parent == NULL)
        {
            
          //  addToRootList(temp);
        }
        else  if (temp->parent->mark == true)
        {
            node * parentofnode= temp->parent ;
            

            temp->parent->mark = false;
            temp->parent->rank--;
            temp->left->right = temp->right;
            temp->right->left= temp->left;

            if (temp->parent->rank!=0 )
            temp->parent->child = temp->right ;
                       

            addToRootList(temp);
           // temp->parent->print();
            
            fixViolation(parentofnode);
             
        }
        else
        {
          //  cout << "hi" << endl;

            temp->parent->mark = true;

            temp->parent->rank--;
            
            temp->left->right = temp->right;
            temp->right->left = temp->left;
            if (temp->parent->rank != 0 )
            temp->parent->child = temp->right;

            addToRootList(temp);
            // max->print();
            // max->right->child->print();
            
            //max->child->print();
        }
    }

    void increaseKey(int old, int new_key)
    {
      //  cout << "trees size" << tree_size << endl;
        //  max->right->parent->print();

        //  cout << old << new_key << endl;
        // max->left->print();
        //cout << old << new_key << endl;

      node *temp = value_node[old];
     // cout << temp->parent->mark << endl;
       // temp->print ();
        if (temp == nullptr)
        {
            cout << "not found" ;
            return ;

        }
        // temp->print();

        // cout << old << endl;
        temp->key = new_key;

        if (temp->parent == NULL)
        {
           // cout << "nullptr";
            if (temp->key > max->key)
             max = temp ;
        }
       // temp->print();
        // cout << temp->parent->key << endl;
        //  temp->print();
        //  cout << "hello" ;
        if (temp->parent != NULL && new_key > temp->parent->key)
        {
          //  cout << "hello";
            fixViolation(temp);
        }
       
        // cout << "hey" ;
        // print();
        // max->print();
        // cout << tree_size << endl;
        // max->right->print();
        // max->right->right->print();
        // max->right->right->right->print();
        // max->right->right->right->right->print();

        //   node * temp =   find (12);
        //   temp->print();
    }

    pair <int,int> findmax()
    {
        return {max->key,max->value};
    }

    void printlist(node *&temp)
    {
        node *root_child = temp->child;
        if (temp->parent != NULL)
            cout << "\t";

        temp->print();

        if (temp->rank != 0)
            cout << "->";
        for (int i = 1; i <= temp->rank; i++)
        {

            root_child->print();
            if (i != temp->rank)
                cout << ",";
            root_child = root_child->right;
        }
        cout << endl;
    }

    void recursiveprint(node *temp)
    {

        if (temp->rank >= 1)
        {

            printlist(temp);
            node *root_child = temp->child;
            for (int i = 1; i <= temp->rank; i++)
            {
                recursiveprint(root_child);
                root_child = root_child->right;
            }
        }
        else if (temp->rank == 0 && temp->parent == NULL)
        {
            printlist(temp);
        }
    }

    
    void print()
    {
       // max->right->print();
        if (tree_size == 0)
         cout << "tree is empty" << endl;
        //  cout << "max :" ;
        // max->print();
        // max->right->print();
        //  cout << endl;
        //  max->print();
        //  max->right->print();
        node *root_list = max;
        // cout << tree_size << endl;

        for (int j = 1; j <= tree_size; j++)
        {
            cout << "tree " << j << " :";

            //  printlist(root_list);

            recursiveprint(root_list);

            //  if (j <= tree_size)
            root_list = root_list->right;

            //  root_list->print();
        }

        //  max->print();

        //   cout << tree_size << endl;
    }

    bool isEmpty  ()
    {
        if (tree_size >= 1)
        return false;
        return true;
    }


    Fibonacci_heap meld (Fibonacci_heap &f_h )
    {
      //  cout << f_h.tree_size << endl;
        
       // f_h.print();
        traverse (f_h);

        if (tree_size == 0) return f_h ;
        if (f_h.tree_size == 0) return *this ;
        node* max_right = max->right;
        node* f_h_right = f_h.max->right;


        max->right = f_h_right ;
        f_h_right->left = max ;

        f_h.max->right= max_right ;
        max_right->left = f_h.max ;


        if (max->key < f_h.max->key)
        max = f_h.max; 

        tree_size = tree_size + f_h.tree_size ;

       //f_h.print();


        return *this ;





    }

};

// int main()
// {
//     Fibonacci_heap f;
//     Fibonacci_heap f2 ;
//     int num = 10;

//     // for (int i = 0 ; i <= num ; i++)
//     // {
//     //     f.insert(i,i);
//     //   //  f.print ();

//     // }
//     // f.print();
//     // // f.extract_max();
//     // // f.print();

//     // // for (int i = 0 ; i < num ; i++)
//     // // {
//     // //     f.increaseKey (i,10000);
//     // //     f.extract_max();
//     // //     f.print();
//     // // }
//     // // f.extract_max();
//     // // f.print();
//     // // f.extract_max();
//     // // f.print();
//     // for (int i = 11 ; i<= 20   ; i++)
//     // {
//     //     f2.insert(i,i);
//     //   //  f.print ();

//     // }
//     // f2.print();
//     // // f2.extract_max();
//     // // f2.print();

//     //  f=f.meld(f2);
//     // f.print();
//     // f.extract_max();
//     // f.print();
//     // // f.extract_max();
    
//     //  f.increaseKey(1,1000);
//     //   f.print();

     


    
//     // for (int i = 0 ; i < num ; i++)
//     // {
//     //    // f.insert(i,i);
//     //   // cout << "after  increase" << i << endl;
//     //    //f.increaseKey (i,10000);
//     //    f.Delete(i) ;
//     //    f.print();
//     //    cout << "after extract" << i <<endl;

//     //    f.extract_max();
//     //    f.print();

//     // }
// //     f.extract_max();
// //     f.print();
// //    // f.print();
//     // f.insert(12, 1);
//     // f.insert(23, 34);
//     // f.insert(200, 2);
//     // f.insert(500, 23);
//     // f.insert(122, 12);
//     // f.insert(233, 3);
//     // f.insert(230, 5);
//     // f.insert(540, 4);
//     // f.print();
//     // f.extract_max();
//     // f.print();
//     // f.increaseKey (3,544);
//     // f.print();
//     // f.extract_max();
//     // f.print();
//    // f.finding (56);


//     //     f.increaseKey(23,600);
//     //     f.print();
//     //     cout << endl;
//     //       f.extract_max();
//     //       f.print();
//     //       f.extract_max();
//     //       f.print();
//     //    ///   f.Delete(200);
//     //       f.print();
//     //    f.Delete(233);
//     //     f.print();
//     //     f.Delete (122) ;
//     //     f.print();
// }
