#pragma once

class CommandLineInput 
{
    public:
        static Equation* getEquationFromCommandLine(const std::string& command);
        static Equation* sumEquations(Equation& first, Equation& second);
        static Equation* substractEquations(Equation& first, Equation& second);
        static Equation* derivative(Equation& first);
        static double getDoubleFromCommand(const std::string& command);
        static Equation* multiplyEquations(Equation& first, Equation& second);
};