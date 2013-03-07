#include <vector>
#include <sstream>
#include <map>

map <string, bool> debug_flags;
vector<string> curr_debug_flag = {"Main"};

#define sstream stringstream

sstream ss;

void debug (string message, string flag = ""){
    if (flag == "") flag = curr_debug_flag.back();

    if (debug_flags.count(flag) == 0 ) {
        cerr << "[" + flag + "]: " + message << endl;
        return;
    }

    if (!debug_flags[flag]) return;

    cerr << "[" + flag + "]: " + message << endl;
}
void debug (){
    string flag = curr_debug_flag.back();
    string temp = ss.str();
    ss.str("");

    if (debug_flags.count(flag) == 0 ) {
        cerr << "[" + flag + "]: " + temp << endl;
        return;
    }

    if (!debug_flags[flag]) return;

    cerr << "[" + flag + "]: " + temp << endl;
}
void debug_init (){
    debug_flags["Main"] = true;
    debug_flags["Initialize"] = true;
    debug_flags["Actualize"] = true;
    debug_flags["Target select"] = true;
    debug_flags["Clock"] = true;
    debug_flags["Path finding"] = true;
    debug_flags["BFS 1"] = false;
    debug_flags["Make beware"] = true;
}

void set_debug_flag (string flag){
    curr_debug_flag.back() = flag;
}

void add_debug_flag (string flag){
    curr_debug_flag.push_back(flag);
}

void undo_debug_flag (){
    curr_debug_flag.pop_back();
}

#define setdf set_debug_flag
#define adddf add_debug_flag
#define unddf undo_debug_flag

