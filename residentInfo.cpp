//==============================================================================
//Program:       MarshallAssn6
//Description:   Program reads data from a text-file of the user's choice, storing
//               it in a linked list. All read residents are displayed to the user,
//               and a menu of options allows the user to select various features
//               (add resident/delete resident/change information/match information/
//               exit). The program will cycle through menu options returning to the 
//               menu until the user chooses to exit; at which point a choice to 
//               save will be given, and the program will write all data, or exit,
//               by user selection.
//Student:       Sherman Marshall
//Course:        CS 362
//File:          User-input
//Functions:     'OpenFile' -- Opens the file the user wishes to input data from.
//               'ReadFile' -- Reads data from file, and stores it in a linked list.
//               'DisplayResidents' -- Displays all stored information to the user.
//               'Menu' -- Displays a list of options to the user for program
//                         funtionality.
//               'AddResident' -- Adds a resident's information to the linked list.
//               'ErrorCheckSSN' -- Reads and checks a user-input ssn for errors.
//               'ErrorCheckLastName' -- Reads and checks a user-input last name
//                                       for errors.
//               'ErrorCheckPhoneNum' -- Reads and checks a user-input phone number
//                                       for errors.
//               'ErrorCheckPhoneType' -- Reads and checks the user-input type of
//                                        phone for errors.
//               'DeleteResident' -- Deletes a resident's information from the 
//                                   linked list.
//               'ChangeResidentInfo' -- Allows the user to change the information
//                                       corresponding to a user.
//               'SortResidents' -- Sorts residents from least to greatest, by ssn.
//               'MatchResident' -- Matches a resident's social with the articles
//                                  in 'RECOVER.txt'
//               'ExitProgram' -- Escapes the menu cycle and allows user to save
//                                stored information.
//               'RebuildList' -- Rebuilds linked list after a node has been removed.
//               'FindSSN'     -- Checks to see if an ssn is present in the linked list.
//==============================================================================
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstddef>
using namespace std;

//Enumerated type for the type-location 
//of the resident's phone.
enum phoneType {HOME, WORK, CELL};

//Enumerated type for the manner in which 
//list is rebuilt.
enum infoType {SSN, LASTNAME};

//Struct containing relevant resident data.
struct residentInfo {
       string ssn;
       string lastName;
       string phoneNum;
       int phoneType;
       residentInfo* nextResident;
       };

const int ASCIILOWBOUND = 48;           //Low-bound for ASCII numbers.
const int ASCIIUPBOUND = 57;            //Upper-bound for ASCII numbers.
const int ASCIICAPLOW = 65;             //Low-bound for ASCII capital letters.
const int ASCIICAPUP = 90;              //Upper-bound for ASCII capital letters.
const int ASCIICHARLOW = 97;            //Upper-bound for ASCII lowercase letters.
const int ASCIICHARUP = 122;            //Upper-bound for ASCII lowercase letters.
const int SOCIALLENGTH = 11;            //Length of an ssn with hyphens.
const int NAMELENGTH = 15;              //Allowed length of a name.
const int NUMLENGTH = 13;               //Length of a phone number with hyphens.
const int FIRSTHYPHEN = 3;              //Position of the first hyphpen.
const int HYPHENSOCIAL = 6;             //Position of the second hyphen in an ssn.
const int HYPHENPHONE = 7;              //Position of the second hyphen in a phone number.
const char HYPHEN = '-';                //A hyphen.
const string RECOVER = "RECOVER.txt";   //Name for text-file 'RECOVER.txt'
const string WRITEHOME = "Home";        //String value for type 'HOME'
const string WRITEWORK = "Work";        //String value for type 'WORK'
const string WRITECELL = "Cell";        //String value for type 'CELL'

//Function prototypes.
bool OpenFile (ifstream& inputFile, string& fileName);
void ReadFile (ifstream& inputFile, residentInfo*&headResident, string& fileName);
void DisplayResidents (residentInfo*&headResident);
void Menu (residentInfo*&headResident);
void AddResident (residentInfo*&headresident, string& ssn);
string ErrorCheckSSN();
string ErrorCheckLastName();
string ErrorCheckPhoneNum();
phoneType ErrorCheckType();
bool DeleteResident(residentInfo*&headResident, string& ssn);
bool ChangeResidentInfo (residentInfo*&headResident, string& ssn);
void SortResidents(residentInfo*&headResident);
bool MatchResident(residentInfo*&headResident);
void ExitProgram(residentInfo*&headResident);
void RebuildList (residentInfo*&headResident, residentInfo* resident, infoType type);
bool FindSSN (residentInfo*&headResident, string& ssn);

//==============================================================================
//Function:          'main'
//Description:       Calls necessary functions to allow the user access to the 
//                   program's features.
//==============================================================================
int main()
{
    ifstream inputFile;          //Name for user-input text-file.
    residentInfo* headResident;  //The top node of the linked list.
    string fileName;             //Filename of the user-input text-file.
    bool open;                   //Determines whether a file read is necessary.
    
    open = OpenFile(inputFile, fileName);
    
    if (open == true)
       ReadFile(inputFile, headResident, fileName);

    Menu(headResident);
    }//End main.

//==============================================================================
//Function:         'OpenFile'
//Description:      Takes the name of a text-file to open from the user, returning 
//                  a value of 'open' based on the user's input.
//Input:
//     Parameters:  'inputFile' -- User-input text-file for data read.
//                  'fileName'  -- User-input name of the file from which to read
//                                 data.
//Return Val:       Returns 'open' which will be true if a file was accepted from
//                  the user, or false, if they wish to proceed anyway.
//==============================================================================    
bool OpenFile (ifstream& inputFile, string& fileName)
{
     char choice;        //Stores user-input for program selections.
     bool open;          //Is true or false depending on if the file opens.
     
     cout << "File Opening Protocol";
     cout << endl << "Input the filename of the file you wish to have read: ";
     cin >> fileName;
     
     //Read file data.
     inputFile.open(fileName.c_str());

     //Allows the user another attempt to input a file for reading data.
     if (!inputFile)
     {
        cout << endl << "Error reading text-file " << fileName << "." << endl
             << "Would you like to input another? (Y/N): ";
        cin >> choice;
        
        choice = toupper(choice);
        
        //Multi-way selction based on user-input.
        switch (choice)
        {
               case 'Y':
                    inputFile.clear();
                    OpenFile(inputFile, fileName);
                    break;
               case 'N':
                    open = false;
                    break;
               default:
                       cout << endl << "Input did not correspond with available "
                            << "options." << endl;
                       system("pause");
                       OpenFile(inputFile, fileName);
                       break;
                       }//End switch.
               }//End if.
               else
                   open = true;
        
        return open;
     }//End 'OpenFile'

//==============================================================================
//Function:          'ReadFile'
//Description:       Reads data from the user-input file, storing it in a linked 
//                   list.
//Input:
//     Parameters:   'inputFile'    -- Variable corresponding to the file the user
//                                     wants to read data from.
//                   'headResident' -- Top node of a linked list to store data.
//                   'fileName'     -- Name of the user-input file.
//==============================================================================
void ReadFile (ifstream& inputFile, residentInfo*&headResident, string& fileName)
{
     residentInfo* resident;        //Stores resident information.
     
     headResident = new residentInfo;
     resident = new residentInfo;
     
     headResident = NULL;
     
     //Priming read.
     inputFile >> resident->ssn >> resident->lastName >> resident->phoneNum 
               >> resident->phoneType;

     //Read data from 'inputFile' and store it in 'headResident'
     while (inputFile)
     {
           resident->nextResident = headResident;
           headResident = resident;
           
           resident = new residentInfo;
           
           inputFile >> resident->ssn >> resident->lastName >> resident->phoneNum
                     >> resident->phoneType;
           }//End data-read.
     SortResidents (headResident);
     inputFile.close();
     }//End 'ReadFile'

//==============================================================================
//Function:          'DisplayResidents'
//Description:       Outputs all stored data from the linked list to the user.
//Input:             
//     Parameters:   'headResident' -- Linked list storing all resident data.
//==============================================================================
void DisplayResidents (residentInfo*&headResident)
{     
     residentInfo* display;    //Creates a new temporary node 'display' to store 
                               //'headResident'
     string type;
     display = new residentInfo;
     
     display = headResident;

     //Display data, or prompt user that there is none.
     if (display == NULL)
     {
        cout << endl << "There are no residents stored in the database." << endl;
        }
        else
        {
            cout << "All stored Residents" << endl << "--------------------" << endl;
            cout << setw(15) << setfill(' ') << "Name" << "  " << setw(11) 
                 << setfill(' ') << "SSN" << "  " << setw(12) << setfill(' ') 
                 << "Phone" << "  " << setw(7) << setfill(' ') << "Type" << endl;
            
            //Display all data in linked list 'headResident'
            for (int counter = 1; display != NULL; counter++)
            {
                //Determines the output for display based on the read 'phoneType'
                switch (display->phoneType)
                {
                       case (HOME):
                            type = WRITEHOME;
                            break;
                       case (CELL):
                            type = WRITECELL;
                            break;
                       case (WORK):
                            type = WRITEWORK;
                            break;
                       default:
                               cout << endl << "Invalid type";
                               break;
                               }//End switch.
                cout << counter << ": " << setw(15) << setfill(' ') << display->lastName
                     << "  " << setw(11) << setfill(' ') << display->ssn << "  "
                     << setw(12) << setfill(' ') << display->phoneNum << "  " 
                     << setw(2) << setfill(' ') << type << endl;
                display = display->nextResident;
                }//End for.
            }//End else.
        }//End 'DisplayResidents'

//==============================================================================
//Function:        'Menu'
//Description:     Outputs all stored data from the linked list, and all options 
//                 for program functionality to the user.
//Input:
//     Parameters: 'headResident' -- Linked list storing all resident data.
//==============================================================================
void Menu (residentInfo*&headResident)
{
     char option;        //User-input determining program flow.     
     string ssn;         //Stores a resident's ssn for reference.        
     
     system("cls");
     DisplayResidents(headResident);
     
     cout << endl << "Menu:" << endl << setw(5) << setfill('-') << endl << endl;
     cout << "Add Resident: (A)" << endl;
     cout << "Delete Resident: (D)" << endl;
     cout << "Change Resident Information (C)" << endl;
     cout << "Match items to residents: (M)" << endl;
     cout << "Exit Program: (E)" << endl << endl;
     cout << "Select the character of the option you would like performed: ";
     cin >> option;
     
     option = toupper(option);
     
     //Switch provides multi-way selection for all program features.
     switch (option)
     {
            case 'A':
                 AddResident(headResident, ssn);
                 Menu(headResident);
                 break;
            case 'D':
                 DeleteResident(headResident, ssn);
                 Menu(headResident);
                 break;
            case 'C':
                 ChangeResidentInfo(headResident, ssn);
                 Menu(headResident);
                 break;
            case 'M':
                 MatchResident(headResident);
                 Menu(headResident);
                 break;
            case 'E':
                 ExitProgram(headResident);
                 break;
            default:
                    cout << endl << "Input did not correspond with one of the above"
                         << " choices." << endl << "Re-enter an option." << endl;
                    system("pause");
                    break;
                    }//End switch.
            }//End 'Menu'  
     
//==============================================================================
//Function:           'AddResident'
//Description:        Takes information for a new resident from the user, and 
//                    adds it to the linked list.
//Input:
//     Parameters:    'headResident' -- Linked list storing all resident data.
//                    'ssn'          -- String storing the user-input social.
//==============================================================================
void AddResident (residentInfo*&headResident, string& ssn)
{
     residentInfo* resident;   //Stores resident information.
     bool present;             //Changes value depending on value returned from
                               //'ValidateEntry'
     
     system("cls");
     resident = new residentInfo;
     
     cout << "Add a resident" << endl << setw(14) << setfill('-') << endl << endl;
     
     present = FindSSN (headResident, ssn);
     
     //Switch statement outputs a prompt letting user know they inputted a social 
     //security number already present within the database, or adds the information
     //of a new resident.
     switch (present)
     {
            case true:
                 cout << endl << endl << "The last resident social security number"
                      << " is already present within the database." << endl;
                 break;
            case false:
                 resident->ssn = ssn;
                 resident->lastName = ErrorCheckLastName();
                 resident->phoneNum = ErrorCheckPhoneNum();
                 resident->phoneType = ErrorCheckType();
                 resident->nextResident = headResident;
                 headResident = resident;
                 SortResidents(headResident);
                 cout << endl << "passed";
                 break;
            default:
                    cout << endl << "Error with received resident status.";
                    break;
                    }//End switch.
     }//End 'AddResident'

//==============================================================================
//Function:           'ErrorCheckSSN'
//Description:        Takes a social security number as input from the user, and
//                    checks to make sure it is formatted properly, calling itself
//                    until it meets requirements.
//Return Val:         Returns the string 'ssn' used to store input.
//==============================================================================
string ErrorCheckSSN ()
{
       string ssn;   //The user-input social security number.
     
       ssn.clear();
       cout << endl << "Enter resident's Social Security Number." << endl;
       cout << "Format (###-##-####): ";
       cin >> ssn;
       
       //Checks length of SSN
       if (ssn.length() > SOCIALLENGTH)
       {
          cout << endl << "Social security number too long.";
          }//End if.
          
       //Checks if hyphens are present in the proper positions.
       if ((ssn[FIRSTHYPHEN] != HYPHEN) || (ssn[HYPHENSOCIAL] != HYPHEN))
       {  
          cout << endl << "Input must contain hyphens (###-##-####)." << endl;
          ErrorCheckSSN();
          }//End if.
          
       //Checks all characters of 'ssn' to ensure none are letters.
       for (int counter = 0; counter < ssn.size(); counter++)
       {   
           //Moves the counter position forward if a hyphen is encountered in the 
           //designated positions.
           if ((counter == FIRSTHYPHEN) || (counter == HYPHENSOCIAL))
              counter++;

           //If a letter is present, or a hyphen is absent, it outputs an error 
           //and calls the function again.
           if ((ssn[counter] > ASCIIUPBOUND) || (ssn[counter] < ASCIILOWBOUND))
           {
              cout << endl << "SSN cannot contain letters or special characters"
                   << " other than '-'";
              ErrorCheckSSN();
              }//End if.
              }//End for.
       
       return ssn;
       }//End 'ErrorCheckSSN'

//==============================================================================
//Function:            'ErrorCheckLastName'
//Description:         Takes a last name input by the user, and checks to ensure
//                     it is formatted correctly, calling itself until input
//                     meets formatting requirements.
//Return Val:          Returns the string 'lastName' which stores input.
//==============================================================================
string ErrorCheckLastName ()
{
       string lastName;   //Stores the last name of a new resident.
       
       lastName.clear();
       
       cout << endl << "Enter resident's last name: ";
       cin.ignore();
       getline(cin, lastName);
       
       //Checks that the length of 'lastName' is no greater than 'NAMELENGTH'
       if (lastName.length() > NAMELENGTH)
       {
          cout << endl << "Last name can contain a maximum of 15 characters. Sorry." << endl;
          ErrorCheckLastName();
          }//End if.
       
       //Changes all values of 'lastName' to capital values.
       for (int counter = 0; counter < lastName.size(); counter++)
       {
           //Location of the capital character, versus all others.
           if (counter == 0)
              lastName[counter] = toupper(lastName[counter]);
              else
                  lastName[counter] = tolower(lastName[counter]);
           }//End for.
           
       //Checks that there are no numbers or special characters in 'lastName'
       for (int counter = 0; counter < lastName.size(); counter++)
       {
           //Checks counter values at 0.
           if (counter == 0)
           {
              //Checks that the value is an upper case ASCII character.
              if ((lastName[counter] > ASCIICAPUP) || (lastName[counter] < ASCIICAPLOW))
              {  
                 cout << endl << "Last name may not contain any special characters." << endl;
                 ErrorCheckLastName();
                 }//End if.
              }//End if.
              else if (counter > 0) //Checks counter values greater than 0.
                   {
                      //Checks that the values are lower case ASCII characters.
                      if ((lastName[counter] > ASCIICHARUP) || (lastName[counter] < ASCIICHARLOW))
                      {
                         cout << endl << "Last name may not contain any spaces, numbers, or special"
                              << " characters.";
                         ErrorCheckLastName();
                         }//End if.
                      }//End if.
                     
           }//End for.
       return lastName;
       }//End 'ErrorCheckLastName'
       
//==============================================================================
//Function:         'ErrorCheckPhoneNum'
//Description:      Takes a phone number as input from the user, checks to see if
//                  it is formatted correctly, calling itself until it meets 
//                  requirements.
//Return Val:       Returns string 'phoneNum' which stores the user-input phone 
//                  number.
//==============================================================================
string ErrorCheckPhoneNum ()
{
       string phoneNum;   //Stores the phone number of the new resident.
       
       cout << endl << "Enter resident's phone number: ";
       cin >> phoneNum;
       
       //Checks if the phone number is too long.
       if (phoneNum.length() > NUMLENGTH)
       {
          cout << endl << "Phone number is too long.";
          ErrorCheckPhoneNum();
          }//End if.
          
       //Checks if hyphens are present in the proper positions.
       if ((phoneNum[FIRSTHYPHEN] != HYPHEN) || (phoneNum[HYPHENPHONE] != HYPHEN))
       {  
          cout << endl << "Input must contain hyphens." << endl;
          ErrorCheckPhoneNum();
          }//End if.
       
       //Checks all values of 'phoneNum' for characters other than numbers.
       for (int counter = 0; counter < phoneNum.size(); counter++)
       {
           //Moves to next stored value of 'phoneNum' if a counter in the proper 
           //position is encountered.
           if ((counter == FIRSTHYPHEN) || (counter == HYPHENPHONE))
              counter++;
           //Checks if there is a non-number character in 'phoneNum'
           if ((phoneNum[counter] > ASCIIUPBOUND) || (phoneNum[counter] < ASCIILOWBOUND))
           {
              cout << endl << "Error with input number.";
              ErrorCheckPhoneNum();
              }//End if.
           }//End for.
       
       return phoneNum;
       }//End 'ErrorCheckPhoneNum'

//==============================================================================
//Function:          'ErrorCheckType'
//Description:       Takes input from the user and checks it to ensure it was 
//                   formatted correctly, calling itself until requirements are met.
//Return Val:        Returns 'type' which holds the enumerated value corresponding
//                   with the phone type.
//==============================================================================
phoneType ErrorCheckType ()
{
          phoneType type;  //User-entered phone type of the new resident.
          char option;     //User-input selector for 'type'
          
          cout << endl << "Enter the character for the type which corresponds with the "
               << "input number." << endl << "Home/Work/Cell (H/W/C): ";
          cin >> option;
          option = toupper(option);
          
          //Outputs the appropriate type of phone number based on user-input.
          switch (option)
          {
                 case 'H':
                      type = HOME;
                      break;
                 case 'W':
                      type = WORK;
                      break;
                 case 'C':
                      type = CELL;
                      break;
                 default:
                         cout << endl << "Input was not one of the options." << endl;
                         ErrorCheckType();
                         break;
                         }//End switch.
                 return type;
                 }//End 'ErrorCheckType'

//==============================================================================
//Function:         'DeleteResident'
//==============================================================================
bool DeleteResident (residentInfo*&headResident, string& ssn)
{    
     bool present;  //Value returned from 'ValidateEntry'
     
     residentInfo* resident;
     residentInfo* list;
     residentInfo* storeList;
     
     system("cls");
     
     resident = new residentInfo;
     list = new residentInfo;
     storeList = new residentInfo;
     
     storeList = NULL;
     resident = headResident;
     
     cout << "Select a resident from the following list to delete: " << endl << endl;
     DisplayResidents(headResident);
          
     cout << endl << endl;
     
     present = FindSSN(headResident, ssn);
     
     //Prompts user that their input did not correspond with anything in the 
     //linked list.
     if (present == false)
     { 
        cout << endl << "The resident with the ssn: " << ssn << " is not in the database.";
        cout << endl << "Returning to menu." << endl;
        system("pause");
        }//End if.
        else
        {
            cout << ssn;
            system("pause");
            //Locate the position corresponding with the node of the resident to delete.
            while (resident->nextResident->ssn != ssn)
            {
                  resident = resident->nextResident;
                  }//End while.
                  
            resident->nextResident = resident->nextResident->nextResident;
            
            cout << endl << "here";
            RebuildList(headResident, resident, SSN);
            
            }//End else.
            SortResidents(headResident);
        }//End 'DeleteResident'
               

//==============================================================================
//Function:          'ChangeResidentInfo'
//Description:       Allows user to alter resident information, locating them
//                   by social security number, and prompting for more changes to
//                   the same -- or a different resident -- until a return to the 
//                   menu is selected.
//Input:
//     Parameters:   'headResident' -- Linked list storing all data read, and 
//                                     added to by the user.
//                   'ssn'          -- Stores the user-input social security number
//                                     to select a resident to alter data.
//==============================================================================
bool ChangeResidentInfo (residentInfo*&headResident, string& ssn)
{
     residentInfo resident;   //Stores resident information for a user.
     residentInfo *list;      //Stores all resident information for
     residentInfo *compare;   //Compares the input resident information with
                              //the presently stored data.
     char option;             //Stores user-input selection for program flow.
     bool present;            //Stores value returned from 'ValidateEntry'
     infoType type;           //Stores the reference type ('SSN' or 'LASTNAME)
                              //for building the list.
     
     system("cls");
     list = new residentInfo;
     
     list = headResident;
                   
     cout << "Change Resident Information" << endl << setw(26) << setfill('-') << endl;
     cout << "Choose a social security number from the following:" << endl << endl;
     
     DisplayResidents(headResident);
     
     cout << endl << setw(40) << setfill('-') << endl << endl;
     
     present = FindSSN(headResident, ssn);
     
     //Allows the user to change information about a resident if the resident's
     //information is present within the database.
     if (present == true)
     {
        //Allows the user to change information about the selected resident until 
        //they choose to alter a different resident's information, or return to 
        //the menu.
        do 
        {
           //Locates the position of the selected resident in 'list'
           while (list->ssn != ssn)
           {
                 list = list->nextResident;
                 }//End while.
                 
           cout << endl << "Resident information:" << endl;
           cout << setw(11) << setfill(' ') << "Social" << "  " << setw(15)
                << setfill(' ') << "Last Name" << "  " << setw(12) << setfill(' ') 
                << "Phone Number" << setw(7) << setfill(' ') << "Type" << endl;
           cout << setw(11) << setfill(' ') << list->ssn << "  " << setw(15) 
                << setfill(' ') << list->lastName << "  " << setw(12) << setfill(' ')
                << list->phoneNum << "  " << setw(7) << setfill(' ') << list->phoneType;
          
           cout << endl << endl << "Which subcategory needs to be changed?" << endl;
           cout << "Input the character in parentheses following the desired selection";
           cout << endl << "Social Security Number (SSN): (S)" << endl;
           cout << "Last Name: (N)" << endl;
           cout << "Phone Number: (P)" << endl;
           cout << "Phone Type: (T)" << endl;
           cout << "Different Resident: (D)" << endl;
           cout << "Return to Menu: (M)" << endl;
           cout << "Enter the character corresponding with your desired selection: ";
           cin >> option;
           option = toupper(option);
        
           //Determines the type of change to resident info based on user input.
           switch (option)
           {
                  case 'S':
                       present = FindSSN(headResident, ssn);
                    //If entered social is present within the database
                    //it is changed to the new value.
                    if (present == false)
                    {
                       list->ssn = ssn;
                       type = LASTNAME;
                       RebuildList(headResident, list, type);
                       }//End if.
                       else 
                       {
                            cout << endl << "The resident information entered was "
                                 << "already present within the database." << endl;
                            ChangeResidentInfo(headResident, ssn);
                            }//End else.
                       break;
                  case 'N':
                       resident.lastName = ErrorCheckLastName();
                       //Checks that the input last name is not the same as the current one.
                       if (resident.lastName == list->lastName)
                       {
                          cout << endl << "The resident information entered was "
                               << "already present within the database." << endl;
                          ChangeResidentInfo(headResident, ssn);
                          }//End if.
                          else
                          {
                              list->lastName = resident.lastName;
                              type = SSN;
                              RebuildList(headResident, list, type);
                              break;
                              }//End else.
                  case 'P':
                       resident.phoneNum = ErrorCheckPhoneNum();
                       
                       if (resident.phoneNum == list->phoneNum)
                       {
                          cout << endl << "The resident information entered was "
                               << "already present within the database." << endl;
                          ChangeResidentInfo(headResident, ssn);
                          }//End if.
                          else
                          {
                              list->phoneNum = resident.phoneNum;
                              type = SSN;
                              RebuildList(headResident, list, type);
                              break;
                              }//End else.
                  case 'T':
                       resident.phoneType = ErrorCheckType();
                       
                       //Checks if the input type is the same as the current record.
                       if (resident.phoneType == list->phoneType)
                       {
                          list->phoneType = resident.phoneType;
                          cout << endl << "The resident information entered was " 
                               << "already present within the database." << endl;
                          ChangeResidentInfo(headResident, ssn);
                          }//End if.
                          else
                          {
                              type = SSN;
                              RebuildList(headResident, list, type);
                              break;
                              }//End else.
                  case 'D':
                       ChangeResidentInfo(headResident, ssn);
                       break;
                  case 'M':
                       Menu(headResident);
                       break;
                  default:
                          cout << endl << "The entered option did not correspond "
                               << "with an available selection. Re-enter option.";
                          system("pause");
                          break;
                          }//End switch.
                  } while (option != 'M');
           }//End if.
           else 
           { 
                cout << endl << "The input ssn: " << ssn << " is not present.";
                cout << endl << "Would you like to try again? (Y/N): ";
                cin >> option;
                
                option = toupper(option);
                
                //Allows user to return to the menu, or call the function again
                //to change resident data.
                switch (option)
                {
                       case 'Y': 
                            ChangeResidentInfo (headResident, ssn);
                            break;
                       case 'N':
                            Menu(headResident);
                            break;
                       default:
                               cout << endl << "Input did not correspond with an option." << endl;
                               cout << "Returning to to menu." << endl;
                               system("pause");
                               break;
                       }//End switch.
                }//End else.
            }//End 'ChangeResidentInfo'

//==============================================================================
//Function:           'SortResidents'
//Description:        Sorts residents in the linked list from least, to greatest.
//Input:
//     Parameters:    'headResident' -- Linked list containing all read data,
//                                      and user-input changes.
//==============================================================================
void SortResidents (residentInfo*&headResident)
{
     residentInfo  *residents,      //Reference to the linked list 'headResident'
                   *sortList,       //The new, sorted list.
                   *addResident,    //Nodes to be added individually to 'sortList'
                   tempResident,    //Stores reference data from 'residents' to 
                   initialResident; //be placed in the new nodes of 'addResident'
     
     residents = new residentInfo;
     sortList = new residentInfo;
     addResident = new residentInfo;
     
     sortList = NULL;
     
     residents = headResident;
     
     initialResident.ssn = residents->ssn;
     tempResident.ssn.clear();
     
     //While-loop locates the lowest value present within 'residents'
     while (residents != NULL)
     {
           //Stores new values for 'initialResident' if one is found 
           //lower than its current value.
           if (residents->ssn < initialResident.ssn)
           {
              initialResident.ssn = residents->ssn;
              initialResident.lastName = residents->lastName;
              initialResident.phoneNum = residents->phoneNum;
              initialResident.phoneType = residents->phoneType;
              }
           //Adjusts values of 'tempResident' if one is found greater than its
           //current value.
           if (residents->ssn > tempResident.ssn)
           {
              tempResident.ssn = residents->ssn;
              tempResident.lastName = residents->lastName;
              tempResident.phoneNum = residents->phoneNum;
              tempResident.phoneType = residents->phoneType;
              }
           residents = residents->nextResident;
           }//End while.
           
     addResident->ssn = tempResident.ssn;
     addResident->lastName = tempResident.lastName;
     addResident->phoneNum = tempResident.phoneNum;
     addResident->phoneType = tempResident.phoneType;
     
     addResident->nextResident = sortList;
     sortList = addResident;
     
     addResident = new residentInfo;
     
     //Loop sorts all values of 'headResident' from least to greatest.
     do
     {
       residents = headResident;
       
       tempResident.ssn = initialResident.ssn;
              
       //Loop checks all values of 'residents' for the next highest value.
       do 
       {
          //Assigns values to 'tempResident' based on the size value of the string
          //from least to greatest.
          if ((residents->ssn > tempResident.ssn) && (residents->ssn < sortList->ssn))
          {
             tempResident.ssn = residents->ssn;
             tempResident.lastName = residents->lastName;
             tempResident.phoneNum = residents->phoneNum;
             tempResident.phoneType = residents->phoneType;
             }//End if.
             
             residents = residents->nextResident;
             } while (residents != NULL);

       addResident->ssn = tempResident.ssn;
       addResident->lastName = tempResident.lastName;
       addResident->phoneNum = tempResident.phoneNum;
       addResident->phoneType = tempResident.phoneType;
        
       addResident->nextResident = sortList;
       sortList = addResident;
       
       addResident = new residentInfo;
       } while (sortList->ssn != initialResident.ssn);
       
       headResident = sortList;
       headResident->lastName = initialResident.lastName;
       headResident->phoneNum = initialResident.phoneNum;
       headResident->phoneType = initialResident.phoneType;
       }//End 'SortResidents'
       
//==============================================================================
//Function:            'MatchResident'
//Description:         Opens the text-file 'RECOVER.txt' and reads values to 
//                     check against the stored ssn's within the linked list.
//Input:
//     Parameters:     'headResident' -- Linked list storing resident information.
//Return Val:          Returns a 'false' if there is a problem with the text-file,
//                     'found' (true or false) once it goes through the linked list
//                     to match socials, and 'none-found' if no read values are 
//                     located within the linked list.
//==============================================================================
bool MatchResident (residentInfo*&headResident)
{
     ifstream recover;           //Fstream variable for 'RECOVER.txt'
     residentInfo *list;         //Creates a reference linked list to 'headResident'
     string article;             //Stores the read missing article.
     string ssn;                 //The ssn belonging to the missing article.
     string phoneType;           //The phone type of the resident.
     bool found = false;         //Changes to true if an article is matched.
     bool noneFound = true;      //Changes to false if an article is matched.
     
     
     recover.open(RECOVER.c_str());
     
     //Check if text-file opens properly.
     if (!recover)
     {
        cout << endl << "Error opening text-file 'RECOVER.txt'" << endl;
        cout << "Returning to menu." << endl;
        system("pause");
        return false;
        }//End if.
        
     list = new residentInfo;
     
     //Check if there is data present in the linked list.
     if (headResident == NULL)
     {
        cout << endl << "There is no stored information to refer to." << endl;
        cout << "Returning to menu.";
        system("pause");
        return false;
        }//End if.
        else
        {
            cout << endl << endl << setw(15) << setfill(' ') << "Name" << "  " 
                 << setw(12) << setfill(' ') << "Phone Number" << "  " << setw(6) 
                 << setfill(' ') << "Type" << "  " << setw(20) << setfill(' ')
                 << "Item Recovered" << endl;
                 
            //Priming read.
            recover >> ssn;
            getline(recover, article);
            }//End else.
                 
     //Output matches of resident info from 'RECOVER.txt' to the user.
     while (recover)
     {
           list = headResident;
           
           //Cycle through stored values in 'list' to find the residents the 
           //articles belong to.
           while (list != NULL)
           {
                 //Assigns values to 'phoneType' if an article matches a social.
                 if (list->ssn == ssn)
                 {
                    //Assign value to output prompt 'phoneType'
                    switch (list->phoneType)
                    {
                           case HOME:
                                phoneType = WRITEHOME;
                                break;
                           case WORK:
                                phoneType = WRITEWORK;
                                break;
                           case CELL:
                                phoneType = WRITECELL;
                                break;
                           default:
                                   cout << endl << "Error reading resident's phone number type.";
                                   phoneType = "ERROR";
                                   break;
                                   }//End switch.
                                   
                     cout << setw(15) << setfill(' ') << list->lastName << "  " 
                          << setw(12) << setfill(' ') << "  " << list->phoneNum 
                          << setw(4) << phoneType << "  " << setw(20) << setfill (' ') 
                          << article << endl;
                     found = true;
                     }//End if.
                     
           //Outputs a prompt if the stored article is not present.
           if (found == false)
              cout << endl << "Article: " << article << " not found."
                   << endl;
              //Changes the value of 'noneFound' if any article matches information
              //present in the list.
              if (found == true)
                 noneFound = false;
           list = list->nextResident;
           
           recover >> ssn;
           getline(recover, article);
           }//End while.
           }//End while.
                     
           //Outputs a prompt to the user if no articles from 'RECOVER.txt' are 
           //matches with the residents.
          if (noneFound == true)
          {
             cout << endl << "None of the articles in 'RESIDENTS.txt' match with"
                  << " residents from the database." << endl; 
             cout << "Returning to menu." << endl;
             system("pause");
             return noneFound;
             }//End if.
          system("pause");
          }//End 'MatchResident'
                 
//==============================================================================
//Function:             'ExitProgram'
//Description:          Necessary function to allow the user to exit the program
//                      once they are finished with it, allowing the user to save
//                      any changes.
//Input:
//     Parameters:      'headResident' -- Linked list storing all resident information.
//==============================================================================
void ExitProgram (residentInfo*&headResident)
{
     char choice;         //Stores user's selection for saving.
     ofstream inputFile;  //Fstream variable for writing to the user's file.
     string fileName;     //Title of the user's text-file.
     
     cout << endl << endl << "Program preparing to exit, would you like to save data?"
          << endl << "Input selection as yes or no (Y/N): ";
     cin >> choice;
     
     choice = toupper(choice);
     
     //Allows user to select a file to write to, choosing to overwrite data if present.
     switch (choice)
     {
            case 'Y':
                 cout << endl << "Input the file name of the file you would like "
                      << "to save data to." << endl;
                 cin >> fileName;
                 
                 inputFile.open(fileName.c_str());
                 
                 //Checks if file opened properly.
                 if (inputFile)
                 {
                    cout << endl << "File already exists and contains data." << endl;
                    cout << "Would you like to overwrite the data? (Y/N): ";
                    cin >> choice;
                    choice = toupper(choice);
                    
                    //Allows user to choose to overwrite saved data.
                    switch (choice)
                    {
                           case 'Y':
                                cout << endl << "Overwriting data..." << endl;
                                //Outputs all data in the linked list to the user input
                                //file.
                                while (headResident !=NULL)
                                {
                                      inputFile << headResident->ssn << " " 
                                                << headResident->lastName << " "
                                                << headResident->phoneNum << " "
                                                << headResident->phoneType << "\n";
                                      headResident = headResident->nextResident;
                                      }//End while.
                                break;
                           case 'N':
                                cout << endl << "Program exiting." << endl;
                                system("pause");
                                break;
                           default:
                                   cout << endl << "Input did not correspond with a yes"
                                        << " or no option. Program exiting." << endl;
                                   system("pause");
                                   break;
                                   }//End switch.
                           }//End if.
                           else
                           {
                               //Outputs a prompt if the file does not open properly.
                               if (!inputFile)
                               {
                                  cout << endl << "Error opening text-file "
                                       << fileName << endl;
                                  cout << "Program exiting.";
                                  }//End if.
                                  else
                                  {
                                      cout << endl << "Writing data to file..." << endl;
                                      
                                      //Writes all stored data in 'headResident' to the 
                                      //user's file.
                                      while (headResident !=NULL)
                                      {
                                            inputFile << headResident->ssn << " " 
                                                      << headResident->lastName
                                                      << headResident->phoneNum << " "
                                                      << headResident->phoneType << endl;
                                            headResident = headResident->nextResident;
                                            }//End while.
                                      cout << endl << "All data written to " << fileName;
                                      cout << endl << "Program exiting." <<  endl;
                                      system("pause");
                                      }//End else.
                                  }//End else.
            case 'N':
                 cout << endl << "Program exiting." << endl;
                 system("pause");
                 break;
            default:
                    cout << endl << "Error with input, must be yes or no (Y/N)." << endl;
                    ExitProgram(headResident);
                    break;
                    }//End switch.
            system("pause");
            }//End 'ExitProgram'

//==============================================================================
//Function:        'RebuildList'
//Description:     Rebuilds the linked list once it has been broken, back to its
//                 initial form based on the value of 'headResident'
//Input:
//     Parameters: 'headResident' -- Linked list storing all resident data.
//                 'resident'     -- Pointer storing the broken linked list.
//                 'type'         -- Enumerated type for how to rebuild the linked
//                                   list, by ssn or last name.
//==============================================================================
void RebuildList (residentInfo*&headResident, residentInfo* resident, infoType type)
{
     residentInfo *builder;   //A reference list for 'headResident' 
     residentInfo *addNode;   //A new node for the list.
     residentInfo startNode;  //Temporary data storage.
     
     builder = new residentInfo;
     startNode.ssn = resident->ssn;
     startNode.lastName = resident->lastName;
     
     //Loops until the initial node matches that of 'headResident'
     do
     {
       addNode = new residentInfo;
       builder = headResident;
       //The type used to rebuild the list (ssn or last name).
       switch (type)
       {
              case (SSN):
                   //Locates the remainder of the list at the position of
                   while (builder != NULL)
                   {
                         if (builder->nextResident->ssn == resident->ssn)
                         {
                            addNode->ssn = builder->ssn;
                            addNode->lastName = builder->lastName;
                            addNode->phoneNum = builder->phoneNum;
                            addNode->phoneType = builder->phoneType;
                            builder->nextResident = NULL;
                            }//End if.
                         builder = builder->nextResident;
                         }
                   addNode->nextResident = resident;
                   resident = addNode;
                   cout << resident->ssn << endl;
                   break;
              case (LASTNAME):
                   while (builder != NULL)
                   {
                         if (builder->nextResident->ssn == resident->ssn)
                         {
                            addNode->ssn = builder->ssn;
                            addNode->lastName = builder->lastName;
                            addNode->phoneNum = builder->phoneNum;
                            addNode->phoneType = builder->phoneType;
                            builder->nextResident = NULL;
                            }//End if.
                         builder = builder->nextResident;
                         }
                   addNode->nextResident = resident;
                   resident = addNode;
                   break;
              default:
                      cout << endl << "Error with the input type of list reference.";
                      break;
                      }//End switch.
       } while (headResident->ssn != resident->ssn);
       
       headResident = headResident->nextResident;
       headResident = resident;
       }//End 'RebuildList'
     
//==============================================================================
//Function:               'FindUnits'
//Description:            Locates a social security number within the linked list
//                        and if present, returns a true value.
//Input:
//     Parameters:        'headResident' -- Linked list storing resident data.
//                        'ssn'          -- Resident's social security number.
//Return Val:             Returns 'present' which will be true if the sought
//                        'ssn' value is present in the linked list, and false
//                        otherwise.
//==============================================================================
bool FindSSN (residentInfo*&headResident, string& ssn)
{
       bool present = false;
       
       residentInfo *residents;
       residents = new residentInfo;
       
       residents = headResident;
       
       ssn = ErrorCheckSSN();
       
       while (residents != NULL)
       {             
             //If statement checks whether the input SSN is present, and 
             //changes the value of 'present' if it is.
             if (residents->ssn == ssn)
                present = true;
                
             residents = residents->nextResident;
             }//End while.
       
          return present;
       }//End 'FindSSN'
