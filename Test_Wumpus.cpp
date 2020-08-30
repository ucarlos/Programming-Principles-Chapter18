//--------------------------------------------------------------------------------------------------
// Created by Ulysses Carlos on 1/19/20 using Ulysses-H270-HD3.
//--------------------------------------------------------------------------------------------------
#include "Wumpus.h"


// Make a intro screen:
string print_line(char ch, int length){
    ostringstream os;
    for (int i = 0; i < length; i++)
	os << ch;
    os << endl;

    return os.str();

}
void intro_screen(void){
    string line = print_line('-', 80); // Made to fit 80 char terminals
    string title = " _      _     _      ____  _     ____ \n"
                   "/ \\  /|/ \\ /\\/ \\__/|/  __\\/ \\ /\\/ ___\\\n"
                   "| |  ||| | ||| |\\/|||  \\/|| | |||    \\\n"
                   "| |/\\||| \\_/|| |  |||  __/| \\_/|\\___ |\n"
                   "\\_/  \\|\\____/\\_/  \\|\\_/   \\____/\\____/\n";
    string creator = "An awful implementation of Wumpus by Ulysses Carlos\n";
    string date = "January 25, 2020\n";

    cout << line << title << line << creator << date << line;
    
}
void instructions(void){
    cout << print_line('-', 80);
    cout << "Instructions:\n";
    cout << "To move a room (such as room 13), type \"m13\".\n";
    cout << "To shoot a arrow through a room (up to three rooms), type "
         << "\"sA-B-C\".\n(A B and C can be any room number)\n";
    cout << "You can choose to wait by typing \"w\".\n";
    cout << "To see information about the current room, input \"i\".\n";
    cout << "To see this message again, input \"h\".\n";
    cout << "To quit the game, input \"q\".\n";
    cout << print_line('-', 80);
}
void start_game(){
    intro_screen();
    instructions();
    system("sleep 1");
    Player player;
    Wumpus the_wumpus{};
    vector<Room> list = generate();
    //cout << "Size of Wumpus list: " << sizeof(list[0]) * list.size() << " bytes\n";
    player.set_location(&list[0]);
    place_hazards(list, the_wumpus);
    string input;

    do{
        check_game_status(list, player, the_wumpus);
        system("sleep 1");
        take_input(player, the_wumpus, list);
    } while (true);

};

int main(){
    start_game();

}


