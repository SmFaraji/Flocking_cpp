#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <vector>
using namespace std;



class Screen
{
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    vector<SDL_FPoint> points;

    public:
    Screen(int& width, int& height)
    {
        w = width;
        h = height;
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(
            width, height, 0, &window, &renderer);
        SDL_RenderSetScale(renderer, 1, 1);
    }

    SDL_Event get_event(){return e;}
    int get_w(){return w;}
    int get_h(){return h;}

    void pixel(double x, double y)
    {
        points.emplace_back(x, y);
    }

    void show(Flock& birds)
    {
        clear();

        for (int i = 0; i < birds.get_numOfBirds(); i++)
        {
           craeteBall(birds.get_birds()[i].get_loc().x, birds.get_birds()[i].get_loc().y); //pixel
            //// craeteArrow(birds.get_birds()[i].get_loc().x, birds.get_birds()[i].get_loc().y,0); //pixel
        }
    /*     craeteArrow(200, 200, 0);
        craeteArrow(250, 200, M_PI/4);
        craeteArrow(300,  300, M_PI/2);*/

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);//100+rand()%100, 100+rand()%100, 100+rand()%100
        
        for(auto& point : points)
        {
            
            SDL_RenderDrawPointF(renderer, point.x, point.y);
        }

        SDL_RenderPresent(renderer);
    }

    void craeteBall(double px, double py);
    void craeteArrow(double px, double py, double dir);

    void clear()
    {
        points.clear();
    }

    void handleEvents(Flock& birds)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    birds.addBird(e.button.x, e.button.y);
                    //cout << e.button.x << '\t' << e.button.y << '\t' << birds.get_birds().back().get_dir() << endl ;
                }
                    
            }

        }
    }

    private:
        int w;
        int h;
};

void Screen::craeteBall(double px, double py)
{
    vector<vector<int>> Ball = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 1, 0, 0},
            {0, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 0}, //c
            {0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0}
                     //c
            };
    int rows = Ball.size();
    int cols = Ball[0].size();
    //cout << rows << '\t' << cols << endl;//out 9 7

    for(auto i=0; i< rows; i++)
    {
        for (auto j=0; j<cols; j++)
        {
            double xx = 0;
            double yy = 0;
            if (Ball[i][j])
            {
                xx = px; yy = py;
                //--
                if (j<4-1)
                    xx = px - (4-1-j);
                else if (j>4-1)
                    xx = px + (j-(4-1));
                //--
                if (i<5-1)
                    yy = py - (5-1-i);
                else if (i>5-1)
                    yy = py + (i-(5-1));
                //--
                pixel(xx, yy);
            }
                        
        }

    }
}

void Screen::craeteArrow(double px, double py, double _dir) {
    vector<vector<int>> Arrow = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1}, // Center
        {1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int rows = Arrow.size();
    int cols = Arrow[0].size();

    // Center of the arrow grid
    double cx = (cols - 1) / 2.0;
    double cy = (rows - 1) / 2.0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (Arrow[i][j]) {
                
                double x = j - cx;
                double y = -(i - cy); // +y is down
                double length_  = sqrt(x*x+y*y);
                double dir_init = atan2(y, x);
                if (dir_init < 0)
                    2*M_PI + dir_init;
                
                double rotatedX =  length_ * cos(_dir + dir_init) ;
                double rotatedY = -length_ * sin(_dir + dir_init) ; // - because +y is down

                // Translate back to original position
                double finalX = px + rotatedX;
                double finalY = py + rotatedY;

                // Draw the pixel
                pixel(finalX, finalY);
            }
        }
    }
}


#endif