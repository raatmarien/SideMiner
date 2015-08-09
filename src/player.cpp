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

#include <player.h>

using namespace sf;

void Player::initialize(PlayerSettings settings, b2World *world) {
    texture = settings.texture;
    sprite.setTexture(*texture);
    setOrigin(settings.walkerSettings.size / 2.0f);

    walker = new Walker(settings.startPosition
                        , settings.walkerSettings, world);
}

void Player::update() {
    setPosition(walker->getPosition());
}

void Player::draw(RenderTarget &target, RenderStates states) const {
    states.transform *= getTransform();
    target.draw(sprite, states);
}
