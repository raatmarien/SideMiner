/*
Copyright (C) 2015  Marien Raat

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <SFML/Graphics.hpp> // For using the correct vectors
#include <Box2D/Box2D.h>

#include <iostream>

struct WalkerSettings {
    sf::Vector2f size;
    float speed;
    float jumpStrength;
    int scale;
};

class Walker {
public:
    Walker(sf::Vector2f startPosition, WalkerSettings *settings
           , b2World *world);
    void walk(bool right);
    void jump();
    sf::Vector2f getPosition();
private:
    b2World *world;
    b2Body *body;
    WalkerSettings *settings;
};
