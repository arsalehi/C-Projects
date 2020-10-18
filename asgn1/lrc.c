#include <stdio.h>
#include <stdlib.h>

// following two functions are used to determine which player is
// directly to the left and right of the current player

// THESE FUNCTIONS WERE PROVIDED BY THE PROFESSOR IN ASGN1.PDF
unsigned int left(unsigned int pos, unsigned int players) {
  return ((pos + players - 1) % players);
}

unsigned int right(unsigned int pos, unsigned int players) {
  return ((pos + 1) % players);
}

int player_num = 0, seed;

typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};

int ind_bank[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
int pot = 0;

const char *names[] = {"Happy",      "Sleepy",      "Sneezy", "Dopey",
                       "Bashful",    "Grumpy",      "Doc",    "Mirror Mirror",
                       "Snow White", "Wicked Queen"};

// prints "Name is Rolling..."
void roll_prompt(int pos);
// prompt for when player rolls a PASS
void pass_prompt();
// prompt for when player rolls LEFT-- also updates bank
void left_prompt(int pos);
// prompt for when player rolls RIGHT-- also updates bank
void right_prompt(int pos);
// prompt for when player rolls CENTER-- also updates bank and pot
void center_prompt(int pos);
// checks to see if game should end-- aka if there is only one player with money
// in bank
int end_check(); // ACTUALLY BOOLEAN -- 1 MEANS GAME ENDS 0 MEANS GO ON
// prints final message declaring winner and their earnings
void end_prompt();

int main(void) {

  // handling seed and player number inputs
  printf("Random Seed: ");
  scanf("%u", &seed);
  srand(seed);
  // printf("How many Players? ");
  // scanf("%u", &player_num);

  while (player_num < 2 || player_num > 10) {
    printf("How many players? ");
    scanf("%u", &player_num);
  }

  int pos = 0, num_rolls = 0;

  // GAME LOOP-- runs if ending condition does not return 1/True/should end
  while (end_check() != 1) {

    // this snippet decides how many times a given player rolls based on bank
    switch (ind_bank[pos % player_num]) {
    case 0:
      num_rolls = 0;
      break;
    case 1:
      num_rolls = 1;
      roll_prompt(pos);
      break;
    case 2:
      num_rolls = 2;
      roll_prompt(pos);
      break;
    default:
      num_rolls = 3;
      roll_prompt(pos);
      break;
    }
    // this snippet performs the rolling and calls designated outcome functions
    for (int i = 0; i < num_rolls; ++i) {
      switch (die[rand() % 6]) {
      case LEFT:
        left_prompt(pos);
        break;
      case RIGHT:
        right_prompt(pos);
        break;
      case CENTER:
        center_prompt(pos);
        break;
      default:
        pass_prompt();
        break;
      }
    }
    if (num_rolls != 0) {
      printf("\n");
    }

    // increment position variable to move from player to player
    // do not account for player numbers here, mod%player_num is done in
    // functions
    ++pos;
  }
  // calls end prompt to designate winner
  end_prompt(pos);

  return 0;
}

// declaration of functions that were prototyped above
// explanation of functions is commented with prototypes

void roll_prompt(int pos) { printf("%s rolls...", names[pos % player_num]); }

void pass_prompt() { printf(" gets a pass"); }

void left_prompt(int pos) {
  printf(" gives $1 to %s", names[left(pos, player_num)]);
  --ind_bank[pos % player_num];
  ++ind_bank[left(pos, player_num)];
}

void right_prompt(int pos) {
  printf(" gives $1 to %s", names[right(pos, player_num)]);
  --ind_bank[pos % player_num];
  ++ind_bank[right(pos, player_num)];
}

void center_prompt(int pos) {
  printf(" puts $1 in the pot");
  --ind_bank[pos % player_num];
  ++pot;
}

int end_check() {
  int num_alive = 0;
  for (int i = 0; i < player_num; ++i) {
    if (ind_bank[i] != 0) {
      num_alive++;
    }
  }
  if (num_alive == 1) {
    return 1;
  } else {
    return 0;
  }
}

void end_prompt() {
  int winner_index = 0;
  for (int i = 0; i < player_num; ++i) {
    if (ind_bank[i] != 0) {
      winner_index = i;
    }
  }
  printf("%s wins the $%u pot with $%u left in the bank!", names[winner_index],
         pot, ind_bank[winner_index]);
}
