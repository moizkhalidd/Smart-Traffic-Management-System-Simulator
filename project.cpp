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
class TrafficGraph 
{
    IntersectionNode* head;

    IntersectionNode* findIntersection(string name) 
    {
        IntersectionNode* current = head;
        while (current != nullptr) 
        {
            if (current->name == name) 
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void removeIncomingEdges(string nodeName) 
    {

        IntersectionNode* current = head;
        while (current != nullptr) 
        {
            EdgeNode* prev = nullptr;
            EdgeNode* edge = current->edgeList;
            while (edge != nullptr) 
            {
                if (edge->destination == nodeName) 
                {
                    if (prev == nullptr) 
                    {
                        current->edgeList = edge->next;
                    } 
                    else 
                    {
                        prev->next = edge->next;
                    }
                    delete edge;
                    break;
                }
                prev = edge;
                edge = edge->next;
            }
            current = current->next;
        }
    }

public:

    TrafficGraph() : head(nullptr) {}


    ~TrafficGraph() 
    {
        while (head != nullptr) 
        {
            IntersectionNode* temp = head;
            head = head->next;

            EdgeNode* edge = temp->edgeList;
            while (edge != nullptr) 
            {
                EdgeNode* edgeTemp = edge;
                edge = edge->next;
                delete edgeTemp;
            }

            delete temp;
        }
    }


    void addIntersection(const string& name) 
    {
        if (findIntersection(name) == nullptr)
        {
            IntersectionNode* newNode = new IntersectionNode(name);
            
            
            if(head == nullptr)
            head = newNode;
            else
            {
               IntersectionNode* temp = head;
               while(temp -> next != nullptr)
               temp = temp -> next;
               
                temp->next = newNode;
                temp = nullptr;
                delete temp;
            }
        }
    }


    void addRoad(const string& source, const string& destination, int travelTime) 
    {

              addIntersection(source); 
              addIntersection(destination);


              IntersectionNode* sourceNode = findIntersection(source);
              EdgeNode* newEdge1 = new EdgeNode(destination, travelTime);
              
              if(sourceNode->edgeList == nullptr)
              sourceNode->edgeList = newEdge1;
              else
              {
                         EdgeNode* temp = sourceNode->edgeList;
                         while(temp -> next != nullptr)
                         temp = temp -> next;
                         
                          temp->next = newEdge1;
                          temp = nullptr;
                          delete temp;
                
              }
              
              IntersectionNode* destinationNode = findIntersection(destination);
              EdgeNode* newEdge2 = new EdgeNode(source, travelTime);
              
              if(destinationNode->edgeList == nullptr)
              destinationNode->edgeList = newEdge2;
              else
              {
                         EdgeNode* temp = destinationNode->edgeList;
                         while(temp -> next != nullptr)
                         temp = temp -> next;
                         
                          temp->next = newEdge2;
                          temp = nullptr;
                          delete temp;
                
              }
    
    } 

    void removeRoad(const string& source, const string& destination) 
    {
        IntersectionNode* sourceNode = findIntersection(source);
        if (sourceNode == nullptr) return;

        EdgeNode* prev = nullptr;
        EdgeNode* edge = sourceNode->edgeList;

        while (edge != nullptr) 
        {
            if (edge->destination == destination) 
            {
                if (prev == nullptr)
                {
                    sourceNode->edgeList = edge->next;
                } 
                else 
                {
                    prev->next = edge->next;
                }
                delete edge;
                return;
            }
            prev = edge;
            edge = edge->next;
        }
    }

    void removeIntersection(const string& name)
    {
        removeIncomingEdges(name); 

        IntersectionNode* prev = nullptr;
        IntersectionNode* current = head;

        while (current != nullptr) 
        {
            if (current->name == name) 
            {
                if (prev == nullptr)
                {
                    head = current->next;
                } 
                else 
                {
                    prev->next = current->next;
                }

                EdgeNode* edge = current->edgeList;
                while (edge != nullptr) 
                {
                    EdgeNode* temp = edge;
                    edge = edge->next;
                    delete temp;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void displayNetwork() 
    {
        IntersectionNode* current = head;
        while (current != nullptr)
        {
            cout << current->name << " -> ";
            EdgeNode* edge = current->edgeList;
            
            while (edge != nullptr) 
            {
                cout  << " (" << edge->destination<< ","<<edge->travelTime<<")";
                edge = edge->next;
            }
            cout << endl;
            current = current->next;
        }
    }
};

