#ifndef ADJMLIST_H_INCLUDED
#define ADJMLIST_H_INCLUDED

#include "MyDefinition.h"
#include <limits.h> //INT_MAX

// 功　能：实现邻接多重表图（无向网）
// 设计者：李钰林
// 版本号：2018-11-17

#define MAXSIZE 100                             //最大顶点数
typedef int EdgeType;                           //权值类型

typedef struct _adjMultilistEdgeNode{           //边表结点
    int mark;                                   //访问标记
    int ivex, jvex;                             //该弧的头尾顶点的下标
    EdgeType weight;                            //顶点数
    struct _adjMultilistNode* ilink, * jlink;   //分别指向和该弧头/尾相同的弧的指针
}AdjMultilistEdgeNode;

typedef struct _adjMultilistVertexNode{         //顶点表结点
    ElemType data;                              //顶点信息
    AdjMultilistEdgeNode* first;                //分别指向该顶点第一条入/出弧
}AdjMultilistVertexNode;

typedef struct{
    AdjMultilistVertexNode list[MAXSIZE];       //顶点表
    int numVertexes;                            //图的顶点数
    int numEdges;                               //图的边数
}AdjMultilistGraph;

//动态创建图
Status AdjMultilistGraphCreate(AdjMultilistGraph** graph);
//利用（邻接）数组创建图，方便测试
Status AdjMultilistGraphCreateByNums(AdjMultilistGraph** graph, const ElemType* vexs, const EdgeType* arc, int size, int EdgeSize);
//销毁图
Status AdjMultilistGraphDestroy(AdjMultilistGraph* graph);
//复制图
Status AdjMultilistGraphCopy(AdjMultilistGraph** to, AdjMultilistGraph* from);
//深度优先遍历
Status AdjMultilistGraphDFS(AdjMultilistGraph* graph);
//深度优先遍历 子函数 ， visit为是否遍历的标志数组， idx为当前迭代顶点下标
Status _AdjMultilistGraphDFS(AdjMultilistGraph* graph, int* visit, int idx);
//广度优先遍历
Status AdjMultilistGraphHFS(AdjMultilistGraph* graph);

#endif // ADJMLIST_H_INCLUDED
