#ifndef func_h
#define func_h

enum moving_type
{
    MOVING_LEFT,
    MOVING_RIGHT,
    MOVING_UP,
    MOVING_DOWN
};

struct location_food
{
    int row;
    int col;
};

struct iron_man
{
    void (*skill_01)(void);
    void (*skill_02)(void);
    char *name;
};

void reset_map(void);
void create_new_snake(void);
void init_map(void);
void display_map(void);
void snake_run(char snake_direction);
void control_snake_run(void);
struct location_food *gen_randum_number(int row_min, int row_max, int col_min, int col_max);
struct location_food *check_snake_gen_food(struct location_food *snake_food, int limit);
void gen_food_ramdum(void);
void food_appear_randum(void);
#endif