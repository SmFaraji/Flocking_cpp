#ifndef MYLIB_H
#define MYLIB_H


#include <vector>
#include <cmath>
using namespace std;

class Bird
{
    public:
        struct birdLoc
            {
                double x, y;
            };
        Bird(double _x, double _y, double _dir);
        void set_loc(double _x, double _y);
        void set_dir(double _dir);
        birdLoc get_loc();
        double get_dir();
    private:
        double x;
        double y;
        double direction;
};

Bird::Bird(double _x, double _y, double _dir)
{
    set_loc(_x, _y);
    set_dir(_dir);
}

void Bird::set_loc(double _x, double _y)
{
    x = _x;
    y = _y;
}

void Bird::set_dir(double _dir)
{
    direction = _dir;
}

Bird::birdLoc Bird::get_loc()
{
    return {x, y};
}

double Bird::get_dir()
{
    return direction;
}


class Flock
{

    public:

        Flock(double separationRatio = 0.7, double cohesionRatio = 0.01, double alignRatio = 1.0, double redirRatio = 0.3)
        : separationRatio(separationRatio), cohesionRatio(cohesionRatio), alignRatio(alignRatio), redirRatio(redirRatio), birds() {}

        
        void addBird(double x, double y);

        void moveAll(double ts);

        void keepIn(int w, int h);

        void removeBirdsIfLeaveScreen(int w, int h);

        vector<Bird> get_birds(){ return birds;}

        double get_dt(){ return dt;}

        int  get_numOfBirds(){return birds.size();}; // return number of birds in screen

        void applyFlockAlg();

        void ApplySepration(double radm);

        void ApplyCohesion(double radm);

        void ApplyAlignment(double radm);
        
    private:
        double dt;
        vector<Bird> birds;

        // Flocking behavior ratios
        double separationRatio; // Separation force ratio
        double cohesionRatio;   // Cohesion force ratio
        double alignRatio;      // Alignment force ratio
        double redirRatio;      // Redirection force ratio (for keeping birds in the window)
};


/* void Flock::moveAll(double ts)
{
    dt = ts;
    for (int i = 0; i < birds.size(); i++)
    {
        double xx = birds[i].get_loc().x + dt*cos( birds[i].get_dir());
        double yy = birds[i].get_loc().y + dt*sin( birds[i].get_dir());
        birds[i].set_loc(xx, yy);
    }
} */
void Flock::moveAll(double ts)
{
    dt = ts;

    for (auto i = 0; i < birds.size(); i++)
    {
        double xx = birds[i].get_loc().x + dt * cos(birds[i].get_dir());
        double yy = birds[i].get_loc().y + dt * sin(-birds[i].get_dir()); // +y in=s down

        birds[i].set_loc(xx, yy);
    }
}


void Flock::addBird(double x, double y)
{
    Bird b = Bird(x, y, (rand()%360)*2*M_PI/360);
    birds.push_back(b);
}

void Flock::keepIn(int w, int h)
{
    double centerX = w / 2.0;
    double centerY = h / 2.0;

    for (auto i = 0; i < birds.size(); i++)
    {
        double xx = birds[i].get_loc().x ;
        double yy = birds[i].get_loc().y ;

        // Apply a force toward the center if close to the boundary
        if (xx < 0.1*w || xx > 0.9*w || yy < 0.1*h || yy > 0.9*h )
        {
            double angleToCenter = atan2(-centerY + birds[i].get_loc().y, -birds[i].get_loc().x + centerX);
            double chaneDirSmooth = birds[i].get_dir() + redirRatio*(angleToCenter-birds[i].get_dir());
            birds[i].set_dir(chaneDirSmooth);
        }

        birds[i].set_loc(xx, yy);
    }
}

void Flock::ApplySepration(double radm)
{
    if (radm < 0)
    {
        cout << "radm parameter is smaller than zero\n";
        abort();
    }

    for (auto i = 0; i < get_numOfBirds(); i++)
    {
        double moveX = 0, moveY = 0;
        for (auto bird = 0; bird < get_numOfBirds(); bird++)
        {
            if (bird != i)
            {
                double dx = birds[i].get_loc().x-birds[bird].get_loc().x;
                double dy = -(birds[i].get_loc().y-birds[bird].get_loc().y);
                double dist_bird_i = sqrt(dx*dx + dy*dy);

                if ( dist_bird_i == 0 ) // when birds are in same location dx is zero and moveX also is zero and sepratipon doesnt work so this is for this scenario
                {
                    moveX = 1 ;
                    moveY = 1 ;
                }
                else if (dist_bird_i < radm)
                {
                    moveX += dx/dist_bird_i ;
                    moveY -= dy/dist_bird_i ;
                } 
            }

        }
        double xx = birds[i].get_loc().x + moveX*separationRatio;
        double yy = birds[i].get_loc().y + moveY*separationRatio;
        birds[i].set_loc(xx, yy);
    }


}

void Flock::ApplyCohesion(double radm)
{
    if (radm < 0)
    {
        cout << "radm parameter is smaller than zero\n";
        abort();
    }

    for (auto i = 0; i < get_numOfBirds(); i++)
    {
        double centerX = 0;
        double centerY = 0;
        int count = 0;

        for (auto bird = 0; bird < get_numOfBirds(); bird++)
        {
            if (bird != i)
            {
                double dx = birds[i].get_loc().x-birds[bird].get_loc().x;
                double dy = birds[i].get_loc().y-birds[bird].get_loc().y;
                double dist_bird_i = sqrt(dx*dx + dy*dy);

                if ( dist_bird_i < radm )//&& dist_bird_i > 100
                {
                    centerX += birds[bird].get_loc().x;
                    centerY += birds[bird].get_loc().y;
                    count++;
                }   
            }

        }
        if (count > 0)
        {
        centerX /= count;
        centerY /= count;

        double xx = birds[i].get_loc().x + (centerX-birds[i].get_loc().x)*cohesionRatio;
        double yy = birds[i].get_loc().y + (centerY-birds[i].get_loc().y)*cohesionRatio;
        birds[i].set_loc(xx, yy);
        }
    }
}

void Flock::ApplyAlignment(double radm)
{
    if (radm < 0)
    {
        cout << "radm parameter is smaller than zero\n";
        abort();
    }


    for (auto i = 0; i < get_numOfBirds(); i++)
    {
        double avgVx = 0;
        double avgVy = 0;
        int count = 0;

        for (auto bird = 0; bird < get_numOfBirds(); bird++)
        {
            if (bird != i)
            {
                double dx = birds[i].get_loc().x-birds[bird].get_loc().x;
                double dy = birds[i].get_loc().y-birds[bird].get_loc().y;
                double dist_bird_i = sqrt(dx*dx + dy*dy);

                if ( dist_bird_i < radm)
                {
                    avgVx += dt*cos(birds[bird].get_dir());
                    avgVy += dt*sin(birds[bird].get_dir());
                    count++;
                }   
            }

        }
        if (count > 0)
        {
        avgVx /= count;
        avgVy /= count;

        double changeDirSmoothly = alignRatio*(atan2(avgVy, avgVx) - birds[i].get_dir()) + birds[i].get_dir();

        birds[i].set_dir(changeDirSmoothly);
        }
    }
}

void Flock::removeBirdsIfLeaveScreen(int w, int h)
{
    for (auto bird = 0; bird < get_numOfBirds(); bird++)
    {
        if (birds[bird].get_loc().x > w || birds[bird].get_loc().x < 0 || birds[bird].get_loc().y > h || birds[bird].get_loc().y < 0)
        {
            
            birds.erase(birds.begin() + bird);
            bird--;
        }

    }
}

void Flock::applyFlockAlg()
{
    ApplySepration(40);
    ApplyCohesion(60);
    ApplyAlignment(40);
}

#endif