//
// Created by We on 14.02.21.
//

#include "Button.h"

Button::Button(const String &id, const Texture &img, const IntRect &text_area, const IntRect &background_area, // NOLINT(cppcoreguidelines-pro-type-member-init)
               const Vector2f &position) {
    name_ = id;
    text_area_ = text_area;
    background_area_ = background_area;

    text_.setTexture(img);
    text_.setTextureRect(text_area_);
    text_.setPosition(position);

    background_.setTexture(img);
    background_.setTextureRect(background_area_);
    background_.setPosition(position);

}

void Button::changeBackground(const IntRect &background_area) {
    //Set button's background color
    background_.setTextureRect(background_area);
    background_area_ = background_area;
}

bool Button::isClicked(const Vector2i &pos) {
    //Check is in button
    if (clicked_) {
        changeState(false);
    }
    else if (pos.x > text_.getPosition().x && pos.x < (text_.getPosition().x + text_.getLocalBounds().width)) {
        if (pos.y > text_.getPosition().y && pos.y < (text_.getPosition().y + text_.getLocalBounds().height)) {
            changeState(true);
        }
    }
    return clicked_;
}

void Button::changeState(const bool &curr) {
    clicked_ = curr;
    if (clicked_) {
        background_.setColor(Color(204, 228, 247));
        return;
    }
    background_.setColor(Color::White);
}

Sprite Button::getDrawable() {
    return text_;
}

void Button::setPosition(const Vector2f &pos) {
    text_.setPosition(pos);
    background_.setPosition(pos);
}

void Button::setText(const IntRect &text_area) {
    text_area_ = text_area;
    text_.setTextureRect(text_area_);
}

void Button::draw(RenderTarget &target, sf::RenderStates states) const {
    target.draw(background_, states);
    target.draw(text_, states);
}

void Button::update() {

}

String Button::getName(){
    return name_;
}

