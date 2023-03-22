#include "AdjMatrixGraph.h"

//动态创建图
Status AdjMatrixGraphCreate(AdjMatrixGraph** graph){
    if(!graph)
        return ERROR;
    AdjMatrixGraphDestroy(*graph);//如果有先释放原先空间
    *graph = (AdjMatrixGraph*)malloc(sizeof(AdjMatrixGraph));
    if(!*graph)//申请内存失败
        return OVERFLOW;
    printf("请输入顶点个数和边数（空格隔开）：\n");
    int size;
    scanf("%d %d", &size, &(*graph)->numEdges);
    (*graph)->numVertexes = size;

    //分别为顶点数组和邻接矩阵二维数组动态申请内存
    (*graph)->vexs = (ElemType*)malloc(sizeof(ElemType) * size);
    if(!(*graph)->vexs)
        return OVERFLOW;
   (*graph)->arc = (EdgeType**)malloc(sizeof(ElemType*) * size);
    if(!(*graph)->arc)
        return OVERFLOW;
    for(int i = 0; i < size; i++){
        (*graph)->arc[i] = (EdgeType*)malloc(sizeof(ElemType) * size);
        if(!(*graph)->arc[i])
            return OVERFLOW;
    }
    //初始化
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++)
            (*graph)->arc[i][j] = INT_MAX;//初始为不可能的权值
    }
    printf("请输入顶点的值（空格隔开）：\n");
    for(int i = 0; i < size; i++){
        scanf("%d", &(*graph)->vexs[i]);

    }
    printf("\n请输入边（vi，vj）的 下标i、j和该边的权值 （空格隔开）：\n");
    int from, to;
    for(int i = 0; i < (*graph)->numEdges; i++){
        scanf("%d %d", &from, &to);
        scanf("%d", &(*graph)->arc[from][to]);
    }
    return OK;
}
//利用数组创建图，方便测试
Status AdjMatrixGraphCreateByNums(AdjMatrixGraph** graph, const ElemType* vexs, const EdgeType* arc, int size, int EdgeSize){
    if(!graph)
        return ERROR;
    AdjMatrixGraphDestroy(*graph);//如果有先释放原先空间
    *graph = (AdjMatrixGraph*)malloc(sizeof(AdjMatrixGraph));
    if(!*graph)//申请内存失败
        return OVERFLOW;

    (*graph)->numVertexes = size;
    (*graph)->numEdges = EdgeSize;

    //分别为顶点数组和邻接矩阵二维数组动态申请内存
    (*graph)->vexs = (ElemType*)malloc(sizeof(ElemType) * size);
    if(!(*graph)->vexs)
        return OVERFLOW;
    (*graph)->arc = (EdgeType**)malloc(sizeof(ElemType*) * size);
    if(!(*graph)->arc)
        return OVERFLOW;
    for(int i = 0; i < size; i++){
        (*graph)->arc[i] = (EdgeType*)malloc(sizeof(ElemType) * size);
        if(!(*graph)->arc[i])
            return OVERFLOW;
    }
    //初始化
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            (*graph)->arc[i][j] = *(arc + i * size + j);
        }
    }
    for(int i = 0; i < size; i++){
        (*graph)->vexs[i] = vexs[i];
    }
    return OK;
}
//销毁图
Status AdjMatrixGraphDestroy(AdjMatrixGraph* graph){
    if(!graph)
        return ERROR;
    int size = graph->numVertexes;
    for(int i = 0; i < size; i++)
        if(graph->arc[i])
            free(graph->arc[i]);
    if(graph->arc)
        free(graph->arc);
    if(graph->vexs)
        free(graph->vexs);
    return OK;
}
//复制图
/*
    不知道具体原因传递二维数组会出错，所以没有调用其他方法
*/
Status AdjMatrixGraphCopy(AdjMatrixGraph** to, const AdjMatrixGraph* from){
    if(!from || !to)
        return ERROR;
    AdjMatrixGraphDestroy(*to);

    *to = (AdjMatrixGraph*)malloc(sizeof(AdjMatrixGraph));
    if(!*to)//申请内存失败
        return OVERFLOW;

    int size = from->numVertexes;
    EdgeType** arc = from->arc;
    ElemType* vexs = from->vexs;

    (*to)->numVertexes = size;
    (*to)->numEdges = from->numEdges;

    //分别为顶点数组和邻接矩阵二维数组动态申请内存
    (*to)->vexs = (ElemType*)malloc(sizeof(ElemType) * size);
    if(!(*to)->vexs)
        return OVERFLOW;
    (*to)->arc = (EdgeType**)malloc(sizeof(ElemType*) * size);
    if(!(*to)->arc)
        return OVERFLOW;
    for(int i = 0; i < size; i++){
        (*to)->arc[i] = (EdgeType*)malloc(sizeof(ElemType) * size);
        if(!(*to)->arc[i])
            return OVERFLOW;
    }
    //初始化
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            (*to)->arc[i][j] = arc[i][j];
        }
    }
    for(int i = 0; i < size; i++){
        (*to)->vexs[i] = vexs[i];
    }

    return OK;
}
//深度优先遍历
Status AdjMatrixGraphDFS(const AdjMatrixGraph* graph){
    if(!graph)
        return ERROR;
    //visit为是否遍历的标志数组
    int* visit = (int*)malloc(sizeof(int) * graph->numVertexes);
    if(!visit)
        return OVERFLOW;
    for(int i = 0; i < graph->numVertexes; i++)
        visit[i] = 0;//初始为没有访问——0

    for(int i = 0; i < graph->numVertexes; i++){
        if(!visit[i])
            _AdjMatrixGraphDFS(graph, visit, i);
    }
    free(visit);
    return OK;
}
//深度优先遍历 子函数 ， visit为是否遍历的标志数组， idx为当前迭代顶点下标
Status _AdjMatrixGraphDFS(const AdjMatrixGraph* graph, int* visit, int idx){
    visit[idx] = 1;//设置为已读
    printf("%d ", graph->vexs[idx]);

    for(int j = 0; j < graph->numVertexes; j++){
        if(graph->arc[idx][j] != INT_MAX && !visit[j]){//该边存在且对应顶点没有读过
            _AdjMatrixGraphDFS(graph, visit, j);//递归
        }
    }
}
//广度优先遍历
Status AdjMatrixGraphHFS(const AdjMatrixGraph* graph){
    if(!graph)
        return ERROR;
    //visit为是否遍历的标志数组
    int* visit = (int*)malloc(sizeof(int) * graph->numVertexes);
    if(!visit)
        return OVERFLOW;
    for(int i = 0; i < graph->numVertexes; i++)
        visit[i] = 0;//初始为没有访问——0

    //创建临时队列，元素个数最多有顶点个数个
    int* queue = (ElemType*)malloc(sizeof(ElemType) * graph->numVertexes);
    if(!queue)
        return OVERFLOW;
    int f = 0, t = 0;//队首队尾

    for(int i = 0; i < graph->numVertexes; i++){
        if(!visit[i]){
            f = t = 0;//队伍初始化
            visit[i] = 1;
            printf("%d ", graph->vexs[i]);//打印当前顶点
            queue[t++] = i;//入队
            while(f != t){//当队列有元素时
                int idx = queue[f++];//出队
                for(int j = 0; j < graph->numVertexes; j++){//找没有打印过的邻接顶点
                    if(graph->arc[idx][j] != INT_MAX && !visit[j]){
                        visit[j] = 1;
                        printf("%d ", graph->vexs[j]);
                        queue[t++] = j;//入队
                    }
                }
            }
        }
    }
    free(visit);
    return OK;
}

//迪杰斯特拉算法，求某个源点（下标）到其余各点的最短路径并打印出来
Status AdjMatrixGraphDijkstraPrint(const AdjMatrixGraph* graph, int idx){
    int size = graph->numVertexes;
    if(!graph || idx >= size)
        return ERROR;

    char path[MAXSIZE][MAXSIZE]= {0};//路径字符串数组
    int visit[MAXSIZE] = {0};//是否遍历数组
    EdgeType value[MAXSIZE] = {0};//最短路径长度

    //初始化信息
    for(int i = 0; i < size; i++){
        value[i] = graph->arc[idx][i];
        sprintf(path[i], "v%d-->v%d", graph->vexs[idx], graph->vexs[i]);
    }

    //设置起点信息
    visit[idx] = 1;
    value[idx] = 0;

    //while循环找所有最小路径
    int count = 1;//已完成查找的顶点数
    while(count < size){
        EdgeType min = INT_MAX;//未遍历部分的最小路径的值;
        int temp = 0;//未遍历部分的最小路径的下标
        //找未遍历的最小路径的点
        for(int i = 0; i < size; i++){
            if(!visit[i] && min > value[i]){
                min = value[i];
                temp = i;
            }
        }
        //设为已读
        visit[temp] = 1;
        //计时器更新
        count++;

        for(int i = 0; i < size; i++){
            if(!visit[i] && graph->arc[temp][i] != INT_MAX &&
               value[temp] < value[i] - graph->arc[temp][i]){
                value[i] = value[temp] + graph->arc[temp][i];
                sprintf(path[i], "%s-->v%d", path[temp], graph->vexs[i]);
            }
        }
    }

    //打印
    printf("迪杰斯特拉算法\n以v%d为起点的图的最小路径为：\n", graph->vexs[idx]);
    for(int i = 0; i < size; i++){
        if(value[i] != INT_MAX)
            printf("%s = %d\n", path[i], value[i]);
        else
            printf("%s = 无路径", path[i]);
    }
    return OK;
}
//弗洛伊德算法，求每一对顶点之间的最短路径
Status AdjMatrixGraphFloydPrint(const AdjMatrixGraph* graph){
    if(!graph)
        return ERROR;
    EdgeType paths[MAXSIZE][MAXSIZE] = {0};

    //初始化路径二维数组
    int size = graph->numVertexes;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            paths[i][j] = graph->arc[i][j];
        }
    }
    //开找
    for(int k = 0; k < size; k++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++)
                if(paths[i][j] - paths[k][j] > paths[i][k] )
                    paths[i][j] = paths[i][k] + paths[k][j];
        }
    }
    //打印
    printf("Floyd算法排序后的最小路径矩阵为：\n");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(paths[i][j] == INT_MAX)
                printf("%2c ", 'm');
            else
                printf("%2d ", paths[i][j]);
        }
        printf("\n");
    }
}

//无向图的最小生成树：普里姆算法
Status AdjMatrixGraphPrimPrint(const AdjMatrixGraph* graph){
    typedef struct{
        int adjVex; //该顶点下一个顶点的下标
        int cost;   //权值
    }node;

    node closedge[MAXSIZE] = {0};
    //初始化
    int size = graph->numVertexes;
    for(int i = 1; i < size; i++){
            closedge[i].adjVex = 0;
            closedge[i].cost = graph->arc[0][i];
    }

    //开找
    for(int i = 1; i < size; i++){
        //求出下一条权值最小且没入树的边
        int temp = 0;
        int minCost = INT_MAX;
        for(int j = 0; j < size; j++){
            if(closedge[j].cost != 0 && closedge[j].cost < minCost){
                minCost = closedge[j].cost;
                temp = j;
            }
        }
        //打印
        printf("v%d-->v%d\n", closedge[temp].adjVex, temp);
        //更新
        for(int k = 0; k < size; k++){
            if(graph->arc[temp][k] < closedge[k].cost){
                closedge[k].adjVex = temp;
                closedge[k].cost = graph->arc[temp][k];
            }
        }
    }
}

//无向图的最小生成树：克鲁斯卡尔算法
Status AdjMatrixGraphKruskalPrint(const AdjMatrixGraph* graph){
    typedef struct{
        int begin;
        int end;
        EdgeType weight;
    }node;

    node edges[MAXSIZE] = {0};//边信息数组
    int parent[MAXSIZE] = {0};//双亲下标数组
    int size = graph->numVertexes, count = 0;
    //初始化双亲下标数组信息
    for(int i = 0; i < size; i++){
        parent[i] = 0;
    }
    //初始化边信息结点
    for(int i = 0; i < size - 1; i++){
        for(int j = i + 1; j < size; j++){
            if(graph->arc[i][j] != INT_MAX){
                edges[count].begin = i;
                edges[count].end = j;
                edges[count++].weight = graph->arc[i][j];
            }
        }
    }

    //边排序（升序）
    for(int i = 0; i < count - 1; i++){
        for(int j = 0; j < count - 1 - i; j++){
            if(edges[j].weight > edges[j + 1].weight){
                node temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
    //自定义函数
    int find(int idx){
        while(parent[idx] > 0)
            idx = parent[idx];
        return idx;
    }
    //开找
    for(int i = 0; i < count; i++){
        int n = find(edges[i].begin);
        int m = find(edges[i].end);
        if(n != m){
            parent[n] = m;
            printf("v%d-->v%d(%d)\n", edges[i].begin, edges[i].end, edges[i].weight);
        }
    }
}







