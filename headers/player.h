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

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include <walker.h>

#include <iostream>

struct PlayerSettings {
    WalkerSettings walkerSettings;
    sf::Texture *texture;
    sf::Vector2f startPosition;
};

class Player
: public sf::Transformable
, public sf::Drawable {
public:
    void initialize(PlayerSettings settings, b2World *world);
    void update();
    Walker *walker;
private:
    sf::Texture *texture;
    sf::Sprite sprite;

    virtual void draw(sf::RenderTarget &target
                      , sf::RenderStates states) const;
};
