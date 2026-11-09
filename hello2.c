// SPDX-License-Identifier: GPL-2.0
/*
 * Lab 5: hello2 calls print_hello() from hello1 "count" times.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#include "hello1.h"

MODULE_AUTHOR("Olha Yakubovska <olasha228@gmail.com>");
MODULE_DESCRIPTION("Hello, world: calls print_hello() from hello1");
MODULE_LICENSE("GPL");

static unsigned int count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count,
		 "How many times to call print_hello() (default 1; 0 or 5..10 gives a warning; >10 is rejected)");

static int __init hello2_init(void)
{
	unsigned int i;

	if (count > 10) {
		pr_err("hello2: invalid count=%u (must be <= 10)\n", count);
		return -EINVAL;
	}

	if (count == 0 || (count >= 5 && count <= 10))
		pr_warn("hello2: count=%u is unusual, continuing\n", count);

	for (i = 0; i < count; i++)
		print_hello();

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("hello2: unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
