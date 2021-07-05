#include "./Edges.hpp"
#include<fstream>
Edges::Edges(std::string scrambledFile, std::string solvedFile = "./test_cubes/solvedEdges.txt"){
    solutionString = "";
    std::ifstream edgeFile(scrambledFile);
    for(int i=0; i<12; i++){
        edgeFile>>edges[i].e1>>edges[i].e2;
    }
    edgeFile.close();
    std::ifstream solvedEdgeFile(solvedFile);
    for(int i=0; i<12; i++){
        solvedEdgeFile>>solvedEdges[i].e1>>solvedEdges[i].e2;
    }
    solvedEdgeFile.close();
}
int Edges::getPos(edge ej){
    char x = ej.e1;
    char y = ej.e2;
    int position;
    int orientation;
    for(int i=0; i<12; i++){
        edge currentEdge = solvedEdges[i];
        char X = currentEdge.e1, Y = currentEdge.e2;
        if(X==x&&Y==y||X==y&&Y==x){
            position = i+1;
            if(X==x&&Y==y){
                orientation = 0;
            }else{
                orientation = 1; //to be flipped to an even position
            }
            return 2*(position-1)+1+orientation;//resulting number is (odd, even) for orientation = (0, 1)
        }
    }
return 0;
}
int Edges::cubeletPosition(int location){
    return (location-1)/2 + 1;
}
int Edges::nextUnsolved(void){
    for(int j=1; j<=12; j++){
        bool is_j_present = false;
        for(int i=0; i<solvedEdgePeices.size(); i++){
            if(solvedEdgePeices[i]==j) is_j_present = true;
        }
        if(is_j_present==false) return 2*j-1;
    }
return 0;
}
Edges::edge Edges::flipEdge(edge ej){
    edge rev; rev.e1 = ej.e2; rev.e2 = ej.e1;
    return rev;
}
void Edges::setSolutionString(void){
    std::string terminator = " ";
    if(Cube::parity == false) solutionString += Cube::jPerm + terminator;
    for(int i=0; i<edgePermuteVector.size(); i++){
        if(i!=edgePermuteVector.size()-1&&edgePermuteVector[i]==edgePermuteVector[i+1]){
            i++;
            continue;
        }else if(edgePermuteVector[i]==3||edgePermuteVector[i]==4){
            continue; 
        }else{
            std::string separator = (bufferMove[edgePermuteVector[i]-1]=="")?"":" ";
            solutionString += bufferMove[edgePermuteVector[i]-1] + separator + Cube::jPerm + separator + Cube::reverseSequence(bufferMove[edgePermuteVector[i]-1]) + terminator;
            Cube::parity = !Cube::parity;
        }
    }
}
void Edges::permute(void){
    int starter = 3;
    int l = 0;
    START:
    int destination = getPos(edges[cubeletPosition(starter)-1]);
    edgePermuteVector.push_back(destination);
    solvedEdgePeices.push_back(cubeletPosition(destination));
    while(1){
        if(cubeletPosition(destination)==cubeletPosition(starter)){
            starter = nextUnsolved();
            if(starter==0) break;
            solvedEdgePeices.push_back(starter);
            edgePermuteVector.push_back(starter);
            goto START;
        }
        destination = (destination%2==0)?getPos(flipEdge(edges[cubeletPosition(destination)-1])):getPos(edges[cubeletPosition(destination)-1]);
        edgePermuteVector.push_back(destination);
        solvedEdgePeices.push_back(cubeletPosition(destination));
    }
    setSolutionString();
}