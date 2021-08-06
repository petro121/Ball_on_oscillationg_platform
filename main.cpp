#include <iostream>
#include <fstream>
#include <string>
#include <cmath>   // For fmod() function.
#include <random>
#include <ctime>

using namespace std;

// This program will perform virtual experiments
// of a ball jumping on an oscillating plane in a
// confined space. The experiments' conditions will
// vary and we will gather the data to empirically
// derive the desired laws.

int main()
{
    float L = 1000;
    float a = 1;
    float omega = 100;
    float V = 0.1;
    float v0 = 100;

    fstream File;
    File.open("data.txt", ios::out | ios::trunc);
    File << "Time Collision Energy" << endl;
    float Time = 0.0;
    float Energy = v0*v0/2;
    File << Time << " 0 " << Energy << endl;

    // To ensure random starting condition, we have to
    // ensure that the plane starts in a random position.
    default_random_engine generator;
    generator.seed(time(NULL));
    uniform_real_distribution<double> distribution(0.0,6.28319);
    double phase = distribution(generator);

    for(int Collision = 1; Collision <= 10000000; Collision++) {
        Time += 2*L/v0;
        // We check the phase of our plane, whether it
        // lies between 0 and pi.
        if(0 <= fmod((omega*Time + phase), 6.28319) && fmod((omega*Time + phase), 6.28319) < 3.14159) {
            v0 += V;
        } else if (3.14159 <= fmod((omega*Time + phase), 6.28319) && fmod((omega*Time + phase), 6.28319) < 6.28319) {
            v0 -= V;
        }
        Energy = v0*v0/2;
        File << Time << ' ' << Collision << ' ' << Energy << endl;
    }
}
