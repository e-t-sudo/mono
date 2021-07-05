#include "./Cube.hpp"
const std::string Cube::jPerm = "F' U B' U2 F U' F' U2 F B U'";
bool Cube::parity = true;
std::string Cube::reverseSequence(std::string str){
    std::string rev = "";
    for(int i=str.length()-1; i>=0; i--){
        if(str[i]<='Z'&&str[i]>='A'){
            if((i!=str.length()-1)&&str[i+1]=='2'){
                rev += str[i];
                rev += "2 ";
            }else if((i!=str.length()-1)&&str[i+1]=='\''){
                rev += str[i];
                rev += " ";
            }else{
                rev += str[i];
                rev += "' ";
            }
        }
    }
    rev[rev.length()-1] = '\0';
return rev;
}