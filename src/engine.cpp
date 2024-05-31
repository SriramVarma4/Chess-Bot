#include <algorithm>
#include <random>
#include <iostream>
#include <limits.h>
#include <utility>
#include <vector>
#include "board.hpp"
#include "engine.hpp"


void Engine::find_best_move(const Board& b) {
    //cout<<time_left.count()<<endl;
    // pick a random move
    Board *temp_b = new Board(b);
    Board *temp_b2 = new Board(b);
    auto moveset = temp_b->get_legal_moves();
    if(moveset.size() == 0){
        this->best_move = 0;
        return;
    }
    vector<U16> moves(moveset.begin(),moveset.end());
    if(moveset.size()==1){
        this->best_move = moves[0];
    }
    int p = 0;
    if(b.data.player_to_play == WHITE){
        p=1;
    }
    int y=3;

    if (time_left.count()>100000 && b.data.board_type==SEVEN_THREE && p==1){
        y=4;
    }
    else if (time_left.count()>10000 && b.data.board_type==SEVEN_THREE && p==1){
        y=3;
    }
    else if (time_left.count()>=0 && b.data.board_type==SEVEN_THREE && p==1){
        y=2;
    }
    else{

    }

    if (time_left.count()>145000 && b.data.board_type==EIGHT_FOUR && p==1){
        y=5;
    }
    else if (time_left.count()>80000 && b.data.board_type==EIGHT_FOUR && p==1){
        y=4;
    }
    else if (time_left.count()>10000 && b.data.board_type==EIGHT_FOUR && p==1){
        y=3;
    }
    else if (time_left.count()>=0 && b.data.board_type==EIGHT_FOUR && p==1){
        y=2;
    }
    else{           
        
    }

    if (time_left.count()>30000 && b.data.board_type==EIGHT_TWO && p==1){
        y=3;
    }
    else if (time_left.count()>=5000 && b.data.board_type==EIGHT_TWO && p==1){
        y=2;
    }
    else if (time_left.count()>=0 && b.data.board_type==EIGHT_TWO && p==1){
        y=1;
    }
    else{
        
    }


    if (time_left.count()>100000 && b.data.board_type==SEVEN_THREE && p==0){
        y=5;
    }
    else if (time_left.count()>40000 && b.data.board_type==SEVEN_THREE && p==0){
        y=4;
    }
    else if (time_left.count()>15000 && b.data.board_type==SEVEN_THREE && p==0){
        y=4;
    }
    else if (time_left.count()>=0 && b.data.board_type==SEVEN_THREE && p==0){
        y=2;
    }
    else{

    }

    if (time_left.count()>145000 && b.data.board_type==EIGHT_FOUR && p==0){
        y=5;
    }
    else if (time_left.count()>80000 && b.data.board_type==EIGHT_FOUR && p==0){
        y=4;
    }
    else if (time_left.count()>15000 && b.data.board_type==EIGHT_FOUR && p==0){
        y=3;
    }
    else if (time_left.count()>=0 && b.data.board_type==EIGHT_FOUR && p==0){
        y=2;
    }
    else{           
        
    }

    if (time_left.count()>=120000 && b.data.board_type==EIGHT_TWO && p==0){
        y=4;
    }
    else if (time_left.count()>=30000 && b.data.board_type==EIGHT_TWO && p==0){
        y=3;
    }
    else if (time_left.count()>=5000 && b.data.board_type==EIGHT_TWO && p==0){
        y=2;
    }
    else if (time_left.count()>=0 && b.data.board_type==EIGHT_TWO && p==0){
        y=1;
    }
    else{
        
    }

    pair<int,int> pr= find_move(temp_b, 0, INT_MIN, INT_MAX, p, y);
    this->best_move = moves[pr.first];
    if(b.data.board_type==SEVEN_THREE){
        k1=0;k2=0;
        if(k==0 && p ==1){
            prevb.clear();
            this->best_move = moves[4];
            k=k+1;
        }
        if(k==0 && p ==0){
            prevb.clear();
            this->best_move = moves[0];
            k=k+1;
        }
        else{

        }
    }
    else if(b.data.board_type==EIGHT_FOUR){
        k=0;k2=0;
        if(k1==0){
            prevb.clear();
            this->best_move = moves[2];
            k1=k1+1;
        }
        else if(k1==3 && p==1){
            this->best_move = moves[0];
            k1=k1+1;
        }
        else if(k1==4 && p==1){
            this->best_move = moves[10];
            k1=k1+1;
        }
        else{
           k1=k1+1;                                             
        }
    }
    else if(b.data.board_type==EIGHT_TWO){
        k=0;k1=0;
        if(k2==0){
            prevb.clear();
            this->best_move = moves[2];
            k2=k2+1;
        }
        else{

        }
    }
    vector<U8> currb;
    for(int i=0; i<64; i++){
        currb.push_back(temp_b2->data.board_0[i]);
    }
    for(uint i=0; i<prevb.size(); i++){
        bool bl = true;
        for(int j=0; j<64; j++){
            if(currb[j]!=prevb[i][j]){
                bl=false;
                break;
            }
        }
        if(bl==true){
            this->best_move = moves[pr.second];
            break;
        }
    }
    prevb.push_back(currb);
}


using namespace std;
vector<vector<U8>> prevb;
int k =0;
int margin_score(Board *b, int p){
    int score = 0;
    if(p==0){
        if(b->data.b_rook_1 != DEAD){
            score+=3;
        } 
        if(b->data.b_rook_2 != DEAD){
            score+=3;
        } 
        if(b->data.b_bishop != DEAD){
            score+=5;
        } 
        U8 pawn1 = b->data.b_pawn_1;
        U8 pawn2 = b->data.b_pawn_2;
        if(pawn1 != DEAD){
            if(b->data.board_0[pawn1] & ROOK){
                score+=3;
            }
            if(b->data.board_0[pawn1] & PAWN){
                score+=1;
            }
            if(b->data.board_0[pawn1] & BISHOP){
                score+=5;
            }
        } 
        if(pawn2 != DEAD){
            if(b->data.board_0[pawn2] & ROOK){
                score+=3;
            }
            if(b->data.board_0[pawn2] & PAWN){
                score+=1;
            }
            if(b->data.board_0[pawn2] & BISHOP){
                score+=5;
            }
        } 
    }  
    else{
        if(b->data.w_rook_1 != DEAD){
            score+=3;
        } 
        if(b->data.w_rook_2 != DEAD){
            score+=3;
        } 
        if(b->data.w_bishop != DEAD){
            score+=5;
        } 
        U8 pawn1 = b->data.w_pawn_1;
        U8 pawn2 = b->data.w_pawn_2;
        if(pawn1 != DEAD){
            if(b->data.board_0[pawn1] & ROOK){
                score+=3;
            }
            if(b->data.board_0[pawn1] & PAWN){
                score+=1;
            }
            if(b->data.board_0[pawn1] & BISHOP){
                score+=5;
            }
        } 
        if(pawn2 != DEAD){
            if(b->data.board_0[pawn2] & ROOK){
                score+=3;
            }
            if(b->data.board_0[pawn2] & PAWN){
                score+=1;
            }
            if(b->data.board_0[pawn2] & BISHOP){
                score+=5;
            }
        } 
    } 
    return score;
}
int movable_score(Board *b, int p){
    PlayerColor cp = b->data.player_to_play;
    PlayerColor qp = WHITE;
    if(p==0){
        qp = BLACK;
    }
    if(cp==qp){
        return b->get_legal_moves().size();
    }
    b->data.player_to_play = qp;
    int moves = b->get_legal_moves().size();
    b->data.player_to_play = cp;
    return moves;
}
int threat_score(Board *b, int p){
    int atc[6] = {0,0,0,0,0,0};
    PlayerColor qp = WHITE;
    if(p==0){
        qp = BLACK;
    }
    PlayerColor cp = b->data.player_to_play;
    bool bl = false;
    if(cp==qp){
        bl=true;
        if(cp==BLACK){
            b->data.player_to_play = WHITE;
        }
        else{
            b->data.player_to_play = BLACK;
        }
    }
    if(qp == BLACK){
        if(b->data.b_rook_1 == DEAD){
            atc[0]=-1;
        } 
        if(b->data.b_rook_2 == DEAD){
            atc[1]=-1;
        } 
        if(b->data.b_bishop == DEAD){
            atc[3]=-1;
        } 
        if(b->data.b_pawn_1 == DEAD){
            atc[4]=-1;
        }
        if(b->data.b_pawn_2 == DEAD){
            atc[5]=-1;
        }
    }
    else{
        if(b->data.w_rook_1 == DEAD){
            atc[0]=-1;
        } 
        if(b->data.w_rook_2 == DEAD){
            atc[1]=-1;
        } 
        if(b->data.w_bishop == DEAD){
            atc[3]=-1;
        } 
        if(b->data.w_pawn_1 == DEAD){
            atc[4]=-1;
        }
        if(b->data.w_pawn_2 == DEAD){
            atc[5]=-1;
        }
    }
    auto moveset = b->get_legal_moves();
    vector<U16> moves(moveset.begin(),moveset.end());
    int score = 0;
    for(uint i=0; i<moves.size(); i++){
        Board *temp_b = new Board(*b);
        temp_b->do_move_(moves[i]);
        if(temp_b->data.player_to_play == WHITE){
            if(b->data.w_rook_1 == DEAD && atc[0]!=-1){
                score+=3;
            } 
            if(b->data.w_rook_2 == DEAD && atc[1]!=-1){
                score+=3;
            } 
            if(b->data.w_bishop == DEAD && atc[3]!=-1){
                score+=5;
            } 
            if(b->data.w_pawn_1 == DEAD && atc[4]!=-1){
                score+=2;
            }
            if(b->data.w_pawn_2 == DEAD && atc[5]!=-1){
                score+=2;
            }
        }
        else{
            if(b->data.b_rook_1 == DEAD && atc[0]!=-1){
                score+=3;
            } 
            if(b->data.b_rook_2 == DEAD && atc[1]!=-1){
                score+=3;
            } 
            if(b->data.b_bishop == DEAD && atc[3]!=-1){
                score+=5;
            } 
            if(b->data.b_pawn_1 == DEAD && atc[4]!=-1){
                score+=2;
            }
            if(b->data.b_pawn_2 == DEAD && atc[5]!=-1){
                score+=2;
            }
        }
    }
    b->data.player_to_play = cp;
    if(bl==false){
        return 2*score;
    }
    return score;
}
int check_score(Board *b, int p){
    PlayerColor qp = WHITE;
    int score=0;
    if(p==0){
        qp = BLACK;
    }
    PlayerColor cp = b->data.player_to_play;
    if(cp==qp){
        if(b->in_check()){
            if(b->get_legal_moves().size()>0){
                score-=10;
            }
            else{
                score-=1000000;
            }
        }
    }
    else{
        if(b->in_check()){
            if(b->get_legal_moves().size()>0){
                score+=10;
            }
            else{
                score+=1000000;
            }
        }
    }
    return score;
}
int eval(Board *b, int p){
    int score = 0;
    if(p==0){
        score += 8*(margin_score(b,0))-8*(margin_score(b,1));
        if(movable_score(b,0)<10){
            score += 10*movable_score(b,0)-6*movable_score(b,1);
        }
        else if(movable_score(b,0)<20){
            score += 8*movable_score(b,0)-4*movable_score(b,1);
        }
        else{
            score += movable_score(b,0)-movable_score(b,1);
        }
        score += 5*(threat_score(b,1))-6*(threat_score(b,0));
        score += check_score(b,0);
    }
    else{
        score += 8*(margin_score(b,1))-8*(margin_score(b,0));
        score += movable_score(b,1)-movable_score(b,0);
        score += 5*(threat_score(b,0))-6*(threat_score(b,1));
        score += check_score(b,1);
    }
    return score;
}

pair<int,int> find_move(Board *b, int d, int alpha, int beta,int p, int maxd){
    auto moveset = b->get_legal_moves();
    vector<U16> moves(moveset.begin(),moveset.end());
    int res=0;
    int secmax=0;
    if(d==maxd || moves.size()==0){
        return make_pair(eval(b, p),d);
    }
    if(moves.size()<5){
        maxd+=1;
    }
    int temp_d = 0;
    if(d%2==0){
        for(uint i=0; i<moves.size(); i++){
            Board *temp_b = new Board(*b);
            temp_b->do_move_(moves[i]);
            pair<int,int> val = find_move(temp_b, d+1, alpha, beta, p, maxd);
            temp_d = val.second;
            if(d==0 && val.first>alpha){
                    secmax = res;
                    res=i;
            }
            alpha = max(alpha,val.first);
            if(beta<=alpha){
                break;
            }
        }
        if(d==0){
            return make_pair(res,secmax);
        }
        return make_pair(alpha,temp_d);
    }
    else{
        for(uint i=0; i<moves.size(); i++){
            Board *temp_b = new Board(*b);
            temp_b->do_move_(moves[i]);
            pair<int,int> val = find_move(temp_b, d+1, alpha, beta, p, maxd);
            temp_d = val.second;
            beta = min(beta,val.first);
            if(beta<=alpha){
                break;
            }
        }
        return make_pair(beta,temp_d);
    }
}

void Engine::find_best_move(const Board& b) {
    cout<<time_left<<endl;
    // pick a random move
    Board *temp_b = new Board(b);
    Board *temp_b2 = new Board(b);
    auto moveset = temp_b->get_legal_moves();
    if(moveset.size() == 0){
        this->best_move = 0;
        cout<<1<<endl;
        return;
    }
    vector<U16> moves(moveset.begin(),moveset.end());
    if(moveset.size()==1){
        this->best_move = moves[0];
    }
    int p = 0;
    if(b.data.player_to_play == WHITE){
        p=1;
    }
    pair<int,int> pr= find_move(temp_b, 0, INT_MIN, INT_MAX, p, 3);
    this->best_move = moves[pr.first];
    if(k==0){
        this->best_move = moves[4];
        k=k+1;
    }
    else{
        
    }
    vector<U8> currb;
    for(int i=0; i<64; i++){
        currb.push_back(temp_b2->data.board_0[i]);
    }
    for(uint i=0; i<prevb.size(); i++){
        bool bl = true;
        for(int j=0; j<64; j++){
            if(currb[j]!=prevb[i][j]){
                bl=false;
                break;
            }
        }
        if(bl==true){
            this->best_move = moves[pr.second];
            break;
        }
    }
    prevb.push_back(currb);
    //cout<<2<<endl;
    // auto moveset = b.get_legal_moves();
    // if (moveset.size() == 0) {
    //     this->best_move = 0;
    // }
    // else {
    //     std::vector<U16> moves;
    //     std::cout << all_boards_to_str(b) << std::endl;
    //     for (auto m : moveset) {
    //         std::cout << move_to_str(m) << " ";
    //     }
    //     std::cout << std::endl;
    //     std::sample(
    //         moveset.begin(),
    //         moveset.end(),
    //         std::back_inserter(moves),
    //         1,
    //         std::mt19937{std::random_device{}()}
    //     );
    //     this->best_move = moves[0];
    // }
}
