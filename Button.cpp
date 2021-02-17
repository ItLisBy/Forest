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
    _text.setPosition((size.x - _text.getGlobalBounds().width),
                      (size.y - _text.getLocalBounds().height) / 2.0f);

    //Setting up button view
    _shape.setSize(size);
    _shape.setFillColor(bg_color);
    _shape.setPosition(position);
}

void Button::setFont(const Font &font) {
    //Set font
    _text.setFont(font);
}

void Button::changeBackColor(const Color &color) {
    //Set button's background color
    _shape.setFillColor(color);
}

void Button::isClicked(const Vector2f &pos) {
    //Check is in button
    if(pos.x > _shape.getPosition().x && pos.x < (_shape.getPosition().x + _shape.getSize().x)) {
        if(pos.y > _shape.getPosition().y && pos.y < (_shape.getPosition().y + _shape.getSize().y)) {
            changeState(!_clicked);
        }
    }
}

void Button::changeState(const bool &curr) {
    _clicked = curr;
    if (_clicked) {
        changeBackColor(_shape.getFillColor() - Color(40, 40, 40));
        return;
    }
    changeBackColor(_shape.getFillColor() + Color(40, 40, 40));
}

Text Button::getText() {
    return _text;
}

RectangleShape Button::getShape() {
    return _shape;
}

void Button::setPosition(const Vector2f &pos) {
    _shape.setPosition(pos);
}

Button::Button(const Texture &img, const Vector2f &position) {
    _sprite.setTexture(img);

}
