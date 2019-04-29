#pragma once

//Simulation
const int FPS = 60; //SFML
const int simulationFPS = 180; //CHANGEABLE

//SFML Window
const int windowWidth = 1400;
const int windowHeight = 800;

//Board
const float boardWidth = 12100;
const float boardHeight = 7030; //3515*2;
const float	fillRatio = .95;

//const float interval = boardwidth / 9;

const float goalSize = 2150; //width of goal
const float slopeSize = 400; //CHANGEABLE //width of slope around borders
const float cornerSlopeReach = 1200;

//Ball
const float ballRadius = 175; //350 / 2;
const float ballAcc = 200; //CHANGEABLE //acceleration (deceleration) of ball due to friction - need to calculate

//Players
const float boxWidth = 120;
const float boxHeight = 210;
const float playerHeight = 500;

