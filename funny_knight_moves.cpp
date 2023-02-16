#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> coord;

const int knight_y[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int knight_x[] = {-1, 1, -2, 2, -2, 2, -1, 1};
const int M = 8;
bool ok[8][8], seen[8][8];
coord parent[8][8];

inline bool valid_coord(coord c){
    return c.first >= 0 && c.first < 8 && c.second >= 0 && c.second < 8;
}

vector<coord> fastest_path(coord from, coord to){
    memset(seen, false, sizeof seen);
    queue<coord> q;
    q.push(from);
    seen[from.first][from.second] = true;
    while(!q.empty()){
        coord c = q.front(); q.pop();
        if (c == to) break;
        coord nc;
        for(int i=0; i<M; ++i){
            nc.first = c.first + knight_x[i];
            nc.second = c.second + knight_y[i];
            if(valid_coord(nc) && ok[nc.first][nc.second] && !seen[nc.first][nc.second]){
                q.push(nc);
                seen[nc.first][nc.second] = true;
                parent[nc.first][nc.second] = c;
            }
        }
    }

    vector<coord> new_pos;
    coord c = to;
    while(c!=from){
        new_pos.push_back(c);
        c = parent[c.first][c.second];
    }
    reverse(new_pos.begin(), new_pos.end());
    return new_pos;
}

void add_moves(vector<coord>& moves, coord from, coord to){
    vector<coord> new_moves = fastest_path(from, to);
    moves.insert(moves.end(), new_moves.begin(), new_moves.end());
}

void mark_queen_spots(coord queen_pos){
    memset(ok, true, sizeof ok);
    coord c = queen_pos;
    while(valid_coord(c)){
        ok[c.first++][c.second++] = false;
    }
    c = queen_pos;
    while(valid_coord(c)){
        ok[c.first++][c.second--] = false;
    }
    c = queen_pos;
    while(valid_coord(c)){
        ok[c.first--][c.second++] = false;
    }
    c = queen_pos;
    while(valid_coord(c)){
        ok[c.first--][c.second--] = false;
    }
    for(int i=0; i<8; ++i) {
        ok[queen_pos.first][i] = false;
        ok[i][queen_pos.second] = false;
    }
}

vector<coord> find_coords_in_order(){
    vector<coord> ret;
    for(int i=0; i<8; ++i){
        for(int j=7; j>=0; --j){
            if(ok[i][j]) ret.push_back({i, j});
        }
    }
    return ret;
}

string coord_to_chess_notation(coord c){
    char c2 = '8' - c.first;
    char c1 = c.second+'a';
    return string({c1, c2});
}

int main(){
    coord queen_pos = {3, 3};
    coord knight_start = {0, 7};
    mark_queen_spots(queen_pos);
    vector<coord> goals = find_coords_in_order();
    vector<coord> moves;

    cout << "starting algorithm\n";
    add_moves(moves, knight_start, goals[0]);
    cout << "goal 0 reached\n";
    for(size_t i=1; i<goals.size(); ++i){
        add_moves(moves, goals[i-1], goals[i]);
        cout << "goal " << i << " reached\n";
    }
    
    cout << "Starting from " << coord_to_chess_notation(knight_start) << "\n";
    for(coord c : moves){
        cout << coord_to_chess_notation(c) << ", ";
    }
    cout << "\b\b  \nNumber of moves " << moves.size() << endl;
}