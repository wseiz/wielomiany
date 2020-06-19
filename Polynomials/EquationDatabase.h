#pragma once

class EquationDatabase 
{
    private:
        std::map<char, Equation> db;
    public:
        EquationDatabase();
        void addEquation(char name, Equation& e);
        void deleteEquation(char name);
        double getValue(char name, double a);
        void printEquationIfExists(char& name);
        bool isEquationExists(char& name);
        Equation* getEquationByName(char& name);
};