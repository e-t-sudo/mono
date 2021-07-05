#include "./Corners.hpp"
#include<fstream>
Corners::Corners(std::string scrambledFile, std::string solvedFile = "./test_cubes/solvedCorners.txt"){
    solutionString = "";
    std::ifstream cornerFile(scrambledFile);
    for(int i=0; i<8; i++){
        cornerFile>>corners[i].c1>>corners[i].c2>>corners[i].c3;
    }
    cornerFile.close();
    std::ifstream solvedCornerFile(solvedFile);
    for(int i=0; i<12; i++){
        solvedCornerFile>>solvedCorners[i].c1>>solvedCorners[i].c2>>solvedCorners[i].c3;
    }
    solvedCornerFile.close();
}
int Corners::getPos(corner crnr){
    char x = crnr.c1;
    char y = crnr.c2;
    char z = crnr.c3;
    int position;
    int orientation;
    for(int i=0; i<8; i++){
        corner currentCorner = solvedCorners[i];
        char X = currentCorner.c1, Y = currentCorner.c2, Z = currentCorner.c3;
        if((X==x&&Y==y&&Z==z)||(X==y&&Y==z&&Z==x)||(X==z&&Y==x&&Z==y)){ //no rotation required, clockwise rotation required, counter-clockwise rotation requried respectively
            position = i+1;
            if(X==x&&Y==y&&Z==z){
                orientation = 0;
            }else if(X==z&&Y==x&&Z==y){
                orientation = 1; //to be turned clockwise ==> position is incremented by +1;
            }else if(X==y&&Y==z&&Z==x){
                orientation = 2; //to be turned counter-clockwise ==> twice clockwise ==> position is incremented by +2;
            }
            return (3*(position-1)+1)+orientation;
        }
    }
return 0;
}
int Corners::cubeletPosition(int location){
    return (location-1)/3 + 1;
}
int Corners::nextUnsolved(void){
    for(int j=1; j<=8; j++){
        bool is_j_present = false;
        for(int i=0; i<solvedCornerPeices.size(); i++){
            if(solvedCornerPeices[i]==j) is_j_present = true;
        }
        if(is_j_present==false) return 3*j-2;
    }
return 0;
}
Corners::corner Corners::counterTurn(corner crnr){
    char x = crnr.c1, y = crnr.c2, z = crnr.c3;     //      x                          y   
    corner ret; ret.c1 = y; ret.c2 = z; ret.c3 = x; //                ---------->       
    return ret;                                     //   z      y                   x      z
}
Corners::corner Corners::clockTurn(corner crnr){
    char x = crnr.c1, y = crnr.c2, z = crnr.c3;     //      x                          z   
    corner ret; ret.c1 = z; ret.c2 = x; ret.c3 = y; //                ---------->       
    return ret;                                     //   z      y                   y      x
}
void Corners::setSolutionString(void){
    std::string terminator = " ";
    if(Cube::parity==false) solutionString += (Cube::jPerm + terminator);
    for(int i=0; i<cornerPermuteVector.size(); i++){
        if(i!=cornerPermuteVector.size()-1&&cornerPermuteVector[i]==cornerPermuteVector[i+1]){
            i++;
            continue;
        }else if(cornerPermuteVector[i]==7||cornerPermuteVector[i]==8||cornerPermuteVector[i]==9){
            continue; 
        }else{
            std::string separator = (bufferMove[cornerPermuteVector[i]-1]=="")?"":" ";
            solutionString += bufferMove[cornerPermuteVector[i]-1] + separator + Cube::jPerm + separator + Cube::reverseSequence(bufferMove[cornerPermuteVector[i]-1]) + terminator;
            Cube::parity = !Cube::parity;
        }
    }
}
void Corners::permute(void){
    int starter = 7;
    int l = 0;
    START:
    int destination = getPos(corners[cubeletPosition(starter)-1]);
    cornerPermuteVector.push_back(destination);
    solvedCornerPeices.push_back(cubeletPosition(destination));
    while(1){
        if(cubeletPosition(destination)==cubeletPosition(starter)){
            starter = nextUnsolved();
            if(starter==0) break;
            solvedCornerPeices.push_back(cubeletPosition(starter));
            cornerPermuteVector.push_back(starter);
            goto START;
        }
        if(destination%3==1){ //no rotation required
            destination = getPos(corners[cubeletPosition(destination)-1]);
        }else if(destination%3==2){
            destination = getPos(counterTurn(corners[cubeletPosition(destination)-1]));
        }else if(destination%3==0){
            destination = getPos(clockTurn(corners[cubeletPosition(destination)-1]));
        }
        cornerPermuteVector.push_back(destination);
        solvedCornerPeices.push_back(cubeletPosition(destination));
    }
    setSolutionString();
}
