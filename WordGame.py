# Display the menu options
# Ask the user to enter their choice
# Check if the choice is valid
# If choice is invalid, display an error message and go back to asking for user input
# if choice is valid, perform the corresponding action based on the menu option
# If user chooses instructions, print the instructions
# if the action is to play a game, ask for the word length
# if user chooses for it ot be random, randomize word length
# If the action is to display the scoreboard, show the scoreboard
# if the action is to exit, terminate the program
# Player will play one letter at a time
# user will input letter, then pogram must go thorugh each letter to see if matches
# if no match, print your letter is not found
# if matched, print your letter is the nth letter
# calclate a score depending on guesses remaining and possibly word length
# if user doesn't guess the word, the score is 0
# if user guesses word, ask for user's name and print the score and return user to menu
# save information in a file with his name and score
# only save if user guesses word
# worked with Jack Yuan
# declare scores as a global variable to store game scores
scores = []

# Define the main function to run the Hangman game
def main():
    # Start an infinite loop for the main game menu
    while True:
        # Display the Hangman menu options
        menu()
        # Prompt the user to enter their choice
        choice = input("Enter your choice: ")

        # Check the user's choice and perform the corresponding action
        if choice == '1':
            instructions()
        elif choice == '2':
            play_game(category='food')
        elif choice == '3':
            play_game(category='animal')
        elif choice == '4':
            play_game(category='state')
        elif choice == '5':
            play_game_random_category()
        elif choice == '6':
            print_scoreboard()
        elif choice == '7':
            exit_game()
        else:
            print("Invalid choice. Please try again.")

# Define the function to display the main menu options
def menu():
    print("===========================================")
    print("                  Hangman                  ")
    print("Menu Options:")
    print("1. Instructions")
    print("2. Play Game (Food)")
    print("3. Play Game (Animal)")
    print("4. Play Game (State)")
    print("5. Play Game (Random Category)")
    print("6. Display Scoreboard")
    print("7. Exit")
    print("===========================================")

# Define the function to display game instructions
def instructions():
    print("Instructions: Hello! Welcome to Hangman where you have a choice to guess letters from a category of your choice or you can randomize it if you wish! The categories are food, animals, and states. The number of guesses you have is the number of letters in the word - 1. For example, if a word has 6 letters, you will have five guesses to guess the word. You need to guess letter for letter. You cannot type numbers or repeat a guess. However, if you do, you will not lose a turn. If you guess the word correctly, your score will be calculated and we will ask for your name. This is because we want to add you to our scoreboard. When you reach the menu, you can display the scoreboard by choosing option 6. The only way to exit is by choosing option 7 when you are in the menu. Good luck and enjoy!")
    input("Press Enter to return to the menu.")

# Define the function to start and manage a game
def play_game(word_length=None, category=None):
    # Check if word_length is not provided, then generate a random word length between 2 and 10
    if word_length is None:
        word_length = random.randint(2, 10)
    
    # Check if category is not provided, then choose from predefined categories
    if category is None:
        categories = ['food', 'animal', 'state']
        category = random.choice(categories)

    # Generate a random secret word based on the word_length and category
    secret_word = random_word(word_length, category)
    # Initialize a set to store guessed letters
    guessed_letters = set()
    # Initialize the number of remaining guesses
    guesses_left = len(secret_word)
    # Add a flag to track whether the word is guessed
    word_guessed = False

    # Start the game loop until the word is guessed or no guesses left
    while guesses_left > 0 and not word_guessed:
        # Display the current state of the word with guessed letters
        current_word(guessed_letters, secret_word)
        # Prompt the user to enter a letter guess
        guess = user_guess(guessed_letters, guesses_left)

        # Check if the guessed letter is in the secret word
        if guess in secret_word:
            # Update the guessed letters and display the position of the letter in the word
            update_guess(secret_word, guessed_letters, guess)
        else:
            # Display a message for incorrect guesses and decrease the remaining guesses
            print(f"Letter '{guess}' is not in the word. {guesses_left - 1} guesses left.")
            guesses_left -= 1

        # Add the guessed letter to the set of guessed letters
        guessed_letters.add(guess)

        # Check if all letters in the word are guessed
        if set(secret_word.lower()) <= guessed_letters:
            word_guessed = True

    # Check if the word is guessed and perform actions accordingly
    if word_guessed:
        # Prompt the user for their name and calculate the score
        player_name = input(f"Congratulations! You guessed the word '{secret_word}' correctly! Enter your name: ")
        score = calculate_score(guesses_left, len(secret_word))
        # Save the player's name and score in the scoreboard
        save_score(player_name, score)
        print(f"Your score is {score}.")
        print("Congratulations, you guessed the word correctly!")
    else:
        # Display a message if the word is not guessed
        print(f"Sorry, you didn't guess the word. The word was: {secret_word}")

# Define the function to start a game with a random category
def play_game_random_category():
    play_game()

# Define the function to generate a random word based on word_length and category
def random_word(word_length, category=None):
    categories = {
        'food': ['pizza', 'burger', 'pasta'],
        'animal': ['lion', 'elephant', 'giraffe'],
        'state': ['california', 'texas', 'florida']
    }

    # Check if category is provided, then choose a random word from that category
    if category is not None:
        return random.choice(categories[category])
    else:
        # If category is not specified, return a random word from any category
        all_words = [word for words in categories.values() for word in words]
        return random.choice(all_words)

# Define the function to display the current state of the word with guessed letters
def current_word(guessed_letters, secret_word):
    current_state = ''.join(letter if letter in guessed_letters else '_' for letter in secret_word)
    print(f"Current Word: {current_state}")

# Define the function to display the position of the guessed letter in the word
def update_guess(secret_word, guessed_letters, guess):
    print(f"Letter '{guess}' is in the word at position {', '.join(str(i+1) for i, letter in enumerate(secret_word) if letter == guess)}.")

# Define the function to prompt the user for a letter guess
def user_guess(guessed_letters, remaining_turns):
    while True:
        guess = input("Enter a letter: ")

        # Check if the input is a single letter
        if guess.isalpha():
            break
        else:
            print("Invalid input. Please enter a single letter.")

    # Check if the guessed letter is not repeated
    if guess not in guessed_letters:
        return guess.lower()
    else:
        print("You've already guessed that letter. Try again.")
        return user_guess(guessed_letters, remaining_turns)

# Define the function to calculate the score based on guesses left and word length
def calculate_score(guesses_left, word_length):
    # Example scoring logic: score = guesses_left * word_length
    return guesses_left * word_length

# Define the function to save the player's name and score in the scoreboard
def save_score(player_name, score):
    global scores
    scores.append(f"{player_name}: {score}")

    # Save scores to the file
    with open("scoreboard.txt", "a") as file:
        file.write(f"{player_name}: {score}\n")

# Define the function to display the scoreboard
def print_scoreboard():
    file_path = "scoreboard.txt"

    try:
        with open(file_path, "r") as file:
            scores_content = file.read()

        # Check if the scoreboard is empty
        if not scores_content:
            print("Scoreboard is empty.")
        else:
            # Split the scores into lines and sort them based on the score in descending order
            scores_lines = scores_content.strip().split('\n')
            sorted_scores = sorted(scores_lines, key=lambda x: int(x.split(': ')[1]), reverse=True)

            print("Scoreboard:")
            # Display each line of the sorted scoreboard
            for score_line in sorted_scores:
                print(score_line)

    except FileNotFoundError:
        print(f"Error: {file_path} not found. The scoreboard is empty.")
    except Exception as e:
        print(f"An error occurred: {e}")

# Define the function to exit the game
def exit_game():
    print("Exiting the game. Goodbye!")
    exit()

# Check if the script is run as the main program
if __name__ == "__main__":
    main()
