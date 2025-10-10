#include <stdio.h>
#include <stdlib.h>

void main(void)
{
    int X = 5,Y = 8, V[5] = {1,3,5,7,9};
    int *AY, *AX;
    AY = &Y;
    X = *AY;
    *AY = V[3] + V[2];
    printf("\nx=%d    y=%d   v[0]=%d   v[1]=%d    v[2]=%d     v[3]=%d    v[4]=%d",X,Y,V[0],V[1],V[2],V[3],V[4]);
    AX = &V[V[0]*V[1]];
    X = *AX;
    Y = *AX * V[1];
    *AX = *AY - 3;
    printf("\nx=%d    y=%d   v[0]=%d   v[1]=%d    v[2]=%d     v[3]=%d    v[4]=%d",X,Y,V[0],V[1],V[2],V[3],V[4]);
}
