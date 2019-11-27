from random import randint

player_BO3_score = 0
computer_BO3_score = 0
# Have computer make a random roll from the array of options
computer_possible_choices = ["Rock", "Paper", "Scissors"]
computer_choice = (computer_possible_choices[randint(0, 2)])
# Run game until one player reaches 3 points
while computer_BO3_score < 3 and player_BO3_score < 3:
    # Have Player select RP or S
    player_choice = input("Choose one: Rock, Paper, or Scissors: ")
    print("You guessed: " + str(player_choice))
    print("Computer guessed: " + str(computer_choice))
    # Compare all possible outcomes from players and computers choices and add scores to BO3 total
    if player_choice == computer_choice:
        print("You two mofuckas tied!  Play again.")
    elif player_choice == "Rock":
        if computer_choice == "Paper":
            print("Computer beats your " + str(player_choice) + " with their " + str(computer_choice))
            computer_BO3_score += 1
            print("Computers Score: " + str(computer_BO3_score) + "\nPlayers Score: " + str(player_BO3_score))
        else:
            print("Computer loses to your " + str(player_choice) + " with their " + str(computer_choice))
            player_BO3_score += 1
            print("Computers Score: " + str(computer_BO3_score) + "\nPlayers Score: " + str(player_BO3_score))
    elif player_choice == "Paper":
        if computer_choice == "Scissors":
            print("Computer beats your " + str(player_choice) + " with their " + str(computer_choice))
            computer_BO3_score += 1
            print("Computers Score: " + str(computer_BO3_score) + "\nPlayers Score: " + str(player_BO3_score))
        else:
            print("Computer loses to your " + str(player_choice) + " with their " + str(computer_choice))
            player_BO3_score += 1
            print("Computers Score: " + str(computer_BO3_score) + "\nPlayers Score: " + str(player_BO3_score))
    elif player_choice == "Scissors":
        if computer_choice == "Rock":
            print("Computer beats your " + str(player_choice) + " with their " + str(computer_choice))
            computer_BO3_score += 1
            print("Computers Score: " + str(computer_BO3_score) + "\nPlayers Score: " + str(player_BO3_score))
        else:
            print("Computer loses to your " + str(player_choice) + " with their " + str(computer_choice))
            player_BO3_score += 1
            print("Computers Score: " + str(computer_BO3_score) + "\nPlayers Score: " + str(player_BO3_score))
    else:
        print("you did not choose a valid move, try dat shit again.")
    # Reset the computers RPS choice
    computer_choice = (computer_possible_choices[randint(0, 2)])

if player_BO3_score == 3:
    print("Oh damn, you won the game!  Aint dat some shit.")
else:
    print("Jesus, you lost the game?  Try again like your momma taught you right.")

# Print out results of the game to console
# Reset the computers choice to another random selection
