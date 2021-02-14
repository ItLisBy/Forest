#ifndef FOREST_BUTTON_H
#define FOREST_BUTTON_H

#include "SFML/Graphics.hpp"

using namespace sf;

///
/// \brief Button class
///
class Button {
public:
    ///
    /// \param showed_text
    /// Text that will be showed on button
    /// \param size
    /// Size of button like Vector2
    /// \param char_size
    /// Size of text
    /// \param bg_color
    /// Color of button background
    /// \param text_color
    /// Color of text on button
    Button(const String &showed_text, const Vector2f &size, const int &char_size, const Color &bg_color, const Color &text_color);

    /// \bried
    /// Setting up font for text
    /// \param font
    /// Font that will be using
    void setFont(const Font &font);

    /// \brief
    /// Change button's background color
    /// \param color
    /// Color for background
    void changeBackColor(const Color &color);
private:
    RectangleShape _button;
    Text _text;
};


#endif //FOREST_BUTTON_H
