#pragma once

class App 
{
    public:
        void start();
    private:
        EquationDatabase* db;
        static void printOptions();
        bool doCommand(std::string& command);
        bool doSingleOperandCommand(std::string command);
        bool doMultipleOperandsCommand(std::string& command);
        bool checkIfUserWantsToUseMathOperations(std::string& command);
        static void checkIfUserWantsToExit(std::string line);
        void printMenuInLoop();
};