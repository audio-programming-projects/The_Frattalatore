#include "threeValuesArray.h"
#include <vector>
#include <iostream>
#include "Fractal.h"

Fractal fractal;

std::vector<threeValuesArray::threeValues> threeValuesArray::calcoloMandelbrot(double cr, double ci, int iterazioni_user, int bellaiterazione)
{
    int numeroRicorsioni = 0;
    double parteRealeZ = 0, parteImmaginariaZ = 0;

    std::vector <threeValues> threeValuesArray;

    while (numeroRicorsioni < iterazioni_user) {

        //calculate elements
        double temp = parteRealeZ * parteRealeZ - parteImmaginariaZ * parteImmaginariaZ + cr;
        parteImmaginariaZ = 2.0 * parteRealeZ * parteImmaginariaZ + ci;
        parteRealeZ = temp;
        numeroRicorsioni++;

        //calculate number of iterations for each element
        double parteRealeZ1 = 0, parteImmaginariaZ1 = 0;
        int cr1 = parteRealeZ;
        int ci1 = parteImmaginariaZ;
        int numeroRicorsioniperelemento = 0;
        while (numeroRicorsioniperelemento < bellaiterazione && parteRealeZ1 * parteRealeZ1 + parteImmaginariaZ1 * parteImmaginariaZ1 < 4.0)
        {
            double temp = parteRealeZ1 * parteRealeZ1 - parteImmaginariaZ1 * parteImmaginariaZ1 + cr1;
            parteImmaginariaZ1 = 2.0 * parteRealeZ1 * parteImmaginariaZ1 + ci1;
            parteRealeZ1 = temp;
            numeroRicorsioniperelemento++;
        }
        
        //push into array of elements with its number of iterations
        threeValuesArray.push_back({ parteRealeZ,parteImmaginariaZ, numeroRicorsioniperelemento });
    }

    return threeValuesArray;
}

std::vector<threeValuesArray::threeValues> threeValuesArray::calcoloJuliaSet1(double cr, double ci, int iterazioni_user, int bellaiterazione)
{
    double parteRealeC = -0.7269, parteImmaginariaC = 0.1889; // starting c constant of the set
    int numeroRicorsioni = 0;
    
    std::vector <threeValues> threeValuesArray;

    //number of iterations for the first element
    int numeroRicorsioni_first = 0;
    int cr0 = cr;
    int ci0 = ci;
    while (numeroRicorsioni_first < bellaiterazione && cr0 * cr0 + ci0 * ci0 < 4.0)
    {
        double tempX = cr0 * cr0 - ci0 * ci0 + parteRealeC;
        double tempY = 2.0 * cr0 * ci0 + parteImmaginariaC;
        cr0 = tempX;
        ci0 = tempY;
        numeroRicorsioni_first++;
    }
   
    threeValuesArray.push_back({ cr,ci,numeroRicorsioni_first });
    
    //calculate elements
    while (numeroRicorsioni < iterazioni_user - 1)
    {
        double tempX = cr * cr - ci * ci + parteRealeC;
        double tempY = 2.0 * cr * ci + parteImmaginariaC;
        cr = tempX;
        ci = tempY;
        numeroRicorsioni++;

        //calculate number of iterations for each element
        int cr1 = cr;
        int ci1 = ci;
        int numeroRicorsioniperelemento = 0;
        while (numeroRicorsioniperelemento < bellaiterazione && cr1 * cr1 + ci1 * ci1 < 4.0)
        {
            double tempX = cr1 * cr1 - ci1 * ci1 + parteRealeC;
            double tempY = 2.0 * cr1 * ci1 + parteImmaginariaC;
            cr1 = tempX;
            ci1 = tempY;
            numeroRicorsioniperelemento++;
        }
        
        //push into array of elements with its number of iterations
        threeValuesArray.push_back({ cr,ci, numeroRicorsioniperelemento });

    }

    return threeValuesArray;
}

std::vector<threeValuesArray::threeValues> threeValuesArray::calcoloJuliaSet2(double cr, double ci, int iterazioni_user, int bellaiterazione)
{
    double parteRealeC = 0.285, parteImmaginariaC = 0.01; // starting c constant of the set
    int numeroRicorsioni = 0;
    
    std::vector <threeValues> threeValuesArray;

    //number of iterations for the first element
    int numeroRicorsioni_first = 0;
    int cr0 = cr;
    int ci0 = ci;
    while (numeroRicorsioni_first < bellaiterazione && cr0 * cr0 + ci0 * ci0 < 4.0)
    {
        double tempX = cr0 * cr0 - ci0 * ci0 + parteRealeC;
        double tempY = 2.0 * cr0 * ci0 + parteImmaginariaC;
        cr0 = tempX;
        ci0 = tempY;
        numeroRicorsioni_first++;
    }
    threeValuesArray.push_back({ cr,ci,numeroRicorsioni_first });
    
    //calculate elements
    while (numeroRicorsioni < iterazioni_user - 1)
    {
        double tempX = cr * cr - ci * ci + parteRealeC;
        double tempY = 2.0 * cr * ci + parteImmaginariaC;
        cr = tempX;
        ci = tempY;
        numeroRicorsioni++;

        //calculate number of iterations for each element
        int cr1 = cr;
        int ci1 = ci;
        int numeroRicorsioniperelemento = 0;
        while (numeroRicorsioniperelemento < bellaiterazione && cr1 * cr1 + ci1 * ci1 < 4.0)
        {
            double tempX = cr1 * cr1 - ci1 * ci1 + parteRealeC;
            double tempY = 2.0 * cr1 * ci1 + parteImmaginariaC;
            cr1 = tempX;
            ci1 = tempY;
            numeroRicorsioniperelemento++;
        }
        //push into array of elements with its number of iterations
        threeValuesArray.push_back({ cr,ci, numeroRicorsioniperelemento });
 
    }

    return threeValuesArray;
}


std::vector<threeValuesArray::threeValues> threeValuesArray::calcoloBurninhShip(double cr, double ci, int iterazioni_user, int bellaiterazione)
{
    int numeroRicorsioni = 0;
    
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    std::vector <threeValues> threeValuesArray;

    while (numeroRicorsioni < iterazioni_user) {

        //calculate elements
        double temp = parteRealeZ * parteRealeZ - parteImmaginariaZ * parteImmaginariaZ + cr;
        parteImmaginariaZ = 2.0 * abs(parteRealeZ * parteImmaginariaZ) + ci;
        parteRealeZ = temp;
        numeroRicorsioni++;
        
        //calculate number of iterations for each element
        double parteRealeZ1 = 0, parteImmaginariaZ1 = 0;
        int cr1 = parteRealeZ;
        int ci1 = parteImmaginariaZ;
        int numeroRicorsioniperelemento = 0;
        while (numeroRicorsioniperelemento < bellaiterazione && parteRealeZ1 * parteRealeZ1 + parteImmaginariaZ1 * parteImmaginariaZ1 < 4.0)
        {
            double temp = parteRealeZ1 * parteRealeZ1 - parteImmaginariaZ1 * parteImmaginariaZ1 + cr1;
            parteImmaginariaZ1 = 2.0 * abs(parteRealeZ1 * parteImmaginariaZ1) + ci1;
            parteRealeZ1 = temp;
            numeroRicorsioniperelemento++;
        }
        
        //push into array of elements with its number of iterations
        threeValuesArray.push_back({ parteRealeZ,parteImmaginariaZ, numeroRicorsioniperelemento });
        
    return threeValuesArray;
}




