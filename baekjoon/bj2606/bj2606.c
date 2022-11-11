#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0

typedef int ElementType;

/* graph data structure */
struct IncidentEdge;
struct Vertex;

typedef struct IncidentEdge {
    struct Vertex* adjacentVertex;
    struct IncidentEdge* next;
} IncidentEdge;

typedef struct Vertex {
    ElementType element;
    int isVisited;
    struct IncidentEdge* incidentEdgeHead;
    struct Vertex* next;
} Vertex;

typedef struct {
    struct Vertex* vertexHead;
} Graph;

Graph* makeGraph(void) {
    Graph* newGraph = (Graph*)malloc(sizeof(Graph));
    newGraph->vertexHead = NULL;
    return newGraph;
}

Vertex* addVertex(Graph* targetGraph, ElementType element) {
    Vertex* newVertex = (Vertex*)malloc(sizeof(Vertex));
    newVertex->element = element;
    newVertex->isVisited = FALSE;
    newVertex->incidentEdgeHead = NULL;
    newVertex->next = NULL;

    if (targetGraph->vertexHead == NULL) {
        targetGraph->vertexHead = newVertex;
    } else {
        Vertex* p = targetGraph->vertexHead;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newVertex;
    }

    return newVertex;
}

Vertex* findVertex(Graph* graph, ElementType element) {
    Vertex* p = graph->vertexHead;

    while (p != NULL) {
        if (p->element == element) {
            return p;
        }
        p = p->next;
    }

    return NULL;
}

IncidentEdge* addIncidentEdge(Vertex* fromVertex, Vertex* toVertex) {
    IncidentEdge* newIncidentEdge = (IncidentEdge*)malloc(sizeof(IncidentEdge));
    newIncidentEdge->adjacentVertex = toVertex;
    newIncidentEdge->next = NULL;
    
    if (fromVertex->incidentEdgeHead == NULL) {
        fromVertex->incidentEdgeHead = newIncidentEdge;
    } else {
        IncidentEdge* p = fromVertex->incidentEdgeHead;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = newIncidentEdge;
    }
    
    return newIncidentEdge;
}

void addEdge(Graph* targetGraph, ElementType elem1, ElementType elem2) {
    Vertex* v1 = findVertex(targetGraph, elem1);
    Vertex* v2 = findVertex(targetGraph, elem2);
    addIncidentEdge(v1, v2);
    addIncidentEdge(v2, v1);
}

void printGraph(Graph* graph) {
    Vertex* p = graph->vertexHead;

    while (p != NULL) {
        printf("[%d]: ", p->element);
        for (IncidentEdge* q = p->incidentEdgeHead; q != NULL; q = q->next) {
            printf("(%d) ", q->adjacentVertex->element);
        }
        printf("\n");
        p = p->next;
    }
}

int getVertexSize(Graph* graph, Vertex* rootElement) { // dfs
    if (rootElement->isVisited) {
        return 0;
    }
    rootElement->isVisited = TRUE;

    IncidentEdge* p = rootElement->incidentEdgeHead;
    int neighborCount = 1; // this element
    while (p != NULL) {
        neighborCount += getVertexSize(graph, p->adjacentVertex);
        p = p->next;
    }

    return neighborCount;
}

int main(void) {
    int vCount, eCount;
    scanf("%d %d", &vCount, &eCount);

    Graph* g = makeGraph();
    for (int i = 1; i <= vCount; i++) {
        addVertex(g, i);
    }

    int edge1, edge2;
    for (int i = 0; i < eCount; i++) {
        scanf("%d %d", &edge1, &edge2);
        addEdge(g, edge1, edge2);
    }

    printf("%d\n", getVertexSize(g, findVertex(g, 1)) - 1);

    return 0;
}