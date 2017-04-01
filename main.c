#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "stu_score.h"



void Usage(char *p_fname)
{
	puts("Usage:");
	printf("%s [filename]\n", p_fname);
	puts("if the filename param is empty,then it will create a new operation,else continue with the filename record");
}

void operation_help()
{
	puts("input: 1 <-> 继续随机抽取学生演讲");
	puts("       2 <-> 停止本次活动");
}

int main(int argc, char *argv[])
{
	unsigned int  n_stu_num = 0;
	int i = 0;
	stu *p_stu_header = NULL;
	unsigned int operation_code = -1;
	if(argc == 2 && strcmp(argv[1], "-h") == 0)
	{
		Usage(argv[0]);
		exit(0);
	}

	if(argc > 2)
	{
		Usage(argv[0]);
		exit(-1);
	}

	srand((unsigned)time(NULL));//初始化种子
	if(1 == argc)
	{
		printf("请输入学生总人数:");
		scanf("%d", &n_stu_num);
		if(n_stu_num > MAX_STU_NUMBER)
		{
			printf("too many students...\n");
			exit(2);
		}
		p_stu_header = (stu*)malloc(sizeof(stu) * n_stu_num);
		stu_init(p_stu_header, n_stu_num);//初始化
	}
	else
	{
		p_stu_header = (stu*)malloc(sizeof(stu) * MAX_STU_NUMBER); //申请最多的空间保存
		printf("read sava file return code:%d\n", stu_read_file(&p_stu_header, &n_stu_num, argv[1]));
	}

	while(1)
	{
		operation_help();

	  scanf("%d", &operation_code);
		//operation_code = getchar();
		switch (operation_code) {
				case 1:
					if(1 == stu_select_5_score_input(p_stu_header, n_stu_num))
					{
						printf("final_score return code:%d\n", stu_score_write_file(&p_stu_header, n_stu_num, "final_score.txt"));//the filename can be defined the param 
						free(p_stu_header);
						exit(0);
					}
					break;
				case 2:
					printf("save file return code:%d\n", stu_write_file(p_stu_header, n_stu_num, "save.txt"));//the finename too
					free(p_stu_header);
					exit(0);
					break;
				default:
					break;
			}
	}




	return 0;
}
