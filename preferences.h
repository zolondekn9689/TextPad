#ifndef PREFERENCES_H
#define PREFERENCES_H
#include <QFont>

class Preferences
{
public:
    static Preferences* getInstance();

    //Following are getters and setters.
    void setTabWidth(int width);
    void setFontSize(int fontSize);
    int getTabWidth();
    int getFontSize();

private:
    static Preferences* inst_;
    Preferences();

    //The following are setting options.
    int fontSize;
    int tabWidth;
    QFont* font;

};



#endif // PREFERENCES_H
