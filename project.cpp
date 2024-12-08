
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
struct TrafficSignal
{
    string intersection;
    int greenTime;

    TrafficSignal() {}
    TrafficSignal(string inter, int time) : intersection(inter), greenTime(time) {}
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
class Queue
{
    struct QueueNode
    {
        string id;
        QueueNode *next;

        QueueNode(string id) : id(id), next(nullptr) {}
    };

    QueueNode *front;
    QueueNode *rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(const string &id)
    {
        QueueNode *newNode = new QueueNode(id);
        if (rear == nullptr)
        {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    bool dequeue(string &id)
    {
        if (front == nullptr)
            return false;

        QueueNode *temp = front;
        id = front->id;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        delete temp;
        return true;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    ~Queue()
    {
        while (front != nullptr)
        {
            QueueNode *temp = front;
            front = front->next;
            delete temp;
        }
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
class TrafficSignalManager
{
private:
    TrafficSignal signals[26];
    int signalCount;

public:
    TrafficSignalManager() : signalCount(0) {}

    TrafficSignal *getSignal(string name)
    {
        for (int i = 0; i < 26; i++)
        {
            if (name == signals[i].intersection)
                return &signals[i];
        }

        return NULL;
    }
    // Parse traffic signal data
    void parseTrafficSignals(const string &filename)
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
            string intersection;
            int greenTime;
            getline(ss, intersection, ',');
            ss >> greenTime;

            signals[signalCount++] = TrafficSignal(intersection, greenTime);
        }
        file.close();
    }

    // Display current signal timings
    void displaySignals()
    {
        for (int i = 0; i < signalCount; ++i)
        {
            cout << "Intersection: " << signals[i].intersection
                 << ", Green Time: " << signals[i].greenTime << " seconds.\n";
        }
    }
};
class TrafficGraph
{
    IntersectionNode *head;
    BlockedRoad *blockedRoads;
    HashTable h;
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

    // Helper function to print the path from start to end
    void path(string previous[], const string &end)
    {
        if (previous[end[0] - 'A'] == "")
        {
            cout << end;
            return;
        }

        h.insertRoad(previous[end[0] - 'A'], end);
        h.incrementVehicleCount(previous[end[0] - 'A'], end);

        path(previous, previous[end[0] - 'A']);
        cout << end;
    }

    // BFS to find the path from start to end intersection
    void BFS(const string &start, const string &end)
    {
        // Arrays to track visited intersections, previous intersections and total weight of the path
        bool visited[256] = {false};
        string previous[256];
        int weight[256] = {0};

        for (int i = 0; i < 256; i++)
        {
            previous[i] = "";
            weight[i] = 0;
        }

        // Queue to explore intersections
        Queue queue;

        // Start BFS from the 'start' node
        queue.enqueue(start);
        visited[start[0] - 'A'] = true;

        while (!queue.isEmpty())
        {
            string current;
            if (!queue.dequeue(current))
                continue;

            // If we reach the destination, print the path and total weight
            if (current == end)
            {
                shortestPath(start, end, 0);
                path(previous, end);
                return;
            }

            // Traverse the adjacent nodes (roads)
            IntersectionNode *currentNode = findIntersection(current);
            if (currentNode == nullptr)
                continue;

            EdgeNode *adj = currentNode->edgeList;
            while (adj != nullptr)
            {
                int adjIndex = adj->destination[0] - 'A';
                if (!visited[adjIndex] && !isRoadBlocked(current, adj->destination))
                {
                    queue.enqueue(adj->destination);
                    visited[adjIndex] = true;
                    previous[adjIndex] = current;
                    weight[adjIndex] = weight[current[0] - 'A'] + adj->travelTime;
                }
                adj = adj->next;
            }
        }

        cout << "No path found from " << start << " to " << end << endl;
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
    void printSignal()
    {
        manager.displaySignals();
    }
    void resetHash()
    {
        h.reset();
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
    void findAllPaths(const string &current, const string &end, bool visited[], string path[], int &pathIndex, int currentWeight)
    {
        // Mark the current node as visited and add it to the path
        visited[current[0] - 'A'] = true;
        path[pathIndex] = current;
        pathIndex++;

        // If we reach the destination, print the path and total weight
        if (current == end)
        {
            cout << "Path: ";
            for (int i = 0; i < pathIndex; i++)
            {
                cout << path[i];
                if (i < pathIndex - 1)
                    cout << " -> ";
            }
            cout << " | Total Weight: " << currentWeight << endl;
        }
        else
        {
            // Explore all adjacent nodes
            IntersectionNode *currentNode = findIntersection(current);
            if (currentNode)
            {
                EdgeNode *adj = currentNode->edgeList;
                while (adj != nullptr)
                {
                    int adjIndex = adj->destination[0] - 'A';
                    if (!visited[adjIndex] && !isRoadBlocked(current, adj->destination))
                    {
                        findAllPaths(adj->destination, end, visited, path, pathIndex, currentWeight + adj->travelTime);
                    }
                    adj = adj->next;
                }
            }
        }

        visited[current[0] - 'A'] = false;
        pathIndex--;
    }

    void printAll(const string &start, const string &end)
    {
        string path[256];            // Array to store the current path
        bool visited[256] = {false}; // Track visited nodes
        int pathIndex = 0;           // Index for the current path
        findAllPaths(start, end, visited, path, pathIndex, 0);
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

    void TrafficSignalsStatus()
    {  
        ifstream signalFile("traffic_signals.csv");
	if (!signalFile.is_open()) {
	    cout << "Error: Could not open traffic_signals.csv\n";
	    return;
	}

	string line;
	getline(signalFile, line); 
	while (getline(signalFile, line)) {
	stringstream ss(line);
	string intersection, greenTimeStr;
	getline(ss, intersection, ',');
	getline(ss, greenTimeStr, ',');


        cout << "Intersection " << intersection << " Green Time: " << greenTimeStr<<endl;
    }
	    
	signalFile.close();
	cout<<endl<<endl;
    }
};

int main()
{
    TrafficGraph trafficGraph;

    trafficGraph.loadFromCSV("road_network.csv");
    trafficGraph.loadDisruptions("road_closures.csv");
    trafficGraph.processVehiclesCSV("vehicles.csv");
     
    int choice;
    bool flag = true;
    while(flag == true)
    {
    	cout<<"------SIMULATION DASHBOARD------"<<endl;
    	cout<<"1.  Display City Traffic Network"<<endl;
    	cout<<"2.  Display Traffic Signal Status"<<endl;
    	cout<<"3.  Display Congestion Status"<<endl;
    	cout<<"4.  Display Blocked Roads"<<endl;
    	cout<<"5.  Handle Emergency Vehicle Routing"<<endl;
    	cout<<"6.  Block Road due to Accident"<<endl;
    	cout<<"7.  Simulate Vehicle Routing"<<endl;
    	cout<<"8.  Add Vehicle"<<endl;
    	cout<<"9.  Manage Signals"<<endl;
    	cout<<"10. Add Priority Vehicle"<<endl;
    	cout<<"11. Shortest Path"<<endl;
    	cout<<"12. Exit Simulation"<<endl;
    	cout<<endl;
    	cout<<"Enter your choice: ";
    	
    	cin>>choice;
    	
    	while (choice > 12 || choice < 1)
    	{
    		cout<<"Invalid Input!"<<endl;
    		cout<<"Enter Valid Option: ";
    		cin>>choice;
    	}
    	
    	switch (choice)
    	{
    		case 1:
    		{
    		     cout<<"------City Traffic Network------"<<endl;
    		     trafficGraph.displayNetwork();
    		     cout << endl;
    		     break;
    		}
    		case 2:
    		{
    			cout<<"------Traffic Signal Status------"<<endl;
    			trafficGraph.TrafficSignalsStatus();
    			break;
    		}
    		case 3:
    		{
    			cout<<"------Congestion status------"<<endl;
    			trafficGraph.totalCongestion();
    			break;
    		}
    		case 4:
    		{
    			cout<<"------Blocked Roads------"<<endl;
    			trafficGraph.printBlockedRoads();
    			break;
    		}
    		case 5:
    		{
    			string st , e;
    			cout<<"------Emergency Vehicle Handling------"<<endl;
    			cout<<"Enter The start Intersection: ";
    			cin>>st;
    			cout<<"Enter The End Intersection: ";
    			cin>>e;
    			trafficGraph.shortestPathdijkstra(st, e);
    			trafficGraph.ok2(st, e, 1);
    			cout<<"Signal Status for emergency"<<endl;
    			trafficGraph.TrafficSignalsStatus();
    			trafficGraph.ok2(st, e, 0);
    			cout<<"Signal Status back to normal"<<endl;
    			trafficGraph.TrafficSignalsStatus();
    			break;    			
    		}
    		case 6:
    		{
    			string st , e;
    			cout<<"------Block Roads------"<<endl;
    			cout<<"Enter The start Intersection of the road you want to block: ";
    			cin>>st;
    			cout<<"Enter The End Intersection of the road you want to block: ";
    			cin>>e;
    			trafficGraph.blockRoad(st, e);
    			trafficGraph.resetHash();
    			trafficGraph.processVehiclesCSV("vehicles.csv");
    			break;
    		}
    		case 7:
    		{
    			string st , e;
    			cout<<"------Vehicle Routing------"<<endl;
    			cout<<"Enter The start Intersection: ";
    			cin>>st;
    			cout<<"Enter The End Intersection: ";
    			cin>>e;
    			cout<<"All Possible paths from "<< st <<" to "<<e<<" are: "<<endl;
    			trafficGraph.printAll(st,e);
    			break;
    		}
    		case 8:
    		{
    		        string st , e;
    			cout<<"------Add Vehicle------"<<endl;
    			cout<<"Enter The start Intersection: ";
    			cin>>st;
    			cout<<"Enter The End Intersection: ";
    			cin>>e;
    			trafficGraph.addVehicle(st,e);
    			break;
    			
    		}
    		case 9:
    		{       
    		        cout<<"------Manage Signal for Highest Priority------"<<endl;
    			trafficGraph.manageSignals();
    			break;
    		}
    		case 10:
    		{
    		        string st , e, name, pr;
    		        int p = -5;
    		        cout<<"------Add Priority Vehicle------"<<endl;
    		        cout<<"Enter Car ID: ";
    			cin>>name;
    			cout<<"Enter The start Intersection: ";
    			cin>>st;
    			cout<<"Enter The End Intersection: ";
    			cin>>e;
    			cout<<"Enter 1)High 2)Medium 3)Low priority: "<<endl;
    			
    			while(p<= 0 || p>3)
    			cin>>p;
    			
    			if(p == 1)
    			pr = "High";
    			else if(p == 2)
    			pr = "Medium";
    			else
    			pr = "Low";
    			
    			trafficGraph.insertVehicleWithPriority(name, st, e,pr);
    			break;
    		}
    		case 11:
    		{
    			cout<<"------Shortest Path------"<<endl;
                        string st , e;
    			cout<<"Enter The start Intersection: ";
    			cin>>st;
    			cout<<"Enter The End Intersection: ";
    			cin>>e;
    			trafficGraph.shortestPathdijkstra(st,e);
    			break;
    		}
    		case 12:
    		{
    			cout<<"Exiting The Simulation!"<<endl;
    			flag = false;
    			break;
    		}
    	}
    	
    } 
     

    return 0;
}
