#ifndef INVERSEADJLISTGRAPH_H_INCLUDED
#define INVERSEADJLISTGRAPH_H_INCLUDED

#include "MyDefinition.h"
#include <limits.h> //INT_MAX

// 功　能：实现逆邻接表图（有向网）
// 设计者：李钰林
// 版本号：2018-11-17

#define MAXSIZE 100                         //最大顶点数
typedef int EdgeType;                       //权值类型

typedef struct _inverseAdjListEdgeNode{     //边表结点
    int adjvex;                             //存储该顶点对应的下标
    EdgeType weight;                        //顶点数
    struct _inverseAdjListEdgeNode* next;   //边数
}InverseAdjListEdgeNode;

typedef struct _inverseAdjListVertexNode{   //顶点表结点
    ElemType data;                          //顶点信息
    InverseAdjListEdgeNode* first;          //边表的头指针
}InverseAdjListVertexNode;

typedef struct{
    InverseAdjListVertexNode list[MAXSIZE]; //顶点表
    int numVertexes;                        //图的顶点数
    int numEdges;                           //图的边数
}InverseAdjListGraph;

//动态创建图
Status InverseAdjListGraphCreate(InverseAdjListGraph** graph);
//利用数组创建图，方便测试
Status InverseAdjListGraphCreateByNums(InverseAdjListGraph** graph, const ElemType* vexs, const EdgeType* arc, int size, int EdgeSize);
//销毁图
Status InverseAdjListGraphDestroy(InverseAdjListGraph* graph);
//复制图
Status InverseAdjListGraphCopy(InverseAdjListGraph** to, const InverseAdjListGraph* from);
//深度优先遍历
Status InverseAdjListGraphDFS(const InverseAdjListGraph* graph);
//深度优先遍历 子函数 ， visit为是否遍历的标志数组， idx为当前迭代顶点下标
Status _InverseAdjListGraphDFS(const InverseAdjListGraph* graph, int* visit, int idx);
//广度优先遍历
Status InverseAdjListGraphHFS(const InverseAdjListGraph* graph);

#endif // INVERSEADJLISTGRAPH_H_INCLUDED
