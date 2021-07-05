#include "./headers/Corners.hpp"
#include "./headers/Edges.hpp"
std::string solution(std::string cornerConfigFile, std::string edgeConfigFile){
    Corners cornerLattice(cornerConfigFile, "./solved/solvedCorners.txt");
    cornerLattice.permute();
    std::string cornerString =  cornerLattice.solutionString;
    Edges edgeLattice(edgeConfigFile, "./solved/solvedEdges.txt");
    edgeLattice.permute();
    std::string edgeString = edgeLattice.solutionString;
return cornerString + "\n\n" + edgeString;
}
int main(void){
    std::cout << "Solution for test #1:\n"
              << "----------------------\n\n";
    std::cout << solution("./tests/test01/corners.txt", "./tests/test01/edges.txt") << "\n";

    std::cout << "Solution for test #2:\n"
              << "----------------------\n\n";
    std::cout << solution("./tests/test02/corners.txt", "./tests/test02/edges.txt") << "\n";

    std::cout << "Solution for test #3:\n"
              << "----------------------\n\n";
    std::cout << solution("./tests/test03/corners.txt", "./tests/test03/edges.txt") << "\n";

    std::cout << "Solution for test #4:\n"
              << "----------------------\n\n";
    std::cout << solution("./tests/test04/corners.txt", "./tests/test04/edges.txt") << "\n";
    
    std::cout << "Solution for test #5:\n"
              << "----------------------\n\n";
    std::cout << solution("./tests/test05/corners.txt", "./tests/test05/edges.txt") << "\n";
    std::cout << "Solution for test #6:\n"
              << "----------------------\n\n";
    std::cout << solution("./tests/test06/corners.txt", "./tests/test06/edges.txt") << "\n";
}
