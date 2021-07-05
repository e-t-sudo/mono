#ifndef EDGES
#define EDGES
#include "./Cube.hpp"
class Edges{
    public:
        std::string solutionString;
        std::string bufferMove[24] = {"M D2 M", "M'", "", "", "", "M2 D2 M", "L2 D M2", "L2 D' M", "L D' M", "L D M2", "E' L D' M", "E' L D M2", "E2 L D' M", "E L' D' M", "L' D M2", "L' D' M", "D2 M", "M2", "D M", "D' M2", "M", "D2 M2", "D' M", "D M2"};
        const int buffer = 2;
        typedef struct edge{
            char e1, e2;
        } edge;
        edge edges[12], solvedEdges[12];
        std::vector<int> edgePermuteVector;
        std::vector<int> solvedEdgePeices; //stores locations of solved edge peices
        Edges(std::string, std::string);
        int getPos(edge);
        int cubeletPosition(int);
        int nextUnsolved(void);
        edge flipEdge(edge);
        void permute(void);
        void setSolutionString(void);
};
#endif