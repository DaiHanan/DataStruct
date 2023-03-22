#include "OLGraph.h"

//动态创建图
Status OLGraphCreate(OLGraph** graph){
    if(!graph)
        return ERROR;
    OLGraphDestroy(*graph);//如果原先有空间，先释放
    *graph = (OLGraph*)malloc(sizeof(OLGraph));
    if(!*graph)
        return OVERFLOW;//申请内存失败

    printf("请输入顶点个数和边数（空格隔开）：\n");
    int size;
    scanf("%d %d", &size, &(*graph)->numEdges);
    (*graph)->numVertexes = size;

    printf("请输入顶点的值（空格隔开）：\n");
    for(int i = 0; i < size; i++){
        scanf("%d", &(*graph)->list[i].data);
        (*graph)->list[i].firstout = NULL;//初始化边表的头出指针
        (*graph)->list[i].firstin = NULL;//初始化边表的头入指针
    }
    printf("\n请输入边（vi，vj）的 下标i、j和该边的权值 （空格隔开）：\n");
    int from, to;
    for(int i = 0; i < (*graph)->numEdges; i++){
        scanf("%d %d", &from, &to);//输入下标
        //创建新的边结点
        OLEdgeNode* newEdgeNode = (OLEdgeNode*)malloc(sizeof(OLEdgeNode));
        if(!newEdgeNode)
            return OVERFLOW;
        //边结点中的存储下标
        newEdgeNode->hvex = from;
        newEdgeNode->tvex = to;
        //边结点中的权值
        scanf("%d", &newEdgeNode->weight);
        //连接边结点（头插法）
        //出
        newEdgeNode->hlink = (*graph)->list[from].firstout;
        (*graph)->list[from].firstout = newEdgeNode;
        //入
        newEdgeNode->tlink = (*graph)->list[to].firstin;
        (*graph)->list[to].firstin = newEdgeNode;
    }
    return OK;
}
//利用（邻接）数组创建图，方便测试
Status OLGraphCreateByNums(OLGraph** graph, const ElemType* vexs, const EdgeType* arc, int size, int EdgeSize){
    if(!graph)
        return ERROR;
    OLGraphDestroy(*graph);//如果原先有空间，先释放
    *graph = (OLGraph*)malloc(sizeof(OLGraph));
    if(!*graph)
        return OVERFLOW;//申请内存失败
    //更新边数和顶点数
    (*graph)->numEdges = EdgeSize;
    (*graph)->numVertexes = size;
    //更新顶点结点
    for(int i = 0; i < size; i++){
        (*graph)->list[i].data = vexs[i];
        (*graph)->list[i].firstout = NULL;//初始化边表的头出指针
        (*graph)->list[i].firstin = NULL;//初始化边表的头入指针
    }
    //更新边结点
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == j) continue;//没有指向自身的边
            if(*(arc + i * size + j) != INT_MAX){//邻接矩阵中该点有权值时
                //创建新的边结点
                OLEdgeNode* newEdgeNode = (OLEdgeNode*)malloc(sizeof(OLEdgeNode));
                if(!newEdgeNode)
                    return OVERFLOW;
                //边结点中的存储下标
                newEdgeNode->hvex = i;
                newEdgeNode->tvex = j;
                //边结点中的权值
                newEdgeNode->weight = *(arc + i * size + j);
                //连接边结点（头插法）
                //出
                newEdgeNode->hlink = (*graph)->list[i].firstout;
                (*graph)->list[i].firstout = newEdgeNode;
                //入
                newEdgeNode->tlink = (*graph)->list[j].firstin;
                (*graph)->list[j].firstin = newEdgeNode;
                }
            }
    }
    return OK;
}
//销毁图
Status OLGraphDestroy(OLGraph* graph){
    if(!graph)
        return ERROR;
    OLEdgeNode* p, *q;//临时指针
    for(int i = 0; i < graph->numVertexes; i++){
        //按照出弧指针一直释放
        p = graph->list[i].firstout;
        while(p){
            q = p->hlink;
            free(p);
            p = q;
        }
    }
    free(graph);
    return OK;
}
//复制图
Status OLGraphCopy(OLGraph** to, const OLGraph* from){
    if(!from)
        return ERROR;
    OLGraphDestroy(*to);//如果原先有空间，先释放
    *to = (OLGraph*)malloc(sizeof(OLGraph));
    if(!*to)
        return OVERFLOW;//申请内存失败
    //更新边数和顶点数
    (*to)->numEdges = from->numEdges;
    (*to)->numVertexes = from->numVertexes;
    //更新顶点结点
    int size = from->numVertexes;
    for(int i = 0; i < size; i++){
        (*to)->list[i].data = from->list[i].data;
        (*to)->list[i].firstout = NULL;//初始化边表的头出指针
        (*to)->list[i].firstin = NULL;//初始化边表的头入指针
    }
    //更新边结点
    for(int i = 0; i < size; i++){
        OLEdgeNode* p = from->list[i].firstout;
        while(p){
            //创建新的边结点
            OLEdgeNode* newEdgeNode = (OLEdgeNode*)malloc(sizeof(OLEdgeNode));
            if(!newEdgeNode)
                return OVERFLOW;
            //边结点中的存储下标
            newEdgeNode->hvex = p->hvex;
            newEdgeNode->tvex = p->tvex;
            //边结点中的权值
            newEdgeNode->weight = p->weight;
            //连接边结点（头插法）
            //出
            newEdgeNode->hlink = (*to)->list[p->hvex].firstout;
            (*to)->list[p->hvex].firstout = newEdgeNode;
            //入
            newEdgeNode->tlink = (*to)->list[p->tvex].firstin;
            (*to)->list[p->tvex].firstin = newEdgeNode;

            //更新指针p
            p = p->hlink;
        }
    }
    return OK;
}
//深度优先遍历
Status OLGraphDFS(const OLGraph* graph){
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
            _OLGraphDFS(graph, visit, i);
    }
    free(visit);
    return OK;
}
//深度优先遍历 子函数 ， visit为是否遍历的标志数组， idx为当前迭代顶点下标
Status _OLGraphDFS(const OLGraph* graph, int* visit, int idx){
    visit[idx] = 1;//设置为已读
    printf("%d ", graph->list[idx].data);

    OLEdgeNode* p = graph->list[idx].firstout;
    while(p){
        if(!visit[p->tvex])//该边存在且对应顶点没有读过
            _OLGraphDFS(graph, visit, p->tvex);//递归
        //更新指针p
        p = p->hlink;
    }
}
//广度优先遍历
Status OLGraphHFS(const OLGraph* graph){
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
            printf("%d ", graph->list[i].data);//打印当前顶点
            queue[t++] = i;//入队
            while(f != t){//当队列有元素时
                int idx = queue[f++];//出队
                OLEdgeNode* p = graph->list[idx].firstout;
                while(p){
                    if(!visit[p->tvex]){
                        visit[p->tvex] = 1;//设置已读
                        printf("%d ", graph->list[p->tvex].data);//打印当前顶点
                        queue[t++] = p->tvex;//入队
                    }
                    p = p->hlink;
                }
            }
        }
    }
    free(visit);
    return OK;
}
