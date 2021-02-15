#ifndef FOREST_BUTTON_H
#define FOREST_BUTTON_H

#include "SFML/Graphics.hpp"

using namespace sf;

/// \brief Button class
///
class Button {
public:
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
    Button(const String &showed_text, const Vector2f &size, const Vector2f &position, const int &char_size,
           const Color &bg_color, const Color &text_color = Color(0, 0, 0));

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

    /// \brief
    /// Check is pos in button
    /// \param pos
    /// Position that is checked
    void isClicked(const Vector2f &pos);

    /// \brief
    /// Change state of button to curr(-ent)
    /// \param curr
    /// True - pressed;
    /// False - unpressed
    void changeState(const bool &curr);

    /// \brief
    /// Set new text for button
    /// \param text
    /// New text
    void setText(const Text &text);

    /// \brief
    /// Set position of button
    /// \param pos
    /// New position of button
    void setPosition(const Vector2f &pos);

    ///
    /// \return
    /// Text that is showing on button
    Text getText();

    ///
    /// \return
    /// Drawable shape on button
    RectangleShape getShape();
private:
    RectangleShape _button;
    Text _text;
    bool _clicked = false;
};


#endif //FOREST_BUTTON_H
