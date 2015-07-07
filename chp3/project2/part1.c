#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/init_task.h>

int minit(void){
	struct task_struct* task;
	printk("pid\ttask_name\tstate\n");
	for_each_process(task){
		printk("%5d\t%s\t%li\n",task->pid,task->comm,task->state);
	}

	return 0;
}

void mexit(void){
	printk("closing module\n");
}

module_init(minit);
module_exit(mexit);
