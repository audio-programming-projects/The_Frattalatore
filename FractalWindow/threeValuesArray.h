#pragma once
#include <vector>


class threeValuesArray
{
    //threeValuesArray();

    //couple of coordinates + number of iterations
    struct threeValues
    {
        double x;
        double y;
        int numeroIterazioni;
    };

public:
    std::vector <threeValues> calcoloMandelbrot(double cr, double ci, int iterazioni_user, int bellaiterazione);
    std::vector <threeValues> calcoloJuliaSet1(double cr, double ci, int iterazioni_user, int bellaiterazione);
    std::vector <threeValues> calcoloJuliaSet2(double cr, double ci, int iterazioni_user, int bellaiterazione);
    std::vector <threeValues> calcoloBurninhShip(double cr, double ci, int iterazioni_user, int bellaiterazione);
   // void stampaThreevalues(threeValues vectorToPrint);

private:
 
};

