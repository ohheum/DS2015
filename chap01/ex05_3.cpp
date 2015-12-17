//
// Created by Oh-Heum Kwon on 9/20/15.
//
#include <stdio.h>
#include <string.h>
#define MAX 100
#define BUFFER_SIZE 20

int coef[MAX];
int expo[MAX];
int n=0;

void handle_define();
void handle_calc();
void handle_print();

int main()
{
    char ch;
    char command[BUFFER_SIZE];

    while(1) {
        printf("$ ");
        scanf("%s", command);
        if (strcmp(command, "define"))
            handle_define();
        else if (strcmp(command, "calc"))
            handle_calc();
        else if (strcmp(command, "print"))
            handle_print();
        else if (strcmp(command, "exit"))
            break;
    }
}

void handle_print() {

}

void handle_calc() {

}

void handle_define() {

}

printOrientation(dof.calcAccel(dof.ax), dof.calcAccel(dof.ay), dof.calcAccel(dof.az));


void printOrientation(float x, float y, float z)
{
    float pitch, roll;

    pitch = atan2(x, sqrt(y * y) + (z * z));
    roll = atan2(y, sqrt(x * x) + (z * z));
    pitch *= 180.0 / PI;
    roll *= 180.0 / PI;

//  Serial.print("Pitch, Roll: ");
    Serial.print(pitch, 2);
    Serial.print(",");
    Serial.println(roll, 2);
}