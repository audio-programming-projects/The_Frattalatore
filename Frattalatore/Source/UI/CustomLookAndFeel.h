/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 9 May 2022 5:48:58pm
    Author:  andre

  ==============================================================================
*/

#pragma once
#pragma once
#include <JuceHeader.h>
using namespace juce;
class CustomLookAndFeel : public LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel();
    void setValues(Image img, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider);
    void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override;
private:
    Image knobImage;
    double rotation;
    int frames, frameId;
    float radius, centerX, centerY, rx, ry, rw;
};