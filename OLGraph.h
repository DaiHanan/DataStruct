#ifndef OLGRAPH_H_INCLUDED
#define OLGRAPH_H_INCLUDED

#include "MyDefinition.h"
#include <limits.h> //INT_MAX

// 功　能：实现十字链表图（有向网）
// 设计者：李钰林
// 版本号：2018-11-17

#define MAXSIZE 100                     //最大顶点数
typedef int EdgeType;                   //权值类型

typedef struct _OLEdgeNode{             //边表结点
    int hvex, tvex;                     //该弧的头尾顶点的下标
    EdgeType weight;                    //顶点数
    struct _OLEdgeNode* hlink, * tlink; //分别指向和该弧头/尾相同的弧的指针
}OLEdgeNode;

typedef struct _OLVertexNode{           //顶点表结点
    ElemType data;                      //顶点信息
    OLEdgeNode* firstin, * firstout;    //分别指向该顶点第一条入/出弧
}OLVertexNode;

typedef struct{
    OLVertexNode list[MAXSIZE];         //顶点表
    int numVertexes;                    //图的顶点数
    int numEdges;                       //图的边数
}OLGraph;

//动态创建图
Status OLGraphCreate(OLGraph** graph);
//利用（邻接）数组创建图，方便测试
Status OLGraphCreateByNums(OLGraph** graph, const ElemType* vexs, const EdgeType* arc, int size, int EdgeSize);
//销毁图
Status OLGraphDestroy(OLGraph* graph);
//复制图
Status OLGraphCopy(OLGraph** to, const OLGraph* from);
//深度优先遍历
Status OLGraphDFS(const OLGraph* graph);
//深度优先遍历 子函数 ， visit为是否遍历的标志数组， idx为当前迭代顶点下标
Status _OLGraphDFS(const OLGraph* graph, int* visit, int idx);
//广度优先遍历
Status OLGraphHFS(const OLGraph* graph);

#endif // OLGRAPH_H_INCLUDED
