#ifndef __STU_SCORE__H
#define __STU_SCORE__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_STU_NUMBER 100

typedef struct stu
{
	unsigned int m_serial_number;
	char m_name[32];
	int m_score;

}stu;

int stu_init(stu *p_stu, unsigned int n_num);
int stu_select_5_score_input(stu *p_stu, unsigned int n_num);
int stu_write_file(stu *p_stu, unsigned int n_num, char *fname);
int stu_read_file(stu **p_stu, unsigned int *n_num, char *fname);
int stu_score_write_file(stu **p_stu, unsigned int n_num, char *fname);

#endif
