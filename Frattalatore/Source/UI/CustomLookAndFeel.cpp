/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 9 May 2022 5:48:58pm
    Author:  andre

  ==============================================================================
*/

#include "CustomLookAndFeel.h"
CustomLookAndFeel::CustomLookAndFeel()
{
    knobImage = juce::ImageCache::getFromMemory(BinaryData::Knob2_png, BinaryData::Knob2_pngSize);
    setColour(Label::textColourId, Colours::antiquewhite);
}

CustomLookAndFeel::~CustomLookAndFeel()
{
}

void CustomLookAndFeel::setValues(Image img, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    rotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
    frames = img.getHeight() / img.getWidth();
    frameId = (int)ceil(rotation * ((double)frames - 1.0));
    radius = jmin(width / 2.0f, height / 2.0f);
    centerX = x + width * 0.5f;
    centerY = y + height * 0.5f;
    rx = centerX - radius;
    ry = centerY - radius;
    rw = 2.0 * radius;
}

void CustomLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider& slider)
{
    if (knobImage.isValid())
    {
        setValues(knobImage, x, y, width, height, sliderPos, rotaryStartAngle, rotaryEndAngle, slider);
        g.setOpacity(1.0f);
        g.drawImage(knobImage, (int)rx, (int)ry, rw, rw, 0, frameId * knobImage.getWidth(), knobImage.getWidth(), knobImage.getWidth());
    }
    else
    {
        static const float textPpercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f, 0.5f * height, width * textPpercent, 0.5f * height);
        g.setColour(Colours::whitesmoke);
        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(), Justification::horizontallyCentred | Justification::centred, 1);
    }
}
