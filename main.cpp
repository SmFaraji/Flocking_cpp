#include <iostream>
#include "myLib.h"
#include "screen.h"
#include <chrono>
using namespace std;

const auto step_rate = chrono::milliseconds(50); // 50 ms

int main()
{
    int win_width  = 680 * 2;
    int win_height = 480 * 2;
    Screen screen(win_width, win_height);
    Flock birds(0.7, 0.02, 1, 0.35);

    auto previous_time = chrono::high_resolution_clock::now();

    while (true)
    {
        auto current_time = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(current_time - previous_time);

        // Wait until 50ms has passed
        if (elapsed >= step_rate)
        {
            previous_time = current_time; // Update the previous time
            birds.removeBirdsIfLeaveScreen(screen.get_w(), screen.get_h());
            // Perform your simulation update
            screen.handleEvents(birds);
            birds.moveAll(4);
            birds.keepIn(screen.get_w(), screen.get_h());

            birds.ApplySepration(30);
            birds.ApplyCohesion(50);
            birds.ApplyAlignment(50);
            
            screen.show(birds);

            cout << birds.get_numOfBirds() << endl;
            // Optional: Log duration for debugging
            //cout << "Elapsed time for this step: " << elapsed.count() << " ms\n";
        }

        // Small delay to prevent high CPU usage
        SDL_Delay(1);
    }

    return 0;
}
