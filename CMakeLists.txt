cmake_minimum_required(VERSION 3.15)
project(dataStruct C)

set(CMAKE_C_STANDARD 99)

add_executable(dataStruct main.c
        AdjListGraph.c
        AdjMatrixGraph.c
        AdjMultilistGraph.c
        Array.c
        ChildTree.c
        CSTree.c
        DoublyLinkedList.c
        DynamicStr.c
        HashTable.c
        HuffManBTree.c
        InverseAdjListGraph.c
        LinkedBTree.c
        LinkedGList.c
        LinkedList.c
        LinkedQueue.c
        LinkedStack.c
        LinkedStr.c
        LoopLinkedList.c
        OLGraph.c
        OLSMatrix.c
        ParentTree.c
        RLSMatrix.c
        Search.c
        SeqBTree.c
        SeqList.c
        SeqQueue.c
        SeqStack.c
        Sort.c
        StaticStr.c
        SubGList.c
        Test.c
        ThreadBTree.c
        TLinkedBTree.c
        TSMatrix.c)