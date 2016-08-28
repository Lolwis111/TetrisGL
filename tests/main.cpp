//-0.6 -0.4 -0.2 0 0.2 0.4 0.6
//   0    1    2 3   4   5   6

#include <math.h>
#include <stdio.h>

int main(int, char**);
int f(float);

int main(int argc, char **argv)
{
    float x = -0.6;
    while(x < 0.6)
    {
        printf("f(%f) = %i\n", x, f(x));
        x += 0.2;
    }

    return 0;
}

int f(float x)
{
    return nearbyint((x + 0.6) * 5);
}

