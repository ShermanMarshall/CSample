//==============================================================================
//Description:                 Program imitates a FSM simulating reliable-data-
//                             transfer 
//Programmer:                 Sherman Marshall
//Functions:                  'InitializeChecksum'
//                            'CalcChecksum'
//                            'Rdt_Send'
//                            'Rdt_Rcv'
//==============================================================================

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstddef>
#include <cctype>
using namespace std;

struct Checksum {
       int word1[16];
       int word2[16];
       int word3[16];
       int complement[16];
       };
       
struct Segment {
       int time;
       bool sequenceNum;
       Checksum* checksum;
       string data;
       };
       
const int MAX_TIME = 5;

//Function prototypes
Checksum* InitializeChecksum();
bool CalcChecksum (Segment*&udpSegment);
int Rdt_Send(Segment*&udpSegment, int time);
int Rdt_Rcv (Segment*&udpSegment);
Segment* Make_Packet(int sequenceNum);

//Begin main
int main() {
     Segment* udpSegment;
     char input;
     int ret;
     
     do { 
     do {
          cout << "Send packet? (Y/N): ";
          cin >> input;
          input = toupper(input);
          
          if ((input != 'Y') && (input != 'N')) 
             cout << endl << "Improper input.";
          } while ((input != 'Y') && (input != 'N'));
          
     if (input == 'N')
        return 0;
        
     udpSegment = Make_Packet(0);
     Rdt_Send(udpSegment, time(0));
     
     
     cout << endl << "Sending next packet: ";
             
     udpSegment = Make_Packet(1);
     Rdt_Send(udpSegment, time(0));
     
     cout << endl << "Packets sent!" << endl;
     } while (input != 'N');
}//End main.     

//==============================================================================
Segment* Make_Packet (int sequenceNum) {
//Description:       Creation of data to be sent as UDP
//==============================================================================
         Segment* udpSegment = new Segment;
         string data;

         data = "Example of data being sent within a segment";
         
         udpSegment->checksum = InitializeChecksum();
         udpSegment->sequenceNum = sequenceNum;
         udpSegment->data = data;
         return udpSegment;
         }
         
//==============================================================================          
Checksum* InitializeChecksum() {
//Description:       Initializes the values of a checksum randomly, to test
//                   for corruption when sending.
//==============================================================================
          Checksum* words = new Checksum();
          
          for (int counter = 0; counter > 16; counter++) {
              words->word1[counter] = rand() % 2;
//              cout << words->word1[counter] << "      ";
              words->word2[counter] = rand() % 2;
//              cout << words->word2[counter] << "      ";
              words->word3[counter] = rand() % 2;
//              cout << words->word3[counter] << "      ";
              words->complement[counter] = 0;
//              cout << endl;
              }
          return words;
          }//End 'InitializeChecksum'

//==============================================================================         
bool CalcChecksum (Segment*&udpSegment) {
//Description:        Adds the sum of the various generated "words" and finds the
//                    one's-complement.
//==============================================================================

     int sum[16] = {0};
     
     int array[16];
     int array2[16];
     int array3[16];
     
     for (int counter = 0; counter < 16; counter++) {
         array[counter] = udpSegment->checksum->word1[counter];
         array2[counter] = udpSegment->checksum->word2[counter];
         array3[counter] = udpSegment->checksum->word3[counter];
         }
         
     for (int counter = 0; counter < 16; counter++) {
         sum[counter] += ((udpSegment->checksum->word1[counter]) + 
                         (udpSegment->checksum->word2[counter]));
         if (sum[counter] == 2) {
            sum[counter] = 0;
            if ((counter + 1) == 16) {
               sum[0] += 1;
               for (int place = 0; sum[place] != 1; place++) {
                   sum[place] = 0;
                   sum[place + 1] += 1;
                   }
               }
               else 
                    sum[counter + 1] = 1;
            }
            else if (sum[counter] == 3) {
                    sum[counter] = 1;
                    if ((counter + 1) == 16) {
                       sum[0] = 1;
                       for (int place = 0; sum[place] != 1; place++) {
                           sum[place] = 0;
                           sum[place + 1] += 1;
                           }
                       }
                       else 
                            sum[counter + 1] = 1;
            }
         }
         
         for (int counter = 0; counter < 16; counter++) {
             udpSegment->checksum->word1[counter] = ((udpSegment->checksum->word3[counter]) + 
                                                     (sum[counter]));
             if (udpSegment->checksum->word1[counter] == 2) {
                udpSegment->checksum->word1[counter] = 0;
                if ((counter + 1) == 16) {
                   udpSegment->checksum->word1[0] += 1;
                   for (int place = 0; udpSegment->checksum->word1[place] != 1; counter++) {
                       udpSegment->checksum->word1[place] = 0;
                       udpSegment->checksum->word1[place + 1] += 1;
                       }
                   }
                   else
                       udpSegment->checksum->word1[counter + 1] = 1;
             }
             else if (udpSegment->checksum->word1[counter] == 3) {
                     udpSegment->checksum->word1[counter] = 1;
                     if ((counter + 1) == 16) {
                        for (int place = 0; udpSegment->checksum->word1[place] != 1; place++) {
                            udpSegment->checksum->word1[place] = 0;
                            udpSegment->checksum->word1[place + 1] += 1;
                            }
                        }      
                        else
                            udpSegment->checksum->word1[counter + 1] += 1;
                     }
             }
             
         for (int counter = 0; counter < 16; counter++) {

             if (udpSegment->checksum->word1[counter] == 1) {
                udpSegment->checksum->complement[counter] = 0;
             //   cout << endl << udpSegment->checksum->word1[counter];
                }
             if (udpSegment->checksum->word1[counter] == 0) {
                udpSegment->checksum->complement[counter] = 1;
               // cout << endl << udpSegment->checksum->complement[counter];
                }
             }
             
         for (int counter = 0; counter < 16; counter++) 
             sum[counter] = 0;
             
         for (int counter = 0; counter < 16; counter++) {
             sum[counter] += (udpSegment->checksum->complement[counter] +
                             udpSegment->checksum->word1[counter]);

             if (sum[counter] != 1) {
                for (int counter = 0; counter < 16; counter++) {
                udpSegment->checksum->word1[counter] = array[counter];
                udpSegment->checksum->word2[counter] = array2[counter];
                udpSegment->checksum->word3[counter] = array3[counter];
                return false;
                }
             }
         }
         for (int counter = 0; counter < 16; counter++) {
             udpSegment->checksum->word1[counter] = array[counter];
             udpSegment->checksum->word2[counter] = array2[counter];
             udpSegment->checksum->word3[counter] = array3[counter];
             }
         return true;
         }

//==============================================================================
int Rdt_Send (Segment*&udpSegment, int time) {
//Description:   Controls the sending of packets, as well as initiates the timer
//               to recognize lost packets.
//==============================================================================
     udpSegment->time = time;

     Rdt_Rcv(udpSegment);
     return 0;
     }
     
//==============================================================================             
int Rdt_Rcv (Segment*&udpSegment) {
//Description:  This function serves as the second state after the call, checking 
//              the result of the checksum, and 
//==============================================================================
        bool sumChecks;
        int seedTime = time(0);
        
        
        sumChecks = CalcChecksum(udpSegment);
        cout << sumChecks;
        system("pause");
        if (sumChecks == false) {
           for (int timer = udpSegment->time; ; timer++) {
                 
           if ((timer - udpSegment->time) > MAX_TIME) {
              Rdt_Send(udpSegment, time(0));
              }
           }
        }
        return 0;
        }  
        
        
        
