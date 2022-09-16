#include <stdio.h>

//calculated values
int validate(int x,int y,int table);

int validate(int x,int y,int table){
    
    if(x<=8 && x>=0 && y<=8 && y>=0 && !table){
        return 1;
    }
    return 0;
}





int main()
{
    printf("Starting...\n");
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
    //next posible positions from x,y coordinates
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
    int fail = 1;
    //largest moves
    int max,count,nom=0;//nom=number of move = index of move
    //we check all the next move possible
    //after that we evaluate how many steps we can take after that
    //we choose the biggest value

    while(c!=0){
        table[x][y]=1;
        // for every coodinates we go through all the possible moves
        fail=1;
        for(int i=0;i<=8;i++){

            temp_x = x+moves[i][0];
            temp_y = y+moves[i][1];
            if(validate(temp_x,temp_y,table[x][y])){
                    //temp
                    temp_cor[i][0] = temp_x;
                    temp_cor[i][1] = temp_y;
                    fail=0;
            }
            else{
                temp_cor[i][0] = -1;
                temp_cor[i][1] = -1;
            }
        }
        //if we found a possible move it does not fail and can take the next step
        //othrewise it program stops
        if(fail){
            return 0;
        }

        //evaluate temp_moves and choose the largest
        //go through the temp_moves with the same algorithm
        max=0;
        for(int j=0;j<=8;j++){//check all the temporary coordinates
            count=0;
            for(int k=0;k<=8;k++){//moves
                temp_x = temp_cor[j][0]+moves[k][0];
                temp_y = temp_cor[j][1]+moves[k][1];
                if(validate(temp_x,temp_y,table[x][y])){
                        count++;
                }
            }
            if(count>max){
                max=count;
                nom=j;
            }
            
        }
        //taking the next step
        printf("%i %i\n",x,y);
        x=temp_cor[nom][0];
        y=temp_cor[nom][1];
        c++;

    }




    return 0;
}
