clox: main.c memory.c chunk.c debug.c value.c vm.c compile.c scanner.c\
		common.h chunk.h memory.h debug.h value.h vm.h compiler.h scanner.h
	gcc -o clox.exe main.c memory.c chunk.c debug.c value.c vm.c compile.c scanner.c\
		 common.h chunk.h memory.h debug.h value.h vm.h compiler.h scanner.h