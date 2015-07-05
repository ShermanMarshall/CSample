//==============================================================================
//Program:            Assignment 5
//Description:        Program takes a user input file and reads in integers into
//					  a binary tree. User is then prompted with a menu of choices, 
//					  and may modify the tree, or exit. Iteration of menu options
//					  occurs until the user selects exit.
//Files:              [user-input]
//Functions:          DestroyTree
//					  RemoveNode
//					  FindNum 
//					  FindCount
//					  AddNum
//					  CreateTree
//					  IsEmpty 
//					  CreateNode 
//					  InsertNode 
//					  NodeCount
//					  FindNode 
//					  DeleteNode 
//					  InOrderDisplay 
//					  ReadFiles 
//==============================================================================
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstddef>
using namespace std;

struct Node {
       int num;
       Node* left;
       Node* right;
       };
       
struct Root {
       int count;
       Node* root;
       };
       
typedef Node* NewNode;
typedef Root* NewRoot;
       
//Function Prototypes       
void DestroyTree (Root*&tree);
void RemoveNode (Root*&tree);
void FindNum (Node*&tree, int count);
int FindCount (Node*&tree, int count, Node* root, Node* temp, int lastNum);
void AddNum(Root*&tree);
NewRoot CreateTree ();
bool IsEmpty (Root*&tree);
NewNode CreateNode (int num);
void InsertNode (Node*&node, Node*&root);
int NodeCount (Root*&tree);
NewNode FindNode (int num, Node*&tree);
bool DeleteNode (int num, Root*&tree);
void InOrderDisplay (Node*&tree, int count, Node* root, Node* temp, int lastNum, int output);
bool ReadFiles (Root*&tree);

int main() {
    Root* tree = CreateTree();
    char proceed;
    char letter;
       
    cout << "\tBinary tree program" << endl << "\t-------------------" << endl;
    if (tree == NULL) {
       cout << endl << "Error initialzing the binary tree, program exiting." << endl;
       cout << system("pause");
       return 0;
    }
       
    bool val = ReadFiles (tree);

    if (!val) {
       do {              
           cout << endl << endl << "\tSome of the values from the file could not "
                << "be read due to a memory error. Proceed? (Y/N): ";
           cin >> proceed;
                
           proceed = toupper(proceed);
                
           if ((proceed != 'Y') && (proceed != 'N'))
              cout << endl << "\tError with input. Re-enter selection.";
              
       } while ((proceed != 'Y') && (proceed != 'N'));
        
       if (proceed == 'N') {
          cout << endl << endl << "System exiting." << endl;

          cout << system("pause");
          return 0;
       }
    }
    
    do {
        do {
            cout << system("cls");

            cout << "\tBinary Tree Program menu: " << endl << "\t-----------------------" 
                 << endl << endl; 
            cout << "\tNumber of stored integers: " << (NodeCount(tree)) << endl
                 << "\tIntegers stored..." << endl << endl << "\t";        
                 
            if (NodeCount(tree) > 0)     
               InOrderDisplay(tree->root, (NodeCount(tree)), tree->root, tree->root, 0, 0);
            else
                cout << "\tBinary search tree is empty." << endl;
            
            cout << endl << endl << endl << "\tSelect a choice from the following options..." << endl
                 << "\t------------------------------------------" << endl;
            cout << "\tAdd an integer to the tree [A]: " << endl;
            cout << "\tDelete a value from the tree [D]: " << endl;
            cout << "\tFind a value within the tree (And display its subtree) [F]: " << endl;
            cout << "\tExit [E]: " << endl;
            cout << "\tEnter your selection: ";
            cin >> letter;
        
            letter = toupper(letter);        
        } while ((letter != 'A') && (letter != 'D') && (letter != 'F') && (letter != 'E'));
    
        switch (letter) {
               case 'A':
                    AddNum(tree);                
                    break;
               case 'D':
                    RemoveNode(tree);
                    break;
               case 'F':
                    FindNum(tree->root, (NodeCount(tree)));
                    break;
               case 'E':
                    cout << endl << "\tExiting program" << endl;
                    DestroyTree (tree);
                    break;
               default:
                       break;
        }              
    cout << system("pause");
    } while (letter != 'E');    
}

//==============================================================================
void DestroyTree (Root*&tree) {
//Description:      DestroyTree recursive deallocates all nodes in the tree.
//Parameters:       'tree'     -- The binary tree containing all integers.
//==============================================================================
     bool exit = false;
     while (((NodeCount(tree)) > 0) && (!exit)) {
           Node* node = tree->root;
           Node* ref = tree->root;
           
           if (tree->count == 1) {
              delete tree->root;
              delete tree;
              exit = true;
           }
           else {
                 do {
                     while (node->left != NULL)
                           node = node->left;
                             
                     if (node->right != NULL)
                        node = node->right;
                          
                     while ((ref->left != NULL) && (ref->left != node))
                           ref = ref->left;
                             
                     while (node->right != NULL)
                           node = node->right;
                             
                     if (node->left != NULL)
                        node = node->left;
                          
                     while ((ref->right != NULL) && (ref->right != node)) 
                           ref = ref->right;                             
                     
                 } while ((node->left != NULL) || (node->right != NULL));

                 if (ref->right == node)
                    ref->right = NULL;
                 else
                      ref->left = NULL;
                 
                 if (tree->count > 1) {
                    delete node;
                    tree->count--;
                 }
           }
     }
}

//==============================================================================    
void RemoveNode (Root*&tree) {
//Description:  Controls removal of user-input desired term for deletion from the tree.
//Parameters:   'tree' -- Binary tree storing all integers.
//==============================================================================
     int num;
     cout << system("cls");
     
     cout << "\tRemove a node in the tree" << endl 
          << "\tInput the non-zero positive integer you wish to" << endl 
          << "\tremove from the binary tree: ";
     cin >> num;
     
     if (num < 1) {
        cout << endl << endl << "\tThe number you entered was zero, or was negative." << endl;

        cout << system("pause");
        RemoveNode (tree);        
     }
     else {
           bool val = DeleteNode (num, tree);
           if (val) {
              cout << endl << "Integer " << num << " removed from the list." << endl;              
           }
     }           
}//End 'RemoveNode'

//==============================================================================
void FindNum (Node*&tree, int count) {
//Description:  Controls the locating of a user-input term within the tree.
//Parameters:   'tree' -- Binary tree storing all integers.
//==============================================================================     
     int num;

     do {
         cout << system("cls");
         cout << "\t";
         
         InOrderDisplay(tree, count, tree, tree, 0, 0);
         
         cout << endl << endl << "\tInput a non-zero positive integer to search from " 
              << endl << "\twithin the binary tree: ";
         cin >> num;
        
         if (num < 1) {
            cout << endl << "\tThe number that was input was less than 0" << endl;
            cout << system("pause");
         }
     } while (num < 1);
      
     Node* node = FindNode (num, tree);
     
     if (node != NULL) {
        num = FindCount (node, 0, tree, tree, 0);     
        cout << endl << "\t";   
        InOrderDisplay (node, num, tree, tree, 0, 0);
     }
     else {
           cout << endl << endl << "\tInteger " << num << " could not be found." << endl;

           cout << system("pause");           
     }
}//End 'FindNum'

//==============================================================================
int FindCount (Node*&tree, int count, Node* root, Node* temp, int lastNum) {
//Description:   Determines the number of terms in the sub-tree.
//Parameters:    'tree'    -- The sub-tree under analysis. 
//               'count'   -- The number of terms found so far.
//               'root'    -- The starting point of the sub-tree.
//               'temp'    -- The starting point of any sub-trees.
//               'lastNum' -- The last number found in the tree.
//Return Value:  Returns the int count of all nodes in the sub-tree.
//==============================================================================
    while ((root->left != NULL) && (lastNum < root->left->num)) {
          root = root->left;
    }
    if (root->num > lastNum) {
       count++;
       lastNum = root->num;
    }
    else
        return count;
    if (root->right != NULL) 
       FindCount (tree, count, root->right, root->right, lastNum);
    else {
          lastNum = root->num;
          if (root == temp) {
             FindCount(tree, count, tree, tree, lastNum);
          }
          else 
               FindCount(tree, count, temp, temp, lastNum);          
    }
}//End 'FindCount'

//==============================================================================
void AddNum(Root*&tree) {
//Description:  Controls the addition of a user-input term to the binary tree.
//Parameters:   'tree' -- Binary tree storing all integers.
//==============================================================================
     int num;
    
     do {
         cout << system("cls");
         cout << endl << "\tEnter an integer greater than 0 to add to the binary tree: ";
         
         cin >> num;
        
         if (num < 1)
            cout << endl << "\tThe number entered was too small. " << endl;
                       
     } while (num < 1);
          
     Node* node = FindNode(num, tree->root);
     if (node == NULL) {
        node = CreateNode(num);
        if (node != NULL) {
           InsertNode(node, tree->root);
           tree->count++;
        }
        else
            cout << endl << "\tNode could not be allocated." << endl;
     }
     else
          cout << endl << "\tInteger cannot be added. It is already present." << endl;           
}//End 'AddNum'
        
//==============================================================================        
NewRoot CreateTree () {
//Description:  Creates a new tree with 0 nodes, and a NULL root.
//Return Value: Returns a pointer to the address of the new tree, or NULL if 
//              memory allocation failed.
//==============================================================================
        Root* root = new Root;
           
        if (root == NULL)
           return root;
        else
            root->count = 0;
            
        root->root = NULL;
     
        return root;
}//End 'CreateTree'
     
//==============================================================================
bool IsEmpty (Root*&tree) {
//Description:  Returns a bool relative to the tree's emptiness.
//Parameters:   'root' -- The root node of the binary tree.
//Return Value: Returns true/false if the tree is empty/not.
//==============================================================================
     if (tree->count == 0)
        return true;
     else
         return false;
}//End 'IsEmpty'

//==============================================================================
NewNode CreateNode (int num) {
//Description: Creates a new node with the passed in integer.
//Parameters:  'num' -- The number to be added.
//Return Value: Returns a pointer to the address of the newly created node.
//==============================================================================        
        Node* node = new Node;
        
        if (node == NULL) 
           return node;

        node->num = num;
        node->left = NULL;
        node->right = NULL;
        return node;
}//End 'CreateNode'

//==============================================================================        
void InsertNode (Node*&node, Node*&root) {
//Description:  Adds the node to the tree passed in at root.
//Parameters:   'node'  -- The node to be added.
//              'root'  -- The root-starting point of the tree to add the node into.
//==============================================================================
     Node* base = root;
     bool inserted = false;
     
     if (base == NULL)
        root = node;        
     else {
           while (!inserted) {
                 if (base->num < node->num) {
                    if (base->right != NULL) 
                       base = base->right;
                    else {
                          base->right = node;
                          inserted = true;
                    }
                 }
                 else {
                      if (base->left != NULL) 
                         base = base->left;
                      else {
                            base->left = node;
                            inserted = true;
                      }                      
                 }                    
           }
     }
}//End 'InsertNode'

//==============================================================================
int NodeCount (Root*&tree) {
//Description:  Returns the number of nodes in the tree.
//Parameters:   'tree' -- The root node of the tree.
//Return Value: Returns the integer number of terms in the tree.
//==============================================================================    
    return tree->count;
}//End 'NodeCount'

//==============================================================================
NewNode FindNode (int num, Node*&tree) {
//Description:   Attempts to locate the passed in integer within the tree.        
//Parameters:    'num'   -- The integer to be found.
//               'tree'  -- The binary tree storing all integers.
//Return Value:  Returns a pointer to the address of the node containing the integer, or NULL.
//==============================================================================
        Node* root = tree;
        bool found = false;

        if (root != NULL)
           while (!found) {
                 if (root->num == num)
                    return root;
                 else {
                      if (root->num < num)  {
                         if (root->right != NULL)
                            root = root->right;
                         else {
                              return NULL;
                         }
                      }
                      else {
                            if (root->left != NULL) 
                               root = root->left;
                            else {
                                  return NULL;
                            }
                      }                      
                 }
           }
        else {
             cout << endl << "\tTree is empty." << endl;
             return NULL;
        }
}//End 'FindNode'

//==============================================================================
bool DeleteNode (int num, Root*&tree) {
//Description:  Attempts to reemove a node from the tree.
//Parameters:   'num'   -- Integer of the node to be removed.
//              'tree'  -- Root of the binary tree.
//Return Value: Returns a boolean value if the node continaing the number was removed successfully.
//==============================================================================
     Node* remove = FindNode(num, tree->root);  
     Node* node;
     Node* base;
               
     if (remove == NULL) {
        cout << endl << "\tNode could not be found." << endl;        
        return false;
     }
     else {
           if (remove->right != NULL) {
              base = remove->right;
              while (base->left != NULL) {
                    base = base->left;                                    
              }
              remove->num = base->num;
              node = remove->right;
              if (base->right != NULL) {                                  
                 while ((node->left != base) && (node->left != NULL)) {
                       node = node->left;
                 }
                 if (node != base)
                    node->left = base->right;                 
                 else
                     remove->right = base->right;                     
              }
              else {
                    while ((node->left != base) && (node->left != NULL)) {
                          node = node->left;
                    }
                    if (base == node)
                       remove->right = NULL;
                    else 
                         node->left = NULL;                    
              }                            
            //delete base;        
            tree->count--;
            return true;
            }
            else if ((remove->left != NULL) && (remove->right == NULL)) {
                    base = remove->left;
                    while (base->right != NULL) {
                          base = base->right;
                    }
                    remove->num = base->num;
                    node = remove->left;
                    if (base->left != NULL) {
                       while ((node->right != base) && (node->right != NULL)) {
                             node = node->right;
                       }
                       if (node != base)
                          node->right = base->left;
                       else
                           remove->left = base->left;
                    }
                    else {
                          while ((node->right != base) && (node->right != NULL)) {
                                node = node->right;
                          }
                          if (base == node)
                             remove->left = NULL;
                          else 
                               node->right = NULL;
                    }                                                               
            //delete base;
            tree->count--;
            return true;
            } 
            else if ((remove->right == NULL) && (remove->left == NULL)) {
                    tree->root = NULL;
                    delete remove;
            }                               
    }                          
}//End 'DeleteNode'

//==============================================================================
void InOrderDisplay (Node*&tree, int count, Node* root, Node* temp, int lastNum, int output) {
//Description:      Displays all integers stored within the binary tree, in their natural order.
//Parameters:       'tree'     -- Binary tree storing all integers.
//                  'count'    -- Integer count 
//                  'root'     -- Starting term of the tree/sub-tree.
//                  'temp'     -- Node of the tree/sub-tree to start from.
//                  'lastNum'  -- Integer of the last number output.
//                  'output'   -- Number of terms output on the line.
//============================================================================== 
     while ((root->left != NULL) && (lastNum < root->left->num)) {
           root = root->left;
     }
     if (root->num > lastNum) {
        cout << root->num;      
        count--;
        output++;
        
        if (output == 10) {
           cout << endl << "\t";
           output = 0;
        }
        else {
              if (count > 0)
                 cout << ", ";                
        }
     }
     if ((root->right != NULL) && (count > 0)) 
        InOrderDisplay (tree, count, root->right, root->right, lastNum, output);
     else {
           lastNum = root->num;
           if ((root == temp) && (count > 0))
              InOrderDisplay (tree, count, tree, tree, lastNum, output);
           else {
                 if (count > 0)
                    InOrderDisplay (tree, count, temp, temp, lastNum, output);
           }
     }
}//End 'InOrderDisplay'

//==============================================================================
bool ReadFiles (Root*&tree) {
//Description:  Reads the integers from a user-input text file.
//Parameters:   'tree' -- Binary tree to store read-in integers.
//Return Value: Returns a boolean value if a memory error occurs or not.
//==============================================================================
     ifstream file;
     int num;
     string fileName;
     
     do {
         cout << "\tInput name of the text file to read in integers: ";
         cin >> fileName;
         cout << endl;
         
         file.open(fileName.c_str());
         
         if (!file)
            cout << endl << "Error opening your text file. Try a different name." << endl;
     } while (!file);       
     
     file >> num;
     
     cout << endl << "\tLoading file: " << endl;
     
     while (file) {
           Node* node = new Node;        
           if (node != NULL) {
              node = FindNode(num, tree->root);
              if (node == NULL) {
                 node = CreateNode(num);
                 InsertNode (node, tree->root);
                 tree->count++;
              }
              else
                  cout << endl << "\tInteger " << num << " will be ignored." << endl;
           }                  
           else 
                return false;
                
           file >> num;
     }
     
     cout << "\tNumbers stored: " << NodeCount(tree) << endl;
     
     file.close();

     cout << system("pause");
     return true;
}
