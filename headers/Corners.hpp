#ifndef CORNERS
#define CORNERS
#include "./Cube.hpp"
class Corners{
    public:
        std::string solutionString;
        std::string bufferMove[24] = {"L D F'", "L F2","F","","F D' F2","F D' L' F","","","","L2 F2","L F","L2 D F'","F2","L' F","D F'","D' F2","D' L' F","F'","D2 F2","D2 L' F","D' F'","D F2","L' F2","L2 F"}; //yet to be filled
        const int buffer = 7;
        typedef struct corner{
            char c1, c2, c3;
        } corner;
        corner corners[8], solvedCorners[8];
        std::vector<int> cornerPermuteVector;
        std::vector<int> solvedCornerPeices; //stores locations of solved corner peices
        Corners(std::string, std::string);
        int getPos(corner);
        int cubeletPosition(int);
        int nextUnsolved(void);
        corner counterTurn(corner); corner clockTurn(corner);
        void permute(void);
        void setSolutionString(void);
};
#endif
