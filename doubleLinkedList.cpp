//==============================================================================
//Program:            Marshall_Wk2_Assignment.cpp
//Description:        Program takes command-line parameters and reads file values into
//                    a linked list, keeping track of the total nodes composing the
//                    linked list. Individual nodes are inserted in ascending order 
//                    into the list. A second command-line parameter reads file values
//                    and returns the node with that position for display to the user.
//Files:              'text-file1'
//                    'text-file2'
//Functions:          ReadFiles
//                    InitializeList
//                    EmptyList
//                    OrderedListInsertIon
//                    NumInList
//                    DestroyList
//                    DisplayList
//                    ListLength
//                    PositionInList
//                    Search
//==============================================================================
#include <iostream>
#include <fstream>
#include <cstddef>
#include <iomanip>
using namespace std;

//Struct for storing a doubly-linked list, and the length of its constituents.
struct Integer {
       int num;
       Integer* prior;
       Integer* next;
       };

//Struct for the nodes of a linked list.
struct DLL {
       int length;
       Integer* top;
       };

//Definition of types to retern pointer variables.       
typedef DLL* DLLStar;
typedef Integer* IntegerStar;

//Function prototypes.
bool ReadFiles (DLL*&eList, DLL*&oList, char* fileNames[]);
DLLStar InitializeList (DLL* list);
bool EmptyList (DLL*&list);
bool OrderedListInsertion (DLL*&list, int num);
IntegerStar NumInList (DLL* list, int num);
void DestroyList (DLL*&list);
void DisplayList (DLL*&list);
int ListLength (DLL*&list);
int PositionInList (DLL*&list, int num);
int Search (Integer*& node, DLL*& list);

//==============================================================================
int main(int argc, char* fileNames[]) {
//Description:     main controls the program flow.
//Parameters:      'argc' -- number of terms read in as input parameters.
//                 'fileNames' -- array of filenames passed in as input parameters.
//==============================================================================
    DLL* eList = new DLL;
    DLL* oList = new DLL;
    bool read;
    
    eList = InitializeList(eList);
    oList = InitializeList (oList); 

    if ((eList == NULL) || (oList == NULL)) {
       cout << "Insufficient memory to initialize new linked list. Program exiting." << endl;
       cout << "Enter 0 to continue: ";
       cin >> read;
       return read;
       }
       
    read = ReadFiles (eList, oList, fileNames);
    
    //Conditional checks if ReadFiles correctly read the values.
    if (read == 0) {
       cout << "Insufficient memory to initialize new linked list. Program exiting." << endl;
       cout << endl << endl << "Enter 0 to continue: ";
       cin >> read;
       }//End if.
       
    }//End main.
    
//==============================================================================    
int ListLength (DLL*&list) {
//Description:             Returns length of the DLL.
//Parameters:              'list' -- Stores the DLL
//Return Value:            Returns lenght of the DLL.
//==============================================================================    
    return list->length;
    }//End ListLength
    
//==============================================================================
bool ReadFiles (DLL*&eList, DLL*&oList, char* fileNames[]) {
//Description:              Reads all values from the first text-file stored as 
//                          command-line parameters, storing them in DLL's, and
//                          references the created DLL versus the values stored in
//                          the second text-file.
//Parameters:               'eList'     -- DLL of even integers.
//                          'oList'     -- DLL of odd integers.
//                          'fileNames' -- Command line parameters.
//==============================================================================
     bool read = false;
     bool full = false;
     ifstream file;
     ifstream fileTwo;
     int num = 0;
     int length;
     Integer* node = new Integer;
     
     if (node == NULL)
        return 0;
     
     file.open(fileNames[1]);
     
     //Loop checks if file opened properly, and accepts prompts until it is so.
     do {
        //Conditional checks if the file opened properly.
        if (!file) {
           num++;
           cout << "Error reading text file. Input the name of the text file: ";
           cin >> fileNames[1];
           cout << endl; 
           
           file.open(fileNames[1]);
           }//End if.
        } while (!file);
           
     if (num > 0)
        cout << endl << endl;
        
     cout << "Reading Input from text file: " << fileNames[1] << endl << endl;
     
     file >> num;
     
     do {
         
           //Conditional inserts the new number into the even list.
           if ((num % 2) == 0) {
              length = eList->length;
              read = OrderedListInsertion (eList, num);
              //Conditional alerts the user that the number last read is already present.
              if ((!read) && (length == eList->length) && (!full)) {
                 cout << "Memory exhausted. No additional nodes may be added." << endl;
                 full = true;
                 }
                 else if ((length == eList->length) && (!full))
                     cout << "Integer " << num << " already present in list." << endl;
                         
                 }//End if.
                 //Conditional inserts the new number into the odd list.
                 else {
                       length = oList->length;
                       read = OrderedListInsertion (oList, num);
                       //Conditional alerts the user that the number last read is already present.
                       if ((!read) && (length == oList->length) && (!full)) {
                          cout << "Memory exhausted. No additional nodes may be added." << endl;
                          full = true;
                          }
                          else if ((length == oList->length) && (!full))
                                  cout << "Integer " << num << " already present in list." << endl;
                       }//End else.
                       
           file >> num;
           
           } while ((file) && (!full));
    
     file.close();
     
     //DisplayList (eList);
     //DisplayList (oList);
     
     cout << endl << "Reading input from text file: " << fileNames[2] << endl << endl;
     
     fileTwo.open(fileNames[2]);
     num = 0;
     //Loop checks if file opened properly, and accepts prompts until it is so.
     do {
        //Conditional checks if the file opened properly.
        if (!fileTwo) {
           num++;
           cout << "Error reading text file. Input the name of the text file: ";
           cin >> fileNames[1];
           cout << endl; 
           
           fileTwo.open(fileNames[1]);
           }//End if.
        } while (!fileTwo);
     
     if (num > 0)
        cout << endl << endl;
     
     //Loop checks all contents from the file to check their presence in either list.
     do {
         fileTwo >> num;
         
         //Conditional determines which list the integer is sought from.
         if ((num % 2) == 0) {
            node = NumInList(eList, num);
            
            cout << "The number: " << setw(5) << num;
            num = Search (node, eList);
            
            //Conditional evaluates whether the number was present within the list.
            if (num != 0)
               cout << " was found " << num << " nodes down in the even list." << endl;
               else 
                    cout << " was not found." << endl;
            }//End if.
            else {
                  node = NumInList (oList, num);
                  
                  cout << "The number: " << setw(5) << num;
                  
                  num = Search (node, oList);
                  
                  if (num != 0)
                     cout << " was found " << num << " nodes down in the odd list." << endl;
                     else
                         cout << " was not found." << endl;
                  }//End else.
            } while (fileTwo);           
            
     fileTwo.close();
     DestroyList (eList);
     DestroyList (oList);
     
     system("pause");
     return true;
         }//End ReadFiles.
        
     
//==============================================================================                 
int Search (Integer*& node, DLL*& list) {
//Description:        Returns the number of nodes down the list the number is located
//                    if the number is present within the list.
//Parameters:         'node' -- the node containing a number.
//                    'list' -- a DLL of integers.
//Return Value:       Returns the number of nodes down in the list the number is found.
//==============================================================================
                                                                                
    if (node != NULL) {
        for (int counter = 1; counter <= list->length; counter++) {
            //Conditional returns the number of iterations it requires to reference the node.
            if (node->num == list->top->num)
               return counter;
               
            node = node->prior;       
            }//End for.
    }//End if.
    else
        return 0;
    }//End Search
    
    
//==============================================================================
DLLStar InitializeList (DLL* list) {
//Description:         InitializeList takes a pointer to a LL as input, initializes
//                     a node of type integers as the first node in the list, and 
//                     returns the list to the calling function.
//Parameters:          'list' -- the linked list of integers.
//Return value:        Returns a DLL pointing to the top of a list of integers.
//==============================================================================
        list = new DLL;
        Integer* initial = new Integer;
        
        //Checks if memory allocation failed.
        if ((initial == NULL) || (list == NULL))
           cout << "Error allocating memory, program exiting.";
           else {
                 initial = NULL;
                    
                 list->top = initial;
                 list->length = 0;
                 }
                    
        return list;
        }//End InitializeList.
        
//==============================================================================
bool EmptyList (DLL*&list) {
//Description:       EmptyList takes a DLL and checks to see if the topmost node
//                   is NULL.
//Parameters:        'list' -- A DLL of Integer nodes.
//Return value:      Returns a true/false depending on the fullness of the list.
//==============================================================================     
     if (list->top == NULL) 
        return true;
     else
         false;
         }//End EmptyList.

//==============================================================================
bool OrderedListInsertion (DLL*&list, int num) {
//Description:            OrderedListInsertIon handles addition of new nodes to 
//                        a given DLL, inputting it in increasing numerical order.
//Parameters:             'list' -- DLL of evens/odds
//                        'num'  -- Integer number to be added to the DLL.
//Return value:           Returns a true value if the number is added correctly
//                        or false, if it is a repeat.
//==============================================================================
     Integer* node = new Integer;
     Integer* copy = new Integer;
     
     //Conditional checks if the new node was allocated properly.
     if ((copy == NULL) || (node == NULL))
        return false;
        //Conditional checks if the number is already present at the head of the list.
        if ((list->top != NULL) && (list->top->num == num))
           return true;
           
     node->num = num;
     copy = list->top;      
     
     //Conditional checks all nodes in list if length is greater than 1.
     if ((ListLength(list)) > 0) {                                      
        //Loop goes through values one by one to input number in ascending order.
        while ((copy != NULL) && (copy->num < num)) {
              copy = copy->next;
              //Conditional returns false if number is a repeat.
              if ((copy != NULL) && (copy->num == num))
                 return true;
              }//End while.        
        
        node->next = copy;

        if (copy != NULL)
           copy->prior = node;
        
        //Conditional checks if the top of the list is already too large.
        if (node->num < list->top->num) {
           list->top = node;
           list->length++;
           return true;
           }//End if.
           else {
                //Loop adds all prior nodes to the list;
                while (node->num != list->top->num) {
                      copy = list->top;
                      //Loop locates next node to add.
                      while ((copy->next != NULL) && (copy->next->num < node->num)) {
                            copy = copy->next;
                            }//End while.
        
                      copy->next = node;
                      node->prior = copy;
                      node = copy;
                      }//End while.
        
                list->top = node;
                list->length++;
                
                copy = NULL;
                node = NULL;
                
                delete copy;
                delete node;
                
                return true;
                }//End else.
        }//End if.
        //Conditional adds number if number is not equivalent to single node.
        else {
               node->next = NULL;
               node->prior = NULL;
                              
               list->top = node;
               
               copy = NULL;
               delete copy;

               list->length++;
               return true;
               }//End else.
        }//End OrderedListInsertIon.
     
//==============================================================================
IntegerStar NumInList (DLL* list, int num) {
//Description:        Takes an input value as a parameter and attempts to locate 
//                    a node in the list which contains the value and is
//                    subsequently returned.
//Parameters:         'list' -- A DLL of even/odd integers.
//                    'num'  -- An integer to locate within either list.
//Return Value:       Returns an interlinked node for a subsequent search.
//==============================================================================
            Integer* search = new Integer;
            Integer* node = new Integer;
            
            if ((search == NULL) || (node == NULL)) 
               return NULL;               
               else 
                    search = list->top;            
                    
            //Loop goes through the list to locate the passed-in parameter.
            for (int counter = list->length; counter > 0; counter--) {
                //Conditional returns the node if it contains the sought integer.
                if (search->num == num) {
                   node = search;
                   
                   search = NULL;
                   delete search;
                   return node;
                   }//End if.
                   
                search = search->next;                
                }//End for.
            
            search = NULL;
            delete search;
            node = NULL;
            delete node;
            
            return NULL;
            }//End NumInList.
                   
//==============================================================================
void DestroyList (DLL*& list) {
//Description:   Destroys the linked list once it is no longer needed.
//Parameters:    'list' -- DLL containing integers.
//==============================================================================
     Integer* node = new Integer;
     
     node = list->top;
     //Loop iterates through DLL deleting unnecessary nodes.
     for (int counter = list->length; counter > 0; counter--) {
         node->prior = NULL;
         node = node->next;
         }
         delete list;
         delete node;
     }//End DestroyList.
         
//==============================================================================
void DisplayList (DLL*& list) {
//Description:   Takes a DLL as input and outputs all integer contents for display.
//Parameters:    'list' -- DLL storing integers.
//==============================================================================
     Integer* aList = new Integer;
     aList = list->top;
     
     cout << endl << "Displaying all " << list->length << " stored ";
     
     //Conditional processes output contingent on parity.
     if ((aList->num % 2) == 0)
        cout << "even integers:" << endl;
     else 
          cout << "odd integers:" << endl;
     
     //Loop outputs all contents 
     for (int counter = 0; counter < list->length; counter++) {
         if ((counter % 10) == 0)
            cout << endl;
             
         cout << aList->num;
         
         if (counter < (list->length - 1))
            cout << ", ";
         aList = aList->next;
         }//End for.

     delete aList;
     cout << endl;
     }//End DisplayList
