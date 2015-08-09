/*
Copyright (C) 2015 Marien Raat

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

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

#include <chunk.h>
#include <chunkManager.h>
#include <player.h>
#include <walker.h>

#define SCALE 48

using namespace sf;

void loadFiles();

void setupChunkManager();
void setupPlayer();

void setWorldBoundaries(int width, int depth);

void handleEvents(RenderWindow *window);
void handleInput(RenderWindow *window);
void update(RenderWindow *window);
void simulatePhysics();
void draw(RenderWindow *window);

// Generic global variables
int screenSizeX = 1920, screenSizeY = 1080;
int worldSizeX, worldSizeY;

// Textures
Texture blocksTexture;
Texture playerTexture;

// Game objects
View view;
ChunkManager chunkManager;
Player player;

// Box2D settings
b2Vec2 gravity(0.0f, 20.0f);
b2World world(gravity);

float box2DTimeStep = 1.0f / 60.0f;
int velocityIterations = 8
    , positionIterations = 3;

Clock fpsTimer;

int main() {
    RenderWindow window(VideoMode(screenSizeX, screenSizeY), "Chunk test");
    window.setVerticalSyncEnabled(true);

    loadFiles();

    srand(time(NULL));

    setupChunkManager();
    setupPlayer();

    int framesForFps = -1;
    fpsTimer.restart();
    while (window.isOpen()) {
        if (framesForFps == 60) {
            float time = fpsTimer.restart().asSeconds();
            std::cout << "FPS: " << (int) (1.0f / (time / 60.0f) + 0.5f) << "\n";
            framesForFps = 0;
        }
        framesForFps++;

        simulatePhysics();
        handleEvents(&window);
        handleInput(&window);
        update(&window);
        draw(&window);
    }
}

void handleEvents(RenderWindow *window) {
    Event event;
    while (window->pollEvent(event)) {
        if (event.type == Event::Closed) {
            window->close();
        }
        if (event.type == Event::Resized) {
            screenSizeX = event.size.width;
            screenSizeY = event.size.height;
            view.setSize(screenSizeX, screenSizeY);
        }
    }
}

void handleInput(RenderWindow *window) {
    // Mouse input
    if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2i globalMousePosition = Mouse::getPosition(*window)
            + Vector2i(view.getCenter().x - (screenSizeX / 2)
                       , view.getCenter().y - (screenSizeY / 2));
        chunkManager.hitTile(globalMousePosition);
    }

    // Keyboard input
    if (Keyboard::isKeyPressed(Keyboard::W)
        || Keyboard::isKeyPressed(Keyboard::Up)) {
        player.walker->jump();
    }
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
        player.walker->jump();
    }
    if (Keyboard::isKeyPressed(Keyboard::S)
        || Keyboard::isKeyPressed(Keyboard::Down)) {
    }
    if (Keyboard::isKeyPressed(Keyboard::A)
        || Keyboard::isKeyPressed(Keyboard::Left)) {
        player.walker->walk(false);
    }
    if (Keyboard::isKeyPressed(Keyboard::D)
        || Keyboard::isKeyPressed(Keyboard::Right)) {
        player.walker->walk(true);
    }
}

void update(RenderWindow *window) {
    chunkManager.update(&view);
    player.update();
    view.setCenter(player.getPosition());
}

void simulatePhysics() {
    world.Step(box2DTimeStep, velocityIterations
               , positionIterations);
    world.ClearForces();
}

void draw(RenderWindow *window) {
    window->setView(view);
    window->clear(Color(143, 178, 255));
    chunkManager.draw(window);
    window->draw(player);
    window->display();
}

void loadFiles() {
    blocksTexture.loadFromFile("sprites/blocksTexture.png");
    playerTexture.loadFromFile("sprites/player.png");
}

void setupChunkManager() {
    ChunkSettings chunkSettings;
    chunkSettings.chunkSize = Vector2i(64, 64);
    chunkSettings.tileSize = Vector2i(16, 16);
    chunkSettings.tileTexSize = Vector2f(16, 16);
    chunkSettings.tilesPerWidthTex = 4;
    chunkSettings.scale = SCALE;
    chunkSettings.world = &world;

    WorldSettings worldSettings;
    worldSettings.worldSize = Vector2i(160, 80);
    worldSettings.chunkTexture = &blocksTexture;
    worldSettings.chunkSettings = chunkSettings;


    worldSizeX = chunkSettings.chunkSize.x * chunkSettings.tileSize.x * worldSettings.worldSize.x;
    worldSizeY = chunkSettings.chunkSize.y * chunkSettings.tileSize.y * worldSettings.worldSize.y;

    chunkManager.initialize(worldSettings);
}

void setupPlayer() {
    PlayerSettings playerSettings;

    playerSettings.walkerSettings.size = Vector2f(28, 48);
    playerSettings.walkerSettings.speed = 30.0f;
    playerSettings.walkerSettings.jumpStrength = 50.0f;
    playerSettings.walkerSettings.scale = SCALE;

    playerSettings.texture = &playerTexture;
    playerSettings.startPosition = Vector2f(0, 0);

    player.initialize(playerSettings, &world);
}

void setWorldBoundaries(int width, int depth) {

}
