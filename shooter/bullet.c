#include "raylib.h"
#include "bullet.h"

Bullet* CreateBullet(
        Vector2 bullet_position,
        Vector2 target_position,
        Color bullet_color,
        bool is_active,
        float bullet_speed,
        Vector2 bullet_speed2
) {
        Bullet* new_bullet = (Bullet*)malloc(sizeof(Bullet));
        if (!new_bullet) {
                printf("bullet creation unsuccessfull. fn -> CreateBullet(), bullet.c \n");
                return NULL;
        }

        new_bullet->bullet_position = bullet_position;
        new_bullet->target_position = target_position;
        new_bullet->bullet_color = bullet_color;
        new_bullet->is_active = is_active;
        new_bullet->bullet_speed = bullet_speed;
        new_bullet->bullet_speed2 = bullet_speed2;

        return new_bullet;
}

void DestroyBullet(Bullet* bullet) {
        free(bullet);
}
