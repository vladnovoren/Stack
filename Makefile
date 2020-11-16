release:
	gcc stack.c funcs_pub.c funcs_prv.c -o stack.out
debug:
	gcc test.c funcs_pub.c funcs_prv.c assertion.c -o stack_d.out -DDEBUG -g