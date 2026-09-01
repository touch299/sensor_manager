#include "sensor.h"
static SensorData *create_node(void)
{
    SensorData *n = malloc(sizeof(SensorData));
    if(n == NULL)
    {
        fprintf(stderr,"内存分配失败\n");
        exit(1);
    }
    n->next = NULL; 
    printf("  名称: ");
    scanf("%31s", n->name);
    printf("  温度: ");
    scanf("%f", &(*n).temperature);
    printf("  湿度: ");
    scanf("%f", &(*n).humidity);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return n;
}

void add_records(SensorData **records)
{
    SensorData *n = create_node();
    if(*records == NULL)   //  空链表：新节点就是第一个
    {
        *records = n;
        return;
    }
    SensorData *p = *records;
    while(p->next != NULL)  // 走到最后一个节点(next为NULL的那个)
    {
        p = p->next;
    }
    p -> next = n;  //挂在末尾
}

void print_list(const SensorData *records)
{
    for(const SensorData *p = records;p != NULL;p = p->next)
    {
        printf("名称: %s\n",p->name);
        printf("温度: %f\n",p->temperature);
        printf("湿度: %f\n",p->humidity);
    }
}

SensorData *find(SensorData *records,SensorData **prev_out) // 是prev的地址，地址当然不是NULL 
{
    char name[32];
    printf("请输入要查找的名称：");
    scanf("%31s",name);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    SensorData *curr = records;
    SensorData *prev = NULL;

    while (curr != NULL)
    {
        if(strcmp(name,curr->name)==0)
        {
            if(prev_out != NULL)
            {
                *prev_out = prev;
            }
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }
    if(prev_out != NULL)
    {
        *prev_out = NULL;
    }
    return NULL;
}

int delete_node(SensorData **records)
{
    SensorData *prev = NULL;
    SensorData *target = find(*records,&prev);
    if(target == NULL)
    {
        printf("未找到该名称\n");
        return -1;    
    }
    if(prev == NULL)
    {
        *records = target->next;
    }
    else
    {
        prev->next = target->next;
    }
    free(target);
    printf("删除成功\n");
    return 1;
}

// 修改
int update_records(SensorData *records)
{
    SensorData *prev = NULL;
    SensorData *target = find(records,&prev);
    if(target == NULL)
    {
        printf("未找到该名称\n");
        return -1;    
    }
    printf("找到记录：%s\n",target->name);
    printf("请输入新的温度: ");
    scanf("%f", &target->temperature);
    printf("请输入新的湿度: ");
    scanf("%f", &target->humidity); 
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    printf("修改成功\n");
    return 1;
}

// 保存
int save_to_file(const SensorData *records,const char *filename)
{
    FILE *fp = fopen(filename,"w");
    if(fp == NULL)
    {
        return -1;
    }
    for(const SensorData *p = records;p != NULL;p = p->next)
    {
        fprintf(fp, "%s %f %f\n",p->name,p->temperature,p->humidity);     
    }
    fclose(fp);
    return 1;
}

// 加载
int load_from_file(SensorData **records,const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        return -1;
    }
    SensorData *new_head = NULL;    // 最终成为新链表的头节点指针
    SensorData *tail = NULL;        // 始终指向当前链表最后一个节点，用于尾插操作
    char name[NAME_MAX];
    float temp, hum;
    while (fscanf(fp, "%31s %f %f", name, &temp, &hum) == 3)
    {
        SensorData *n = malloc(sizeof(SensorData));
        if(n == NULL)
        {
            fclose(fp);
            free_list(&new_head);
            return -1;
        }
        strcpy(n->name,name);
        n->temperature = temp;
        n->humidity = hum;
        n->next = NULL;
        if(tail == NULL)
        {
            new_head = tail = n;
        }
        else 
        {
            tail->next = n;
            tail = n;
        }
    }
    fclose(fp);
    if(*records != NULL)
    {
        free_list(records);
    }
    *records = new_head;
    return 1;
}
void free_list(SensorData **records)
{
    SensorData *p = *records;
    while (p != NULL)
    {
        SensorData *next = p->next;
        free(p);
        p = next;
    }
    *records = NULL;
}