#include <iostream>
#include <unordered_set>

using namespace std;

class VertexNode {
 public:
    int vertexNumber;
    int inDegree = 0;
    char color = '?';

    explicit VertexNode(int vertexNumber) {
        this->vertexNumber = vertexNumber;
    }
};

class AdjacencyLineNode {
 public:
    int vertexNumber;
    AdjacencyLineNode* next = nullptr;

    explicit AdjacencyLineNode(int vertexNumber, AdjacencyLineNode* next = nullptr) {
        this->vertexNumber = vertexNumber;
        this->next = next;
    }
};

class AdjacencyLine {
 public:
    VertexNode* vertexOwner;
    AdjacencyLineNode* next;
    AdjacencyLineNode* tail;

    AdjacencyLine(VertexNode* vertexOwner, AdjacencyLineNode* next = nullptr) {
        this->vertexOwner = vertexOwner;
        this->next = next;
    }
};

class AdjacencyList {
 public:
    AdjacencyLine** adjacencyListArray;
    int arraySize;

    explicit AdjacencyList(int arraySize) {
        this->arraySize = arraySize;
        this->adjacencyListArray = (AdjacencyLine **) calloc(arraySize, sizeof(AdjacencyLine*));
        VertexNode* vertexNode;
        AdjacencyLine* vertexNodeAdjacencyLine;
        for (int i = 0; i < arraySize; i++) {
            vertexNode = new VertexNode(i);
            vertexNodeAdjacencyLine = new AdjacencyLine(vertexNode);
            adjacencyListArray[i] = vertexNodeAdjacencyLine;
        }
    }

    void addEdge(int from, int to) {
        AdjacencyLineNode* newAdjacencyLineNode = new AdjacencyLineNode(to, nullptr);
        bool adjacencyLineIsEmpty = this->adjacencyListArray[from]->next == nullptr;
        if (!adjacencyLineIsEmpty) {
            this->adjacencyListArray[from]->tail->next = newAdjacencyLineNode;
        } else {
            this->adjacencyListArray[from]->next = newAdjacencyLineNode;
        }
        this->adjacencyListArray[from]->tail = newAdjacencyLineNode;
    }
};

class StackNode {
 public:
    int value;
    StackNode* previous;

    explicit StackNode(int value, StackNode* previous = nullptr) {
        this->value = value;
        this->previous = previous;
    }
};

class Stack {
 public:
    StackNode* head = nullptr;

    bool isEmpty() {
        return head == nullptr;
    }

    void push(int value) {
        StackNode* newStackNode = new StackNode(value);
        if (!isEmpty()) {
            newStackNode->previous = this->head;
        }
        this->head = newStackNode;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty, nothing to pop." << endl;
            return -1;
        }

        StackNode* previousHead = this->head;
        this->head = previousHead->previous;
        int result = previousHead->value;
        free(previousHead);

        return result;
    }
};

class Graph {
 public:
    AdjacencyList* adjacencyList = nullptr;
    int verticesNumber;

    explicit Graph(int verticesCapacity) {
        this->adjacencyList = new AdjacencyList(verticesCapacity);
        this->verticesNumber = verticesCapacity;
    }

    void addEdge(int from, int to) {
        this->adjacencyList->addEdge(from, to);
    }

    void print() {
        cout << "Graph" << endl;
        if (adjacencyList == nullptr) {
            return;
        }

        AdjacencyLineNode* currentAdjacencyLineNode;
        for (int i = 0; i < adjacencyList->arraySize; i++) {
            if (adjacencyList->adjacencyListArray[i]->next != nullptr) {
                cout << i << " - ";
                currentAdjacencyLineNode = adjacencyList->adjacencyListArray[i]->next;
                while (currentAdjacencyLineNode->next != nullptr) {
                    cout << currentAdjacencyLineNode->vertexNumber << " ";
                    currentAdjacencyLineNode = currentAdjacencyLineNode->next;
                }
                cout << currentAdjacencyLineNode->vertexNumber;
            } else {
                cout << i << " - None";
            }

            cout << endl;
        }
    }

    void visitVertexDFS(int vertex, Stack* answer) {
        this->adjacencyList->adjacencyListArray[vertex]->vertexOwner->color = 'g';
        AdjacencyLineNode* targetVertex = this->adjacencyList->adjacencyListArray[vertex]->next;
        while (targetVertex != nullptr) {
            if (this->adjacencyList->adjacencyListArray[targetVertex->vertexNumber]->vertexOwner->color == 'w') {
                visitVertexDFS(targetVertex->vertexNumber, answer);
            }
            targetVertex = targetVertex->next;
        }

        this->adjacencyList->adjacencyListArray[vertex]->vertexOwner->color = 'b';
        answer->push(vertex);
    }

    void depthFirstSearch(Stack* answer) {
        for (int i = 0; i < this->verticesNumber; i++) {
            this->adjacencyList->adjacencyListArray[i]->vertexOwner->color = 'w';
        }

        for (int i = 0; i < this->verticesNumber; i++) {
            if (this->adjacencyList->adjacencyListArray[i]->vertexOwner->color == 'w') {
                visitVertexDFS(i, answer);
            }
        }
    }
};

class QueueNode {
 public:
    QueueNode* previous;
    int vertexNumber;

    explicit QueueNode(int vertexNumber, QueueNode * previous = nullptr) {
        this->vertexNumber = vertexNumber;
        this->previous = previous;
    }
};

class Queue {
 public:
    QueueNode * head = nullptr;
    QueueNode * tail = nullptr;
    int length;

    bool isEmpty() {
        return length == 0;
    }

    void enqueue(int vertexNumber) {
        QueueNode * queueNode = new QueueNode(vertexNumber, nullptr);
        if (this->isEmpty()) {
            this->head = queueNode;
            this->tail = queueNode;
            length++;
            return;
        }

        this->tail->previous = queueNode;
        this->tail = queueNode;
        this->length++;
    }

    int dequeue() {
        if (this->isEmpty()) {
            return -1;
        }

        QueueNode* result = this->head;

        if (this->length == 1) {
            free(this->head);
            this->head = nullptr;
            this->tail = nullptr;
        } else {
            QueueNode* prevHead = this->head;
            this->head = this->head->previous;
            free(prevHead);
        }

        this->length--;
        return result->vertexNumber;
    }

    void print() {
        QueueNode* currentNode = this->head;
        while (currentNode != nullptr) {
            cout << currentNode->vertexNumber << " ";
            currentNode = currentNode->previous;
        }
        cout << endl;
    }
};

int main() {
    cout << "Enter the number of vertices:" << endl;
    int numberOfVertices;
    cin >> numberOfVertices;
    Graph* graph = new Graph(numberOfVertices);
    cout << "Enter the adjacency matrix:" << endl;

    int isAdjacent = 0;
    for (int from = 0; from < numberOfVertices; from++) {
        for (int to = 0; to < numberOfVertices; to++) {
            cin >> isAdjacent;
            if (isAdjacent) {
                graph->addEdge(from, to);
                graph->adjacencyList->adjacencyListArray[to]->vertexOwner->inDegree += 1;
            }
        }
    }

    graph->print();

    Queue* answer = new Queue();
    Queue* utilityQueue = new Queue();
    AdjacencyLine* currentLine;
    for (int i = 0; i < graph->verticesNumber; i++) {
        if (graph->adjacencyList->adjacencyListArray[i]->vertexOwner->inDegree == 0) {
            utilityQueue->enqueue(i);
        }
    }

    int extractedVertex;
    while (!utilityQueue->isEmpty()) {
        extractedVertex = utilityQueue->dequeue();
        answer->enqueue(extractedVertex);

        AdjacencyLineNode* childNode = graph->adjacencyList->adjacencyListArray[extractedVertex]->next;
        VertexNode* childVertex;
        while (childNode != nullptr) {
            childVertex = graph->adjacencyList->adjacencyListArray[childNode->vertexNumber]->vertexOwner;
            childVertex->inDegree -= 1;
            if (childVertex->inDegree == 0) {
                utilityQueue->enqueue(childVertex->vertexNumber);
            }
            childNode = childNode->next;
        }
    }

    if (answer->length != graph->verticesNumber) {
        cout << "Topological sort is not valid on this graph." << endl;
    } else {
        cout << "Khan`s topological sort result:" << endl;
        answer->print();
    }

    return 0;
}
