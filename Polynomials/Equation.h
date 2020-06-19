#pragma once

class Equation 
{
    private:
        std::list<EquationNode> factors; 
    public:
        explicit Equation(const  std::list<EquationNode>& factors);
        static bool checkNameOfEquation(char name);
        double calculate(double a);
        Equation* add(const Equation& another);
        Equation* multiply(const Equation& another);
        Equation* substract(const Equation& another);
        Equation* derivative();

        friend std::ostream& operator<<(std::ostream& o, const Equation& e) {
            int listSize = e.factors.size(); // sprawdza  czy jest to osatani factor z listy, jesli tak to wyswietla bez +
            int cos = 1;
            for (auto factor : e.factors) {
                if (cos == 1)
                {
                    if (factor.getPower() == 0) {
                        o << factor.getBase() << std::endl;
                        std::cout << "--------------------" << std::endl; //ZMIANA
                        cos++;
                    }
                    else if (factor.getPower() == 1) {
                        if (cos < listSize) {
                            o << factor.getBase() << "x";
                            cos++;
                        }
                        else {
                            o << factor.getBase() << "x";
                            std::cout << std::endl;
                            std::cout << "--------------------" << std::endl;
                        }
                    }
                    else {
                        if (cos < listSize) {
                            o << factor.getBase() << "x^" << factor.getPower();
                            cos++;
                        }
                        else {
                            o << factor.getBase() << "x^" << factor.getPower();
                            std::cout << std::endl;
                            std::cout << "--------------------" << std::endl;
                        }
                    }
                }
                else
                {
                    if (factor.getPower() == 0) {
                        if (factor.getBase() > 0)
                        {
                            o << "+" << factor.getBase() << std::endl;
                        }
                        else
                        {
                            o << " " << factor.getBase() << std::endl;
                        }
                        std::cout << "--------------------" << std::endl; //ZMIANA
                    }
                    else if (factor.getPower() == 1) {
                        if (cos < listSize) {
                            if (factor.getBase() > 0)
                            {
                                o << "+" << factor.getBase() << "x";
                            }
                            else
                            {
                                o << factor.getBase() << "x";
                            }
                            cos++;
                        }
                        else {
                            o << factor.getBase() << "x";
                            std::cout << std::endl;
                            std::cout << "--------------------" << std::endl;
                        }
                    }
                    else {
                        if (cos < listSize) {
                            if (factor.getBase() > 0)
                            {
                                o << "+" << factor.getBase() << "x^" << factor.getPower();
                            }
                            else
                            {
                                o << factor.getBase() << "x^" << factor.getPower();
                            }
                            cos++;
                        }
                        else {
                            if (factor.getBase() < 0)
                            {
                                o << factor.getBase() << "x^" << factor.getPower();
                                std::cout << std::endl;
                                std::cout << "--------------------" << std::endl;
                            }
                            else
                            {
                                o << "+" << factor.getBase() << "x^" << factor.getPower();
                                std::cout << std::endl;
                                std::cout << "--------------------" << std::endl;
                            }
                            cos++;   
                        }
                    }
                }
            }
            cos = 1;
            return o;
        }
};