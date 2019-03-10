typedef struct QNode{
    int data;
    struct QNode *next;
}QNode;

typedef struct Queue{
    struct QNode* first;
    struct QNode* last;
}Queue;

void PushQueue(Queue *queue, int data){
    QNode *p = NULL;
    p = (QNode*)malloc(sizeof(QNode));
    p->data = data;
    if(queue->first == NULL){
        queue->first = p;
        queue->last = p;
        p->next = NULL;
    }
    else{
        p->next = NULL;
        queue->last->next = p;
        queue->last = p;
    }
}

int PopQueue(Queue *queue){
    QNode *p = NULL;
    int data;
    if(queue->first == NULL){
        return -1;
    }
    p = queue->first;
    data = p->data;
    if(queue->first->next == NULL){
        queue->first = NULL;
        queue->last = NULL;
    }
    else{
        queue->first = p->next;
    }
    free(p);
    return data;
}

static int NeighborDirection[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};

void SearchNeighbor(unsigned char *bitmap, int width, int height, int *labelmap, 
                    int labelIndex, int pixelIndex, Queue *queue){
    int searchIndex, i, length;
    labelmap[pixelIndex] = labelIndex;
    length = width * height;
    for(i = 0;i < 8;i++){
        searchIndex = pixelIndex + NeighborDirection[i][0] * width + NeighborDirection[i][1];
        if(searchIndex > 0 && searchIndex < length && 
            bitmap[searchIndex] == 255 && labelmap[searchIndex] == 0){
            labelmap[searchIndex] = labelIndex;
            PushQueue(queue, searchIndex);
        }
    }
}

int ConnectedComponentLabeling(unsigned char *bitmap, int width, int height, int *labelmap){
    int cx, cy, index, popIndex, labelIndex = 0;
    Queue *queue = NULL;
    queue = (Queue*)malloc(sizeof(Queue));
    queue->first = NULL;
        queue->last = NULL;
    memset(labelmap, 0, width * height);
    for(cy = 1; cy < height - 1; cy++){
        for(cx = 1; cx < width - 1; cx++){
            index = cy * width + cx;
            if(bitmap[index] == 255 && labelmap[index] == 0){
                labelIndex++;
                SearchNeighbor(bitmap, width, height, labelmap, labelIndex, index, queue);

                popIndex = PopQueue(queue);
                while(popIndex > -1){
                SearchNeighbor(bitmap, width, height, labelmap, labelIndex, popIndex, queue);
                    popIndex = PopQueue(queue);
                }
            }
        }
    }
    free(queue);
    return labelIndex;
}
