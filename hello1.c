// SPDX-License-Identifier: GPL-2.0
/*
 * Lab 5: hello1 exports print_hello() and keeps the timing of every call.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

#include "hello1.h"

MODULE_AUTHOR("Olha Yakubovska <olasha228@gmail.com>");
MODULE_DESCRIPTION("Hello, world: print_hello() with timing of each call");
MODULE_LICENSE("GPL");

struct hello_event {
	struct list_head node;
	ktime_t time_before;
	ktime_t time_after;
};

static LIST_HEAD(hello_list);

void print_hello(void)
{
	struct hello_event *ev;

	ev = kmalloc(sizeof(*ev), GFP_KERNEL);
	if (!ev)
		return;

	ev->time_before = ktime_get();
	pr_info("Hello, world!\n");
	ev->time_after = ktime_get();

	list_add_tail(&ev->node, &hello_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("hello1: loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_event *ev, *tmp;
	ktime_t delta;

	list_for_each_entry_safe(ev, tmp, &hello_list, node) {
		delta = ktime_sub(ev->time_after, ev->time_before);
		pr_info("hello1: print took %lld ns\n", ktime_to_ns(delta));
		list_del(&ev->node);
		kfree(ev);
	}

	pr_info("hello1: unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
