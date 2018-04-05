#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum { FALSE, TRUE } bool;

typedef struct GraphNode
{
char szName[256]; /* Name of the location stored in the node */
bool visited; /* used in recPathExists to track if the node has been searched yet */
} GraphNode;

typedef struct
{
int iNumNodes; /* Number of nodes in the graph */
GraphNode* nodeArray; /* Array of nodes of the graph */
int** adjMatrix; /* Adjacency matrix repressenting the edges of the graph */
} Graph;

/* Provided functions (do not change) */
void printGraph( Graph G , FILE *out_file );
void printPathMatrix( Graph G, int **pathMatrix, FILE *out_file );
void resetVisited( Graph G );

/* To be completed by you */
bool recPathExists( Graph G , int iIndex1, int iIndex2 );
void allPathsRecFunc( Graph G , int **pathMatrix );
void allPathsWarshall( Graph G , int **pathMatrix );

/* provided code - DO NOT CHANGE (you can comment out different lines to run test data of various sizes)
* main reads in a graph and then compares the runtimes of your two implementations of allPaths.
*/
int main( )
{
//char graphFileName[] = "A6-GraphData8Nodes.txt"; /* Simple test data. Both will finish in <1 millisecond */
char graphFileName[] = "A6-GraphData50Nodes.txt"; /* Medium test data. Both will finish in <20 milliseconds */
//char graphFileName[] = "A6-GraphData100Nodes.txt"; /* Long test data. Both will finish in <100 milliseconds */
//char graphFileName[] = "A6-GraphData500Nodes.txt"; /* Super Long test data. Both will finish in <1 minute! */
//char graphFileName[] = "A6-GraphData1000Nodes.txt";
char outFileName[] = "GraphOutput.txt";
FILE *in_file = fopen(graphFileName, "r");
FILE *out_file = fopen(outFileName, "w");

clock_t start, end;
double lfSeconds;
Graph G;
int **pathMatrix1;
int **pathMatrix2;
int i, j;
bool flag = TRUE;

printf("CS 2123 Assignment 6 written by Grecia Gonzalez\n");

if (in_file == NULL)
{
printf("File %s not found.\n", graphFileName);
return -1;
}

/* read the number of nodes from file and allocate space to store them */
if( fscanf( in_file, "%d", &G.iNumNodes )==0 || G.iNumNodes == 0 )
{
printf( "An invalid number of nodes for the graph was given.");
exit(-1);
}
G.nodeArray = (GraphNode*) malloc( G.iNumNodes*sizeof( GraphNode ) );

/* allocate space to store edges as well as to store the computed path matrix */
G.adjMatrix = (int**) malloc( G.iNumNodes*sizeof( int* ) );
pathMatrix1 = (int**) malloc( G.iNumNodes*sizeof( int* ) );
pathMatrix2 = (int**) malloc( G.iNumNodes*sizeof( int* ) );
for( i=0 ; i<G.iNumNodes; i++)
{
G.adjMatrix[i] = (int*) malloc( G.iNumNodes*sizeof( int ) );
pathMatrix1[i] = (int*) calloc( G.iNumNodes, sizeof( int ) );
pathMatrix2[i] = (int*) calloc( G.iNumNodes, sizeof( int ) );
}

/* read in names of nodes */
for( i=0 ; i<G.iNumNodes; i++)
{
if( fscanf( in_file, "%255s", G.nodeArray[i].szName) == 0 ){
printf( "Failed to read the name of node number %d", i );
exit(-1);
}
G.nodeArray[i].visited = FALSE;
}

/* read in edges and store in matrix */
for( i=0 ; i<G.iNumNodes; i++)
{
for( j=0 ; j<G.iNumNodes; j++)
{
if( fscanf( in_file, "%d", &(G.adjMatrix[i][j]) ) == 0 )
{
printf( "Failed to read position row %d column %d of the adjacency matrix", i, j );
exit(-1);
}
}
}

/* Print the graph out */
printGraph( G, out_file );

/* Zero out pathMatrix */
for( i=0 ; i<G.iNumNodes; i++)
{
for( j=0 ; j<G.iNumNodes; j++)
{
pathMatrix1[i][j] = 0;
pathMatrix2[i][j] = 0;
}
}

/* Call and calculate the runtime of your allPathsRecFunc function */
start = clock();
allPathsRecFunc( G, pathMatrix1 );
end = clock();

/* Print the pathMatrix out */
printPathMatrix( G, pathMatrix1, out_file );

/* Print runtime of your allPathsRecFunc function */
lfSeconds = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
printf( "allPathsRecFunc ran for %.2f milliseconds\n", lfSeconds );

/* Call and calculate the runtime of your allPathsRecFunc function */
start = clock();
allPathsWarshall( G, pathMatrix2 );
end = clock();

/* Print the pathMatrix out */
printPathMatrix( G, pathMatrix2, out_file );

/* Print runtime of your allPathsRecFunc function */
lfSeconds = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
printf( "allPathsWarshall ran for %.2f milliseconds\n", lfSeconds );

/* Compare pathMatrix1 and pathMatrix2 */
for( i=0 ; i<G.iNumNodes; i++)
{
for( j=0 ; j<G.iNumNodes; j++)
{
if( pathMatrix1[i][j] != pathMatrix2[i][j] )
flag = FALSE;
}
}
if( flag == TRUE )
printf( "Your implementations computed the same path matrix! :)\n" );
else
printf( "Your implementations computed different path matrices! :(\n" );

/* Free graph and pathMatrix data */
for( i=0 ; i<G.iNumNodes; i++)
{
free(G.adjMatrix[i]);
free(pathMatrix1[i]);
free(pathMatrix2[i]);
}
free(G.adjMatrix);
free(pathMatrix1);
free(pathMatrix2);
free(G.nodeArray);

fclose(in_file);
fclose(out_file);

return 0;
}

bool recPathExists( Graph G, int iIndex1, int iIndex2 )
{
if (G.adjMatrix[iIndex1][iIndex2])
return TRUE;

bool found = FALSE;
for (int i = 0; i < G.iNumNodes; i++) {
if (found == TRUE)
return found;
else if (G.adjMatrix[iIndex1][i] && G.nodeArray[i].visited == FALSE) {
G.nodeArray[i].visited = TRUE;
found = recPathExists(G, i, iIndex2);
}
}

return found;
}

void allPathsRecFunc( Graph G , int **pathMatrix )
{
for (int i = 0; i < G.iNumNodes; i++) {
for (int j = 0; j < G.iNumNodes; j++) {
if (recPathExists(G, i, j) == TRUE)
pathMatrix[i][j] = 1;

resetVisited(G);
}
}
}


void allPathsWarshall( Graph G , int **pathMatrix )
{
for (int i = 0; i < G.iNumNodes; i++)
for (int j = 0; j < G.iNumNodes; j++)
pathMatrix[i][j] = G.adjMatrix[i][j];

for (int i = 0; i < G.iNumNodes; i++)
for (int j = 0; j < G.iNumNodes; j++)
if (pathMatrix[j][i])
for (int k = 0; k < G.iNumNodes; k++)
pathMatrix[j][k] = pathMatrix[j][k] || pathMatrix[i][k];
}


void printGraph( Graph G, FILE *out_file )
{
int i, j;

for( i=0 ; i<G.iNumNodes; i++)
{
fprintf(out_file, "%s\t", G.nodeArray[i].szName);
for( j=0 ; j<G.iNumNodes; j++)
{
fprintf(out_file, "%d ", G.adjMatrix[i][j]);
}
fprintf(out_file, "\n");
}
fprintf(out_file, "\n");
}


void printPathMatrix( Graph G, int **pathMatrix, FILE *out_file )
{
int i, j;

for( i=0 ; i<G.iNumNodes; i++)
{
fprintf(out_file, "%s\t", G.nodeArray[i].szName);
for( j=0 ; j<G.iNumNodes; j++)
{
fprintf(out_file, "%d ", pathMatrix[i][j]);
}
fprintf(out_file, "\n");
}
fprintf(out_file, "\n");
}


void resetVisited( Graph G )
{
int i;

for( i=0 ; i<G.iNumNodes; i++)
{
G.nodeArray[i].visited = FALSE;
}
}
