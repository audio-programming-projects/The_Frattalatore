#include "Fractal.h"

Fractal::Fractal()
{
    
}
Fractal::~Fractal()
{

}

int Fractal::recursionsMandelbrot(double cr, double ci, int max_iterations) {
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    int numeroRicorsioni = 0;

    while (numeroRicorsioni < max_iter && parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ < 4.0)
    {
        double temp = parteRealeZ * parteRealeZ - parteImmaginariaZ * parteImmaginariaZ + cr;
        parteImmaginariaZ = 2.0 * parteRealeZ * parteImmaginariaZ + ci;
        parteRealeZ = temp;
        numeroRicorsioni++;
    }
    return numeroRicorsioni;
}

juce::Image Fractal::drawMandelbrotFractal() {
    juce::Image fractalImage = juce::Image(juce::Image::PixelFormat::RGB, W, H, true);
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            //calcolo gli intervalli del set 
            double cr = min_re + (max_re - min_re) * x / W;
            double ci = min_im + (max_im - min_im) * y / H;
            int n = recursionsMandelbrot(cr, ci, max_iter);
            int r = ((int)(n * sinf(n)) % 256);
            int g = ((n * 3) % 256);
            int b = (n % 256);
            fractalImage.setPixelAt(x, y, juce::Colour(r, g, b));
        }
    }
    return fractalImage;
}

juce::Image Fractal::drawJulia1Fractal() {
    juce::Image fractalImage = juce::Image(juce::Image::PixelFormat::RGB, W, H, true);
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            //calcolo gli intervalli del set 
            double cr = min_re + (max_re - min_re) * x / W;
            double ci = min_im + (max_im - min_im) * y / H;
            int n = recursionsMandelbrot(cr, ci, max_iter);
            int r = ((int)(n * sinf(n)) % 256);
            int g = ((n * 3) % 256);
            int b = (n % 256);
            fractalImage.setPixelAt(x, y, juce::Colour(r, g, b));
        }
    }
    return fractalImage;
}


juce::Image Fractal::drawJulia2Fractal() {
    juce::Image fractalImage = juce::Image(juce::Image::PixelFormat::RGB, W, H, true);
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            //calcolo gli intervalli del set 
            double cr = min_re + (max_re - min_re) * x / W;
            double ci = min_im + (max_im - min_im) * y / H;
            int n = recursionsMandelbrot(cr, ci, max_iter);
            int r = ((int)(n * sinf(n)) % 256);
            int g = ((n * 3) % 256);
            int b = (n % 256);
            fractalImage.setPixelAt(x, y, juce::Colour(r, g, b));
        }
    }
    return fractalImage;
}


juce::Image Fractal::drawBurningShipFractal() {
    juce::Image fractalImage = juce::Image(juce::Image::PixelFormat::RGB, W, H, true);
    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            //calcolo gli intervalli del set 
            double cr = min_re + (max_re - min_re) * x / W;
            double ci = min_im + (max_im - min_im) * y / H;
            int n = recursionsMandelbrot(cr, ci, max_iter);
            int r = ((int)(n * sinf(n)) % 256);
            int g = ((n * 3) % 256);
            int b = (n % 256);
            fractalImage.setPixelAt(x, y, juce::Colour(r, g, b));
        }
    }
    return fractalImage;
}


 juce::Image Fractal::drawFractal(const int choice)
{
     juce::Image img;
    switch (choice)
    {
    case 0: //Mandelbrot
        img = drawMandelbrotFractal();
        break;
    case 1: //Julia1
        img = drawJulia1Fractal();
        break;
    case 2: //Julia2
        img = drawJulia2Fractal();
        break;
    case 3:
        img = drawBurningShipFractal();
        break;
    default:
        break;
    }
    return img;
}
