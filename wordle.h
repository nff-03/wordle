#ifndef WORDLE_H
#define WORDLE_H

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>

class wordle : public Wt::WApplication{
    public:
        // Constructor for the wordle application
        wordle(const Wt::WEnvironment& env);

    private:
        // Widgets for the user interface
        Wt::WLineEdit *text_field;           // Text input field
        Wt::WContainerWidget* output_container; // Container for displaying output
        Wt::WPushButton* submit_button;      // Submit button

        // Signal connection for button click event
        Wt::Signals::connection connection_;

        int tries_count;               // Number of attempts
        std::string targetWord;        // Target word for the game

        // Generate a random word from the word list in "wordList.txt" file
        std::string randomWordGenrator();

        // Initialize the game
        void initialize_application();

        // Set up the user interface
        void setUpInterface();

        // Handle user input
        void input_handle();

        // End the game
        void game_end();

        // Reset the game
        void game_reset();
};


#endif // WORDLE_H
