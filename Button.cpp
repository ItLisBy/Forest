//
// Created by We on 14.02.21.
//

#include "Button.h"

Button::Button(const String &showed_text, const Vector2f &size, const Vector2f &position, const int &char_size,
               const Color &bg_color, const Color &text_color) {
    //Setting up showed text
    _text.setString(showed_text);
    _text.setCharacterSize(char_size);
    _text.setFillColor(text_color);
    _text.setOrigin(_text.getOrigin().x + _text.getLocalBounds().width / 2.0f,
                    _text.getOrigin().y + _text.getLocalBounds().height / 2.0f);
    _text.setPosition(size.x / 2.0f,
                      (size.y - _text.getLocalBounds().height) / 2.0f);

    //Setting up button view
    _button.setSize(size);
    _button.setFillColor(bg_color);
    _button.setPosition(position);
}

void Button::setFont(const Font &font) {
    //Set font
    _text.setFont(font);
}

void Button::changeBackColor(const Color &color) {
    //Set button's background color
    _button.setFillColor(color);
}

void Button::isClicked(const Vector2f &pos) {
    //Check is in button
    if(pos.x > _button.getPosition().x && pos.x < (_button.getPosition().x + _button.getSize().x)) {
        if(pos.y > _button.getPosition().y && pos.y < (_button.getPosition().y + _button.getSize().y)) {
            changeState(!_clicked);
        }
    }
}

void Button::changeState(const bool &curr) {
    _clicked = curr;
    if (_clicked) {
        changeBackColor(_button.getFillColor() - Color(40, 40, 40));
        return;
    }
    changeBackColor(_button.getFillColor() + Color(40, 40, 40));
}

Text Button::getText() {
    return _text;
}

RectangleShape Button::getShape() {
    return _button;
}

void Button::setPosition(const Vector2f &pos) {
    _button.setPosition(pos);
}
