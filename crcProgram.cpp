//==============================================================================
//Programmer:                Sherman Marshall
//Course:                    CS 450
//Description:               Program imitates the 32-bit CRC code implemented to 
//                           verify and validate data transferred over the link-layer
//==============================================================================                                                    
#include <iostream>
#include <iomanip>
using namespace std;

struct CRC {
       bool* D;
       int r;
       bool* G;
       int n;
       int d;
       bool* crc;
       };
        
//Prototypes       
void CRCreturn (CRC*&val);
void XOR (CRC*&val);
void Received (CRC*&val);

//Main function
int main()
{
    CRC* val = new CRC;
    cout << "CRC Algorithm" << endl << endl;
    cout << "D * 2^r XOR R = nG";
    
    CRCreturn(val);
    Received(val);
    cout << endl << endl;
    system("pause");
}

//=============================
void CRCreturn (CRC*&val) {
//Description:            function serves to initialize values corresponding with the
//                        32-bit CRC generator, prepares a random number of bits to 
//                        send as data, outputs the values to the user, and calls the
//                        XOR function, to provide a remainder value for reference to 
//                        the data being sent.
//Parameters:       val - struct containing relevant values for CRC generation/reference
//==============================
     int num;
     int bytes;
     double ex; 
     val->d = 128;
     val->r = 32;
     bool array[33] = {true, false, false, false, false, false, true, false, 
                              false, true, true, false, false, false, false, false, 
                              true, false, false, false, true, true, true, false, 
                              true, true, false, true, true, false, true,true, true};
     
    
     val->D = new bool[val->d + val->r];
     
     cout << endl << endl << "Number of bits being sent is: " << val->d;

     
     //Ensures leftmost bit is 1, validating size of following input.
     val->D[0] = 1;
     
     srand(time(0));
     for (int counter = 1; (counter < (val->d)); counter++) {
         val->D[counter] = rand() % 2;
         }
         
     for (int counter = val->d; (counter < (val->d + val->r)); counter++) {
         val->D[counter] = 0;
         }
         
     cout << endl << "Bits are: " << endl;   
     
     for (int counter = 0; counter < (val->d + val->r); counter++) {
         if (counter % 40 == 0)
            cout << endl;
         cout << val->D[counter];
         }
         
     cout << endl << endl << "Value of r is: " << val->r << endl << "Bits are: ";
     
     val->G = new bool[val->r + 1];
     for (int counter = 0; counter < 33; counter++) {
         val->G[counter] = array[counter];
         cout << val->G[counter];
         }
     
     val->crc = new bool[val->r];

     XOR (val);
     
     }
                  
//==============================
void XOR (CRC*& val) {
//Description:                  function serves to perform the XOR division for 
//                              later reference in checking if data arrived intact
//Parameters:             val - struct containing values for CRC generation/reference.
//==============================
    bool dividend[32] = {0};
    int offset = 0;
    bool set = false;
    
    for (int counter = 0; (counter <  (val->d + val->r)); counter +=offset) {
        set = false;
        offset = 0;
        if (counter == 0) {                    
            for (int orX = 0; (orX < (val->r +1)); orX++) {
                if ((((val->D[orX] == 0) && (val->G[orX] == 0)) ||
                   ((val->D[orX] == 1) && (val->G[orX] == 1))) && (set == false)) {
                   dividend[orX] = 0;
                   offset++;
                   }
                else if (((val->D[orX] == 0) && (val->G[orX] == 0)) ||
                        ((val->D[orX] == 1) && (val->G[orX] == 1))) {
                        dividend[orX] = 0;
                        }
                        else {
                             dividend[orX] = 1;
                             set = true;
                             }
                        }
            }
            else {
                  for (int nextOp = 0; nextOp < (val->r + 1); nextOp++) {
                      if (((dividend[nextOp] == 0) && (val->G[nextOp] == 0)) ||
                         ((dividend[nextOp] == 1) && (val->G[nextOp] == 1)) && 
                         (set = false)) {
                         dividend[nextOp] = 0;
                         offset++;
                         }
                         else if (((dividend[nextOp] == 0) && (val->G[nextOp] == 0)) ||
                                 ((dividend[nextOp] == 1) && (val->G[nextOp] == 1))) {
                                 dividend[nextOp] = 0;
                                 }
                                 else {
                                       dividend[nextOp] = 1;
                                       set = true;
                                       }
                                 }
                         }
                                                                       
        for (int place = 0; (place < (val->r - offset)); place++) {
            dividend[place] = dividend[place+offset];
            }
        
        if (!(counter + offset) > val->d) {
           for (int place = 0; place < offset; place++) {
               dividend[val->r - offset + place] = val->D[(val->r + 1) + place];
               }
           }
        }
    
    cout << endl << endl << "The CRC for this sequence of numbers \nis: ";
    
    for (int counter = 0; counter < val->r; counter++) {
        val->crc[counter] = dividend[counter];        
        cout << val->crc[counter];
        }
    }

//=============================            
void Received (CRC*&val) {
//Descrption:                  function serves to output a simulated value of the CRC
//                             upon receipt by the networked system. It outputs the results
//                             for view, before calling the same function to perform the 
//                             XOR division and verify the results.
//Parameters:            val - struct containing values for CRC genration/reference.
//=============================
          cout << endl << endl << "Performing CRC check of packet contents..." << endl 
               << "Expected results: ";
          for (int counter = 0; counter < val->r; counter++) {
              cout << val->crc[counter];
              }          
          
          XOR (val);
          }
