/*
 * scheduler.h
 *
 *  Created on: Nov 23, 2023
 *      Author: M S I
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#define SCH_MAX_TASKS  40
//#define   TICK   	   10

#include <stdint.h>

typedef struct {
	void ( * pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTasks;

typedef struct {
	sTasks TASK_QUEUE[SCH_MAX_TASKS];
	int NumOfTask;
} TasksList;

TasksList SCH_TASKS_LIST;

void SCH_Init (void);
void SCH_Add_Task (void(*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
void Insert_to_List(sTasks task);
void SCH_Update(void);
void SCH_Delete_Task(void);
void SCH_Dispatch_Tasks(void);
#endif /* INC_SCHEDULER_H_ */
