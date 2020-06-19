#include <utility>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <cmath>
#include <sstream>
#include <locale.h>
#include "EquationNode.h"
#include "Equation.h"
#include "EquationBuilder.h"
#include "CommandLineInput.h"
#include "EquationDatabase.h"
#include "App.h"

EquationNode::EquationNode(int base, int power) : base(base), power(power) {}

int EquationNode::getBase() const 
{
    return base;
}

int EquationNode::getPower() const 
{
    return power;
}

bool EquationNode::sortByPowerAsc(EquationNode first, EquationNode second) 
{
    return (int(first.power) > int(second.power));
}
//--------------------------------------------------------------------------------------

Equation::Equation(const std::list<EquationNode>& factors) 
{
    this->factors = *new std::list<EquationNode>;
    for (auto f : factors) 
    {
        if (f.getBase() != 0) 
        {
            this->factors.push_back(f);
        }
    }
    this->factors.sort(EquationNode::sortByPowerAsc);
}

bool Equation::checkNameOfEquation(char name) // Sprawdzanie nazwy wielomianu. Poprawnie wartoœæ od A-Z
{                    
    if (name == 'X' or !(name >= 'A' && name <= 'Z')) 
    {
        std::cout << "       Z³a nazwa wielomianu." << std::endl;
        std::cout << "--------------------" << std::endl;
        return false;
    }
    return true;
}

double Equation::calculate(double a) 
{
    double result = 0;
    for (auto node : factors) 
    {
        result += pow(a, node.getPower()) * node.getBase();
    }
    return result;
}

Equation* Equation::add(const Equation& another) 
{
    auto* newFactors = new std::list<EquationNode>;
    auto* all = new std::list<EquationNode>;
    for (auto& factor : this->factors) // A=B+C
    {                
        all->push_front(*new EquationNode(factor.getBase(), factor.getPower()));
    }
    for (auto factor : another.factors) 
    {
        all->push_front(*new EquationNode(factor.getBase(), factor.getPower()));
    }
    all->sort(EquationNode::sortByPowerAsc);
    std::list<EquationNode>::const_iterator it = all->begin();
    if (!all->empty()) 
    {
        int base = it->getBase();
        int power = it->getPower();
        it++;
        while (it != all->end()) // do metody ustawiajacej wielomiany
        {          
            if (it->getPower() != power) 
            {
                newFactors->push_front(*new EquationNode(base, power));
                base = it->getBase();
                power = it->getPower();
            }
            else 
            {
                base += it->getBase();
            }
            ++it;
        }
        newFactors->push_front(*new EquationNode(base, power));
    }
    newFactors->sort(EquationNode::sortByPowerAsc);
    auto newEquation = new Equation(*newFactors);
    return new Equation(*newFactors);
}

Equation* Equation::multiply(const Equation& another) 
{
    auto* newFactors = new std::list<EquationNode>;
    auto* all = new std::list<EquationNode>;
    for (auto& factor : this->factors) 
    {
        for (auto factor2 : another.factors) 
        {
            all->push_front(*new EquationNode(factor.getBase() * factor2.getBase(), factor.getPower() + factor2.getPower()));
        }
    }
    all->sort(EquationNode::sortByPowerAsc);

    std::list<EquationNode>::const_iterator it = all->begin();
    if (!all->empty()) 
    {
        int base = it->getBase();
        int power = it->getPower();
        it++;
        while (it != all->end())  // do metody ustawiajacej wielomiany
        {          
            if (it->getPower() != power) 
            {
                newFactors->push_front(*new EquationNode(base, power));
                base = it->getBase();
                power = it->getPower();
            }
            else 
            {
                base += it->getBase();
            }
            ++it;
        }
        newFactors->push_front(*new EquationNode(base, power));
    }

    newFactors->sort(EquationNode::sortByPowerAsc);
    auto newEquation = new Equation(*newFactors);
    return new Equation(*newFactors);
}

Equation* Equation::substract(const Equation& another) 
{
    auto* newFactors = new std::list<EquationNode>;
    auto* all = new std::list<EquationNode>;
    for (auto& factor : this->factors) 
    {
        all->push_front(*new EquationNode(factor.getBase(), factor.getPower()));
    }
    for (auto factor : another.factors) 
    {
        all->push_front(*new EquationNode(factor.getBase(), factor.getPower()));
    }
    all->sort(EquationNode::sortByPowerAsc);
    std::list<EquationNode>::const_iterator it = all->begin();
    if (!all->empty()) 
    {
        int base = it->getBase();
        int power = it->getPower();
        it++;
        while (it != all->end()) 
        {
            if (it->getPower() != power) 
            {
                newFactors->push_front(*new EquationNode(base, power));
                base = it->getBase();
                power = it->getPower();
            }
            else 
            {
                base -= it->getBase();
            }
            ++it;
        }
        newFactors->push_front(*new EquationNode(base, power));
    }
    newFactors->sort(EquationNode::sortByPowerAsc);
    auto newEquation = new Equation(*newFactors);
    return new Equation(*newFactors);
}

Equation* Equation::derivative() 
{
    auto* newFactors = new std::list<EquationNode>;
    for (auto& factor : this->factors) 
    {
        newFactors->push_front(*new EquationNode(factor.getBase() * factor.getPower(), factor.getPower() - 1));
    }
    newFactors->sort(EquationNode::sortByPowerAsc);
    auto newEquation = new Equation(*newFactors);
    return new Equation(*newFactors);
}

//-------------------------------------------------------------------------------------------------------------

EquationBuilder::EquationBuilder(std::list<int> params) : params(std::move(params)) {}

Equation* EquationBuilder::buildEquation() 
{
    if (params.size() % 2 == 1) 
    {
        std::cout << "       Wartoœci nie s¹ zgrupowane w parach.";
        std::cout << "--------------------" << std::endl;
        return nullptr;
    }
    int end1 = params.back();
    params.pop_back();
    int end2 = params.back();
    params.pop_back();
    if (end2 != 0 && end1 != 0) 
    {
        std::cout << std::endl << "       Równanie koñczy siê : " << end1 << end2;
        std::cout << "       parametry nie maj¹ wymaganego zakoñczenia par¹ 0 0!";
        std::cout << "--------------------" << std::endl;
        return nullptr;
    }
    auto nodes = new std::list<EquationNode>;
    while (!params.empty()) 
    {
        int base = params.front();
        params.pop_front();
        int power = params.front();
        params.pop_front();
        auto newNode = new EquationNode(base, power);
        nodes->push_front(*newNode);
    }
    return new Equation(*nodes);
}

//-----------------------------------------------------------------------------------

Equation* CommandLineInput::getEquationFromCommandLine(const std::string& command) 
{
    std::string numbers = command.substr(2);
    std::stringstream ss;
    ss.str(numbers);
    int base = 99;
    int power = 99;
    auto nodes = new std::list<int>;
    while (true) 
    {
        ss >> base;
        ss >> power;
        nodes->push_back(base);
        nodes->push_back(power);
        if (base == 0 && power == 0) break;
    }
    auto builder = new EquationBuilder(*nodes);
    return builder->buildEquation();
}

Equation* CommandLineInput::sumEquations(Equation& first, Equation& second) 
{
    return first.add(second);
}

Equation* CommandLineInput::substractEquations(Equation& first, Equation& second) 
{
    // return first.substract(second);
    return second.substract(first);
}

Equation* CommandLineInput::derivative(Equation& first) 
{
    return first.derivative();
}

double CommandLineInput::getDoubleFromCommand(const std::string& command) 
{
    return stod(command.substr(2));
}

Equation* CommandLineInput::multiplyEquations(Equation& first, Equation& second) 
{
    return first.multiply(second);
}

//-------------------------------------------------------------------------------------------

EquationDatabase::EquationDatabase() { db = *new std::map<char, Equation>; }

void EquationDatabase::addEquation(char name, Equation& e)
{
    if (!Equation::checkNameOfEquation(name)) return;
    if (db.find(name) != db.end()) 
    {
        std::cout << "       Znaleziono ju¿ równanie o nazwie \"" << name << "\"" << std::endl;
        std::cout << "       Równanie zostanie nadpisane." << std::endl;
        std::cout << "--------------------" << std::endl;
        db.erase(name);
    }
    db.insert(std::pair<char, Equation>(name, e));
}

void EquationDatabase::deleteEquation(char name)
{
    if (db.find(name) != db.end()) 
    {
        db.erase(name);
        std::cout << "       Usuniêto " << name << std::endl;
        std::cout << "--------------------" << std::endl;
    }
    else 
    {
        std::cout << "       Nie znaleziono " << name << " do usuniêcia." << std::endl;
        std::cout << "--------------------" << std::endl;
    }
}

double EquationDatabase::getValue(char name, double a) 
{
    if (db.find(name) != db.end()) 
    {
        return db.at(name).calculate(a);
    }
    std::cout << "       Nie znaleziono równania " << name << "." << std::endl;
    std::cout << "--------------------" << std::endl;
    return 0.0;
}

void EquationDatabase::printEquationIfExists(char& name) 
{
    auto it = db.find(name);
    if (it != db.end()) 
    {
        std::cout << it->first << "=" << it->second; // first i second
    }
    else 
    {
        std::cout << "       Nie znaleziono takiego równania." << std::endl;
        std::cout << "--------------------" << std::endl;
    }
}

bool EquationDatabase::isEquationExists(char& name) 
{
    if (db.find(name) != db.end()) return true;
    std::cout << "       Nie znaleziono równania" << name << "." << std::endl;
    std::cout << "--------------------" << std::endl;
    return false;
}

Equation* EquationDatabase::getEquationByName(char& name) 
{
    if (!Equation::checkNameOfEquation(name)) return nullptr;
    auto it = db.find(name);
    if (it != db.end()) 
    {
        return &(it->second);
    }
    else 
    {
        return nullptr;
    }
}

//----------------------------------------------------------------------------------------------

void App::start() 
{
    db = new EquationDatabase();
    printOptions();
    printMenuInLoop();
}

void App::printOptions() 
{
    //std::cout << "--------------------" << std::endl;
    std::cout << "A=     Ci¹g par zakoñczony par¹ 0 0 - definicja wielomianu" << std::endl;
    std::cout << "A=B+C  Sumowanie" << std::endl;
    std::cout << "A=B-C  Odejmowanie" << std::endl;
    std::cout << "A=B*C  Mno¿enie" << std::endl;
    std::cout << "A=B'   Ro¿niczkowanie" << std::endl;
    std::cout << "A?     Wydruk wielomianu" << std::endl;
    std::cout << "A(a)   Wartoœæ wielomianu dla x=a" << std::endl;
    std::cout << "A#     Usuwanie wielomianu" << std::endl;
    std::cout << "M!     Poka¿ menu" << std::endl;
    std::cout << "#      Koniec" << std::endl;
    std::cout << "--------------------" << std::endl;
}

bool App::doCommand(std::string& command)
{
    checkIfUserWantsToExit(command);
    return doSingleOperandCommand(command) or doMultipleOperandsCommand(command);
}

bool App::doSingleOperandCommand(std::string command) 
{
    if (!Equation::checkNameOfEquation(command[0])) return true;
    if (command[1] == '#') 
    {
        db->deleteEquation(command[0]);
        return true;
    }
    else if (command[1] == '?') 
    {
        db->printEquationIfExists(command[0]);
        return true;
    }
    else if (command[1] == '(') 
    {
        double value = CommandLineInput::getDoubleFromCommand(command);
        std::cout << command[0] << "(" << db->getValue(command[0], value) << ") = " << db->getValue(command[0], value) << std::endl;
        std::cout << "--------------------" << std::endl;
        return true;
    }
    else if (command[1] == '!') 
    {
        printOptions();
        return true;
    }
    return false;
}

bool App::doMultipleOperandsCommand(std::string& command) 
{
    if (command[1] != '=') return false;
    if (checkIfUserWantsToUseMathOperations(command)) return true;
    auto equation = CommandLineInput::getEquationFromCommandLine(command);
    db->addEquation(command[0], *equation);
    return true;
}

bool App::checkIfUserWantsToUseMathOperations(std::string& command) 
{
    char operationChar = command.at(3);
    Equation* first;
    Equation* second;
    Equation* result;
    char& firstEquationName = command[2];
    switch (operationChar) 
    {
        case '+':
            if (!db->isEquationExists(command[4]))
                return true;
            first = db->getEquationByName(firstEquationName);
            second = db->getEquationByName(command[4]);
            result = CommandLineInput::sumEquations(*first, *second);
            break;
        case '-':
            if (!db->isEquationExists(command[4]))
                return true;
            first = db->getEquationByName(firstEquationName);
            second = db->getEquationByName(command[4]);
            result = CommandLineInput::substractEquations(*first, *second);
            break;
        case '\'':
            first = db->getEquationByName(firstEquationName);
            result = CommandLineInput::derivative(*first);
            break;
        case '*':
            if (!db->isEquationExists(command[4]))
                return true;
            first = db->getEquationByName(firstEquationName);
            second = db->getEquationByName(command[4]);
            result = CommandLineInput::multiplyEquations(*first, *second);
            break;
        default:
            return false;
    }
    if (!db->isEquationExists(firstEquationName))
        return true;
    db->addEquation(command[0], *result);
    return true;
}

void App::checkIfUserWantsToExit(std::string line) 
{
    if (line[0] == '#') 
    {
        std::cout << "       Dziêkujemy za skorzystanie z programu." << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        exit(0);
    }
}

void App::printMenuInLoop() 
{
    while (true) 
    {
        std::string line;
        getline(std::cin, line);
        if (line.length() == 3)
        {
            std::cout << "--------------------" << std::endl;
            std::cout << "       B³¹d wykonania komendy" << std::endl;
            std::cout << "--------------------" << std::endl;
            App::printMenuInLoop();
        }
        else 
        {
            std::cout << "--------------------" << std::endl;
            if (!doCommand(line)) 
            {
                std::cout << "       B³¹d wykonania komendy" << std::endl;
                std::cout << "--------------------" << std::endl;
            }
        }
    }
}
