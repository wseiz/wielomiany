#include <utility>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <cmath>
#include <sstream>
#include <locale.h>
#include "../Polynomials/EquationNode.h"
#include "../Polynomials/Equation.h"
#include "../Polynomials/EquationBuilder.h"
#include "../Polynomials/CommandLineInput.h"
#include "../Polynomials/EquationDatabase.h"
#include "../Polynomials/App.h"

int main()
{
    setlocale(LC_ALL, "");
    std::cout << "       Operacje na wielomianach 1 zmiennej" << std::endl;
    std::cout << std::endl;
    std::cout << "--------------------" << std::endl;
    auto app = new App();
    app->App::start();
    return 0;
}