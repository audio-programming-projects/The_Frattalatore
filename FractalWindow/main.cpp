#include <SFML/Graphics.hpp>
#include "MainMenu.hpp"
#include "Fractal.h"
#include "threeValuesArray.h"
#include "changeParameters.h"
#include "osc/OscOutboundPacketStream.h"
#include "osc/ip/UdpSocket.h"


#define ADDRESS "127.0.0.1"

#define OUTPUT_BUFFER_SIZE 1024
using namespace sf;

double zoom = 1.0;
double step = 20.0;

//static variables
static int x_fp = 0;
static int y_fp = 0;
float XoscToSend;
float YoscToSend;
int nIterationToSend;

int main()
{
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p1(buffer, OUTPUT_BUFFER_SIZE);
    osc::OutboundPacketStream p2(buffer, OUTPUT_BUFFER_SIZE);
    osc::OutboundPacketStream p3(buffer, OUTPUT_BUFFER_SIZE);
    osc::OutboundPacketStream p4(buffer, OUTPUT_BUFFER_SIZE);
    osc::OutboundPacketStream p5(buffer, OUTPUT_BUFFER_SIZE);

    UdpTransmitSocket transmitSocket1(IpEndpointName(ADDRESS, 7000));
    UdpTransmitSocket transmitSocket2(IpEndpointName(ADDRESS, 7001));
    UdpTransmitSocket transmitSocket3(IpEndpointName(ADDRESS, 7002));
    UdpTransmitSocket transmitSocket4(IpEndpointName(ADDRESS, 7003));
    UdpTransmitSocket transmitSocket5(IpEndpointName(ADDRESS, 7004));

    // Create the main window
    RenderWindow menu(VideoMode(800, 400), "Main Menu", Style::Default);
    MainMenu mainMenu(menu.getSize().x, menu.getSize().y);
    Image plotFrattale;
    Fractal mainFractal;
    double xNew = 0;
    double yNew = 0;
    static Event newEvent;
    threeValuesArray arrayOSC;
    Texture texture;
    Sprite sprite;
    changeParameters modifier;
    plotFrattale.create(mainFractal.getW(), mainFractal.getH());
    //set background
    RectangleShape background;
    background.setSize(Vector2f(800, 400));
    Texture Maintexture;
    Maintexture.loadFromFile("Images/Orange.jpg");
    background.setTexture(&Maintexture);
    while (menu.isOpen())
    {
        Event event;
        while (menu.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                menu.close();
                break;
            }


            else if (event.type == sf::Event::KeyReleased)
            {

                if (event.key.code == sf::Keyboard::Up)
                {

                    mainMenu.MoveUp();
                    break;
                }

                else if (event.key.code == sf::Keyboard::Down)
                {

                    mainMenu.MoveDown();
                    break;
                }

                else  if (event.key.code == sf::Keyboard::Enter)
                {

                  int scelta = mainMenu.getMainMenuPressed();

                  if (scelta == 0)
                  {
                      RenderWindow MandelWindow(VideoMode(600, 600), "Mandelbrot");
                      Fractal MandelFractal;
                      int iter = 0;
                      iter = MandelFractal.getMaxIter();
                      
                      while (MandelWindow.isOpen())
                      {
                          Event mandelEvent;
                          while (MandelWindow.pollEvent(mandelEvent))
                          {
                              if (mandelEvent.type == Event::Closed)
                              {
                                  MandelWindow.close();
                              }
                              if (mandelEvent.type == Event::KeyPressed)
                              {
                                  if (mandelEvent.key.code == Keyboard::Escape)
                                  {
                                      MandelWindow.close();
                                  }
                              }
                              
                              for (int y = 0; y < mainFractal.getH(); y++)
                              {
                                  for (int x = 0; x < mainFractal.getW(); x++)
                                  {
                                      double cr = MandelFractal.getMinRe() + (static_cast<double>(MandelFractal.getMaxRe()) - MandelFractal.getMinRe()) * x / MandelFractal.getW();
                                      double ci = MandelFractal.getMinIm() + (static_cast<double>(MandelFractal.getMaxIm()) - MandelFractal.getMinIm()) * y / MandelFractal.getH();
                                      int n = MandelFractal.ricorsioniMandelbrot(cr, ci, iter);
                                      Color c = MandelFractal.paint_fractal(n, iter);
                                      plotFrattale.setPixel(x, y, Color(c));
                                  }
                              }
                              texture.loadFromImage(plotFrattale);
                              sprite.setTexture(texture);
                              MandelWindow.draw(sprite);
                              MandelWindow.display();
                              
                              if (mandelEvent.type == Event::KeyPressed)
                              {
                                  if (mandelEvent.key.code == Keyboard::Enter)
                                  {
                                      const Vector2i mouse_pos = Mouse::getPosition(MandelWindow);
                                      MandelFractal.setXfp(mouse_pos.x);
                                      MandelFractal.setYfp(mouse_pos.y);

                                      if (MandelFractal.getXfp() > MandelFractal.getW() || MandelFractal.getYfp() > MandelFractal.getH() || MandelFractal.getXfp() < 0 || MandelFractal.getYfp() < 0)
                                      
                                      else
                                      {
                                          xNew = modifier.nuovaCoordinataX(MandelFractal.getXfp());
                                          yNew = modifier.nuovaCoordinataY(MandelFractal.getYfp());

                                          arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter);

                                           XoscToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[0].x;
                                           YoscToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[0].y;
                                           nIterationToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[0].numeroIterazioni;

                                           p1.Clear();
                                           p1 << osc::BeginMessage("/juce/osc1")
                                               << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend<< osc::EndMessage;
                                           transmitSocket1.Send(p1.Data(), p1.Size());

                                           XoscToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[1].x;
                                           YoscToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[1].y;
                                           nIterationToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[1].numeroIterazioni;

                                           p2.Clear();
                                           p2 << osc::BeginMessage("/juce/osc2")
                                               << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                           transmitSocket2.Send(p2.Data(), p2.Size());

                                           XoscToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[2].x;
                                           YoscToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[2].y;
                                           nIterationToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[2].numeroIterazioni;

                                           p3.Clear();
                                           p3 << osc::BeginMessage("/juce/osc3")
                                               << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                           transmitSocket3.Send(p3.Data(), p3.Size());

                                           XoscToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[3].x;
                                           YoscToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[3].y;
                                           nIterationToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[3].numeroIterazioni;

                                           p4.Clear();
                                           p4 << osc::BeginMessage("/juce/osc4")
                                               << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                           transmitSocket4.Send(p4.Data(), p4.Size());

                                           XoscToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[4].x;
                                           YoscToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[4].y;
                                           nIterationToSend = arrayOSC.calcoloMandelbrot(xNew, yNew, 5, iter)[4].numeroIterazioni;
                                           p5.Clear();
                                           p5 << osc::BeginMessage("/juce/osc5")
                                               << iter <<nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                           transmitSocket5.Send(p5.Data(), p5.Size());

                                      }
                                  }
                              }
                              
                              else if (mandelEvent.type == Event::MouseWheelScrolled)
                              {
                                  int newIter = 0;
                                  if (mandelEvent.MouseWheelScrolled)
                                  {
                                      if (mandelEvent.mouseWheelScroll.wheel == Mouse::VerticalWheel)
                                      {
                                          if (mandelEvent.mouseWheelScroll.delta > 0)
                                          {
                                              newIter = iter*2;
                                              iter = newIter;
                                              cout << "New max iterations: "<< iter <<endl;
                                          }
                                          else
                                          {
                                              newIter = iter /2;
                                              iter = newIter;
                                              cout << "New max iterations: "<< iter <<endl;
                                          
                                              if(iter < 1) iter = 1;
                                          }
                                      }
                                  }
                              }
                          }
                      }
                  }
                      
                   
            
                                     
                  else if (scelta == 1)
                  {
                      RenderWindow Julia1Window(VideoMode(600, 600), "Julia1");
                      Fractal julia1Fractal;
                      int iter = 0;
                      iter = julia1Fractal.getMaxIter();
                      
                      while (Julia1Window.isOpen())
                      {
                          Event julia1Event;
                          while (Julia1Window.pollEvent(julia1Event))
                          {
                              if (julia1Event.type == Event::Closed)
                              {
                                  Julia1Window.close();
                              }
                              if (julia1Event.type == Event::KeyPressed)
                              {
                                  if (julia1Event.key.code == Keyboard::Escape)
                                  {
                                      Julia1Window.close();
                                  }
                              }
                              
                              for (int y = 0; y < mainFractal.getH(); y++)
                              {
                                  for (int x = 0; x < mainFractal.getW(); x++)
                                  {
                                      double cr = julia1Fractal.getMinRe() + (static_cast<double>(julia1Fractal.getMaxRe()) - julia1Fractal.getMinRe()) * x / julia1Fractal.getW();
                                      double ci = julia1Fractal.getMinIm() + (static_cast<double>(julia1Fractal.getMaxIm()) - julia1Fractal.getMinIm()) * y / julia1Fractal.getH();
                                      int n = julia1Fractal.ricorsioniJuliaSet1(cr, ci, iter);
                                      Color c = julia1Fractal.paint_fractal(n, iter);
                                      plotFrattale.setPixel(x, y, Color(c));
                                  }
                              }
                              texture.loadFromImage(plotFrattale);
                              sprite.setTexture(texture);
                              Julia1Window.draw(sprite);
                              Julia1Window.display();
                              
                              if (julia1Event.type == Event::KeyPressed)
                              {
                                  if (julia1Event.key.code == Keyboard::Enter)
                                  {
                                      const Vector2i mouse_pos = Mouse::getPosition(Julia1Window);
                                      julia1Fractal.setXfp(mouse_pos.x);
                                      julia1Fractal.setYfp(mouse_pos.y);

                                      if (julia1Fractal.getXfp() > julia1Fractal.getW() || julia1Fractal.getYfp() > julia1Fractal.getH() || julia1Fractal.getXfp() < 0 || julia1Fractal.getYfp() < 0)

                                      else
                                      {
                                          xNew = modifier.nuovaCoordinataX(julia1Fractal.getXfp());
                                          yNew = modifier.nuovaCoordinataY(julia1Fractal.getYfp());

                                          arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter);

                                          XoscToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[0].x;
                                          YoscToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[0].y;
                                          nIterationToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[0].numeroIterazioni;

                                          p1.Clear();
                                          p1 << osc::BeginMessage("/juce/osc1")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket1.Send(p1.Data(), p1.Size());

                                          XoscToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[1].x;
                                          YoscToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[1].y;
                                          nIterationToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[1].numeroIterazioni;

                                          p2.Clear();
                                          p2 << osc::BeginMessage("/juce/osc2")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket2.Send(p2.Data(), p2.Size());

                                          XoscToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[2].x;
                                          YoscToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[2].y;
                                          nIterationToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[2].numeroIterazioni;

                                          p3.Clear();
                                          p3 << osc::BeginMessage("/juce/osc3")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket3.Send(p3.Data(), p3.Size());

                                          XoscToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[3].x;
                                          YoscToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[3].y;
                                          nIterationToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[3].numeroIterazioni;

                                          p4.Clear();
                                          p4 << osc::BeginMessage("/juce/osc4")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket4.Send(p4.Data(), p4.Size());

                                          XoscToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[4].x;
                                          YoscToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[4].y;
                                          nIterationToSend = arrayOSC.calcoloJuliaSet1(xNew, yNew, 5, iter)[4].numeroIterazioni;
                                          p5.Clear();
                                          p5 << osc::BeginMessage("/juce/osc5")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket5.Send(p5.Data(), p5.Size());

                                      }
                                  }
                              }
                              
                              else if (julia1Event.type == Event::MouseWheelScrolled)
                              {
                                  int newIter = 0;
                                  if (julia1Event.MouseWheelScrolled)
                                  {
                                      if (julia1Event.mouseWheelScroll.wheel == Mouse::VerticalWheel)
                                      {
                                          if (julia1Event.mouseWheelScroll.delta > 0)
                                          {
                                              newIter = iter*2;
                                              iter = newIter;
                                              cout << "New max iterations: "<< iter <<endl;
                                          }
                                          else
                                          {
                                              newIter = iter /2;
                                              iter = newIter;
                                              cout << "New max iterations: "<< iter <<endl;
                                          
                                              if(iter < 1) iter = 1;
                                          }
                                      }
                                  }
                              }
                          }
                      }
                  }
                
                  else if (scelta == 2)
                  {
                      RenderWindow Julia2Window(VideoMode(600, 600), "Julia2");
                      Fractal julia2Fractal;
                      int iter = 0;
                      iter = julia2Fractal.getMaxIter();
                      
                      while (Julia2Window.isOpen())
                      {
                          Event julia2Event;
                          while (Julia2Window.pollEvent(julia2Event))
                          {
                              if (julia2Event.type == Event::Closed)
                              {
                                  Julia2Window.close();
                              }
                              if (julia2Event.type == Event::KeyPressed)
                              {
                                  if (julia2Event.key.code == Keyboard::Escape)
                                  {
                                      Julia2Window.close();
                                  }
                              }
                              
                              for (int y = 0; y < mainFractal.getH(); y++)
                              {
                                  for (int x = 0; x < mainFractal.getW(); x++)
                                  {
                                      double cr = julia2Fractal.getMinRe() + (static_cast<double>(julia2Fractal.getMaxRe()) - julia2Fractal.getMinRe()) * x / julia2Fractal.getW();
                                      double ci = julia2Fractal.getMinIm() + (static_cast<double>(julia2Fractal.getMaxIm()) - julia2Fractal.getMinIm()) * y / julia2Fractal.getH();
                                      int n = julia2Fractal.ricorsioniJuliaSet2(cr, ci, iter);
                                      Color c = julia2Fractal.paint_fractal(n, iter);
                                      plotFrattale.setPixel(x, y, Color(c));
                                  }
                              }
                              texture.loadFromImage(plotFrattale);
                              sprite.setTexture(texture);
                              Julia2Window.draw(sprite);
                              Julia2Window.display();
                              
                              if (julia2Event.type == Event::KeyPressed)
                              {
                                  if (julia2Event.key.code == Keyboard::Enter)
                                  {
                                      const Vector2i mouse_pos = Mouse::getPosition(Julia2Window);
                                      julia2Fractal.setXfp(mouse_pos.x);
                                      julia2Fractal.setYfp(mouse_pos.y);

                                      if (julia2Fractal.getXfp() > julia2Fractal.getW() || julia2Fractal.getYfp() > julia2Fractal.getH() || julia2Fractal.getXfp() < 0 || julia2Fractal.getYfp() < 0)

                                      else
                                      {

                                          xNew = modifier.nuovaCoordinataX(julia2Fractal.getXfp());
                                          yNew = modifier.nuovaCoordinataY(julia2Fractal.getYfp());

                                          arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter);

                                          XoscToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[0].x;
                                          YoscToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[0].y;
                                          nIterationToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[0].numeroIterazioni;

                                          p1.Clear();
                                          p1 << osc::BeginMessage("/juce/osc1")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket1.Send(p1.Data(), p1.Size());

                                          XoscToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[1].x;
                                          YoscToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[1].y;
                                          nIterationToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[1].numeroIterazioni;

                                          p2.Clear();
                                          p2 << osc::BeginMessage("/juce/osc2")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket2.Send(p2.Data(), p2.Size());

                                          XoscToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[2].x;
                                          YoscToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[2].y;
                                          nIterationToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[2].numeroIterazioni;

                                          p3.Clear();
                                          p3 << osc::BeginMessage("/juce/osc3")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket3.Send(p3.Data(), p3.Size());

                                          XoscToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[3].x;
                                          YoscToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[3].y;
                                          nIterationToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[3].numeroIterazioni;

                                          p4.Clear();
                                          p4 << osc::BeginMessage("/juce/osc4")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket4.Send(p4.Data(), p4.Size());

                                          XoscToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[4].x;
                                          YoscToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[4].y;
                                          nIterationToSend = arrayOSC.calcoloJuliaSet2(xNew, yNew, 5, iter)[4].numeroIterazioni;
                                          p5.Clear();
                                          p5 << osc::BeginMessage("/juce/osc5")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket5.Send(p5.Data(), p5.Size());

                                      }
                                  }
                              }
                              
                              else if (julia2Event.type == Event::MouseWheelScrolled)
                              {
                                  int newIter = 0;
                                  if (julia2Event.MouseWheelScrolled)
                                  {
                                      if (julia2Event.mouseWheelScroll.wheel == Mouse::VerticalWheel)
                                      {
                                          if (julia2Event.mouseWheelScroll.delta > 0)
                                          {
                                              newIter = iter*2;
                                              iter = newIter;
                                              cout << "New max iterations: "<< iter <<endl;
                                          }
                                          else
                                          {
                                              newIter = iter /2;
                                              iter = newIter;
                                              cout << "New max iterations: "<< iter <<endl;
                                          
                                              if(iter < 1) iter = 1;
                                          }
                                      }
                                  }
                              }
                          }
                      }
                  }
                      
                    
                  else if (scelta == 3)
                  {
                      RenderWindow BurningShipWindow(VideoMode(600, 600), "Burning ship");
                      Fractal burningFractal;
                      int iter = 0;
                      iter = burningFractal.getMaxIter();
                      
                      while (BurningShipWindow.isOpen())
                      {
                          Event burningEvent;
                          while (BurningShipWindow.pollEvent(burningEvent))
                          {
                              if (burningEvent.type == Event::Closed)
                              {
                                  BurningShipWindow.close();
                              }
                              if (burningEvent.type == Event::KeyPressed)
                              {
                                  if (burningEvent.key.code == Keyboard::Escape)
                                  {
                                      BurningShipWindow.close();
                                  }
                              }

                              for (int y = 0; y < mainFractal.getH(); y++)
                              {
                                  for (int x = 0; x < mainFractal.getW(); x++)
                                  {
                                      double cr = burningFractal.getMinRe() + (static_cast<double>(burningFractal.getMaxRe()) - burningFractal.getMinRe()) * x / burningFractal.getW();
                                      double ci = burningFractal.getMinIm() + (static_cast<double>(burningFractal.getMaxIm()) - burningFractal.getMinIm()) * y / burningFractal.getH();
                                      int n = burningFractal.ricorsioniBurning_ship(cr, ci, iter);
                                      Color c = burningFractal.paint_fractal(n, iter);
                                      plotFrattale.setPixel(x, y, Color(c));
                                  }
                              }
                              texture.loadFromImage(plotFrattale);
                              sprite.setTexture(texture);
                              BurningShipWindow.draw(sprite);
                              BurningShipWindow.display();
                            
                              if (burningEvent.type == Event::KeyPressed)
                              {
                                  if (burningEvent.key.code == Keyboard::Enter)
                                  {
                                      const Vector2i mouse_pos = Mouse::getPosition(BurningShipWindow);
                                      burningFractal.setXfp(mouse_pos.x);
                                      burningFractal.setYfp(mouse_pos.y);

                                      if (burningFractal.getXfp() > burningFractal.getW() || burningFractal.getYfp() > burningFractal.getH() || burningFractal.getXfp() < 0 || burningFractal.getYfp() < 0)
                                     
                                      else
                                      {
                                          xNew = modifier.nuovaCoordinataX(burningFractal.getXfp());
                                          yNew = modifier.nuovaCoordinataY(burningFractal.getYfp());

                                          arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter);

                                          XoscToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[0].x;
                                          YoscToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[0].y;
                                          nIterationToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[0].numeroIterazioni;

                                          p1.Clear();
                                          p1 << osc::BeginMessage("/juce/osc1")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket1.Send(p1.Data(), p1.Size());

                                          XoscToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[1].x;
                                          YoscToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[1].y;
                                          nIterationToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[1].numeroIterazioni;

                                          p2.Clear();
                                          p2 << osc::BeginMessage("/juce/osc2")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket2.Send(p2.Data(), p2.Size());

                                          XoscToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[2].x;
                                          YoscToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[2].y;
                                          nIterationToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[2].numeroIterazioni;

                                          p3.Clear();
                                          p3 << osc::BeginMessage("/juce/osc3")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket3.Send(p3.Data(), p3.Size());

                                          XoscToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[3].x;
                                          YoscToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[3].y;
                                          nIterationToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[3].numeroIterazioni;

                                          p4.Clear();
                                          p4 << osc::BeginMessage("/juce/osc4")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket4.Send(p4.Data(), p4.Size());

                                          XoscToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[4].x;
                                          YoscToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[4].y;
                                          nIterationToSend = arrayOSC.calcoloBurninhShip(xNew, yNew, 5, iter)[4].numeroIterazioni;
                                          p5.Clear();
                                          p5 << osc::BeginMessage("/juce/osc5")
                                              << iter << nIterationToSend << (float)XoscToSend << (float)YoscToSend << osc::EndMessage;
                                          transmitSocket5.Send(p5.Data(), p5.Size());
                                      }
                                  }
                              
                              else if (burningEvent.type == Event::MouseWheelScrolled)
                              {
                                  int newIter = 0;
                                  if (burningEvent.MouseWheelScrolled)
                                  {
                                      if (burningEvent.mouseWheelScroll.wheel == Mouse::VerticalWheel)
                                      {
                                          if (burningEvent.mouseWheelScroll.delta > 0)
                                          {
                                              newIter = iter*2;
                                              iter = newIter;
                                              cout << "New max iterations: "<< iter <<endl;
                                          }
                                          else
                                          {
                                              newIter = iter /2;
                                              iter = newIter;
                                              cout << "New max iterations: "<< iter <<endl;
                                          
                                              if(iter < 1) iter = 1;
                                          }
                                      }
                                  }
                              }
                          }
                      }
                  }
                }
            }
        }
        
        menu.clear();
        menu.draw(background);
        mainMenu.draw(menu);
        menu.display();
    }
    return 0;
}
