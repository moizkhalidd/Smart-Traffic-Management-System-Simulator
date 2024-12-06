#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
struct EdgeNode 
{
    string destination;
    int travelTime;
    EdgeNode* next;

    EdgeNode(string dest, int time)
    { 
       destination = dest; 
       travelTime = time;
       next = nullptr;
    }
};
struct IntersectionNode 
{
    string name;
    EdgeNode* edgeList;
    IntersectionNode* next;

    IntersectionNode(string nodeName)
    { 
       name = nodeName; 
       edgeList = nullptr; 
       next = nullptr;
    }
};
