#include "graphics.hpp"
#include "cstdlib"
#include "ctime"

using namespace genv;
using namespace std;

const int WIDTH = 600;
const int HEIGHT = 400;
const int CELL_SIZE = 20;
const int WALL_COUNT = 3;

struct Point{
    int x,y;
};

class Snakegame{
private:
    vector<Point> snake; //A kígyó mozgásánál mindig az elejére adunk hozzá egy új fejet és a végébõl törlünk egy elemet, kivéve ha épp élelmet eszik.
    //kígyó állapotát, mozgásirányt
    vector<Point> wall;
    Point food;
    //élelem helyét
    int dx, dy;
    bool running;
public:
    Snakegame(){
        snake.push_back({WIDTH/2,HEIGHT/2});
        dx = CELL_SIZE;
        dy = 0;
        generate_food();
        generate_wall();
        running = true;
    }
    void generate_food(){
        bool food_collides = false;

        do{
            food.x = (rand() % (WIDTH / CELL_SIZE))*CELL_SIZE;
            food.y = (rand() % (HEIGHT / CELL_SIZE))*CELL_SIZE;

            food_collides = false;
            for(const auto& segment : snake){
                if(food.x == segment.x && food.y == segment.y){//ne tudjon a kígyóra megjelenni
                    food_collides = true;
                    break;
                }
            }
            for(const auto& segment : wall){
                if(food.x == segment.x && food.y == segment.y){//ne tudjon a falra megjelenni
                    food_collides = true;
                    break;
                }
            }
        }while(food_collides);
    }
    void generate_wall(){
        wall.clear();
        for(int i = 0; i < WALL_COUNT; i++){
        Point new_wall;
        bool collides;
        do {
            collides = false;
            new_wall.x = (rand() % (WIDTH / CELL_SIZE)) * CELL_SIZE;
            new_wall.y = (rand() % (HEIGHT / CELL_SIZE)) * CELL_SIZE;

            for(const auto& segment : snake){
                if(abs(new_wall.x - segment.x) < 2 * CELL_SIZE &&
                   abs(new_wall.y - segment.y) < 2 * CELL_SIZE) {
                    collides = true;
                    break;
                }
            }
        } while (collides);

        for(int j = 0; j < 3; j++){
            wall.push_back({new_wall.x, new_wall.y + j * CELL_SIZE});
        }
    }

    }
    void handle_input(event ev) {
        if (ev.type == ev_key) {
            if (ev.keycode == key_up && dy != CELL_SIZE) { // Csak akkor mehet felfelé, ha nem lefelé megy
                dx = 0;
                dy = -CELL_SIZE;
            }
            else if (ev.keycode == key_down && dy != -CELL_SIZE) { // Csak akkor mehet lefelé, ha nem felfelé megy
                dx = 0;
                dy = CELL_SIZE;
            }
            else if (ev.keycode == key_left && dx != CELL_SIZE) { // Csak akkor mehet balra, ha nem jobbra megy
                dx = -CELL_SIZE;
                dy = 0;
            }
            else if (ev.keycode == key_right && dx != -CELL_SIZE) { // Csak akkor mehet jobbra, ha nem balra megy
                dx = CELL_SIZE;
                dy = 0;
            }
            else if (ev.keycode == key_escape) { // ESC gomb megnyomására kilépés
                running = false;
            }
        }
    }
    void update(){
        if(!running) return;
        Point new_head = {snake.front().x + dx, snake.front().y + dy};// fejpozíciót , mozgásirányt adja vissza, és kiszámoljuk az új fej helyzetét
        if(new_head.x < 0 || new_head.y <0 ||new_head.x >= WIDTH || new_head.y >= HEIGHT){ //falhoz ér kilép a játékból
            running = false;
            return;
        }
        for(const auto& segment : snake){
            if(new_head.x == segment.x && new_head.y == segment.y){//új fej beleütközik-e a kígyó saját testébe
                running = false;
                return;
            }
        }
        for(const auto& segment : wall){
            if(new_head.x == segment.x && new_head.y == segment.y){
                running = false;
                return;
            }
        }

        snake.insert(snake.begin(),new_head);//új fejet a kígyó elejére illesztjük
        if(new_head.x == food.x && new_head.y == food.y){//ha élelmet kap
            generate_food();
        }
        else{
            snake.pop_back();//ha nem kap élelmet akkor a farkát levágják
        }
    }
    void draw(){
        gout << move_to(0,0) << color(0,0,0) << box(WIDTH,HEIGHT);
        if(running){
           gout << move_to(food.x,food.y) << color(255,0,0) << box(CELL_SIZE, CELL_SIZE);
            for(const auto& segment: snake){
                gout << move_to(segment.x,segment.y) << color(0,255,0)<<box(CELL_SIZE-1,CELL_SIZE-1);
            }
            for(const auto& segment : wall){
                gout << move_to(segment.x,segment.y) << color(255,255,255) << box(CELL_SIZE, CELL_SIZE);
            }
        }
        else{
            gout << move_to(WIDTH / 2 -50, HEIGHT/2-20)<<color(255,255,255)<< text("Game Over");
            gout << move_to(WIDTH/2-160,HEIGHT/2+20)<<color(255,255,255)<<text("Press Esc to exit, or Space to restart");
        }

    }
    bool is_running(){
        return running;
    }
    void reset_game(){
        snake.clear();
        snake.push_back({WIDTH/2,HEIGHT/2});
        dx = CELL_SIZE;
        dy = 0;
        generate_food();
        generate_wall();
        running = true;
    }
};

int wait_for_start(){
    event ev;
    gout << move_to(0,0) << color(255,255,255) << box(WIDTH, HEIGHT);
    gout << move_to(WIDTH/2 -100,HEIGHT/2 -30) << color(0,0,0) << text("Press 1 for HARD (Fast)");
    gout << move_to(WIDTH/2 -100,HEIGHT/2) << color(0,0,0) << text("Press 2 for NORMAL (Normal)");
    gout << move_to(WIDTH/2 -100,HEIGHT/2 +30) << color(0,0,0) << text("Press 3 for EASY (Slow)");
    gout << move_to(WIDTH/2 -100,HEIGHT/2 +60) << color(0,0,0) << text("Press ESC to EXIT");

    gout << refresh;
    while(gin >> ev){
        if(ev.type == ev_key && ev.keycode == '1'){
            return 50;
        }
        else if(ev.type == ev_key && ev.keycode == '2'){
            return 100;
        }
        else if(ev.type == ev_key && ev.keycode == '3'){
            return 150;
        }
        if(ev.type == ev_key && ev.keycode == key_escape){
            exit(0);
        }
    }
}

void game_loop(Snakegame& game, int& speed) {
    event ev;
    gin.timer(speed);
    while(gin >> ev && game.is_running()) {
        if (ev.type == ev_key) game.handle_input(ev);
        if (ev.type == ev_timer) {
            game.update();
            game.draw();
            gout << refresh;
        }
    }
}
int main()
{
    srand(time(0));
    gout << font("LiberationSans-Regular.ttf",20);
    gout.open(WIDTH,HEIGHT);
    event ev;
    Snakegame game;

    int speed = wait_for_start();

    game_loop(game, speed);

    while (gin >> ev && !game.is_running()) {
        if(ev.type == ev_key){
            if (ev.keycode == key_escape) {
            exit(0);
            }
            else if(ev.type == ev_key && ev.keycode == key_space){
                game.reset_game();
                speed = wait_for_start();
                gin.timer(speed);
                game_loop(game, speed);
            }
        }
        game.draw();
        gout << refresh;
    }
    return 0;
}
