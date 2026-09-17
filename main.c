#include "sensor.h"

void print_menu(void)
{
    printf("\n");
    printf("  传感器数据管理系统\n");
    printf("  ================\n");
    printf("  1. 添加记录\n");
    printf("  2. 显示所有记录\n");
    printf("  3. 删除记录\n");
    printf("  4. 修改记录\n");
    printf("  5. 保存到文件\n");
    printf("  6. 从文件加载\n");
    printf("  0. 退出\n");
    printf("  ================\n");
    printf("  请输入选项: ");
}

int main()
{
    SensorData *records = NULL;
    int choice;
    int running = 1;
    while (running)
    {
        print_menu();

        int ret = scanf("%d",&choice);
		
		if(ret == EOF)
		{
			printf("\n检测到输入结束，程序退出\n");
			running = 0;
			break;
		}
		if(ret != 1)
		{
			printf("输入无效，请重新输入\n");
			int c;
			while ((c=getchar()) != '\n' && c != EOF);
			continue;
		}
		
		int ch;
        while ((ch = getchar()) != '\n' && ch!=EOF);

        switch (choice)
        {
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
                if (a == -1)
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
                if (a == -1)
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
                int a = save_to_file(records, "data.txt");
                if (a == -1)
                {
                    printf("保存失败\n");
                    break;
                }
                printf("保存成功\n");
                break;
            }
            case 6:
            {
                int a = load_from_file(&records, "data.txt");
                if (a == -1)
                {
                    printf("加载失败\n");
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
                printf("输入错误\n");
        }
    }

    return 0;
}