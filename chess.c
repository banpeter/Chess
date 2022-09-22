#include <stdio.h>
#include <string.h>

//calculated values
int validate(int x,int y,int table);
int test(int all_steps[63][2],int k);
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

    int all_steps[63][2];

    //our x,y coordinates 
    int x=0,y=0;
    
    //temporary coordinates so we can check the future steps
    int temp_x,temp_y;
    int c=0;
    int fail = 1;
    int counter=0;
    //largest moves
    int min,count,nom=0;//nom=number of move = index of move
    //we check all the next move possible
    //after that we evaluate how many steps we can take after that
    //we choose the biggest value
    int t;
    printf("Would you like to run the test?(0/1): ");
    scanf("%d",&t);
    if(!t){
        printf("Choose a starting position(x,y):");
        scanf("%d %d",&x,&y);
        x=x-1;
        y=y-1;
    }

    for(int a=0;a<8;a++){
        for(int b=0;b<8;b++){
            if(t){
                x=a;
                y=b;
            }
            
            counter++;
            memset(table,0,8*8*sizeof (int));

            while(c!=65){
            

            all_steps[c][0]=x;
            all_steps[c][1]=y;
            // for every coodinates we go through all the possible moves
            fail=0;
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
                printf("end\n");
                table[x][y]=1;
                for(int g=0;g<8;g++){
                    for(int h=0;h<8;h++){
                        printf("%i ",table[g][h]);
                    }
                    printf("\n");
                }
                break;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                //return 0;
            }

            //evaluate temp_moves and choose the largest
            //go through the temp_moves with the same algorithm
            min=100;
        
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
            }
            //taking the next step
        

            table[x][y]=1;
            x=temp_cor[nom][0];
            y=temp_cor[nom][1];
            //printf(" %i %i %i\n",x+1,y+1,c);
            
            
            /*for(int i=0;i<8;i++){
                printf("%i %i\n",temp_cor[i][0],temp_cor[i][1]);
            }*/
            /*printf(" %i %i %i\n",x+1,y+1,c);
            printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");*/
            
            c++;
            if(!t){
            for(int g=0;g<8;g++){
                for(int h=0;h<8;h++){
                    printf("%i ",table[g][h]);
                }
                printf("\n");
            }
            printf(" %i %i %i\n",x+1,y+1,c);
            printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
            }

        }
        /*if(t){
            for(int g=0;g<8;g++){
                for(int h=0;h<8;h++){
                    printf("%i ",table[g][h]);
                }
                printf("\n");
            }
            printf(" %i %i %i\n",x+1,y+1,c);
            printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
            }*/
        test(all_steps,counter);

        if(!t){break;}
            
        }
        if(!t){break;}
    }

    return 0;
}

//test
int test(int all_steps[63][2],int k){

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

}

//create an array for checking for all the coordinates if it really solved the problem