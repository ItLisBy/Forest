//
// Created by We on 14.02.21.
//

#include "Button.h"

Button::Button(const String &showed_text, const Vector2f &size, const int &char_size, const Color &bg_color, const Color &text_color) {
    //Setting up showed text
    _text.setString(showed_text);
    _text.setFillColor(text_color);
    _text.setCharacterSize(char_size);

    //Setting up button view
    _button.setSize(size);
    _button.setFillColor(bg_color);
}

void Button::setFont(const Font &font) {
    //Set font
    _text.setFont(font);
}

void Button::changeBackColor(const Color &color) {
    //Set button's background color
    _button.setFillColor(color);
}
