#include <Wt/WApplication.h>
#include "wordle.h"

int main(int argc, char **argv)
{
    // Run the Wt web application with a lambda function
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        // Create and return a new instance of the 'wordle' application
        return std::make_unique<wordle>(env);
    });
}
