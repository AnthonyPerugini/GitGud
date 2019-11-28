
secret_word = "Giraffe"
users_guess = ""
guess_count = 0
guess_limit = 3
out_of_guesses = False

while users_guess != secret_word and not out_of_guesses:
    if guess_count < guess_limit:
        users_guess = input("Guess a word: ")
        guess_count += 1
    else:
        out_of_guesses = True

if out_of_guesses:
    print("you lost the game!")
else:
    print ("you win!")