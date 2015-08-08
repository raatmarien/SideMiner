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

#include <walker.h>

using namespace sf;

Walker::Walker(Vector2f startPosition, WalkerSettings *settings
               , b2World *world) {
    this->settings = settings;
    this->world = world;

    // Create appropiate body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(startPosition.x / settings->scale
                         , startPosition.y / settings->scale);
    bodyDef.fixedRotation = true;

    body = world->CreateBody(&bodyDef);

    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(settings->size.x / (2.0f * settings->scale)
                     , settings->size.y / (2.0f * settings->scale));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.1f;

    body->CreateFixture(&fixtureDef);
}

void Walker::walk(bool right) {
    body->ApplyForce(b2Vec2((right ? 1 : -1) * settings->speed, 0)
                     , body->GetWorldCenter(), true);
}

void Walker::jump() {
    body->ApplyForce(b2Vec2(0, -settings->jumpStrength)
                     , body->GetWorldCenter(), true);
}

Vector2f Walker::getPosition() {
    b2Vec2 bodyPos = body->GetPosition();
    bodyPos *= (float) (settings->scale);
    return Vector2f(bodyPos.x, bodyPos.y);
}
