#include "preferences.h"

Preferences *Preferences::inst_ = nullptr;

Preferences::Preferences()
{
    setTabWidth(4);
    setFontSize(8);
}

Preferences* Preferences::getInstance()
{
    if (inst_ == nullptr)
    {
        inst_ = new Preferences();
    }
    return inst_;
}

//FOLLOWING BELLOW THIS POINT ARE GETTERS AND SETTERS.
void Preferences::setTabWidth(int width)
{
    this->tabWidth = width;
}

void Preferences::setFontSize(int fontSize) {
    this->fontSize = fontSize;
}

int Preferences::getTabWidth() {
    return tabWidth;
}

int Preferences::getFontSize() {
    return fontSize;
}
