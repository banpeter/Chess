#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

//calculated values
int validate(int x,int y,int table);
int test(int all_steps[63][10][2],int k);
int solve(int table[8][8],int moves[8][2],int temp_cor[8][2],int all_steps[63][10][2],int x,int y,int t);
int show_board(int table[8][8],int x, int y);
int prev(int all_steps[63][10][2],int c,int x,int y);


int validate(int x,int y,int table){
    //printf("%i %i %i\n",x,y,table);
    if(x<8 && x>=0 && y<8 && y>=0 && table==0){
        //printf("%i %i***\n",x,y);
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
    int x=0,y=0;
    
    int all_steps[63][10][2];


    int counter=0;
    //largest moves
    
    int t;
    printf("Would you like to run the test?(0/1): ");
    scanf("%d",&t);
    if(!t){
        printf("Choose a starting position(x,y):");
        scanf("%d %d",&x,&y);
        x=x-1;
        y=y-1;
    }
    if(t){
        for(int a=0;a<8;a++){
            for(int b=0;b<8;b++){
                if(t){
                    x=a;
                    y=b;
                }
                counter++;

                
                solve(table,moves,temp_cor,all_steps,x,y,t);
                
                memset(table,0,8*8*sizeof (int));
                test(all_steps,counter);
                memset(all_steps,0,63*10*2*sizeof (int));

                
            }
            
        }
        
    }
    else{
        
        solve(table,moves,temp_cor,all_steps,x,y,t);

    }
    return 0;
}


//test
int test(int all_steps[63][10][2],int k){

    int same=-1;
    int f = 0;

    for(int i=0;i<63;i++){
        same=-1;
        
        for(int j=0;j<63;j++){
            if(all_steps[i][0]==all_steps[j][0] && all_steps[i][1]==all_steps[j][1]){
                
                same++;
            }
        }
        if(same){
            f++;
            break;
        }
        
    }
    if(f){
            printf("%i Fail!\n",k);
        }
        else{
            printf("%i Succes!\n",k);
        }
    return 1;

}
int show_board(int table[8][8],int x, int y){

    for(int g=0;g<8;g++){
        for(int h=0;h<8;h++){
            if(g==x && h==y){
                printf(ANSI_COLOR_RED "[%i] "ANSI_COLOR_RESET,table[g][h]);
            }
            else{
                printf(ANSI_COLOR_BLUE "[%i] "ANSI_COLOR_RESET ,table[g][h]);
            }
             

        }
        printf("\n");
        }
    printf("Current position: %i %i\n",x,y);
    printf("\n////////////////////////////////////////////\n");

}

int solve(int table[8][8],int moves[8][2],int temp_cor[8][2],int all_steps[63][10][2],int x,int y,int t){

            

            //temporary coordinates so we can check the future steps
            int temp_x,temp_y;
            int c=0;
            int fail = 1;
            int found;

            int min,count,nom=0;//nom=number of move = index of move
            //we check all the next move possible
            //after that we evaluate how many steps we can take after that
            //we choose the biggest value
            while(c<64){//65
            

            all_steps[c][0][0]=x;
            all_steps[c][0][1]=y;

            /*for(int v=0;v<5;v++){
                    printf("%d %d\n",all_steps[c][v][0],all_steps[c][v][1]);
                }
            */
            // for every coodinates we go through all the possible moves
            fail=0;
            //printf("%i %i dhkfgaskhdfgaksdfgahlksd",x,y);
            for(int i=0;i<8;i++){

                temp_x = x+moves[i][0];
                temp_y = y+moves[i][1];
                //table might return error if the indexes are invalid
                if(validate(temp_x,temp_y,table[temp_x][temp_y])){
                        //temp
                        temp_cor[i][0] = temp_x;
                        temp_cor[i][1] = temp_y;
                        fail=1;
                }
                else{
                    //printf("%i %i %i***********\n",temp_cor[i][0],temp_cor[i][1],table[temp_x][temp_y]);
                    temp_cor[i][0] = -1;
                    temp_cor[i][1] = -1;
                }
            }
            
            //if we found a possible move it does not fail and can take the next step
            //otherwise the program stops
            if(fail==0){
                
                //itt kell varázsolni
                printf("///////////////////////////////////////////////////////////////////////////////////////////////\n");
                //////////////////////////////////////////////A C megfelelő használata
                int finished = 0;
                do{
                    
                    printf("problem\n");
                    if(x==-1 && y==-1){
                            return 0;
                    }
                    if(all_steps[c][9][0]>1 && all_steps[c][9][1]!=all_steps[c][9][0]){///////////////////////////////////////////////////////////
                        //vegig kell turatni
                        //megnézem van-e 1-nél tobb min
                        //ha igen ugrani kell a kovetkezőre
                        printf("1\n");
                        printf("%i asdasdasdasd\n",c);
                        
                        printf("%i bbbbbbbbbbbb\n",all_steps[c][9][0]);
                        for(int z=1;z<all_steps[c][9][0];z++){
                            //printf("%i %i\n",all_steps[c-1][1][0],all_steps[c-1][1][1]);
                            printf("2\n");
                            show_board(table,all_steps[c][0][0],all_steps[c][0][1]);
                            for(int v=1;v<=all_steps[c][9][0];v++){
                            printf("%d %d\n",all_steps[c][v][0],all_steps[c][v][1]);
                            }
                            //meg kell nézni hogy mit választott és az alapján megnézni

                            printf("%d %d ++++++++\n",all_steps[c][0][0],all_steps[c][0][1]);//itt van
                            //table[all_steps[c+1][0][0]][all_steps[c+1][0][1]]=0;
                            printf("%d %d ++++++++\n",all_steps[c+1][0][0],all_steps[c+1][0][1]);//itt lesz

                            //meg kell allapítani hogy a kovetkezoben melyik
                            //itt allitja at -1-re
                            if(all_steps[c][z][0]=all_steps[c+1][0][0] && all_steps[c][z][1]==all_steps[c+1][0][1]){
                                printf("3\n");
                                all_steps[c][9][1] +=1;

                                all_steps[c][z][0]=-1;
                                all_steps[c][z][1]=-1;

                                

                                x=all_steps[c][z+1][0];
                                y=all_steps[c][z+1][1];
                                printf("%d %d ++++++++\n",x,y);
                                //???????
                                all_steps[c+1][0][0]=x;
                                all_steps[c+1][0][1]=y;
                                //terkepen 0
                                //c--;
                                
                                finished=1;
                                printf("3\n");
                                
                                show_board(table,x,y);
                                break;
                                
                                
                            }
                        }
                    }
                    else{
                        printf("4\n");
                        //previous step set to 0
                        table[all_steps[c-1][0][0]][all_steps[c-1][0][1]] = 0;
                        c--;
                        //töröljuk a jelenlegi koordinátát vagy csak vissza ugrunk1-et
                        //vissza lepunk egyet
                    }


                }while(!finished);///////////////////////////////////////
                printf("5\n");
                printf("%i %i\n",x,y);
             
         
                //table[x][y]=0;

                //return 0;
                
                
            }
            /*else{

            }*/

            //evaluate temp_moves and choose the largest
            //go through the temp_moves with the same algorithm
            if(fail){
            min=100;
            found=0;
            for(int j=0;j<8;j++){//check all the temporary coordinates
                count=0;
                for(int k=0;k<8;k++){//moves
                    if(temp_cor[j][0] != -1){
                        temp_x = temp_cor[j][0]+moves[k][0];
                        temp_y = temp_cor[j][1]+moves[k][1];
                        if(validate(temp_x,temp_y,table[temp_x][temp_y])){
                                count++;
                        }
                    }
                    
                }
                if(count<min && count>0){
                        min=count;
                        nom=j;
                        
                }
                //ez csak akkor fussson le ha nem fail-elt
                if(count<=min && count>0){
                        found++;
                        all_steps[c][found][0]=temp_cor[j][0];
                        all_steps[c][found][1]=temp_cor[j][1];
    
                        all_steps[c][9][0]=found;
                        all_steps[c][9][1]=1;      
                }            
            }
            }
            //taking the next step
        
            if(fail){
                printf("%i ggggggggggggggggggggggggggggggg\n",c);
                table[x][y]=c+1;
                x=temp_cor[nom][0];
                y=temp_cor[nom][1];
            }
            

            if(fail){
                //printf("%i ggggggggggggggggggggggggggggggg\n",c);
                c++;
                all_steps[c][9][0]=0;
            }
            

            if(!t){
                printf("bruh\n");
                show_board(table,x,y);
                }
            if(c==63){
               return 1; 
            } 
            }
            if(c==63){
               return 1; 
            }
            return 1;

        }





//create an array for checking for all the coordinates if it really solved the problem