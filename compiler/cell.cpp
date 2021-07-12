#include <stdlib.h>
#include <time.h>
#include "cell.h"

// class Cell{
//    public:
//     bool alive;
//     int incubation;           //Days of incubation before the cell is infectious
//     bool infected;            // If the cell is infected or not
//     int duration;             // How many days to finish and recover or to get worse
//     int inmunity;             // How inmune the cell is to infection after recovery or not
//     bool medication;          // If the cell has taken its medication or not
//     bool quarantined;         // If the cell is in quarantine
//     int state;
//     int quaratineDays; 

//     Cell();
//     void infect(int, int);

// };


// Cell::Cell (){
//     alive         = true;
//     state         = 0;
//     infected      = false;       // If the cell is infected or not

//     //Parámetros a partir de aquí
//     incubation    = -1;          // Days of incubation before the cell is infectious
//     duration      = -1;          // How many days to finish and recover or to get worse
//     inmunity      = -1;          // How inmune the cell is to infection after recovery or not
//     medication    = false;       // If the cell has taken its medication or not
//     quarantined   = false;       // If the cell is in quarantine
//     quaratineDays = -1;
// }

// //Cell become infected  
// void Cell::infect(int incubation, int duration){
//     infected   = true;
//     state      = 1;
//     incubation = incubation;
//     duration   = duration;
// }

// // Cell become recovered
// void recover(int inmunity){
//     // print("me he recuperado")
//     infected = false;
//     incubation = -1;
//     duration   = -1;
//     inmunity   = inmunity;
//     state      = 3;
// }

// void die(){
//     alive    = false;
//     infected = false;
//     duration = -1;
//     state    = 5;
// }

// void quarantine(){
//     quarantined   = true;
//     state         = 4;
//     quaratineDays = 10;
// }

// // bool medicate(double medEfficacy){
// //     srand(time(NULL));
// //     double num = (rand() % (1001))/1000.0;
// //     if (num < medEfficacy) {
// //         return true; // The medication works and the cell recover
// //     } else {
// //         medication = true;
// //         return false; // The medication doesn't work and the cell stay infected
// //     }
// // }

// int process(double deadliness){
//     if(infected){
//         if (incubation > 0) {
//             incubation = incubation - 1;
//             return 0; // The cell stay incubating
//         } else {
//             state = 2;  // Red Ya ha incubado el virus por lo que ya es infeccioso
//             if (duration > 0) {
//                 duration = duration - 1;
//                 return 3; // The cell stay infected
//             } else { // If the virus has been incubated and the duration of the disease ends
//                 srand(time(NULL));
//                 double num = (rand() % (1001))/1000.0;
//                 if (num > deadliness) {
//                     return 1; // The cell recovers
//                 } else {
//                     return 2; // The cell dies
//                 }
//             }
//         }
//     }
//     return -1;
// }



// int processQuarantine(double quarentEfficacy){
//     if (quaratineDays > 0) {
//         quaratineDays = quaratineDays - 1;
//         return 3;  // The cell stay in quarantine
//     }else{
//         quaratineDays = -1;
//         quarantined = false;
//         srand(time(NULL));
//         double num = (rand() % (1001))/1000.0;
//         if (num < quarentEfficacy) {
//             return 1; // The cell recovers
//         }else{
//             if(incubation > 0) { state = 1;}
//             else { state = 2; }
//             return 2; // The cell stay infected
//         }
//     }
// }

