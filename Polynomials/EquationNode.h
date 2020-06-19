#pragma once

class EquationNode 
{
    private:
        int base;
        int power;
    public:
        EquationNode(int, int);
    public:
        int getBase() const;
        int getPower() const;
        static bool sortByPowerAsc(EquationNode first, EquationNode second);
};