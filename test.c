/*
* Author: Julia Zeng 
*
* Code description: Test Breadth-First Search graph traversal implementations.  
* 
* Note: Any code that was borrowed from the instructors of EC527 (High Performance 
* Computing) of the Boston University's ECE department are indicated as such with 
* comments. Please see README for more references to external resources used. 
* 
*/ 

/* Include libraries */ 
#include "param.h"
#include "benchmark.h"
#include "matrix.h"
#include "bfs_serial.h"
#include "bfs_pthread.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
printf("\n"
"                              _.-'''.                   \n"
"                    _       .\'       \\\n"
"      ,..______  .-/\\`--.../          \\\n"
"      |        '\\| \\_`_-.  `.  _       \\\n"
"     /        _ .\' / /_`\\`\\  \\/ \'.      \\\n"
"    /       /` /  /\\_|_\\/\\ \'._|   \\      :\n"
"  .\'       /  :   \\ _  |  `\\ .\'__ |      | __,\'\\\n"
"  \\        | __\'. |/.`\'----./ /| `\'    .\'\'\'     \'-.\n"
"   :      .`\"\\ `\'\\/ |`\'\'--.\'/`  \\     /          /\n"
"   |     /|   |   \\ |    / |     \\   /          /\n"
"   \'    | \'.__\\\'____\'_ .\'_.\'      | /          |\n"
"  /     \\     ___.-\'`\\`\'-.._      |/          .\'\n"
" \'-.     `--\'` \'.     `.    `\'-._/__..._       |\n"
"    `-.    __    `.     \\_..,____..\'    \\      /\n"
"     / `\'-\'  `---- \\      .--\'\'\'`       |    ,\'.__\n"
"    /               `-...:____          |  .\'/ _. \'\'--.\n"
"  ,\' julia zeng   ,\'`        `\\--\'`.   |\'\'`,-\'-.   ,\'`\n"
".\'   ec527 final .\'            _\\    \\  |,\' \\    _,\'\n"
"\'-._   project  \'--..._   _,-\'  \'.   \'-\'..__.-\'\n"
"    `.                /`-\' /    |\'-._  `\'.___\n"
"      \\         _    /|   |     /.\' .`-.__..\'`\\\n"
"     ,-\'.---\'\'\'`/`'./ `.  |-.  |/  /    _\'-._`|\n"
"    /    -\'\'- ,\'-.     | |   \\  \\      /  \\   ' |\n"
"   .\' .-\'\'\'-,\'\\   \\    `|/   \',.--.   \'  .\'\\.__`|\n"
"   | \'    ,\'   |   \'    \'   ,\'     `\\    \'  \\   \\\n"
"   .     / \\   \'   |       /         /--.    \'. \'.\n"
"   /   .\'  |     _,\'      .\'  \'`\'--,\'.   \\.   \\  |\n"
"   | .\'    \' _.,\'         |  ___ ,\'  \\    |`-._  |\n"
"  /.\'__.,-\'\'\'            .| \'   / \\   |   \'    `-.\n"
" \'--\'                    |    ,\'  |   \'   /      \'|\n"
"                         |  ,\'    \'  _,.-\'\n"
"                        .\' /   _,.--\'\n"
"                        |..--\'\'\n\n\n\n"); 


    /* 
    * Initialize data structures, time structures, and parameters.
    */
    int OPTION;
    struct timespec time_start, time_stop;
    double time_stamp[OPTIONS][NUM_TESTS];
    double wd;
    long int x, n;
    long int alloc_size;

    x = NUM_TESTS-1;
    alloc_size = A*x*x + B*x + C;	/* the graph will have at least alloc_size vertices */

    /* 
    * Warm up processor and get out of power-saving mode
    */
    wd = wakeup_delay();


    /* 
    * Allocate memory to the graph structures. Because the same seed is
    * used for all initializatons, as long as the size argument is the same
    * the same graph will be created with init_graph. 
    */
	struct Graph *G;		// declare Graph G

    /*
    * Serial BFS Benchmarking
    */ 
    OPTION = 0;
    printf("OPTION %d - Serial bfs\n", OPTION);
    for (x = 0; x < NUM_TESTS && (n = A*x*x + B*x + C, n <= alloc_size); x++) {
    	G = init_graph(n);			// initialize Graph and adjacency matrix
		clock_gettime(CLOCK_REALTIME, &time_start);
		bfs_serial(G);	 			// run through serial bfs
		clock_gettime(CLOCK_REALTIME, &time_stop);
		time_stamp[OPTION][x] = interval(time_start, time_stop);
		free_graph(G);				// free Graph 
		printf("iter %ld done\n", x);
    }
    
    /*
    * pthread BFS Benchmarking
    */ 
    OPTION++;
    printf("OPTION %d - pthread bfs\n", OPTION);
    for (x = 0; x < NUM_TESTS && (n = A*x*x + B*x + C, n <= alloc_size); x++) {
    	G = init_graph(n);			// initialize Graph and adjacency matrix
		clock_gettime(CLOCK_REALTIME, &time_start);
		bfs_pthread(G);			// run through pthread bfs
		clock_gettime(CLOCK_REALTIME, &time_stop);
		time_stamp[OPTION][x] = interval(time_start, time_stop);
		printf("iter %ld done\n", x);
    }
   


	/* Display results */
    printf("\n");
    printf("All measurements are in cycles (if CPNS is set correctly in the code)\n");
    printf("row_len,  serial_bfs,  pthread_bfs\n");
    {
	int i, j;
	for (i = 0; i < NUM_TESTS; i++) {
	    printf("%d\t", A*i*i + B*i + C);	// print row length 
	    for (j = 0; j < OPTIONS; j++) {
			//printf("%ld    ", (long int)((double)(CPNS) * 1.0e9 * time_stamp[j][i]));	// print time in cycles
			printf("%f    ", time_stamp[j][i]);	// print time 
	    }
	    printf("\n");
	}
    }

    printf("Wakeup delay calculated %f\n", wd);

    return 0;
} /* end main */












