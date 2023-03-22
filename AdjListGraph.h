#ifndef ADJLISTGRAPH_H_INCLUDED
#define ADJLISTGRAPH_H_INCLUDED

#include "MyDefinition.h"
#include <limits.h> //INT_MAX

// 功　能：实现邻接表图（有向网）
// 设计者：李钰林
// 版本号：2018-11-17

#define MAXSIZE 100                     //最大顶点数
typedef int EdgeType;                   //权值类型

typedef struct _adjListEdgeNode{        //边表结点
    int adjvex;                         //存储该顶点对应的下标
    EdgeType weight;                    //顶点数
    struct _adjListEdgeNode* next;      //边数
}AdjListEdgeNode;

typedef struct _adjListVertexNode{      //顶点表结点
    ElemType data;                      //顶点信息
    AdjListEdgeNode* first;             //边表的头指针
}AdjListVertexNode;

typedef struct{
    AdjListVertexNode list[MAXSIZE];    //顶点表
    int numVertexes;                    //图的顶点数
    int numEdges;                       //图的边数
}AdjListGraph;

//动态创建图
Status AdjListGraphCreate(AdjListGraph** graph);
//利用数组创建图，方便测试
Status AdjListGraphCreateByNums(AdjListGraph** graph, const ElemType* vexs, const EdgeType* arc, int size, int EdgeSize);
//销毁图
Status AdjListGraphDestroy(AdjListGraph* graph);
//复制图
Status AdjListGraphCopy(AdjListGraph** to, const AdjListGraph* from);
//深度优先遍历
Status AdjListGraphDFS(const AdjListGraph* graph);
//深度优先遍历 子函数 ， visit为是否遍历的标志数组， idx为当前迭代顶点下标
Status _AdjListGraphDFS(const AdjListGraph* graph, int* visit, int idx);
//广度优先遍历
Status AdjListGraphHFS(const AdjListGraph* graph);

//有向图的拓扑排序
Status AdjListGraphTopologicalSort(const AdjListGraph* graph);
//有向图的拓扑排序 子函数 求每个顶点的入度
int* _AdjListGraphTopologicalSort(const AdjListGraph* graph);

//有向图的关键路径
Status AdjListGraphCriticalPath(const AdjListGraph* graph);
//有向图的关键路径 子函数 拓扑排序修改版 rStack为拓扑逆向栈，ve为事件最早发生时间
Status _AdjListGraphCriticalPath(const AdjListGraph* graph, int rStack[], EdgeType ve[]);

#endif // ADJLISTGRAPH_H_INCLUDED
