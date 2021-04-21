#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

class Cell{
    public:
        bool alive;
        int incubation;           //Days of incubation before the cell is infectious
        bool infected;            // If the cell is infected or not
        int duration;             // How many days to finish and recover or to get worse
        int inmunity;             // How inmune the cell is to infection after recovery or not
        bool medication;          // If the cell has taken its medication or not
        bool quarantined;         // If the cell is in quarantine
        int state;
        int quaratineDays; 

        Cell();
        void infect(int, int);
    private:
};

#endif