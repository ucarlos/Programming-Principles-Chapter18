//--------------------------------------------------------------------------------------------------
// Created by Ulysses Carlos on 1/19/20 using Ulysses-H270-HD3.
//--------------------------------------------------------------------------------------------------


#ifndef CHAPTER18_WUMPUS_H
#define CHAPTER18_WUMPUS_H
#include <iostream>
#include <new>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <fstream>
#include <random>

#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

// Global functions in this case;
constexpr int max_rooms = 12;
const int wumpus_count = 1;
const int bat_count = 1;
const int pit_count = 1;
const int max_arrows = 5;
constexpr int max_tunnels = 3;

enum room_type{
    clear = 0, wumpus, pit, giant_bat, secret_area
};


class Room{
public:
    Room(int room_id, Room *tunnel1, Room *tunnel2, Room *tunnel3,
         enum room_type &room_hazard);
    Room()= default;;
    explicit Room(int room_id) { this->room_id = room_id; }

    int get_id(){return room_id;}
    string get_connections();
    string room_status();

    int get_room_type(){return room_hazard;}
    bool add_tunnel(Room *pointer);
    void set_full_tunnels(bool check) { has_max_tunnels = check;}
    void toggle_full_tunnels(){if (tunnel_amount() >= max_tunnels) has_max_tunnels = true;}
    bool is_full(){return has_max_tunnels;}
    int tunnel_amount() { return (tunnels.empty()) ? 0 : tunnels.size();}
    void set_room_hazard(room_type new_hazard){ room_hazard = new_hazard;}
    void set_secret_room(bool bl) { secret_room = bl;}
    bool is_secret_room(){return secret_room;}

    const vector<Room*>& get_tunnel_vector(){ return tunnels; }
private:
    bool has_max_tunnels{false};
    bool secret_room{false}; // Handles rooms with only one tunnel.
    int room_id{0};
//    Room *tunnels[3] = {nullptr};
    vector<Room*> tunnels; // Should be 3;
    enum room_type room_hazard{clear};
};

//------------------------------------------------------------------------------
// Player Class
//------------------------------------------------------------------------------

class Player{
public:
    Player()= default;
    Player(int health, int arrows, Room * location);
    int moves{0};
    int check_arrows() { return arrows;}
    void shot_arrow() { arrows--; }
    void set_arrows(int na) { arrows = na;}
    void replenish_arrows(){arrows = max_arrows;}
    Room * get_location(){return current_location;}
    void set_location(Room * rp){ current_location = rp;}

    Room * get_previous_location(){ return previous_location;}
    void set_previous_location(Room *p) { previous_location = p;}
    int health{1}; // Only one health
private:
    int arrows {max_arrows};
    Room *current_location{nullptr};
    Room *previous_location{nullptr};
};




//------------------------------------------------------------------------------
// Wumpus Class
//------------------------------------------------------------------------------


constexpr int wumpus_health = 3;
class Wumpus{
public:
    string health_status();
    Room * get_location(){return Location;}
    void set_location(Room * rp){ Location = rp;}
    bool is_dead(){return (health <= 0);}
    void kill(){ health = 0; }
    void injure(){ health--; }
    void set_health(int new_health){ this->health = new_health;}
    Wumpus (Room *location, int health){ this->Location = location; this->health = health;}
    explicit Wumpus (int health) { this->health = health; }
    Wumpus()= default;;


private:
    int health{wumpus_health};
    Room *Location{nullptr};
};

//------------------------------------------------------------------------------
// Class declarations
//------------------------------------------------------------------------------
void generate(vector<Room> &list);
vector<Room> generate();


void generate_rand_number(int *num_list, const int list_length, int value);
vector<Room*> get_random_tunnels(vector<Room*> &list, Room &initial_room, int connections);
void set_tunnels(vector<Room*> &list, Room &initial_room);
void print_rooms(vector<Room> &list);
void place_hazards(vector<Room> &list, Wumpus &the_wumpus);
bool check_duplicates(vector<Room*> &list);
int search_list(vector<Room*> &list, Room &item);

//------------------------------------------------------------------------------
// Game functions
//------------------------------------------------------------------------------
void start_game();
Room* move_to_room(Room &initial_room, int room_id);
// Function to take input
// Function to shoot arrow at shoot at up to three rooms
bool valid_arrow_path(Room &initial_room, vector<int> &arrow_path);
void shoot_arrow(Player &player, Wumpus &wumpus, vector<int> &arrow_path);
void shoot_arrow(vector<Room> &list, Player &player, Wumpus &wumpus, vector<int> &arrow_path);
// Function to move wumpus
void move_wumpus(vector<Room> &list, Wumpus &wumpus);
// Function to determine game status
void check_game_status(vector<Room> &list, Player &player, Wumpus &wumpus);
void end_game(string &game_end_message);
// Giant Bat Function -- Place bat there,
void giant_bat_teleport(vector<Room> &list, Player &player);
void secret_room(Player &player);
void take_input(Player &player, Wumpus &the_wumpus, vector<Room> &list);
void instructions();
string print_line(char ch, int length);
#endif //CHAPTER18_WUMPUS_H
