#include "stu_score.h"


static void bubble_sort(int unsorted[], unsigned int len)
{
  int i = 0, j = 0;
  for (i = 0; i <  len; ++i)
  {
    for (j = 0; j < len - i - 1; j++)
      {
          if (unsorted[j] > unsorted[j+1])
            {
                int temp = unsorted[j];
                unsorted[j] = unsorted[j+1];
                unsorted[j+1] = temp;
            }
      }
  }
}

int stu_init(stu *p_stu, unsigned int n_num)
{
  int i = 0;

  if(p_stu == NULL || n_num == 0)
  {
      return -1;
  }
  for(; i < n_num; ++i)
  {
    printf("请输入编号%i的名字:",i+1);
    scanf("%s", p_stu[i].m_name);
    p_stu[i].m_serial_number = i+1;
    p_stu[i].m_score = -1;  //not be selected
  }
  return 0;
}

static int is_full(stu *p_stu, unsigned int n_num)
{
  int i = 0;

  if(p_stu == NULL || n_num == 0)
  {
      return -1;
  }
  for(; i<n_num; ++i)
  {
    if(p_stu[i].m_score == -1)
    {
      return 0; // false ,has empty
    }
  }
  return 1; //true,full
}
int stu_select_5_score_input(stu *p_stu, unsigned int n_num)
{
  int i = 0;
  int select = 0;
  int score[5] = {-1};
  if(p_stu == NULL || n_num == 0)
  {
      return -1;
  }

  if(is_full(p_stu, n_num) == 1)
  {
    printf("OK\n");
    return 1;
  }
  while(1)
  {
    select = rand() % n_num;
    printf("select:%d\n", select);
    if(p_stu[select].m_score == -1)
    {
      break;
    }
  }
  printf("请5位评委输入第%d号%s同学的成绩(eg:90 91 99 92 93):",p_stu[select].m_serial_number,p_stu[select].m_name);
  scanf("%d %d %d %d %d",&score[0], &score[1], &score[2], &score[3], &score[4]);
  bubble_sort(score, 5);
  p_stu[select].m_score = (score[1]+score[2]+score[3]) / 3;
  printf("第%d号%s同学获得%d分\n", select+1, p_stu[select].m_name, p_stu[select].m_score);
  return 0;
}

int stu_write_file(stu *p_stu, unsigned int n_num, char *fname)
{
  FILE *fp = NULL;
  if(p_stu == NULL || n_num == 0 || fname == NULL)
  {
    return -1;
  }
  fp = fopen(fname, "w");
  if(fp == NULL)
  {
    return -2; //file IO fail
  }
  if(n_num != fwrite(p_stu, sizeof(*p_stu), n_num, fp))
  {
    return -3; //write error
  }
  fclose(fp);
  return 0;
}

int stu_read_file(stu **p_stu, unsigned int *n_num, char *fname)
{
  FILE *fp = NULL;
  if(p_stu == NULL || n_num == 0 || fname == NULL)
  {
    return -1;
  }
  fp = fopen(fname, "r");
  if(NULL == fp)
  {
    return -2;
  }
  if((*n_num = fread(*p_stu, sizeof(**p_stu), MAX_STU_NUMBER, fp)) == 0)
  {
    return -3;
  }
  fclose(fp);
  return 0;
}

static void show_score(stu *p_stu, unsigned int n_num)
{
  int i = 0;
  for(; i< n_num; ++i)
  {
    printf("%d号%s同学成绩为%d分\n", p_stu[i].m_serial_number, \
          p_stu[i].m_name, p_stu[i].m_score);
  }
}
static void bubble_sort_score(stu **p_stu, unsigned int len)
{
  int i = 0, j = 0;
  for (i = 0; i <  len; ++i)
  {
    for (j = 0; j < len - i - 1; j++)
      {
          if ((*p_stu)[j].m_score < (*p_stu)[j+1].m_score)
            {
                stu temp = (*p_stu)[j];
                (*p_stu)[j] = (*p_stu)[j+1];
                (*p_stu)[j+1] = temp;
            }
      }
  }
}

int stu_score_write_file(stu **p_stu, unsigned int n_num, char *fname)
{
  FILE *fp = NULL;
  int i = 0;
  int first = 0, second = 0, third = 0;
  char *str = NULL;
  char buffer[64] = {0};
  int n = 0;
  if(p_stu == NULL || n_num == 0 || fname == NULL)
  {
    return -1;
  }
  fp = fopen(fname, "w");
  if(fp == NULL)
  {
    return -2; //file IO fail
  }
  bubble_sort_score(p_stu, n_num);
  show_score(*p_stu, n_num);
  first = ceil(n_num * 0.1);
  str = "First:\n";
  fwrite(str,sizeof(str), 1, fp);
  for(i = 0; i < first; ++i)
  {
    n = sprintf(buffer, "%d    %s    %d\n", (*p_stu)[i].m_serial_number, \
      (*p_stu)[i].m_name, (*p_stu)[i].m_score);
    fwrite(buffer, n, 1, fp);
    fflush(fp);
    memset(buffer, 0x00, sizeof(buffer));
  }
  second = ceil(n_num * 0.2);
  str = "Second:\n";
  fwrite(str,sizeof(str), 1, fp);
  for(i = first; i<first + second; ++i)
  {
    n = sprintf(buffer, "%d    %s    %d\n", (*p_stu)[i].m_serial_number, \
      (*p_stu)[i].m_name, (*p_stu)[i].m_score);
    fwrite(buffer, n, 1, fp);
    fflush(fp);
    memset(buffer, 0x00, sizeof(buffer));

  }
  third = ceil(n_num * 0.3);
  str = "Third:\n";
  fwrite(str,sizeof(str), 1, fp);
  for(i = second; i < second + third; ++i)
  {
    n = sprintf(buffer, "%d    %s    %d\n", (*p_stu)[i].m_serial_number, \
      (*p_stu)[i].m_name, (*p_stu)[i].m_score);
    fwrite(buffer, n, 1, fp);
    fflush(fp);
    memset(buffer, 0x00, sizeof(buffer));

  }
  fclose(fp);
  return 0;
}
