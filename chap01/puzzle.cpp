#include <stdlib.h>

/*
#include<stdio.h>

#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))
int array[] = {23,34,12,17,204,99,16};

int main()
{
    int d;

    for(d=-1; d <= (TOTAL_ELEMENTS-2); d++)
        printf("%d %d\n",d, array[d+1]);

    return 0;
}

#include <stdio.h>
int main()
{
    int i=43;
    printf("%d\n",printf("%d",printf("%d",i)));
    return 0;
}
 */

#include <stdio.h>

int main() {
    int *p = (int *)malloc(1);
    int *p2 = (p + 99);

    *(p+100) = 1;

    printf("%d %d", *(p+100), *(p2+1)); //p[100] ==*(p2+1)
}


void printHeading(float hx, float hy)
{
    float heading;

    if (hy > 0)
    {
        heading = 90 - (atan(hx / hy) * (180 / PI));
    }
    else if (hy < 0)
    {
        heading = - (atan(hx / hy) * (180 / PI));
    }
    else // hy = 0
    {
        if (hx < 0) heading = 180;
        else heading = 0;
    }

//  Serial.print("Heading: ");
    Serial.print(heading, 2);
    Serial.print(",");
}
