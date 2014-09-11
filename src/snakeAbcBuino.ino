//imports the SPI library (needed to communicate with Gamebuino's screen)
#include <SPI.h>
//importe the Gamebuino library
#include <Gamebuino.h>

//creates a Gamebuino object named gb
Gamebuino gb = Gamebuino();

//logo
const byte PROGMEM logo[] =
{
64,36,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B11100111,B10001110,B00000000,B00000000,B00000000,
B00011101,B01001001,B01011101,B00010100,B01010000,B00000000,B00000000,B00000000,
B00010001,B11010101,B01010001,B00010100,B01010000,B00000000,B00000000,B00000000,
B00011101,B01011101,B10011001,B11110100,B01010000,B01100101,B01010101,B11000000,
B00000101,B01010101,B01010001,B00010111,B10010000,B01010101,B00011101,B01000000,
B11111101,B01010101,B01011101,B00010100,B01010000,B01100101,B01010101,B01000000,
B00000000,B00000000,B00000001,B00010100,B01010000,B01010101,B01010101,B01000000,
B00000000,B00000000,B00000001,B00010111,B10001110,B01100111,B01010101,B11000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00001111,B11011111,B10111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00001111,B11011111,B10111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00001111,B11011111,B10111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00001111,B11011111,B10111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00001111,B11011111,B10111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00001111,B11011111,B10111111,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B11110111,B11101111,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B11110111,B11101111,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B11110111,B11101111,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B11110111,B11101111,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B11110111,B11101111,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B11110111,B11101111,B11000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
};
//END logo

//sounds variables
enum soundsFxChannel_t {
  SND_FX_CHANNEL_1 = 0,
  SND_FX_CHANNEL_2 = 1,
  SND_FX_CHANNEL_3 = 2,
  SND_FX_CHANNEL_4 = 3
};

enum soundsFx_t {
  SND_FX_LETTER = 0,
  SND_FX_GAME_OVER = 1
};

const int soundfx[2][8] =
{
  {0,45,26,1,0,1,7,10}, // SND_FX_LETTER
  {0,30,34,10,0,1,7,25} // SND_FX_GAME_OVER
};
//END sounds variables

//game variables
boolean initialize = false;
int game_frame_rate = 20;//default 20
boolean game_over = false;
boolean game_menu = false;

short game_level = 1; // 1,2,3,4,5,6,7,8,9 Levels
short game_menu_level = game_level;
#define GAME_LEVEL_MAX 9
int game_levels[GAME_LEVEL_MAX] = { 300, 250, 200, 175, 150, 125, 100, 90, 80 };
int game_score = 0;
unsigned int game_delai = 200;
const short game_speed = 2;
unsigned long game_prevTime = 0;
//END game variables

//snake variables
#define SNAKE_MAX_SIZE 100
short snake_direction = 1; // 1: right, 2: left, 3: up, 4: down
int snake[100][2];
boolean snake_has_moved = true;
const short snake_w = 4;
const short snake_h = 4;
const short snake_v = 4;
int snake_head[2];
const int snake_default_size = 3;
int snake_size = snake_default_size;
//END snake variables

//letter variables
#define LETTERS_MAX_SIZE 26
int letter_x = 50;
int letter_y = 30;
const short letter_w = 4;
const short letter_h = 6;
short letter_index = 0;
short letter_max_index = 0;
boolean new_letter = false;
char letters[LETTERS_MAX_SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
//END letter variables

//the setup routine runs once when Gamebuino starts up
void setup(){
  //initialize the Gamebuino object
  gb.begin();
  gb.pickRandomSeed();
  
  //display the main menu
  gb.titleScreen(logo);

  gb.battery.show = false;//hide the battery indicator
}

//the loop routine runs over and over again forever
void loop(){
  if (!initialize) {
    InitGame();
  }
  
  if(gb.update()){
    if (!game_over && !game_menu) {
      if(gb.buttons.pressed(BTN_C)){
          gb.sound.playCancel();
          game_menu = true;
      }
      
      Play();
    }
    else if (game_menu) {
      GameMenu();
    }
    else if (game_over) { 
      GameOver();
    }
  }
}

void InitGame() {
  //gb.setFrameRate(game_frame_rate);
  
  snake_size = snake_default_size;
  snake_direction = 1;
  for(byte index = 0; index < SNAKE_MAX_SIZE; index++) {
    if (index == 0) {
      snake[index][0] = 30;
      
      snake_head[0] = 30;
      snake_head[1] = 30;
    }
    else {
      snake[index][0] = 30 - (index * (snake_w + 1));
    }
    snake[index][1] = 30;
  }
  
  letter_index = 0;
  letter_max_index = 0;
  
  game_score = 0;
  game_menu_level = game_level;
  game_delai = game_levels[game_level-1];
  game_over = false;
  
  initialize = true;
}

void Play() {
  MoveSnake();
      
  DrawField();
  DrawSnake();
  DrawLetter();
  
  if (game_over) {
    PlaySoundFxGameOver();
  }
}

void GameMenu() {
  gb.display.cursorX = 5;
  gb.display.cursorY = 1;
  gb.display.print(F("-CHOOSE GAME LEVEL-"));
  
  gb.display.fillTriangle(30, 10, 25, 15, 35, 15);
  gb.display.fillTriangle(30, 28, 25, 23, 35, 23);
    
  gb.display.cursorX = 0;
  gb.display.cursorY = 17;
  gb.display.print("LEVEL: " + String(game_menu_level));

  gb.display.cursorX = 0;
  gb.display.cursorY = 40;
  gb.display.print(F("\x15:accept \x16:cancel"));
  
  if(gb.buttons.pressed(BTN_UP)){
    if ((game_menu_level + 1) <= GAME_LEVEL_MAX) {
      game_menu_level++;
    }
  }
  if(gb.buttons.pressed(BTN_DOWN)){
    if ((game_menu_level - 1) >= 1) {
      game_menu_level--;
    }
  }
  if(gb.buttons.pressed(BTN_A)){
    gb.sound.playOK();
    
    game_level = game_menu_level;
    initialize = false;
    game_menu = false;
  }
  if(gb.buttons.pressed(BTN_B)){
    gb.sound.playOK();

    game_menu = false;
  }
  if(gb.buttons.pressed(BTN_C)){
    gb.sound.playOK();
    
    gb.changeGame();
  }
}

void GameOver() {
  gb.display.cursorX = 22;
  gb.display.cursorY = 1;
  gb.display.print(F("!GAME OVER!"));
  
  gb.display.cursorX = 0;
  gb.display.cursorY = 10;
  gb.display.print("Score:" + String(game_score) + " (x" + String(game_level) + ")= " + String(game_score * game_level));

  String game_letters = "";
  for (int i = 0; i < letter_max_index; i++) {
    game_letters += " " + String(letters[i]);
  }
  gb.display.cursorX = 0;
  gb.display.cursorY = 20;
  gb.display.textWrap = true;
  gb.display.print(game_letters);
  gb.display.textWrap = false;
  
  gb.display.cursorX = 0;
  gb.display.cursorY = 40;
  gb.display.print(F("\x16:accept"));
  if(gb.buttons.pressed(BTN_B)){
    gb.sound.playOK();
    
    initialize = false;
    game_over = false;
  }
}

void MoveSnake() {
  int last[2] = { snake[0][0], snake[0][1] };
  int next[2] = { snake[0][0], snake[0][1] }; 

  if (snake_has_moved) {
    if (gb.buttons.repeat(BTN_RIGHT, 1) && snake_direction != 2 && snake_direction != 1) {
      snake_direction = 1;
      snake_has_moved = false;
    }
    else if (gb.buttons.repeat(BTN_LEFT, 1) && snake_direction != 1 && snake_direction != 2) {
      snake_direction = 2;
      snake_has_moved = false;
    }
    else if (gb.buttons.repeat(BTN_UP, 1) && snake_direction != 4 && snake_direction != 3) {
      snake_direction = 3;
      snake_has_moved = false;
    }
    else if (gb.buttons.repeat(BTN_DOWN, 1) && snake_direction != 3 && snake_direction != 4) {
      snake_direction = 4;
      snake_has_moved = false;
    }
  }

  unsigned long game_currentTime = millis();
  if ((game_currentTime - game_prevTime) >= game_delai) {
    if(snake_direction == 1) {
      next[0] += (snake_v + 1);
    }
    else if(snake_direction == 2) {
      next[0] -= (snake_v + 1); 
    }
    else if(snake_direction == 3) {
      next[1] -= (snake_v + 1);  
    }
    else if(snake_direction == 4) {
      next[1] += (snake_v + 1);   
    }
  
    snake_head[0] = next[0];
    snake_head[1] = next[1];
      
    //check collision with letter
    CheckLetterCollision();
    
    //check collision with border
    if (next[0] > LCDWIDTH || next[0] < 0 || next[1] < 0 || next[1] > LCDHEIGHT) {
      game_over = true;
    }
      
    //move snake
    for(byte index = 0; index < SNAKE_MAX_SIZE; index++) {
      last[0] = snake[index][0];
      last[1] = snake[index][1];
      
      //check collision with snake
      //if (index > 0 && index < snake_size && snake_head[0] == snake[index][0] && snake_head[1] == snake[index][1]) {
      if (index > 0 && index < snake_size && gb.collideRectRect(snake_head[0], snake_head[1], snake_w - 1, snake_h - 1, next[0], next[1], snake_w - 1, snake_h - 1)) {    
        game_over = true;
      }
      
      snake[index][0] = next[0];
      snake[index][1] = next[1];

      next[0] = last[0];
      next[1] = last[1];
    }
    
    //update prevtime
    game_prevTime = game_currentTime;
    snake_has_moved = true;
  }
}

void CheckLetterCollision() {
  if (gb.collideRectRect(snake[0][0], snake[0][1], snake_w, snake_h, letter_x, letter_y, letter_w, letter_h)) {
    new_letter = true;

    if ((letter_index + 1) <= (LETTERS_MAX_SIZE - 1)) {
      letter_index++;
      if (letter_max_index != LETTERS_MAX_SIZE) {
        letter_max_index++;
      }
    }
    else {
      letter_index = 0;
      letter_max_index = LETTERS_MAX_SIZE;
    }
      
    PlaySoundFxLetter();
      
    UpdateGameScore();
  }
}

void UpdateGameScore() {
  game_score++;
      
  //increase snake speed, snake size
  if (game_delai > 60) {
    game_delai -= game_speed;
  }
  snake_size++;// = snake_size + 1;
}

//int isRectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
//rect1: start point (x1,y1) with height=h1 and width=w1
//rect2: start point (x2,y2) with height=h2 and width=w2
//  return !( x2     >  x1+w1  || 
//            x2+w2  <  x1     || 
//            y2     >  y1+h1  ||
//            y2+h2  <  y1     );
//}

void DrawField() {
  gb.display.drawRect(0, 0, LCDWIDTH, LCDHEIGHT);
}

void DrawLetter() {
  if (new_letter) {
    int x = -1;
    int y = -1;
  
    while(new_letter) {
      if (x == -1) {
        x = random((0 + letter_w), (LCDWIDTH - letter_w));
      }
      if (y == -1) {
        y = random((0 + letter_h), (LCDHEIGHT - letter_h));
      }
      
      for(byte index = 0; index < snake_size; index++) {
        if (gb.collideRectRect(snake[index][0], snake[index][1], snake_w, snake_h, x, y, letter_w, letter_h)) {
          x = -1;
          y = -1;
          break;
        }
      }
      
      if (x != -1 && y != -1) {
        letter_x = x;
        letter_y = y;
        new_letter = false;
      }
    }
  }
  
  gb.display.fontSize = 1;
  gb.display.cursorX = letter_x;
  gb.display.cursorY = letter_y;
  gb.display.print(letters[letter_index]);
}

void DrawSnake() {
  for(byte index = 0; index < snake_size; index++) {
    gb.display.fillRect(snake[index][0], snake[index][1], snake_w, snake_h);
  }
}

void ShowFrame() {
  //declare a variable named count of type integer :
  int count;
  //get the number of frames rendered and assign it to the "count" variable
  count = gb.frameCount;
  //prints the variable "count"
  gb.display.cursorX = 1;
  gb.display.cursorY = 1;
  ShowDebug(String(count));
}

void ShowDebug(String message) {
  //print debug line
  gb.display.fontSize = 1;
  gb.display.cursorX = 1;
  gb.display.cursorY = 1;
  gb.display.print("[ " + message + " ]");
}

void PlaySoundFxLetter() {
  //gb.sound.playTick();
  PlaySoundFx(SND_FX_LETTER, SND_FX_CHANNEL_1);
}

void PlaySoundFxGameOver() {
  PlaySoundFx(SND_FX_GAME_OVER, SND_FX_CHANNEL_1);
}

//Play Gambuino sound effect (http://www.yodasvideoarcade.com/gamebuino.php)
void PlaySoundFx(int fxno, int channel) {
  gb.sound.command(0,soundfx[fxno][6],0,channel); // set volume
  gb.sound.command(1,soundfx[fxno][0],0,channel); // set waveform
  gb.sound.command(2,soundfx[fxno][5],-soundfx[fxno][4],channel); // set volume slide
  gb.sound.command(3,soundfx[fxno][3],soundfx[fxno][2]-58,channel); // set pitch slide
  gb.sound.playNote(soundfx[fxno][1],soundfx[fxno][7],channel); // play note
}

