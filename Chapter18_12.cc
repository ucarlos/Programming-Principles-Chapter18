/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/19/2020
 * 
 * Chapter18_12
 * Implement a version of the game “Hunt the Wumpus.” “Hunt the Wum-
 * pus” (or just “Wump”) is a simple (non-graphical) computer game origi-
 * nally invented by Gregory Yob. The basic premise is that a rather smelly
 * monster lives in a dark cave consisting of connected rooms. Your job is to
 * slay the wumpus using bow and arrow. 
 *
 * In addition to the wumpus, the
 * cave has two hazards: bottomless pits and giant bats. If you enter a room
 * with a bottomless pit, it’s the end of the game for you. If you enter a room
 * with a bat, the bat picks you up and drops you into another room. If you
 * enter the room with the wumpus or he enters yours, he eats you. 
 *
 * When you enter a room you will be told if a room_type is nearby:
 *    “I smell the wumpus”: It’s in an adjoining room.
 *    “I feel a breeze”: One of the adjoining rooms is a bottomless pit.
 *    “I hear a bat”: A giant bat is in an adjoining room.
 *
 * For your convenience, rooms are numbered. Every room is con-
 * nected by tunnels to three other rooms. When entering a room, you are
 * told something like “You are in room 12; there are tunnels to rooms 1, 13,
 * and 4; move or shoot?” Possible answers are m13 (“Move to room 13”)
 * and s13–4–3 (“Shoot an arrow through rooms 13, 4, and 3”). The range
 * of an arrow is three rooms. 
 *
 * At the start of the game, you have five arrows.
 * The snag about shooting is that it wakes up the wumpus and he moves to
 * a room adjoining the one he was in — that could be your room.
 *
 * Probably the trickiest part of the exercise is to make the cave by
 * selecting which rooms are connected with which other rooms. You’ll
 * probably want to use a random number generator (e.g., randint() from
 * std_lib_facilities.h ) to make different runs of the program use different
 * caves and to move around the bats and the wumpus. Hint: Be sure to
 * have a way to produce a debug output of the state of the cave.
 *
 * -----------------------------------------------------------------------------
 */

#include "Wumpus.h"

//------------------------------------------------------------------------------
// Class Definitions
//------------------------------------------------------------------------------

bool Room::add_tunnel(Room *pointer){
    if (tunnel_amount() > max_tunnels)
		return false;
    else{
		tunnels.push_back(pointer);
		return true;
    }
}

Room::Room(int room_id, Room *tunnel1, Room *tunnel2,
           Room *tunnel3, enum room_type &room_hazard) {

    this->room_id = room_id;
    this->tunnels.clear();
    this->tunnels[0] = tunnel1;
    this->tunnels[1] = tunnel2;
    this->tunnels[2] = tunnel3;
    this->room_hazard = room_hazard;
	
}

string Room::room_status(){ // Only use for debugging.
    string check;
    switch(room_hazard){
    case 0 :
        check = "This room is empty.";
        break;
    case 1:
        check = "EEK! There's a Wumpus in this room!";
        break;
    case 2:
        check = "There's a bottomless pit in this room!";
        break;
    case 3:
        check = "There's a giant bat in this room!";
        break;
    case 4:
        check = "WOAAH! I've entered a secret room!";
        break;
    default:
        check = "ERROR: UNDEFINED ROOM.";
    }

    return "Room Status: " + check;

}

string Room::get_connections(){
    ostringstream os;
    os << "You are connected to the following rooms:\n";
    for (auto & tunnel : tunnels){
        os << "Room " << tunnel->get_id() << "\n";
    }

    return os.str();
       
}


//------------------------------------------------------------------------------
// Generate Room Functions
//------------------------------------------------------------------------------
int search_list(vector<Room*> &list, Room &item){
    for (int i = 0; i < list.size(); i++){
        if (list[i]->get_id() == item.get_id())
            return i;
    }
    return -1; // Not found.
}

void remove_duplicates(vector<Room*> &queue, vector<Room*> &plist) {
    int search;
    for (auto & i : plist) {
        i->toggle_full_tunnels();
        if (i->is_full()){
            search = search_list(queue, *i);
            if (search != -1)
                queue.erase(queue.begin() + search);
        }
    }
}

void generate(vector<Room> &list){
    int *tunnel_id_list = new int[max_tunnels];

    vector<Room*> queue (list.size());
    for (int i = 0; i < queue.size(); i++){
        queue[i] = &list[i];
    }

    int value = queue.size();
    int search;
    for (int i = 0; i < list.size() && !queue.empty(); i++){
        search = search_list(queue, list[i]);
        if (search != -1){
            list[i].toggle_full_tunnels();
            queue.erase(queue.begin() + search);
            if (list[i].is_full()) {
                queue.erase(queue.begin() + search);
                continue;
            }


            vector<Room*> plist = get_random_tunnels(queue, list[i],
													 max_tunnels - list[i].tunnel_amount());

            if (!plist.empty()) {
                set_tunnels(plist, list[i]);
                remove_duplicates(queue, plist);
            } else
                break;

        }
        else
            continue;
    }


    for (int i = 0; i < list.size(); i++){ // If a room has no tunnels, make a hidden tunnel to the beginning.
        if (!list[i].tunnel_amount()) {
            list[i].add_tunnel(&list[0]);
            list[i].set_secret_room(true);
            list[i].set_room_hazard(secret_area);
        }
    }

}

void place_hazards(vector<Room> &list, Wumpus &the_wumpus){
    // Place the wumpus, giant bat, and bottomless pit somewhere
    // Make sure that the secret room, is not chosen.
    // THERE SHOULD ONLY BE ONE WUMPUS.
    int max_hazards = wumpus_count + bat_count + pit_count;
    int hazard_index[max_hazards];
    vector<Room*>hazard_list;
    bool valid = false;
    do {
        hazard_list.clear();
        generate_rand_number(hazard_index, max_hazards, list.size());

        for (int i = 0; i < max_hazards; i++)
            hazard_list.push_back(&list[hazard_index[i]]);

        if (!check_duplicates(hazard_list))
            continue;

        int i;

        for (i = 0; i < max_hazards; i++)
            if (hazard_list[i]->get_room_type() != clear || hazard_list[i]->get_id() == 0) // Room 0 is always safe.
                break;

        if (i == max_hazards)
            valid = true;

    }while (!valid);

    // Now apply the results:
    int i;
    for (i = 0; i < wumpus_count; i++){
        hazard_list[i]->set_room_hazard(wumpus);
		the_wumpus.set_location(hazard_list[i]);
    }
    for (i; i < wumpus_count + bat_count; i++)
        hazard_list[i]->set_room_hazard(giant_bat);
    for (i; i < max_hazards; i++)
        hazard_list[i]->set_room_hazard(pit);
}

vector<Room> generate(){
    vector<Room> list;
    for (int i = 0; i < max_rooms; i++)
        list.push_back(Room(i));

    generate(list);
    return list;
}



void generate_rand_number(int *num_list, const int list_length, int value){
#ifdef _WIN32
    static std::random_device rd;
    static std::mt19937 gen(rd());
    uniform_int_distribution<> dis(0, value);
    for (int i = 0; i < list_length; i++){
        num_list[i] = dis(gen);
    }

#endif


    // Open /dev/random on linux:
	/* // C-Equivalent

	   int buffer_size = sizeof(int);
	   FILE *rand_file = fopen("/dev/urandom", "r");
	   if (!rand_file) throw runtime_error("Cannot open /dev/urandom.");
	   fread(num_list, buffer_size, list_length, rand_file);
	   fclose(rand_file);
    */

    ifstream rand_file{"/dev/urandom", ios_base::in};
    if (!rand_file) throw runtime_error("Cannot open /dev/urandom. ");

    unsigned int buffer_size = sizeof(int) * list_length;
    rand_file.read(reinterpret_cast<char *> (num_list), buffer_size);
    unsigned int temp;
    for (int i = 0; i < list_length; i++){
		temp = num_list[i];
        num_list[i] = ((temp % value));
    }

}



bool check_tunnels(vector<Room*> &list,vector<Room*> &plist){
    bool valid = true;
    //
    for (auto & i : plist){
        if (i->tunnel_amount() >= max_tunnels){
            i->set_full_tunnels(true);
            valid = false;
        }
    }

    return valid;
}

void set_tunnels(vector<Room*> &list, Room &initial_room){
    for(auto & i : list){
        initial_room.add_tunnel(i);
        i->add_tunnel(&initial_room);
        i->toggle_full_tunnels();
    }
    // Just in case.
    initial_room.toggle_full_tunnels();
}
bool check_duplicates(vector<Room*> &list){
    for (int i = 0; i < list.size(); i++){
        for (int j = 0; j < list.size(); j++){
            if ((i != j) && (list[i]->get_id() == list[j]->get_id()))
                return false;
        }
    }
    return true;
}
vector<Room*> get_random_tunnels(vector<Room*> &list, Room &initial_room, int connections){
    if (connections <= 0){
        throw runtime_error("The number of connections is negative. What the fuck.");
    }

    int id_list[connections];
    vector <Room*> plist;
    int valid_rooms = 0;

    int max_range = list.size();
    while (!list.empty() && valid_rooms != connections && (list.size() >= connections)){
        plist.clear();
        generate_rand_number(id_list, connections, max_range);
        for (int i = 0; i < connections; i++)
            plist.push_back(list[id_list[i]]);

        // Check for duplicates:
        if (!check_duplicates(plist)) {
            continue;
        }

        if (!check_tunnels(list, plist)){ // remove all full tunnels
            remove_duplicates(list, plist);
        }
        else
            valid_rooms = connections;

        max_range = list.size();
    }

    if (plist.empty() || list.empty()) {
        plist.clear();
        return plist;
    }
    else
        return plist;

}


void print_rooms(vector<Room> &list){
    for (int i = 0; i < list.size(); i++) {
        cout << "For List[" << i << "]:\n";
        cout << list[i].room_status() << "\n";
        cout << list[i].get_connections() << endl;
    }
    

}
//------------------------------------------------------------------------------
// Player Class
//------------------------------------------------------------------------------
Player::Player(int health, int arrows, Room* location){
    this->health = health;
    this->arrows = arrows;
    this->current_location = location;
}

//------------------------------------------------------------------------------
// Wumpus Class
//------------------------------------------------------------------------------


string Wumpus::health_status(){
    switch(health){
    case 0:
		return "The Wumpus is dead!!";
    case 1:
		return "The Wumpus is severely injured!";
    case 2:
		return "The Wumpus is slightly injured...";
    default:
		return "The Wumpus is unharmed.";

    }
}


//------------------------------------------------------------------------------
// Game functions
//------------------------------------------------------------------------------

Room * move_to_room(Room &initial_room, int room_id){
    
    const vector<Room*> &tunnel_list = initial_room.get_tunnel_vector();
    for (auto i : tunnel_list){
	    if (i->get_id() == room_id)
	        return i; // If found
    }

    return nullptr; // If not found.
}

bool valid_arrow_path(Room &initial_room, vector<int> &arrow_path){
    // Assume sanitized input
    if (arrow_path.empty() || (arrow_path.size() > 3))
		return false; // Don't know if I should through a runtime error

    // Okay
    Room *check;
    Room *rp = &initial_room;
	for (int i : arrow_path){
		//Search if you can travel to path from
		check = move_to_room(*rp, i);
		if (!check) return false;
		else
			rp = check;
    }
    
    return true;
}


void shoot_arrow(vector<Room> &list, Player &player, Wumpus &wumpus, vector<int> &arrow_path){
    // Make sure that I have arrows:
    if (!player.check_arrows()){
		cout << "Damn it, I don't have any arrows!\n";
		return;
    }
    
    // check first if the arrow makes it
    bool can_shoot = valid_arrow_path(*player.get_location(), arrow_path);
    if (!can_shoot){
        cout << "I can't shoot any arrows there!\n";
        return;
    }

    // Now check if the wumpus is in the last room.
    int last_room = arrow_path[arrow_path.size() - 1];
    if (&list[last_room] == wumpus.get_location()){
        cerr << "I shot an arrow at the Wumpus and damaged it!\n" << endl;
        wumpus.injure();
		if (wumpus.is_dead()){
			string win = "Congrats! You killed the Wumpus!";
			end_game(win);
		}
		else
			move_wumpus(list, wumpus);
    }
    else
        cout << "I shot an arrow into Room " << last_room << " but the Wumpus isn't there!\n";

    player.shot_arrow();
    // Check Winning conditions
}

void check_game_status(vector<Room> &list, Player &player, Wumpus &the_wumpus){
    string death_message;
    Room *room_p = player.get_location();
    if (!player.moves){
        cout << print_line('-', 80);
	    cout << "You find yourself in a cave with several tunnels. For some reason, each room is\n"
			 << "marked with a number.This cave has the number \"0\" displayed in the middle of "
			 << "\nthe floor. Each tunnel has a plaque on top displaying various numbers, presumably\n"
			 << "the room it connects to."
			 << " You also notice that there's a minute disgusting smell\nthat permeates all around "
			 << "you. Could it be the legendary Wumpus?\n";
        cout << print_line('-', 80);
    }
    else if (room_p == player.get_previous_location())
	    cout << "You remain in room " << player.get_location()->get_id() << ".\n";
    else
        cout << "You are now in room " << room_p->get_id() << ".\n";

    
    // First check the place.

    // Is the room the player in a hazard? i.e Wumpus, Giant Bat, Pit, if so, execute their functions
    if (room_p == the_wumpus.get_location()){
        death_message = "You encounter the Wumpus. Despite your strength, You are no match for\nthe Wumpus"
			" head on. It devours you. (GAME OVER)\n";
        end_game(death_message);
    }

    cout << endl;
    //cout << "Room Status: " << endl;
    switch (room_p->get_room_type()){
    case giant_bat:
        giant_bat_teleport(list, player);
        room_p = player.get_location();
        cout << "You walk into a room that holds a giant bat. Despite looking quite threatening,\nthe giant bat asks "
			 << "you if you would like for it to move you somewhere.\nBefore you even respond, it picks you up with\n"
             << "its claws to somewhere else.\n"
			 << "After dropping you in this new room, it promptly returns back to its nest.\n"
			 << "You look at the middle of the room, where the number " << room_p->get_id()
			 << " is displayed.\n";
        break;
    case pit:
        death_message = "Absentmindedly, You walk into a room with a bottomless pit. You then"
			" fall to your death. 0/10 would not play again. (GAME OVER)";
        end_game(death_message);
        break;
    case secret_area:
        secret_room(player);
        break;
    default:
        cout << "You see nothing out of the ordinary in this room.\n";

    }
    
    // Otherwise state your room is fine.
    //cout << "Additional Info:\n";
    vector<Room *> tunnel_list = room_p->get_tunnel_vector();
    enum room_type type;
    for (auto & i : tunnel_list){
	    type = (enum room_type)i->get_room_type();
	    if (type == giant_bat)
	        cout << "You hear what appears to be a bat at the end of"
				 << " a tunnel.\n";
	    else if (type == pit)
	        cout << "You feel a breeze coming from the room at the end of"
				 << " a tunnel.\n";
	    else if (type == wumpus)
	        cout << "You smell a horrible odor coming from the room at the end of"
				 << " a tunnel.\nIt's got to be the Wumpus!\n";
    }
    
    cout << endl;
    // You can connect to a, b, or c.

    // Next, determine if you've killed the wump
    if (player.get_location()->tunnel_amount() > 1)
        cout << "You see tunnels connecting to ";
    else
        cout << "You see a tunnel connecting to ";

    for (int i = 0; i < tunnel_list.size(); i++){
        cout << "Room " << tunnel_list[i]->get_id();
        if ((i + 1) == tunnel_list.size())
            cout << endl;
        else cout << ", ";
    }
}

void move_wumpus(vector<Room> &list, Wumpus &the_wumpus){
    // First, set your current room back to normal.
    the_wumpus.get_location()->set_room_hazard(clear);
	// Try to make sure that the tunnels don't point to a giant bat or pit.
    // If they do, move somewhere else (It's a good idea to go to room 0)
    // Move at random.
    // Okay, get the tunnel length list:
    
    int *index = new int;
    Room *new_room = nullptr;
    vector<Room*> tunnel_list = the_wumpus.get_location()->get_tunnel_vector();
    generate_rand_number(index, 1, tunnel_list.size());
    
    new_room = tunnel_list[*index];
    
    if (new_room->get_room_type() != clear){
		// Teleport to Room 0.
		cerr << "From a distance you hear the sound of a large hole being dug.\n";
		cerr << "Could the Wumpus have done that?\n";
		the_wumpus.set_location(&list[0]);
    }
    else
		the_wumpus.set_location(new_room);

    the_wumpus.get_location()->set_room_hazard(wumpus);
    delete index;
}


void giant_bat_teleport(vector<Room> &list, Player &player){
    int *index = new int;

    Room *new_room = nullptr;
    
    generate_rand_number(index, 1, list.size());
    
    new_room = &list[*index];
    
    if (new_room->get_room_type() != clear){
		// Teleport to Room 0. 
		player.set_location(&list[0]);
    }
    else
		player.set_location(new_room);

    delete index;

}

void end_game(string &game_end_message){
    cout << game_end_message << endl;
    exit(EXIT_SUCCESS);

}


void secret_room(Player &player){
    cout << "You find yourself in what appears to be a well-furnished armory, far different\n"
		 << "than the usual dank and faintly smelly rooms you have walking through.\n"
		 << "Numerous weapons adorn the wall, yet standing ahead of them, a gold covered \n"
		 << "plaque attracts your interest. It reads:\n\n\"This room isn't supposed to exist "
		 << "had I understood why code didn't work as I\nexpected it to do. Instead, it's "
		 << "like trying to bandaid a gaping wound.To make\nit up to you, I'll replenish"
		 << "your arrow supply. I'll also throw in a free heal,\nbut you're already at full "
		 << "health aren't you? I'd also like to play some nice\nand relaxing music, but "
		 << "that seems to be beyond my grasp.\"\n\n";

    cout << "You then replenish your arrow supply, but wonder why the programmer\n"
         << "hadn't implemented any other means of attacking. Maybe he was pressed\n"
         << "for time? Or maybe he was two incompetent to do so? Either way, you've\n"
         << "got to get out of this cave.\n";
    player.replenish_arrows();

}

void take_input(Player &player, Wumpus &the_wumpus, vector<Room> &list) {
    // First, how should we consider input?
    // For movement, we have m14, or m room 15, or whatever,
    // For shooting we have s14-14-21, we can use cine.ignore
    string error_message = "Invalid command.\n";
    player.set_previous_location(player.get_location());
    Room *check_p;
    vector<int>room_id_list;
    string input_string;
    int temp_arg;
    cout << "> ";
    cin >> input_string;

    char command = tolower(input_string[0]);

    stringstream ss{input_string};
    ss.seekg(1);

    player.moves++;
    switch(command){
	case 'i': // Info:
		check_game_status(list, player, the_wumpus);
		return;
	case 'm': {// Moving then:
		ss >> temp_arg;
		if (!ss) {
			cerr << error_message;
			break;
		}
		// Now call the function and then do so.
		check_p = move_to_room(*player.get_location(), temp_arg);

		if (!check_p) {
			cerr << "Cannot move to Room " << temp_arg << "\n";
			return;
		} else
			player.set_location(check_p);
		break;
	}
	case 's':
	    // Make sure that way it should be handled is a-b-c

		while ((ss >> command) && ss.good()){
			if (command == '-') continue;
			else
				ss.unget();
			ss >> temp_arg;
			room_id_list.push_back(temp_arg);
		}
	
		if (!valid_arrow_path(*player.get_location(), room_id_list)){
			cerr << "Could not make a shot towards that path.";
			break;
		}
		else
			shoot_arrow(list, player, the_wumpus, room_id_list);
		break;
	case 'h': // Don't move the wumpus if you input help
		instructions();
		return;
	case 'w':
		cout << "You decide to wait in this room.\n";
		break;
	case 'q': {
		string temp{"Goodbye!"};
		end_game(temp);
		break;
	}
	default:
		cout << error_message;
		return;
	
    }


    move_wumpus(list, the_wumpus);

}
