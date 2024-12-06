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
struct NodeDistance 
{
  string name;
  int distance;
  bool visited;
  string parent;
  NodeDistance()
  {}
  
  NodeDistance(string n, int d)
  {
     name= n;
     distance = d;
     visited = 0;
     parent = "";
  }
};
struct BlockedRoad 
{
    string source;
    string destination;
    BlockedRoad* next;

    BlockedRoad(string s, string d) 
    { 
      source = s;  
      destination = d;
      next = nullptr;
    }
};
class TrafficGraph 
{
    IntersectionNode* head;
    BlockedRoad* blockedRoads;

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
    
    

      int getIndex(const string& name, NodeDistance nodes[], int nodeCount) 
      {
          for (int i = 0; i < nodeCount; ++i) 
          {
              if (nodes[i].name == name) 
              return i;
          }
          return -1;
      }

      bool isRoadBlocked(string source, string destination) 
      {
        BlockedRoad* current = blockedRoads;
        while (current) {
            if ((current->source == source && current->destination == destination) || (current->source == destination && current->destination == source)) 
            {
                return true; 
            }
            current = current->next;
        }
        return false;
       }
  
public:

    TrafficGraph() : head(nullptr) , blockedRoads(nullptr){}

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

     void blockRoad(string source, string destination) 
    {
          IntersectionNode* sourceNode = findIntersection(source);
          if (sourceNode == nullptr) 
          {
              cout << "Error: Source intersection " << source << " does not exist." << endl;
              return;
          }

          EdgeNode* edge = sourceNode->edgeList;
          bool roadExists = false;

          while (edge) 
          {
              if (edge->destination == destination) 
              {
                  roadExists = true; 
                  break;
              }
              edge = edge->next;
          }
    
      
        if (roadExists) 
        {
            BlockedRoad* newBlockedRoad = new BlockedRoad(source, destination);
            newBlockedRoad->next = blockedRoads;
            blockedRoads = newBlockedRoad;


            newBlockedRoad = new BlockedRoad(destination, source);
            newBlockedRoad->next = blockedRoads;
            blockedRoads = newBlockedRoad;
        }
        else
        cout<<"Road does not exist from "<<source<<" to "<<destination<<endl;
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


    void loadFromCSV(string filename) 
    {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        string line, source, destination, weightStr;
        while (getline(file, line)) 
        {
            stringstream ss(line);
            getline(ss, source, ',');
            getline(ss, destination, ',');
            getline(ss, weightStr, ',');

             try 
             {
                int weight = stoi(weightStr);
                addRoad(source, destination, weight);
             } 
             catch (const invalid_argument& e) {}
        }
        file.close();
    }

    void loadDisruptions(const string& filename) 
    {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        string line;
        getline(file, line);


        string source, destination, status;
        while (getline(file, line)) 
        {
            stringstream ss(line);
            getline(ss, source, ',');
            getline(ss, destination, ',');
            getline(ss, status, ',');

            if (status == "Blocked" || status == "Under Repair" ) 
            {
                blockRoad(source, destination);
            }
        }
        file.close();
    }
    
    
    void shortestPathdijkstra(string start, string end) 
    {
         int INF = 1e9;

        NodeDistance nodes[26];

        int nodeCount = 0;
        IntersectionNode* current = head;
        
        while (current) 
        {
            NodeDistance defaultNode(current->name, INF);
            nodes[nodeCount++] = defaultNode;
            current = current->next;
        }
        
        
        int startIndex = getIndex(start, nodes,nodeCount);
       
       if (startIndex == -1) 
        {
            cout << "Start node not found." << endl;
            return;
        }
        
        nodes[startIndex].distance = 0;

        for (int i = 0; i < nodeCount; ++i) 
        {
            int minDist = INF, u = -1;
            
            for (int j = 0; j < nodeCount; ++j) 
            {
                if (!nodes[j].visited && nodes[j].distance < minDist) 
                {
                    minDist = nodes[j].distance;
                    u = j;
                }
            }

            if (u == -1) 
            break; 
           
            nodes[u].visited = true;

            IntersectionNode* node = findIntersection(nodes[u].name);
            EdgeNode* edge = node->edgeList;

            while (edge) 
            {
                  if (isRoadBlocked(nodes[u].name, edge->destination)) 
                  {
                      edge = edge->next;
                      continue;
                  }
               
                int neighborIndex = getIndex(edge->destination, nodes,nodeCount);
                if (!nodes[neighborIndex].visited) 
                {
                    int newDist = nodes[u].distance + edge->travelTime;
                    if (newDist < nodes[neighborIndex].distance) 
                    {
                        nodes[neighborIndex].distance = newDist;
                        nodes[neighborIndex].parent = nodes[u].name;
                    }
                }
                edge = edge->next;
            }
        }

    void printBlockedRoads() 
    {
          if (blockedRoads == nullptr) 
          {
            cout << "No blocked roads." << endl;
            return;
          }

          BlockedRoad* current = blockedRoads ->next;
          
          cout << "Blocked Roads: " << endl;
          while (current) 
          {
              cout << "From " << current->source << " to " << current->destination << endl;
              if(current->next)
              current = current->next -> next;
              else
              current = nullptr;
          }
    }

};

int main() {    
    return 0;
}
