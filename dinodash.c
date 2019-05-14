/*
  Authors: Natalie Soluren and John Russel Garcia
*/
#include "../../sdk/dexsdk.h"

//--constants
#define max_row 25
#define max_col 78
#define jump_key ' '
#define quit_key 'q'
#define restart_key 'r'
#define MAX_STRING_SIZE 100

//-- prototypes
void draw_line(int col, int row);
void draw_road();
void HomeScreen();
void print_statistices();
void draw();
void draw_dinosaur();
void draw_obstacles();
void collision();
void GameOverScreen();


//-- ASCII objects
char dino_text[9][MAX_STRING_SIZE];
char dash_text[9][MAX_STRING_SIZE];
char dinosaur[6][MAX_STRING_SIZE];
char dinosaur2[6][MAX_STRING_SIZE];
char dinosaur_dead[6][MAX_STRING_SIZE];
char tree[3][MAX_STRING_SIZE];
char gameover_text[9][MAX_STRING_SIZE];

//--globals
char keypress;
char ignore;
int animate = 0;


//initials:
int lives = 3;
int level = 1;
int score = 0;
int dino_jump = 0;
int dino_position = 0;

int obstacle[3] = {0,-25,-50};

int main(){
  clrscr();
  do{

    //homescreen
    while(keypress != jump_key){
      clrscr();
      HomeScreen();
      if(kb_ready()){
        keypress=(char)getch();
      }
      delay(10);
      animate ++;
    }

    //game start
    clrscr();
    while(keypress != quit_key){
      clrscr(); // clear screen

      //drawing elements:
      draw_dinosaur();
      draw_road();
      draw_obstacles();
      delay(6);

      if(kb_ready()){ //actions
        if(dino_position == 0){
          keypress=(char)getch();
        }else{
          ignore=(char)getch();
        }
      }

      if(keypress == jump_key){//jump key pressed
        dino_jump = 4; //if it's not jumping already, jump.
      }else if(keypress == quit_key || lives == 0){
        GameOverScreen();
        keypress = quit_key;
        break;
      }

      collision();
      keypress = '#';
      score++;
      level = score/100;
      animate ++;
    }


  }while(keypress != quit_key);

}

//adjust na lang na ung paa di ung ulo. tahnsk.
void collision(){
  for(int i = 0; i<3; i++){
    if(obstacle[i]>=61 && obstacle[i]<=63&& dino_jump ==0){
      gotoxy(0,10); textcolor(YELLOW);
      printf("OUCH!++++++++++++++++ \n");
      lives--;
    }
  }
}
void HomeScreen(){
  draw(dino_text, 10, 2,9,0);
  draw(dash_text, 20, 11,9,2);
  gotoxy(20,21); textcolor(YELLOW);
  printf("PRESS SPACE TO START THE GAME... \n");
  draw_road();
}

void GameOverScreen(){
  clrscr();
  draw(gameover_text, 0, 5,9,1);
  gotoxy(20,19); textcolor(YELLOW);
  printf("PRESS R TO RESTART THE GAME... \n");
  gotoxy(20,20); textcolor(YELLOW);
  printf("PRESS Q TO QUIT... \n");
  draw_road();
  draw(dinosaur_dead,57,16,6,2);
  do{
      keypress = (char)getch();
  }while(keypress != quit_key && keypress != restart_key );
  if(keypress == restart_key){
    lives = 5;
    score = 0;
    level = 1;
    obstacle[0] = 0;
    obstacle[1] = -25;
    obstacle[2] = -50;

    main();
  }
  clrscr();
}
void draw_road(){
    textcolor(LIGHTBLUE);
    draw_line(0,21);
    textcolor(GREEN);
    draw_line(0,22);
    print_statistices();
}

void draw_line(int col, int row){
  gotoxy(col,row);
  for (col=0;col<max_col+2;col++) printf("-");
  printf("\n");
}

void print_statistices(){
  gotoxy(17, 24); textcolor(GREEN);
  printf("L i v e s : %d   L e v e l : %d   S c o r e : %d\n", lives, level, score);
}

void draw(char object[][MAX_STRING_SIZE], int col, int row, int size, int coloring){
  char color = BLUE;
  char color2 = LIGHTBLUE;
  char temp;
  if(coloring == 1){
    color = RED;
    color2 = LIGHTRED;
  }else if(coloring ==2){
    color = GREEN;
    color2 = LIGHTGREEN;
  }
  //alter
  if(animate%2 == 0){
    temp = color;
    color = color2;
    color2 = temp;
  }

  char alter = color;
  for (int i = 0; i<size; i++){
    alter = (alter == color)? color2: color;
    gotoxy(col, row+i); textcolor(alter);
    printf("%s\n",object[i]);
  }
}

void draw_dinosaur(){
  int pos = 16;
  if(dino_jump>0){
    dino_jump--;
    dino_position++;
  }
  if(dino_position!=0 &&dino_jump==0) dino_position--; //if in the air and no more jump, go back to the ground.
  pos = pos - dino_position;
  if(animate%2 == 0){
    draw(dinosaur,61,pos,6,2);
  }else{
    draw(dinosaur2,61,pos,6,2);
  }
}
void draw_obstacles(){
    for(int i = 0; i<3; i++){
      draw(tree,obstacle[i],21,3,1);
      if(obstacle[i]==max_col) obstacle[i] = 0;
      obstacle[i] = obstacle[i] + 3;
    }
}

char dino_text[9][MAX_STRING_SIZE] =
{
":.:.:.:........::....:..::::..::.......::.:.:.:.:",
":.:.:.:'########:'####'##::: ##:'#######:':.:.:.:",
":.:.:.: ##.... ##. ##::###:: ##'##.... ##::.:.:.:",
":.:.:.: ##:::: ##: ##::####: ##:##:::: ##::.:.:.:",
":.:.:.: ##:::: ##: ##::## ## ##:##:::: ##::.:.:.:",
":.:.:.: ##:::: ##: ##::##. ####:##:::: ##::.:.:.:",
":.:.:.: ##:::: ##: ##::##:. ###:##:::: ##::.:.:.:",
":.:.:.: ########:'####:##::. ##. #######:::.:.:.:",
":.:.:.:........::....:..::::..::.......::.:.:.:.:",
};

char dash_text[9][MAX_STRING_SIZE] =
{
":.:.:.:.......::..:::::..::......::..:::::..::.:.:.:",
":.:.:.:########::::'###::::'######:'##::::'##:.:.:.:",
":.:.:.:##.... ##::'## ##::'##... ##:##:::: ##:.:.:.:",
":.:.:.:##:::: ##:'##:. ##::##:::..::##:::: ##:.:.:.:",
":.:.:.:##:::: ##'##:::. ##. ######::#########:.:.:.:",
":.:.:.:##:::: ##:#########:..... ##:##.... ##:.:.:.:",
":.:.:.:##:::: ##:##.... ##'##::: ##:##:::: ##:.:.:.:",
":.:.:.:########::##:::: ##. ######::##:::: ##:.:.:.:",
":.:.:.:.......::..:::::..::......::..:::::..::.:.:.:",
};

//pakibaliktad pre. katamad. lol.
char dinosaur[6][MAX_STRING_SIZE] =
{
"               __ ",
"              / _)",
"     _.----._/ /  ",
"    /         /   ",
" __/ (  | (  |    ",
"/__.-'|_|--|_|    ",
};
//pakibaliktad pre. katamad. lol.
char dinosaur2[6][MAX_STRING_SIZE] =
{
"               __ ",
"              / _)",
"     _/\\/\\/\\_/ /  ",
"   _|         /   ",
" _|  (  | (  |    ",
"/__.-'|_|--|_|    ",
};

char dinosaur_dead[6][MAX_STRING_SIZE] =
{
"                    __ ",
"                   / _)",
"     _/\\/\\/\\_/ /  ",
"   _|         /   ",
" _|  (  | (  |    ",
"/__.-'|_|--|_|    ",
};

char tree[3][MAX_STRING_SIZE] =
{
"#",
"#",
"#",
};

char gameover_text[9][MAX_STRING_SIZE]=
{
"::......:::..:::::..:..:::::..:........:::.......:::::...::::........:..:::::..::",
"::'######:::::'###:::'##::::'##'########::'#######:'##::::'##'########'########::",
":'##... ##:::'## ##:::###::'###:##.....::'##.... ##:##:::: ##:##.....::##.... ##:",
"::##:::..:::'##:. ##::####'####:##::::::::##:::: ##:##:::: ##:##:::::::##:::: ##:",
"::##::'####'##:::. ##:## ### ##:######::::##:::: ##:##:::: ##:######:::########::",
"::##::: ##::#########:##. #: ##:##...:::::##:::: ##. ##:: ##::##...::::##.. ##:::",
"::##::: ##::##.... ##:##:.:: ##:##::::::::##:::: ##:. ## ##:::##:::::::##::. ##::",
":. ######:::##:::: ##:##:::: ##:########:. #######:::. ###::::########:##:::. ##:",
"::......:::..:::::..:..:::::..:........:::.......:::::...::::........:..:::::..::",
};
