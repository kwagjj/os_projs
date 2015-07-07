#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>

int print_children(struct task_struct *parent){

	printk("%10d%20s%10li\n",parent->pid,parent->comm,parent->state);	// first print out info of parent

	struct task_struct *task;
	struct list_head *list;
	list_for_each(list,&(parent->children)){	// if there is no children, then it won't go any further
		task=list_entry(list,struct task_struct,sibling);	// returns pointer of struct_task
		print_children(task);

	}

	return 0;
}

int start(void){


	printk("starting module\n");
	printk("pid\ttask_name\tstate\n");



	// printk("%10d%20s%10li\n",init_task.pid,init_task.comm,init_task.state);

	print_children(&init_task);
	return 0;
}


void ending(void){
	printk("closing module\n");
}

module_init(start);
module_exit(ending);


