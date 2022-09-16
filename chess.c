#include <stdio.h>

//calculated values
int validate(int x,int y);


int main()
{

    //define chess board
    int table[8][8] = 
    { 
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},};

    //define horse moves 
    //first element tells you how much you will move on x axis(subtrasck or add to x coordinate)
    //the second element tells you how many you have to move on the y axis (subtrasck or add to y coordinate)
    //only valid moves
    int moves[8][2]=
    {
        {-2,1},// ^^>
        {-1,2},//^>>
        {1,2},// ˇ>>
        {2,1},//ˇˇ>

        {2,-1},// ˇˇ<
        {1,-2},//ˇ<<
        {-1,-2},// ^<<
        {-2,-1},//^^<
    };
    int temp_cor[8][2]={
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
        {0,0},
    };
    //our x,y coordinates 
    int x=4,y=4;
    //temporary coordinates so we can check the future steps
    int temp_x,temp_y;
    int c=1;
    //we check all the next move possible
    //after that we evaluate how many steps we can take after that
    //we choose the biggest value

    while(c!=0){
        for(int i=0;i<8;i++){
            temp_x = x+moves[i][0];
            temp_y = moves[i][1]+y;
            if(validate(temp_x,temp_y)){
                    //temp
                    temp_cor[i][0] = temp_x;
                    temp_cor[i][0] = temp_y;
            }
            else{
                temp_cor[i][0] = -1;
                temp_cor[i][0] = -1;
            }
        }
        //evaluate temp_moves and choose the largest

        c++;

    }

int validate(int x,int y){
    
    if(x<=8 && x>=0 && y<=8 && y>=0){
        return 1;
    }
    return 0;
}
    return 0;
}
