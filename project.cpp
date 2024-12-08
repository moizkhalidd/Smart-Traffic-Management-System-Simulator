
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
struct Road
{
    string source;
    string destination;
    int vehicleCount;
    Road *next;

    Road(string src, string dest, int count = 0)
        : source(src), destination(dest), vehicleCount(count), next(nullptr) {}
};
struct EdgeNode
{
    string destination;
    int travelTime;
    EdgeNode *next;

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
    EdgeNode *edgeList;
    IntersectionNode *next;

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
    {
    }

    NodeDistance(string n, int d)
    {
        name = n;
        distance = d;
        visited = 0;
        parent = "";
    }
};
struct BlockedRoad
{
    string source;
    string destination;
    string status;
    BlockedRoad *next;

    BlockedRoad(string s, string d, string stat)
    {
        source = s;
        destination = d;
        next = nullptr;
        status = stat;
    }
};
struct HeapNode
{
    string id;
    string start;
    string end;
    int priority;

    HeapNode(string name, string s, string e, string p) : id(name), start(s), end(e)
    {
        if (p == "High")
        {
            priority = 1;
        }
        else if (p == "Medium")
        {
            priority = 2;
        }
        else
            priority = 3;
    }
};
class MinHeap
{
private:
    HeapNode *heap[100];
    int size;

    void heapifyUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[parent]->priority <= heap[index]->priority)
                break;

            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    void heapifyDown(int index)
    {
        int left, right, smallest;
        while (true)
        {
            left = 2 * index + 1;
            right = 2 * index + 2;
            smallest = index;

            if (left < size && heap[left]->priority < heap[smallest]->priority)
                smallest = left;
            if (right < size && heap[right]->priority < heap[smallest]->priority)
                smallest = right;

            if (smallest == index)
                break;

            swap(heap[smallest], heap[index]);
            index = smallest;
        }
    }

public:
    MinHeap() : size(0) {}

    void insert(string &id, const string &src, string &end, string priority)
    {
        if (size >= 100)
            return; // Heap capacity
        heap[size] = new HeapNode(id, src, end, priority);
        heapifyUp(size);
        size++;
    }

    HeapNode *extractMin()
    {
        if (size == 0)
            return nullptr;
        HeapNode *root = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        return root;
    }

    bool isEmpty()
    {
        return size == 0;
    }
};

class HashTable
{
private:
    Road *table[100] = {nullptr};

    int hashFunction(const string &source, const string &destination)
    {
        int hash = 0;
        for (char c : source + destination)
        {
            hash = (hash * 31 + c) % 100;
        }
        return hash;
    }

public:
    void reset()
    {
        for (int i = 0; i < 100; i++)
        {
            table[i] = nullptr;
        }
    }

    int getCount(string start, string end)
    {
        int index = hashFunction(start, end);
        Road *current = table[index];

        while (current)
        {
            if (current->source == start && current->destination == end)
            {
                return current->vehicleCount;
            }
            current = current->next;
        }

        return 0;
    }
    // Insert a road into the hash table
    void insertRoad(const string &source, const string &destination)
    {
        int index = hashFunction(source, destination);
        Road *current = table[index];

        while (current)
        {
            if (current->source == source && current->destination == destination)
            {
                return;
            }
            current = current->next;
        }

        Road *newRoad = new Road(source, destination);
        newRoad->next = table[index];
        table[index] = newRoad;
    }

    // Increment vehicle count
    void incrementVehicleCount(const string &source, const string &destination)
    {
        int index = hashFunction(source, destination);
        Road *current = table[index];
        while (current)
        {
            if (current->source == source && current->destination == destination)
            {
                current->vehicleCount++;
                return;
            }
            current = current->next;
        }
    }

    // decrement vehicle count
    void decrementVehicleCount(const string &source, const string &destination)
    {
        int index = hashFunction(source, destination);
        Road *current = table[index];
        while (current)
        {
            if (current->source == source && current->destination == destination)
            {
                current->vehicleCount--;
                if (current->vehicleCount < 0)
                    current->vehicleCount = 0;
                return;
            }
            current = current->next;
        }
    }

    // Retrieve vehicle count
    int getVehicleCount(const string &source, const string &destination)
    {
        int index = hashFunction(source, destination);
        Road *current = table[index];
        while (current)
        {
            if (current->source == source && current->destination == destination)
            {
                return current->vehicleCount;
            }
            current = current->next;
        }
        return -1; // Road not found
    }

    // Display congestion levels
    void displayCongestion()
    {
        for (int i = 0; i < 100; ++i)
        {
            Road *current = table[i];
            while (current)
            {
                cout << "Road: " << current->source << " -> " << current->destination
                     << ", Vehicles: " << current->vehicleCount << endl;
                current = current->next;
            }
        }
    }
};
class TrafficGraph
{
    IntersectionNode *head;
    BlockedRoad *blockedRoads;
    TrafficSignalManager manager;
    MinHeap heap;

    IntersectionNode *findIntersection(string name)
    {
        IntersectionNode *current = head;
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

        IntersectionNode *current = head;
        while (current != nullptr)
        {
            EdgeNode *prev = nullptr;
            EdgeNode *edge = current->edgeList;
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

    int getIndex(const string &name, NodeDistance nodes[], int nodeCount)
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
        BlockedRoad *current = blockedRoads;
        while (current)
        {
            if ((current->source == source && current->destination == destination) || (current->source == destination && current->destination == source))
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

public:
    TrafficGraph() : head(nullptr), blockedRoads(nullptr)
    {
        manager.parseTrafficSignals("traffic_signals.csv");
        emergencyCSV("emergency_vehicles.csv");
    }

    ~TrafficGraph()
    {
        while (head != nullptr)
        {
            IntersectionNode *temp = head;
            head = head->next;

            EdgeNode *edge = temp->edgeList;
            while (edge != nullptr)
            {
                EdgeNode *edgeTemp = edge;
                edge = edge->next;
                delete edgeTemp;
            }

            delete temp;
        }
    }

    void emergencyCSV(const string &filename)
    {
        ifstream file(filename);
        string line;
        int i = 0;
        while (getline(file, line))
        {

            if (i == 0)
            {
                i++;
                continue;
            }
            stringstream ss(line);
            string name, src, end, priority;

            getline(ss, name, ',');
            getline(ss, src, ',');
            getline(ss, end, ',');
            getline(ss, priority, ',');

            heap.insert(name, src, end, priority);
        }
        file.close();
    }

    void addIntersection(string name)
    {
        if (findIntersection(name) == nullptr)
        {
            IntersectionNode *newNode = new IntersectionNode(name);

            if (head == nullptr)
                head = newNode;
            else
            {
                IntersectionNode *temp = head;
                while (temp->next != nullptr)
                    temp = temp->next;

                temp->next = newNode;
                temp = nullptr;
                delete temp;
            }
        }
    }

    void addRoad(string source, string destination, int travelTime)
    {

        addIntersection(source);
        addIntersection(destination);

        IntersectionNode *sourceNode = findIntersection(source);
        EdgeNode *newEdge1 = new EdgeNode(destination, travelTime);

        if (sourceNode->edgeList == nullptr)
            sourceNode->edgeList = newEdge1;
        else
        {
            EdgeNode *temp = sourceNode->edgeList;
            while (temp->next != nullptr)
                temp = temp->next;

            temp->next = newEdge1;
            temp = nullptr;
            delete temp;
        }

        IntersectionNode *destinationNode = findIntersection(destination);
        EdgeNode *newEdge2 = new EdgeNode(source, travelTime);

        if (destinationNode->edgeList == nullptr)
            destinationNode->edgeList = newEdge2;
        else
        {
            EdgeNode *temp = destinationNode->edgeList;
            while (temp->next != nullptr)
                temp = temp->next;

            temp->next = newEdge2;
            temp = nullptr;
            delete temp;
        }
    }

    void removeIntersection(string name)
    {
        removeIncomingEdges(name);

        IntersectionNode *prev = nullptr;
        IntersectionNode *current = head;

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

                EdgeNode *edge = current->edgeList;
                while (edge != nullptr)
                {
                    EdgeNode *temp = edge;
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

    void removeRoad(string source, string destination)
    {
        IntersectionNode *sourceNode = findIntersection(source);
        if (sourceNode == nullptr)
            return;

        EdgeNode *prev = nullptr;
        EdgeNode *edge = sourceNode->edgeList;

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

    void blockRoad(string source, string destination, string status = "Blocked")
    {
        IntersectionNode *sourceNode = findIntersection(source);
        if (sourceNode == nullptr)
        {
            cout << "Error: Source intersection " << source << " does not exist." << endl;
            return;
        }

        EdgeNode *edge = sourceNode->edgeList;
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
            BlockedRoad *newBlockedRoad = new BlockedRoad(source, destination, status);
            newBlockedRoad->next = blockedRoads;
            blockedRoads = newBlockedRoad;

            newBlockedRoad = new BlockedRoad(destination, source, status);
            newBlockedRoad->next = blockedRoads;
            blockedRoads = newBlockedRoad;
        }
        else
            cout << "Road does not exist from " << source << " to " << destination << endl;
    }

    void displayNetwork()
    {
        IntersectionNode *current = head;
        while (current != nullptr)
        {
            cout << current->name << " -> ";
            EdgeNode *edge = current->edgeList;

            while (edge != nullptr)
            {
                cout << " (" << edge->destination << "," << edge->travelTime << ")";
                edge = edge->next;
            }
            cout << endl;
            current = current->next;
        }
    }

    void loadFromCSV(string filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
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
            catch (const invalid_argument &e)
            {
            }
        }
        file.close();
    }

    void loadDisruptions(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
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

            if (status == "Blocked" || status == "Under Repair")
            {
                blockRoad(source, destination, status);
            }
        }
        file.close();
    }

    void shortestPathdijkstra(string start, string end)
    {
        int INF = 1e9;

        NodeDistance nodes[26];

        int nodeCount = 0;
        IntersectionNode *current = head;

        while (current)
        {
            NodeDistance defaultNode(current->name, INF);
            nodes[nodeCount++] = defaultNode;
            current = current->next;
        }

        int startIndex = getIndex(start, nodes, nodeCount);

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

            IntersectionNode *node = findIntersection(nodes[u].name);
            EdgeNode *edge = node->edgeList;

            while (edge)
            {
                if (isRoadBlocked(nodes[u].name, edge->destination))
                {
                    edge = edge->next;
                    continue;
                }

                int neighborIndex = getIndex(edge->destination, nodes, nodeCount);
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

        int endIndex = getIndex(end, nodes, nodeCount);

        if (endIndex == -1 || nodes[endIndex].distance == INF)
        {
            cout << "No path from " << start << " to " << end << endl;
        }
        else
        {
            cout << "Shortest path from " << start << " to " << end << " is " << nodes[endIndex].distance << " minutes." << endl;

            cout << "Path: ";

            string path[26];
            int pathIndex = 0;

            string currentNode = end;

            while (currentNode != start)
            {
                path[pathIndex++] = currentNode;
                currentNode = nodes[getIndex(currentNode, nodes, nodeCount)].parent;
            }
            path[pathIndex++] = start;

            for (int i = pathIndex - 1; i >= 0; --i)
            {
                cout << path[i];
                if (i != 0)
                    cout << " -> ";
            }
            cout << endl;
        }
    }

    void printBlockedRoads()
    {
        if (blockedRoads == nullptr)
        {
            cout << "No blocked roads." << endl;
            return;
        }

        BlockedRoad *current = blockedRoads->next;

        cout << "Blocked Roads: " << endl;
        while (current)
        {
            cout << current->source << " to " << current->destination << " is " << current->status << endl;
            if (current->next)
                current = current->next->next;
            else
                current = nullptr;
        }
    }

    void shortestPath(string start, string end, bool inp)
    {
        int INF = 1e9;

        NodeDistance nodes[26];

        int nodeCount = 0;
        IntersectionNode *current = head;

        while (current)
        {
            NodeDistance defaultNode(current->name, INF);
            nodes[nodeCount++] = defaultNode;
            current = current->next;
        }

        int startIndex = getIndex(start, nodes, nodeCount);

        if (startIndex == -1)
        {
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

            IntersectionNode *node = findIntersection(nodes[u].name);
            EdgeNode *edge = node->edgeList;

            while (edge)
            {
                if (isRoadBlocked(nodes[u].name, edge->destination))
                {
                    edge = edge->next;
                    continue;
                }

                int neighborIndex = getIndex(edge->destination, nodes, nodeCount);
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

        int endIndex = getIndex(end, nodes, nodeCount);

        if (endIndex == -1 || nodes[endIndex].distance == INF)
        {
        }
        else
        {
            string path[26];
            int pathIndex = 0;

            string currentNode = end;

            while (currentNode != start)
            {
                path[pathIndex++] = currentNode;
                currentNode = nodes[getIndex(currentNode, nodes, nodeCount)].parent;
            }
            path[pathIndex++] = start;

            for (int i = pathIndex - 1; i >= 0; --i)
            {
                if (inp)
                {
                    h.insertRoad(path[i], path[i - 1]);
                    h.incrementVehicleCount(path[i], path[i - 1]);
                    if (h.getCount(path[i], path[i - 1]) >= 5)
                    {
                        BFS(start, end);
                    }
                }
                else
                {
                    h.insertRoad(path[i], path[i - 1]);
                    h.decrementVehicleCount(path[i], path[i - 1]);
                }
            }
        }
    }

    void shortestPath2(string start, string end, bool inp)
    {
        int INF = 1e9;

        NodeDistance nodes[26];

        int nodeCount = 0;
        IntersectionNode *current = head;

        while (current)
        {
            NodeDistance defaultNode(current->name, INF);
            nodes[nodeCount++] = defaultNode;
            current = current->next;
        }

        int startIndex = getIndex(start, nodes, nodeCount);

        if (startIndex == -1)
        {
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

            IntersectionNode *node = findIntersection(nodes[u].name);
            EdgeNode *edge = node->edgeList;

            while (edge)
            {
                if (isRoadBlocked(nodes[u].name, edge->destination))
                {
                    edge = edge->next;
                    continue;
                }

                int neighborIndex = getIndex(edge->destination, nodes, nodeCount);
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

        int endIndex = getIndex(end, nodes, nodeCount);

        if (endIndex == -1 || nodes[endIndex].distance == INF)
        {
        }
        else
        {
            string path[26];
            int pathIndex = 0;

            string currentNode = end;

            while (currentNode != start)
            {
                path[pathIndex++] = currentNode;
                currentNode = nodes[getIndex(currentNode, nodes, nodeCount)].parent;
            }
            path[pathIndex++] = start;

            for (int i = pathIndex - 1; i >= 0; --i)
            {
                if (inp)
                {
                    TrafficSignal *sig = manager.getSignal(path[i]);
                    if (sig != NULL)
                        sig->greenTime += 30;
                }
                else
                {
                    TrafficSignal *sig = manager.getSignal(path[i]);
                    if (sig != NULL)
                        sig->greenTime -= 30;
                }
            }
        }
    }

    void manageSignals()
    {

        HeapNode *road = heap.extractMin();

        shortestPath2(road->start, road->end, 1);
        cout << "Timings Adjusted for Emergency Vehicle" << endl;
        manager.displaySignals();
        shortestPath2(road->start, road->end, 0);
        cout << "Timings Set back to Normal" << endl;
        manager.displaySignals();
    }
};

int main()
{
    return 0;
}
