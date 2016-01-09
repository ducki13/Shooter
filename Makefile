# Makefile for SDL project

SDL2_CFLAGS  := $(shell sdl2-config --cflags)
SDL2_LDFLAGS := $(shell sdl2-config --libs) -lSDL2_image

CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -pedantic -O3 $(SDL2_CFLAGS)
LDFLAGS  = $(SDL2_LDFLAGS) -lz
LN       = ln

SRCDIR = Shooter
VPATH  = $(SRCDIR)

all: main

main: main.o Game.o AnimatedGraphic.o MenuButton.o Player.o Enemy.o     \
SDLGameObject.o GameObject.o LoaderParams.o TextureManager.o Vector2D.o \
InputHandler.o MainMenuState.o PauseState.o MenuState.o PlayState.o     \
GameOverState.o GameState.o GameStateMachine.o GameObjectFactory.o      \
StateParser.o Level.o LevelParser.o TileLayer.o                         \
tinyxml.o tinyxmlerror.o tinyxmlparser.o tinystr.o base64.o
	$(CXX) $^ -o $@ $(LDFLAGS)
	if ! [ -L assets ]; then $(LN) -s $(SRCDIR)/assets assets; fi

main.o: main.cpp Game.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

Game.o: Game.cpp Game.h AnimatedGraphic.o MenuButton.o Player.o Enemy.o \
InputHandler.o GameStateMachine.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

Player.o: Player.cpp Player.h SDLGameObject.o GameObjectFactory.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

Enemy.o: Enemy.cpp Enemy.h SDLGameObject.o GameObjectFactory.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

MenuButton.o: MenuButton.cpp MenuButton.h SDLGameObject.o GameObjectFactory.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

AnimatedGraphic.o: AnimatedGraphic.cpp AnimatedGraphic.h SDLGameObject.o GameObjectFactory.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

SDLGameObject.o: SDLGameObject.cpp SDLGameObject.h GameObject.o \
TextureManager.o Vector2D.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

GameObject.o: GameObject.cpp GameObject.h LoaderParams.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

LoaderParams.o: LoaderParams.cpp LoaderParams.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

TextureManager.o: TextureManager.cpp TextureManager.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Vector2D.o: Vector2D.cpp Vector2D.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

InputHandler.o: InputHandler.cpp InputHandler.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

MainMenuState.o: MainMenuState.cpp MainMenuState.h MenuState.o StateParser.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

PauseState.o: PauseState.cpp PauseState.h MenuState.o StateParser.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

MenuState.o: MenuState.cpp MenuState.h GameState.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

PlayState.o: PlayState.cpp PlayState.h GameState.o StateParser.o Level.o LevelParser.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

GameOverState.o: GameOverState.cpp GameOverState.h GameState.o StateParser.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

GameState.o: GameState.cpp GameState.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

GameStateMachine.o: GameStateMachine.cpp GameStateMachine.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

GameObjectFactory.o: GameObjectFactory.cpp GameObjectFactory.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

StateParser.o: StateParser.cpp StateParser.h tinyxml.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

LevelParser.o: LevelParser.cpp LevelParser.h Level.o TileLayer.o tinyxml.o base64.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

Level.o: Level.cpp Level.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

TileLayer.o: TileLayer.cpp TileLayer.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

tinyxml.o: tinyxml.cpp tinyxml.h tinyxmlerror.o tinyxmlparser.o tinystr.o
	$(CXX) $(CXXFLAGS) -c $< -o $@

tinyxmlerror.o: tinyxmlerror.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tinyxmlparser.o: tinyxmlparser.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tinystr.o: tinystr.cpp tinystr.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

base64.o: base64.cpp base64.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) main *.o assets
