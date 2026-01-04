#ifndef SIMULATION_H
#define SIMULATION_H

#include "raylib.h"

void InitSimulation(int screenWidth, int screenHeight);
void UpdateSimulation(float dt);
void DrawSimulation(void);
void CloseSimulation(void);
void AddBody(Vector2 pos, Vector2 vel, float mass, float radius, Color color);
void ResetSimulation(void);

#endif 
