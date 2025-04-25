//IT23231528_Implementing a Two-Player Yahtzee Game in C 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define NUM_DICE 5
#define NUM_ROLLS 3
#define NUM_ROUNDS 13


// Function to simulate rolling a single die
int rollDice() {
    return(rand() % 6) + 1; // return random number  1-6 
}

// Function to roll all dice
void rollAllDice(int dice[]) {
    for (int i = 0; i< NUM_DICE; i++) {
        dice[i] = rollDice();
    }
}

// Function to display the dice values
void displayDice(int dice[]) {
    printf("Current Dice: ");
     for (int i = 0; i< NUM_DICE; i++) {
        printf("%d ", dice[i]);
    }
    printf("\n");
}

// Function to score "One"
int scoreOne(int dice[]) {
    int totalScore = 0;
     for (int i = 0; i< NUM_DICE; i++) {
        if (dice[i] ==1){
            totalScore += 1; 
        }
    }
    return totalScore;
}

// Function to score "Two"
int scoreTwo(int dice[]) {
    int totalScore = 0;
    for (int i = 0; i < NUM_DICE; i++) {
        if (dice[i] == 2) {
            totalScore += 2; 
        }
    }
    return totalScore;
}

// Function to score "Three"
int scoreThree(int dice[]) {
    int totalScore = 0;
      for (int i = 0; i< NUM_DICE; i++) {
        if (dice[i] ==3) {
            totalScore += 3;
        }
    }
    return totalScore;
}


// Function to score "Four"
int scoreFour(int dice[]) {
    int totalScore = 0;
      for (int i = 0; i< NUM_DICE; i++) {
        if (dice[i] == 4) {
            totalScore += 4;
        }
    }
    return totalScore;
}


// Function to score "Five"
int scoreFive(int dice[]) {
    int totalScore = 0;
      for (int i = 0; i< NUM_DICE; i++) {
        if (dice[i] == 5) {
            totalScore += 5;
        }
    }
    return totalScore;
}

// Function to score "Six"
int scoreSix(int dice[]) {
    int totalScore = 0;
    for (int i = 0; i< NUM_DICE; i++) {
        if (dice[i] == 6) {
            totalScore += 6; 
        }
    }
    return totalScore;  
}


// function to score "Three of a Kind"
int scoreThreeOfAKind(int dice[]) {
    int counts[6] = {0}; // Count occurrences of each die face
      for (int i = 0; i< NUM_DICE; i++) {
        counts[dice[i] - 1]++;
    }
    for (int i = 0; i < 6; i++) {
        if (counts[i] >= 3) {
            return dice[0] + dice[1] + dice[2] + dice[3] + dice[4]; // Sum of all dice
        }
    }
    return 0; 
}

//  function to score "Four of a Kind"
int scoreFourOfAKind(int dice[]) {
    int counts[6] = {0}; 
    for (int i = 0; i < NUM_DICE; i++) {
        counts[dice[i] - 1]++;
    }
    for (int i = 0; i < 6; i++) {  // any die face appears 4 or more times
        if (counts[i] >= 4) {
            return dice[0] + dice[1] + dice[2] + dice[3] + dice[4];
        }
    }

  
    return 0;
}

// Function to score "Full House"
int scoreFullHouse(int dice[]) {
    int counts[6] = {0}; 
      for (int i = 0; i< NUM_DICE; i++) {
        counts[dice[i] - 1]++;
    }

    int hasThreeOfAKind = 0;
    int hasPair = 0;

    // Check for three of a kind and a pair
    for (int i = 0; i < 6; i++) {
        if (counts[i] == 3) {
            hasThreeOfAKind = 1;
        }
        if (counts[i] == 2) {
            hasPair = 1;
        }
    }
    
    if (hasThreeOfAKind && hasPair) {  // If both conditions are met, return 25
        return 25; 
    }

    return 0; 
}

// Function to check for a Small Straight 
int scoreSmallStraight(int dice[]) {
    int counts[6] = {0}; 
    
       for (int i = 0; i< NUM_DICE; i++) {
        counts[dice[i] - 1]++;
    }
    
    if ((counts[0] >= 1 && counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1) || // 1-2-3-4
        (counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1) || // 2-3-4-5
        (counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1)) { // 3-4-5-6
        return 30;  
    }

    return 0;  
}

// Function to score "Large Straight"
int scoreLargeStraight(int dice[]) {
    int counts[6] = {0};  
    
      for (int i = 0; i< NUM_DICE; i++) {
        counts[dice[i] - 1]++;
    }
    
    if ((counts[0] >= 1 && counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1) || // 1-2-3-4-5
        (counts[1] >= 1 && counts[2] >= 1 && counts[3] >= 1 && counts[4] >= 1 && counts[5] >= 1)) { // 2-3-4-5-6
        return 40;  
    }

    return 0;  
}

// Function to score "Yahtzee"
int scoreYahtzee(int dice[]) {
    int counts[6] = {0};  
    
      for (int i = 0; i< NUM_DICE; i++) {
        if (dice[i] >= 1 && dice[i] <= 6) {
            counts[dice[i] - 1]++;
        }
    }

    for (int i = 0; i < 6; i++) {  // Check all 5 dices shows same number 
        if (counts[i] == NUM_DICE) {
            return 50; 
        }
    }

    return 0;  
}

// Function to score "Chance"
int scoreChance(int dice[]) {
    int totalScore = 0;
    
    for (int i = 0; i< NUM_DICE; i++) {
        totalScore += dice[i];
    }

    return totalScore; 
}

// Function for the human player's turn
void playerTurn(int dice[], int *score) {
    int rolls = 1;
    char choice;
    rollAllDice(dice); 
    
    while (rolls < NUM_ROLLS) {
        displayDice(dice);
        printf("Do you want to re-roll any dice? (y/n): ");
        scanf(" %c", &choice);
        
        while (getchar() != '\n'); //consume characters up to a new line
        if (choice == 'n') {
            break;
        }
        
        printf("Enter the dice you want to re-roll (1-5, separated by spaces): ");
        
        // read the users rerolling input dices
        char rerollInput[100];
        fgets(rerollInput, sizeof(rerollInput), stdin); 
        
        // Process the input
        int reroll;
        char *token = strtok(rerollInput, " ");  // Split the input by spaces
        
        while (token != NULL) {
            reroll = atoi(token);  // Convert token to an integer
            if (reroll >= 1 && reroll <= NUM_DICE) {
                dice[reroll - 1] = rollDice(); // Re-roll selected dice
            }
            token = strtok(NULL, " ");  // Get the next number
        }

        rolls++;
    }
    displayDice(dice); 

    // Choose a scoring category
    printf("\nChoose a scoring category:\n");
    printf("1.  Ones\n");
    printf("2.  Twos\n");
    printf("3.  Threes\n");
    printf("4.  Fours\n");
    printf("5.  Fives\n");
    printf("6.  Sixes\n");
    printf("7.  Three of a Kind\n");
    printf("8.  Four of a Kind\n");
    printf("9.  Full House\n");
    printf("10. Small Straight\n");
    printf("11. Large Straight\n");
    printf("12. Yahtzee\n");
    printf("13. Chance\n\n");
    printf("Enter your choice (1-13): ");
    
    int choiceNum;
    scanf("%d", &choiceNum);

    int scoreForRound = 0;
    switch (choiceNum) {
    	
    	case 1: 
		     scoreForRound = scoreOne(dice); 
			 break;
			 
        case 2: 
		     scoreForRound = scoreTwo(dice); 
		     break;
		
        case 3:
		     scoreForRound = scoreThree(dice); 
		     break;
		     
        case 4: 
		     scoreForRound = scoreFour(dice); 
		     break;
		     
        case 5:
		     scoreForRound = scoreFive(dice);
		     break;
		     
        case 6: 
		     scoreForRound = scoreSix(dice);
		     break;
		     
        case 7:
		     scoreForRound = scoreThreeOfAKind(dice); 
		     break;
		     
        case 8:
		     scoreForRound = scoreFourOfAKind(dice); 
		     break;
		     
        case 9: 
		     scoreForRound = scoreFullHouse(dice); 
		     break;
		     
        case 10:
		     scoreForRound = scoreSmallStraight(dice); 
		     break;
		     
        case 11:
		     scoreForRound = scoreLargeStraight(dice); 
		    break;
		    
        case 12:
		     scoreForRound = scoreYahtzee(dice);
		    break;
		    
        case 13:
		    scoreForRound = scoreChance(dice);
		    break;
		    
        default: printf("Invalid choice.\n"); 
		break;
    }
    
    *score += scoreForRound;
    printf("Human Score: %d\n", *score);
}

// Function for the computer's turn
void computerTurn(int dice[], int *score) {
    int rolls = 1;
    
    rollAllDice(dice); //1 st roll
    displayDice(dice); // Display the dice after the  1st roll
    
    while (rolls < NUM_ROLLS) {
    	rollAllDice(dice); //  2 nd Re-roll 
        displayDice(dice);
        rolls++;
    }
    
    int category = rand() % 13 + 1;  // Random choice between 1 and 13
    int scoreForRound = 0;
    
    switch (category) {
    	
        	case 1: 
		     scoreForRound = scoreOne(dice); 
			 break;
			 
        case 2: 
		     scoreForRound = scoreTwo(dice); 
		     break;
		
        case 3:
		     scoreForRound = scoreThree(dice); 
		     break;
		     
        case 4: 
		     scoreForRound = scoreFour(dice); 
		     break;
		     
        case 5:
		     scoreForRound = scoreFive(dice);
		     break;
		     
        case 6: 
		     scoreForRound = scoreSix(dice);
		     break;
		     
        case 7:
		     scoreForRound = scoreThreeOfAKind(dice); 
		     break;
		     
        case 8:
		     scoreForRound = scoreFourOfAKind(dice); 
		     break;
		     
        case 9: 
		     scoreForRound = scoreFullHouse(dice); 
		     break;
		     
        case 10:
		     scoreForRound = scoreSmallStraight(dice); 
		     break;
		     
        case 11:
		     scoreForRound = scoreLargeStraight(dice); 
		    break;
		    
        case 12:
		     scoreForRound = scoreYahtzee(dice);
		    break;
		    
        case 13:
		    scoreForRound = scoreChance(dice);
		    break;
		    
        default: printf("Invalid choice.\n"); 
		break;
    }

    *score += scoreForRound;
    printf("Computer Score: %d\n", *score);
}

int main() {
    srand(time(NULL));  // Initialize random number generator
    int humanScore = 0;
    int computerScore = 0;
    int dice[NUM_DICE];

    printf("WELCOME TO YAHATZEE\n\n");
    
    
	printf("The scoring categories include options like:\n");
    printf("Upper section:\n");
    printf("1. Ones:   Score the sum of all dice showing the value of 1\n");
    printf("2. Twos:   Score the sum of all dice showing the value of 2\n");
    printf("3. Threes: Score the sum of all dice showing the value of 3\n");
    printf("4. Fours:  Score the sum of all dice showing the value of 4\n");
    printf("5. Fives:  Score the sum of all dice showing the value of 5\n");
    printf("6. Sixes:  Score the sum of all dice showing the value of 6\n\n");
    
    printf("Lower section:\n");
    printf("7.  Three of a Kind: If at least three of them are the same 'Score the sum of all dice'.\n");
    printf("8.  Four of a Kind:  If at least four of them are the same 'Score the sum of all dice'.\n");
    printf("9.  Full House: If you got combination of three of one number and two of another ' Score 25 points'.\n");
    printf("10. Small Straight: Score 30 points for four consecutive numbers.\n");
    printf("11. Large Straight: Score 40 points for five consecutive numbers.\n");
    printf("12. Yahtzee: Score 50 points for five dice showing the same number.\n");
    printf("13. Chance: Score the sum of all dice.\n\n");
    
     printf("Let's start\n\n");



    //play rounds 13
    for (int round = 0; round < NUM_ROUNDS; round++) {
        printf("--- Round %d ---\n", round + 1);

        // human's turn
        printf("Human's turn:\n");
        playerTurn(dice, &humanScore);

        // computer's turn 
        printf("\nComputer's turn:\n");
        computerTurn(dice, &computerScore);

        printf("\n");
    }

    printf("Game Over!\n");
    printf("Final Human Score: %d\n", humanScore);
    printf("Final Computer Score: %d\n", computerScore);

    if (humanScore > computerScore) {
        printf("Human wins!!\n");
    } else if (humanScore < computerScore) {
        printf("Computer wins!!\n");
    } else {
        printf("It's a tie!\n");
    }

    return 0;
}
