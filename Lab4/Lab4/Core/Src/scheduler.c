/*
 * scheduler.c
 *
 *  Created on: Nov 23, 2023
 *      Author: M S I
 */

#include "scheduler.h"
#include "Tasks.h"
#include "main.h"

void SCH_Init(void){
	SCH_TASKS_LIST.NumOfTask = 0;
	for(int index = 0; index < SCH_MAX_TASKS; index++){
		SCH_TASKS_LIST.TASK_QUEUE[index].Delay = 0;
		SCH_TASKS_LIST.TASK_QUEUE[index].Period = 0;
		SCH_TASKS_LIST.TASK_QUEUE[index].RunMe = 0;
		SCH_TASKS_LIST.TASK_QUEUE[index].pTask = 0;
	}
}

void Insert_to_List(sTasks task){
	if(SCH_TASKS_LIST.NumOfTask == 0){
		SCH_TASKS_LIST.TASK_QUEUE[0] = task;
		SCH_TASKS_LIST.NumOfTask += 1;
		return;
	}
	else{
		int loc = 0;
		int bef = SCH_TASKS_LIST.TASK_QUEUE[0].Delay;
		int sum = SCH_TASKS_LIST.TASK_QUEUE[0].Delay;
		while(loc < SCH_TASKS_LIST.NumOfTask && task.Delay > sum){
			loc++;
			if(loc < SCH_TASKS_LIST.NumOfTask){
				bef = sum;
				sum += SCH_TASKS_LIST.TASK_QUEUE[loc].Delay;
			}
		}
		if(loc == SCH_TASKS_LIST.NumOfTask){
			task.Delay -= sum;
			SCH_TASKS_LIST.TASK_QUEUE[loc] = task;
			SCH_TASKS_LIST.NumOfTask += 1;
			return;
		}
		else{
			for(int i = SCH_TASKS_LIST.NumOfTask; i > loc; i--){
				SCH_TASKS_LIST.TASK_QUEUE[i] = SCH_TASKS_LIST.TASK_QUEUE[i - 1];
			}
			if(loc == 0){
				SCH_TASKS_LIST.TASK_QUEUE[loc] = task;
				sum = 0;
				bef = task.Delay;
			}
			else{
				task.Delay -= bef;
				sum = bef;
				bef += task.Delay;
				SCH_TASKS_LIST.TASK_QUEUE[loc] = task;
			}
			sum += SCH_TASKS_LIST.TASK_QUEUE[loc + 1].Delay;
			SCH_TASKS_LIST.TASK_QUEUE[loc + 1].Delay = sum - bef;
			SCH_TASKS_LIST.NumOfTask += 1;
		}
	}
}

void SCH_Add_Task (void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	if(SCH_TASKS_LIST.NumOfTask >= SCH_MAX_TASKS){
		return;
	}
	sTasks temp;
	temp.pTask = pFunction;
	temp.Delay = DELAY;
	temp.Period = PERIOD;
	temp.RunMe = 0;
	Insert_to_List(temp);
}

void SCH_Update(void){
	if(!SCH_TASKS_LIST.TASK_QUEUE[0].pTask){
		return;
	}
	else{
		if(SCH_TASKS_LIST.TASK_QUEUE[0].Delay == 0){
			SCH_TASKS_LIST.TASK_QUEUE[0].RunMe += 1;
			if(SCH_TASKS_LIST.TASK_QUEUE[0].Period){
				SCH_TASKS_LIST.TASK_QUEUE[0].Delay = SCH_TASKS_LIST.TASK_QUEUE[0].Period;
			}
		}
		else SCH_TASKS_LIST.TASK_QUEUE[0].Delay -= 1;
	}
}

void SCH_Delete_Task(void){
	int index = 0;
	int add_back_flag = 0;
	sTasks temp;
	if (SCH_TASKS_LIST.TASK_QUEUE[index].Period){
		add_back_flag = 1;
		temp = SCH_TASKS_LIST.TASK_QUEUE[index];
	}
	for (;index < SCH_TASKS_LIST.NumOfTask - 1; index++){
		SCH_TASKS_LIST.TASK_QUEUE[index] = SCH_TASKS_LIST.TASK_QUEUE[index + 1];
	}
	SCH_TASKS_LIST.TASK_QUEUE[index].pTask = 0x0000;
	SCH_TASKS_LIST.TASK_QUEUE[index].Delay = 0;
	SCH_TASKS_LIST.TASK_QUEUE[index].Period = 0;
	SCH_TASKS_LIST.TASK_QUEUE[index].RunMe = 0;
	SCH_TASKS_LIST.NumOfTask -= 1;
	if(add_back_flag == 1){
		Insert_to_List(temp);
	}
}

void SCH_Dispatch_Tasks(void){
	for(int index = 0; index < SCH_MAX_TASKS; index++){
		if(SCH_TASKS_LIST.TASK_QUEUE[index].RunMe > 0){
			(*SCH_TASKS_LIST.TASK_QUEUE[index].pTask)();
			SCH_TASKS_LIST.TASK_QUEUE[index].RunMe -= 1;
			SCH_Delete_Task();
		}
	}
}
