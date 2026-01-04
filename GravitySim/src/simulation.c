#include "simulation.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Body {
    Vector2 pos;
    Vector2 vel;
    float mass;
    float radius;
    Color color;
} Body;

static Body *bodies = NULL;
static int bodyCount = 0;
static int scrW = 800, scrH = 600;

void InitSimulation(int screenWidth, int screenHeight) {
    scrW = screenWidth; scrH = screenHeight;
    bodyCount = 4;
    bodies = (Body*)malloc(sizeof(Body) * bodyCount);

    // Централно масивно тяло
    bodies[0].pos = (Vector2){scrW*0.5f, scrH*0.5f};
    bodies[0].vel = (Vector2){0,0};
    bodies[0].mass = 30000.0f;
    bodies[0].radius = 20.0f;
    bodies[0].color = GOLD;

    // Тела в орбита
    bodies[1].pos = (Vector2){scrW*0.5f + 120, scrH*0.5f};
    bodies[1].vel = (Vector2){0, -80};
    bodies[1].mass = 10.0f;
    bodies[1].radius = 6.0f;
    bodies[1].color = BLUE;

    bodies[2].pos = (Vector2){scrW*0.5f - 180, scrH*0.5f};
    bodies[2].vel = (Vector2){0, 60};
    bodies[2].mass = 20.0f;
    bodies[2].radius = 8.0f;
    bodies[2].color = RED;

    bodies[3].pos = (Vector2){scrW*0.5f + 220, scrH*0.5f - 40};
    bodies[3].vel = (Vector2){20, -40};
    bodies[3].mass = 5.0f;
    bodies[3].radius = 5.0f;
    bodies[3].color = GREEN;
}

void UpdateSimulation(float dt) {
    if (!bodies) return;
    const float G = 200.0f; // Калибрирана гравитационна константа

    // Изчисляване на сили между всички двойки
    for (int i = 0; i < bodyCount; i++) {
        Vector2 accel = {0,0};
        for (int j = 0; j < bodyCount; j++) {
            if (i == j) continue;
            float dx = bodies[j].pos.x - bodies[i].pos.x;
            float dy = bodies[j].pos.y - bodies[i].pos.y;
            float dist2 = dx*dx + dy*dy;
            float dist = sqrtf(dist2) + 0.001f;
            float force = G * bodies[j].mass / (dist2 + 25.0f); // омекотяване
            accel.x += force * dx / dist;
            accel.y += force * dy / dist;
        }
        bodies[i].vel.x += accel.x * dt;
        bodies[i].vel.y += accel.y * dt;
    }

    // Интегриране на позициите
    for (int i = 0; i < bodyCount; i++) {
        bodies[i].pos.x += bodies[i].vel.x * dt;
        bodies[i].pos.y += bodies[i].vel.y * dt;

        // Просто обвиване при граници
        if (bodies[i].pos.x < 0) bodies[i].pos.x += scrW;
        if (bodies[i].pos.x > scrW) bodies[i].pos.x -= scrW;
        if (bodies[i].pos.y < 0) bodies[i].pos.y += scrH;
        if (bodies[i].pos.y > scrH) bodies[i].pos.y -= scrH;
    }
}

void DrawSimulation(void) {
    if (!bodies) return;
    for (int i = 0; i < bodyCount; i++) {
        DrawCircleV(bodies[i].pos, bodies[i].radius, bodies[i].color);
    }
}

void CloseSimulation(void) {
    if (bodies) free(bodies);
    bodies = NULL;
    bodyCount = 0;
}

void AddBody(Vector2 pos, Vector2 vel, float mass, float radius, Color color) {
    Body *tmp = (Body*)realloc(bodies, sizeof(Body) * (bodyCount + 1));
    if (!tmp) return; // неуспешно заделяне на памет -> игнорирай
    bodies = tmp;
    bodies[bodyCount].pos = pos;
    bodies[bodyCount].vel = vel;
    bodies[bodyCount].mass = mass;
    bodies[bodyCount].radius = radius;
    bodies[bodyCount].color = color;
    bodyCount++;
}

void ResetSimulation(void) {
    CloseSimulation();
    InitSimulation(scrW, scrH);
}