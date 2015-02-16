/* 
 * File:   main.cpp
 * Author: elliot
 *
 * Created on February 12, 2015, 9:12 PM
 */

#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <list>
#include <vector>
#include <iterator>

using namespace std;


int cube[6] = {0, 0, 0, 0, 0, 0};
int pos = 0;
bool invalid = false;
int validCount = 0;
int validCount2 = 0;
vector<vector<int> > validCubes;
vector<int> validCube;
vector<vector<int> > validCubes2;
int SQUARES[9][2] = {
    {0, 1},
    {0, 4},
    {0, 9},
    {1, 6},
    {2, 5},
    {3, 6},
    {4, 9},
    {6, 4},
    {8, 1}};
int validCombos = 0;


/**
 * 
 * @param pos: current position out of the 6 faces of the cube
 * @param cube: an array of 6, where each index holds the value of a face on the cube
 * 
 * This is a recursive function that creates all of the possible arrangements of values 0-9 on a 6 sided cube.
 */
void makeCube(int pos, int cube[]) {

    if (pos >= 6) {

        //check for valid cubes
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (i != j && cube[i] == cube[j]) {
                    invalid = true;
                }
            }
        }
        if (!invalid) {
            validCount++;
            //cout << "Valid cube: ";
            validCube.clear();
            for (int i = 0; i < 6; i++) {
                validCube.push_back(cube[i]);
                //cout << cube[i] << ", ";
            }
            validCubes.push_back(validCube);
            //cout << endl;
            //Sleep(250); 
        }
        invalid = false;

    }
    else {
        for (int i = pos; i <= pos + 4; i++) {
            if (cube[i] == 0 || cube[i] > cube[i - 1]) {
                cube[pos] = i;
                makeCube(pos + 1, cube);

            }
        }
    }

}//makeCube


/**
 * 
 * @param cubes: the vector containing all of the final 210 valid cubes
 * @param posit: the position in the vector to begin checking from.
 *               The position is progressed through the vector by a for loop in the main method.
 * 
 * This function takes the first cube in the cubes vector and combines it with every cube that follows it, one at a time.
 * It checks one face at a time on each cube to look for a match for any of the first digits of the perfect squares.
 * If one of the cubes matches the first digit of a perfect cube, it next checks each face of the other cube to see if there is a match
 * for the second digit of the perfect square.
 */
void checkCubes(vector<vector<int> > cubes, int posit) {

    vector<int> cube1 = cubes.at(posit);
    int squaresCheck = 0;

    for(int q = posit+1; q < cubes.size(); q++){
        vector<int> cube2 = cubes.at(q);
        for(int i = 0; i < 7; i ++){
            for(int j = 0; j < 9; j++){
                if(cube1.at(i) == SQUARES[j][0]){
                    for(int k = 0; k < 7; k++){
                        if(cube2.at(k) == SQUARES[j][1]){
                            squaresCheck++;
                        }
                    }
                }
                else if (cube2.at(i) == SQUARES[j][0]){
                    for(int k = 0; k < 7; k++){
                        if(cube1.at(k) == SQUARES[j][1]){
                            squaresCheck++;
                        }
                    }
                }
            }
        }
        //cout<<squaresCheck<<endl;
        //cout<<validCombos<<endl;
            //Sleep(250);
        if(squaresCheck == 9){
            
            validCombos++;
        }
        squaresCheck = 0;
    }

    //cout<<squaresCheck<<endl;


}//checkCubes


/**
 * 
 * This function scans through the vector of all the possible cube configurations, looking for duplicate cubes.
 * Unique cube configurations are pushed onto a new vector.
 */
void checkForDuplicateCubes(){


    for(int i = 0; i < validCubes.size(); i++){
        vector<int> cube1 = validCubes.at(i);
        int checker = 0;
        for(int j = i+1; j < validCubes.size(); j++){
            vector<int> cube2 = validCubes.at(j);
            int cubeCheck = 0;
            for(int q = 0; q < 6; q++){
                for(int w = 0; w < 6; w++){
                    if(cube1.at(q) == cube2.at(w)){
                        cubeCheck++;
                    }
                }
            }
            if(cubeCheck == 6){
                checker++;
            }
        }
        if(checker ==0){
            validCubes2.push_back(cube1);
            validCount2++;
        }
    }
}//checkForDuplicateCubes


/**
 * 
 * @param cube: one of the final 210 valid cubes
 * 
 * This function checks a cube to determine if it has a 6 or 9.
 * If it has only a six or a nine, it will push the other digit onto the cube, giving it 7 faces.
 * Otherwise, it pushes a -1 onto the 7th face.
 */
void sixNineCheck(vector<int>* cube){
    
    //int workCount = 0;
    bool six = false;
    bool nine = false;
    for(int i = 0; i < 6; i++){
        if(cube->at(i) == 6){
            six = true;
        }
        if(cube->at(i) == 9){
            nine = true;
        }
    }
    if(!six && nine){
        //workCount++;
        cube->push_back(6);
    }
    else if(six && !nine){
        cube->push_back(9);
    }
    else{
        cube->push_back(-1);
    }
    //cout<<"Working Count: "<< workCount<<endl;
    
}//sixNineCheck



int main(int argc, char** argv) {

    makeCube(pos, cube);
    checkForDuplicateCubes();    
    
    for(int i = 0; i < validCubes2.size(); i++){
        vector<int>* cube1 = &validCubes2.at(i);
        sixNineCheck(cube1);
        vector<int> cube = *cube1;
        for(int j = 0; j < 7; j++){
            cout<< cube.at(j) << ", ";
            
        }
        cout<<endl;
    }
    cout<<"# Valid Cubes: " << validCount2 << endl;
    

    for (int i = 0; i < validCubes2.size(); i++) {
        checkCubes(validCubes2, i);
    }
    cout << "# of Valid Combos: " << validCombos << endl;


    return 0;
}//main