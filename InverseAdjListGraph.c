#include "InverseAdjListGraph.h"

//动态创建图
Status InverseAdjListGraphCreate(InverseAdjListGraph** graph){
    if(!graph)
        return ERROR;
    InverseAdjListGraphDestroy(*graph);//如果原先有空间，先释放
    *graph = (InverseAdjListGraph*)malloc(sizeof(InverseAdjListGraph));
    if(!*graph)
        return OVERFLOW;//申请内存失败

    printf("请输入顶点个数和边数（空格隔开）：\n");
    int size;
    scanf("%d %d", &size, &(*graph)->numEdges);
    (*graph)->numVertexes = size;

    printf("请输入顶点的值（空格隔开）：\n");
    for(int i = 0; i < size; i++){
        scanf("%d", &(*graph)->list[i].data);
        (*graph)->list[i].first = NULL;//初始化边表的头指针
    }
    //更新边结点，和邻接表不同是行列交换
    printf("\n请输入边（vi，vj）的 下标i、j和该边的权值 （空格隔开）：\n");
    int from, to;
    for(int i = 0; i < (*graph)->numEdges; i++){
        scanf("%d %d", &from, &to);//输入下标
        //创建新的边结点
        InverseAdjListEdgeNode* newEdgeNode =
        (InverseAdjListEdgeNode*)malloc(sizeof(InverseAdjListEdgeNode));
        if(!newEdgeNode)
            return OVERFLOW;
        //边结点中的存储下标
        newEdgeNode->adjvex = from;
        //边结点中的权值
        scanf("%d", &newEdgeNode->weight);
        //连接边结点（头插法）
        newEdgeNode->next = (*graph)->list[to].first;
        (*graph)->list[to].first = newEdgeNode;
    }
    return OK;
}
//利用数组创建图，方便测试
Status InverseAdjListGraphCreateByNums(InverseAdjListGraph** graph, const ElemType* vexs, const EdgeType* arc, int size, int EdgeSize){
    if(!graph)
        return ERROR;
    InverseAdjListGraphDestroy(*graph);//如果原先有空间，先释放
    *graph = (InverseAdjListGraph*)malloc(sizeof(InverseAdjListGraph));
    if(!*graph)
        return OVERFLOW;//申请内存失败
    //更新边数和顶点数
    (*graph)->numEdges = EdgeSize;
    (*graph)->numVertexes = size;
    //更新顶点结点
    for(int i = 0; i < size; i++){
        (*graph)->list[i].data = vexs[i];
        (*graph)->list[i].first = NULL;//初始化边表的头指针
    }
    //更新边结点，和邻接表不同是行列交换
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == j) continue;//没有指向自身的边
            if(*(arc + i * size + j) != INT_MAX){//邻接矩阵中该点有权值时
                //创建新的边结点
                InverseAdjListEdgeNode* newEdgeNode =
                (InverseAdjListEdgeNode*)malloc(sizeof(InverseAdjListEdgeNode));
                if(!newEdgeNode)
                    return OVERFLOW;
                //边结点中的存储下标
                newEdgeNode->adjvex = i;
                //边结点中的权值
                newEdgeNode->weight = *(arc + i * size + j);
                //连接边结点（头插法）
                newEdgeNode->next = (*graph)->list[j].first;
                (*graph)->list[j].first = newEdgeNode;
            }
        }
    }
    return OK;
}
//销毁图
Status InverseAdjListGraphDestroy(InverseAdjListGraph* graph){
    if(!graph)
        return ERROR;
    //临时边结点指针
    InverseAdjListEdgeNode* p, * q;
    for(int i = 0; i < graph->numVertexes; i++){
        p = graph->list[i].first;//每个结点的边表的头指针
        //释放所有边结点
        while(p){
            q = p->next;
            free(p);
            p = q;
        }
    }
    free(graph);//释放图
    return OK;
}
//复制图
Status InverseAdjListGraphCopy(InverseAdjListGraph** to, const InverseAdjListGraph* from){
    if(!from)
        return ERROR;
    InverseAdjListGraphDestroy(*to);//如果原先有空间，先释放
    *to = (InverseAdjListGraph*)malloc(sizeof(InverseAdjListGraph));
    if(!*to)
        return OVERFLOW;//申请内存失败
    //更新边数和顶点数
    (*to)->numEdges = from->numEdges;
    (*to)->numVertexes = from->numVertexes;
    //更新顶点结点
    int size = from->numVertexes;
    for(int i = 0; i < size; i++){
        (*to)->list[i].data = from->list[i].data;
        (*to)->list[i].first = NULL;//初始化边表的头指针
    }
    //更新边结点
    for(int i = 0; i < size; i++){
        InverseAdjListEdgeNode* p = from->list[i].first;
        while(p){
            //创建新的边结点
            InverseAdjListEdgeNode* newEdgeNode =
            (InverseAdjListEdgeNode*)malloc(sizeof(InverseAdjListEdgeNode));
            if(!newEdgeNode)
                return OVERFLOW;
            //边结点中的存储下标
            newEdgeNode->adjvex = p->adjvex;
            //边结点中的权值
            newEdgeNode->weight = p->weight;
            //连接边结点（头插法）
            newEdgeNode->next = (*to)->list[i].first;
            (*to)->list[i].first = newEdgeNode;

            //更新指针p
            p = p->next;
        }
    }
    return OK;
}
//深度优先遍历
Status InverseAdjListGraphDFS(const InverseAdjListGraph* graph){
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
            _InverseAdjListGraphDFS(graph, visit, i);
    }
    free(visit);
    return OK;
}
//深度优先遍历 子函数 ， visit为是否遍历的标志数组， idx为当前迭代顶点下标
Status _InverseAdjListGraphDFS(const InverseAdjListGraph* graph, int* visit, int idx){
    visit[idx] = 1;//设置为已读
    printf("%d ", graph->list[idx].data);

    for(int i = 0; i < graph->numVertexes; i++){
        if(!visit[i]){//找未读顶点
            InverseAdjListEdgeNode* p = graph->list[i].first;
            while(p){
                if(p->adjvex == idx){//找到下标idx顶点所指向的未读顶点
                    _InverseAdjListGraphDFS(graph, visit, i);
                }
                p = p->next;
            }
        }
    }
}
//广度优先遍历
Status InverseAdjListGraphHFS(const InverseAdjListGraph* graph){
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
                //for循环用来找到所有未读的邻接顶点
                for(int j = 0; j < graph->numVertexes; j++){
                    if(j == i) continue;
                    if(!visit[j]){//找未读顶点
                        InverseAdjListEdgeNode* p = graph->list[j].first;
                        while(p){
                            if(p->adjvex == idx){//找到下标idx顶点所指向的未读顶点
                                visit[j] = 1;
                                printf("%d ", graph->list[j].data);//打印当前顶点
                                queue[t++] = j;
                                break;
                            }
                            p = p->next;
                        }
                    }
                }
            }
        }
    }
    free(visit);
    return OK;
}
