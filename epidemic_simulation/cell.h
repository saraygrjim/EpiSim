#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

class Cell{
    public:
        //Estos tres son primordiales porque en cualquier ac es necesario alive y state y en caso de ser una epidemia es necesario el aprametro infected
        bool alive;
        int state;
        bool infected;            // If the cell is infected or not
        
        //Parámetros a partir de aquí
        int incubation;           //Days of incubation before the cell is infectious
        int duration;             // How many days to finish and recover or to get worse
        int inmunity;             // How inmune the cell is to infection after recovery or not
        bool medication;          // If the cell has taken its medication or not
        bool quarantined;         // If the cell is in quarantine
        int quaratineDays; 

        Cell();
        void infect(int, int);
    private:
};

#endif