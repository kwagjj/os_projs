#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/string.h>

static int depth=0;

void shiftstr(char namebuf[30]){
	int j=0;
	for(j=0;j<29;j++){
		namebuf[29-j]=namebuf[29-j-1];
	}
	
}

int print_children(struct task_struct *parent){

	//printk("%10d%20s%10li\n",parent->pid,parent->comm,parent->state);	// first print out info of parent
	printk("%10d",parent->pid);
	char namebuf[30];
	strcpy(namebuf,parent->comm);
	int i=0;
	for(i=0;i<depth;i++){
		shiftstr(namebuf);
		namebuf[0]='-';
	}
	printk("%20s%10li\n",namebuf,parent->state);

	// parent info print finished.
	//
	//
	//
	struct task_struct *task;
	struct list_head *list;
	list_for_each(list,&(parent->children)){	// if there is no children, then it won't go any further
		depth++;
		task=list_entry(list,struct task_struct,sibling);	// returns pointer of struct_task
		print_children(task);
		depth--;

	}

	return 0;
}

int start(void){

	printk("starting module\n");
	printk("%10s%20s%10s\n","pid","task_name","state");



	// printk("%10d%20s%10li\n",init_task.pid,init_task.comm,init_task.state);

	print_children(&init_task);
	return 0;
}


void ending(void){
	printk("closing module\n");
}

module_init(start);
module_exit(ending);


