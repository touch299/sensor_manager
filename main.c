#include "sensor.h"

void print_menu(void)
{
    printf("\n");
    printf("  传感器数据管理器\n");
    printf("  ================\n");
    printf("  1. 添加传感器数据\n");
    printf("  2. 查看所有数据\n");
    printf("  3. 按名称删除\n");
    printf("  4. 按名称修改\n");
    printf("  5. 保存到文件\n");
    printf("  6. 从文件加载\n");
    printf("  0. 退出\n");
    printf("  ================\n");
    printf("  请选择: ");
}

int main()
{
    SensorData *records = NULL;
    int choice;
    int running = 1;
    while(running)
    {
        print_menu();
        if(scanf("%d", &choice) != 1)
        {
            printf("输入无效，请重试\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        switch(choice){
            case 1:
            {
                add_records(&records);
                break;
            }
            case 2:
            {
                print_list(records);
                break;
            }
            case 3:
            {
                int a = delete_node(&records);
                if(a == -1)
                {
                    printf("删除失败\n");
                }
                else 
                {
                    printf("删除成功\n");
                }
                break;
            }
            case 4:
            {
                int a = update_records(records);
                if(a == -1)
                {
                    printf("修改失败\n");
                }
                else 
                {
                    printf("修改成功\n");
                }
                break;
            }
            case 5:
            {
                int a = save_to_file(records,"data.txt");
                if(a == -1)
                {
                    printf("保存错误\n");
                    break;
                }
                printf("保存成功\n");
                break;
            }
            case 6:
            {
                int a = load_from_file(&records,"data.txt");
                if(a == -1)
                {
                    printf("加载错误\n");
                    break;
                }
                printf("加载成功\n");
                break;
            }
            case 0:
                running = 0;
                free_list(&records);
                break;
            default:
                printf("无效选项\n");        
        }
    }
    return 0;
}