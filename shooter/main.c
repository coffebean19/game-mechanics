#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "bullet.h"

#define MAX_BULLETS 100

static const int screen_width = 800;
static const int screen_height = 450;

// Player stuff
static Vector2 ball_position;
static float radius = 10.0f;
static Color ball_color = WHITE;

static Vector2 aim_position;

// Bullet stuff
static Vector2 bullet_position;
static Vector2 target_position;
static Color bullet_color = RED;
static bool bullet_active = false;
static float bullet_speed = 300.0f;
static Vector2 bullet_speed2 = { 0.0f, 0.0f};

// Magazine
static Bullet* bullets[MAX_BULLETS];

static float delta;

void UpdateBallPosition();
void FireBullet();
void FireBulletOld();


// DEPRECATED FUNCTIONS
void CalculateBulletTrajectory();
void CalculateBulletSpeed();
float NormalizeDegrees(float x);


char debug[150];

int main() {

    InitWindow(screen_width, screen_height, "Test 2D movement");
    EnableCursor();
    SetTargetFPS(60);

    ball_position.x = screen_width/2;
    ball_position.y = screen_height/2;


    while(!WindowShouldClose()) {

        delta = GetFrameTime();

        UpdateBallPosition();

        aim_position = GetMousePosition();

        if (bullet_active) {
            bullet_position.x = bullet_position.x + bullet_speed2.x * delta;
            bullet_position.y = bullet_position.y + bullet_speed2.y * delta;

            if (bullet_position.x < 0 || bullet_position.x > screen_width || bullet_position.y < 0 || bullet_position.y > screen_height) {
                bullet_active = false;
            } 
            sprintf(debug, "ball: (%f, %f), mouse: (%f, %f), angle: %.2f", ball_position.x, ball_position.y, aim_position.x, aim_position.y, atan((ball_position.y - aim_position.y) / (ball_position.x - aim_position.x)) * (180.0 / M_PI));
        }
        
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawCircle(ball_position.x, ball_position.y, radius, ball_color);
        DrawLine(ball_position.x, ball_position.y, aim_position.x, aim_position.y, WHITE);
        DrawRectangle(aim_position.x, aim_position.y, 10, 10, GREEN);
        if (bullet_active) {
         DrawRectangle(bullet_position.x, bullet_position.y, 5, 5, bullet_color);  
         DrawText(debug, 10, 10, 20, WHITE); 
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}   


void UpdateBallPosition() {
    float speed = 200.0f;
    if (IsKeyDown(KEY_W)) ball_position.y -= speed * delta;
    if (IsKeyDown(KEY_S)) ball_position.y += speed * delta;
    if (IsKeyDown(KEY_A)) ball_position.x -= speed * delta;
    if (IsKeyDown(KEY_D)) ball_position.x += speed * delta;
    if (IsKeyDown(KEY_SPACE)) {
        FireBullet();
    }
}

void CreateBullets() {
        for (int i = 0;i < MAX_BULLETS;i++) {
                bullets[i] = CreateBullet(
                        ball_position,
                        (Vector2) { 0.0f, 0.0f },
                        RED,
                        false,
                        bullet_speed,
                        bullet_speed2
             );
        }
}

void newFireBullet() {
        for (int i = 0;i < MAX_BULLETS;i++) {
                if (bullets[i]->is_active == false) {
                }
        }
}

void FireBullet() {
    bullet_active = true;
    
    bullet_position = ball_position;
    
    Vector2 direction = {
        aim_position.x - ball_position.x,
        aim_position.y - ball_position.y
    };
    
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
    
    if (length != 0.0f) {
        direction.x /= length;
        direction.y /= length;
    }
    
    bullet_speed2.x = direction.x * bullet_speed;
    bullet_speed2.y = direction.y * bullet_speed;
}


// DEPRECATED FUNCTIONS
void FireBulletOld() {
    bullet_active = true;
    bullet_position.x = ball_position.x;
    bullet_position.y = ball_position.y;
    target_position.x = aim_position.x;
    target_position.y = aim_position.y;

    // if (target_position.x > ball_position.x) {
    //     bullet_speed = 500.0f;
    // } else {
    //     bullet_speed = -500.0f;
    // }

    CalculateBulletTrajectory();
    CalculateBulletSpeed();
}


void CalculateBulletSpeed() {
    // y = -x + bullet_speed
    // - atan == arctan, atan gives back result in radians. Convert radians to degrees by * 180 / PI
    float angle = fabs(atan((ball_position.y - aim_position.y) / (ball_position.x - aim_position.x)) * (180.0 / M_PI));
    float norm_degree = NormalizeDegrees(angle);
    // x = 500 - (500 * norm_degree)

    bullet_speed2.x = bullet_speed - (bullet_speed * norm_degree);
    bullet_speed2.y = -1 * bullet_speed2.x + bullet_speed;

    if (ball_position.x > aim_position.x) {
        bullet_speed2.x *= -1;
    } 
    if (ball_position.y > aim_position.y) {
        bullet_speed2.y *= -1;
    }
}

float NormalizeDegrees(float x) {
    float normalized_degree = (x - 0) / 90 - 0;

    return normalized_degree;
}
