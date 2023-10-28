/*

Author: Nour Fayadh

Date: Sep 30, 2023

Description of file: this file is a c++ implementation of the popular game wordle. It takes a random word from a list of words, and 
gives the user 6 chances to guess this word. This file creates the inteerface where the user can input their guesses and helps prompt
the user for the needed info. 

*/

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include "wordle.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <cctype>


// Constructor for the wordle application
wordle::wordle(const Wt::WEnvironment& env)
        : WApplication(env), 
          tries_count(0)   
{
    // Initialize the game and set up the user interface
    initialize_application();
    setUpInterface();
}

// Generate a random word from the word list in "wordList.txt" file
std::string wordle::randomWordGenrator() {
    std::string filePath= "wordList.txt";

    std::vector<std::string> words;
    std::ifstream file(filePath); // open the given file

    if (file.is_open() == false) {
        // Return an empty list if the file cannot be opened
        return "";
    }

    std::string word;

    while (file >> word) {    
        // Read a word from the file and append it to the 'words' vector
        words.push_back(word);
    }

    file.close(); // close the file

    int randomInd = std::rand() % words.size(); // get a random number in the range of the length of the txt file

    return words[randomInd]; // return the word at that index
}

// Initialize the game, including setting the target word and applying styles
void wordle::initialize_application() {
    
    // Generate a random target word
    targetWord = randomWordGenrator();
    std::cout << "The selected word is: " << targetWord << std::endl;

    // Set the application title and apply a CSS stylesheet
    setTitle("Wordle Game");
    useStyleSheet("style.css");
}

// Set up the user interface with text field, submit button, and output container
void wordle::setUpInterface(){

    // Create a text field for user input
    text_field = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    text_field->setPlaceholderText("Enter a guess, 5 letters max: ");
    text_field->addStyleClass("textField");

    // Create a submit button for submitting guesses
    submit_button = root()->addWidget(std::make_unique<Wt::WPushButton>("Submit"));
    submit_button->addStyleClass("submit_button");
    submit_button->setText("<i class=\"fa fa-paper-plane\"></i> Submit");
    submit_button->setTextFormat(Wt::TextFormat::XHTML);

    // Connect the submit button's click event to the input_handle method
    connection_ = submit_button->clicked().connect(this, &wordle::input_handle);

    // Create a container for displaying output messages
    output_container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    output_container->addStyleClass("output-container");
    
    // Connect the Enter key press event in the text field to the input_handle method
    text_field->enterPressed().connect(this, &wordle::input_handle);

}

// Handle user input and display feedback
void wordle::input_handle(){

    std::string print_text = ""; // string to print after the user inputs their guess
    bool guess = true;  // boolean to check if guess is correct or not

    // Get the user's input from the text field and convert it to uppercase
    std::string input = text_field->text().toUTF8();
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);

    // if user inputs an invalid input
    if (input.length() != 5 || !std::all_of(input.begin(), input.end(), ::isalpha)) {
        // Display an error message for invalid input
        output_container->addWidget(std::make_unique<Wt::WText>("Invalid input. Please enter a 5-letter word.<br/>"));
        text_field->setText(""); // empty the text field
        return;
    }

    tries_count++;  // incremeant the number of tries by one

    int i = 0;
    // loop through the 5 letters
    while(i < 5){
        
        // if characters at both position are the same
        if(input[i] == targetWord[i]){
            // Display the correctly guessed letter in the correct position
            print_text += "<span class='correct'>" + std::string(1, input[i]) + "</span>";
        }

        else{

            bool letterFound = false;  // boolean to check if the letter is found in the target word at input's current char

            // loop through target to look for the current character in input
            for (int j=0; j < 5; j++){

                // if that character is found
                if(input[i] == targetWord[j]){
                    letterFound = true;  // set the boolean to true
                    break;
                }
            }

            // if that boolean is found 
            if(letterFound == true){
                guess = false; // set guess to false
                // Display the correctly guessed letter in an incorrect position
                print_text += "<span class='incorrect-position'>" + std::string(1, input[i]) + "</span>";
            }

            else{
                guess = false;  // set guess to false
                // Display an incorrect guess
                print_text += "<span class='incorrect'>" + std::string(1, input[i]) + "</span>";
            }

        }

        i++;

    }

    print_text += "<br/>"; // Add an HTML line break for formatting the output
    // Display the feedback message
    output_container->addWidget(std::make_unique<Wt::WText>(print_text));
    text_field->setText("");

    // if the input word was the correct guess
    if(guess){
        // Display a congratulatory message and end the game
        output_container->addWidget(std::make_unique<Wt::WText>("Congratulations! You've guessed the word correctly. Would you like to play again?<br/>"));
        game_end();
    } else if(tries_count == 6){        
        // Display a message for running out of guesses and end the game
        output_container->addWidget(std::make_unique<Wt::WText>("You ran out of guesses! The correct guess was " + targetWord + " Would you like to play again?<br/>"));
        game_end();
    }
}

// End the game
void wordle::game_end(){
        text_field->setDisabled(true); // Disable the text input field

        // change the text on the button to restart
        submit_button->setText("Restart");

        connection_.disconnect();

        // Connect the restart button to the game_reset method
        connection_ = submit_button->clicked().connect(this, &wordle::game_reset);

}

// Reset the game
void wordle::game_reset(){
    tries_count = 0; // reset the tries count to zero tries

    text_field->setDisabled(false); // Unable the text input field
    text_field->setText(""); // empty the text input box

    output_container->clear(); // remove all the ouput from previous try

    submit_button->setText("Submit");   // change the text on the button to submit

    connection_.disconnect();

    // Generate a new target word and connect the submit button to input_handle
    targetWord = randomWordGenrator();

    connection_ = submit_button->clicked().connect(this, &wordle::input_handle);
}
