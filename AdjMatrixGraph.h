#ifndef ADJMETRIXGRAPH_H_INCLUDED
#define ADJMETRIXGRAPH_H_INCLUDED

#include "MyDefinition.h"
#include <limits.h> //INT_MAX
#include <string.h>

// 功　能：实现邻接矩阵图（有向网）
// 设计者：李钰林
// 版本号：2018-11-10

#define MAXSIZE 100//最大个数，迪算法用
typedef int EdgeType;   //权值类型

typedef struct{
    ElemType* vexs;     //顶点表，动态分配
    EdgeType** arc;     //邻接矩阵（二维数组），动态分配
    int numVertexes;    //顶点数
    int numEdges;       //边数
}AdjMatrixGraph;

//动态创建图
Status AdjMatrixGraphCreate(AdjMatrixGraph** graph);
//利用数组创建图，方便测试
Status AdjMatrixGraphCreateByNums(AdjMatrixGraph** graph, const ElemType* vexs, const EdgeType* arc, int size, int EdgeSize);
//销毁图
Status AdjMatrixGraphDestroy(AdjMatrixGraph* graph);
//复制图
Status AdjMatrixGraphCopy(AdjMatrixGraph** to, const AdjMatrixGraph* from);
//深度优先遍历
Status AdjMatrixGraphDFS(const AdjMatrixGraph* graph);
//深度优先遍历 子函数 ， visit为是否遍历的标志数组， idx为当前迭代顶点下标
Status _AdjMatrixGraphDFS(const AdjMatrixGraph* graph, int* visit, int idx);
//广度优先遍历
Status AdjMatrixGraphHFS(const AdjMatrixGraph* graph);

//迪杰斯特拉算法，求某个源点（下标）到其余各点的最短路径并打印出来
Status AdjMatrixGraphDijkstraPrint(const AdjMatrixGraph* graph, int idx);
//弗洛伊德算法，求每一对顶点之间的最短路径
Status AdjMatrixGraphFloydPrint(const AdjMatrixGraph* graph);

//无向图的最小生成树：普里姆算法
Status AdjMatrixGraphPrimPrint(const AdjMatrixGraph* graph);
//无向图的最小生成树：克鲁斯卡尔算法
Status AdjMatrixGraphKruskalPrint(const AdjMatrixGraph* graph);

#endif // ADJMETRIXGRAPH_H_INCLUDED
