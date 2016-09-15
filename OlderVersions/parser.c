// Usage: ./parser design_file fault_file
// fixed sizes of arrays - might be too small/large
// doesn't do anything with top 4 # lines of gate design file

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {

	char *design_file;
	char *fault_file;
	int input_array[1000];           // data to be passed to algorithm
	int output_array[1000];          // data to be passed to algorithm
	int flipflop_array[1000][5];     // data to be passed to algorithm
	int buff_array[1000][2];         // data to be passed to algorithm
	int not_array[1000][2];          // data to be passed to algorithm
	int and_array[1000][3];          // data to be passed to algorithm
	int nand_array[1000][3];         // data to be passed to algorithm
	int or_array[1000][3];           // data to be passed to algorithm
	int nor_array[1000][3];          // data to be passed to algorithm
	int xor_array[1000][3];          // data to be passed to algorithm
	int nxor_array[1000][3];         // data to be passed to algorithm
	char *fault_array[10000][3];     // data to be passed to algorithm
	char *fault_array2[10000][3];
	char line[100];
	char *line2;
	int input_counter = 0;
	int output_counter = 0;
	int flipflop_counter = 0;
	int buff_counter = 0;
	int not_counter = 0;
	int and_counter = 0;
	int nand_counter = 0;
	int or_counter = 0;
	int nor_counter = 0;
	int xor_counter = 0;
	int nxor_counter = 0;
	int fault_counter = 0;
	char *data1;
	char *data2;
	char *data3;
	char *data4;
	char *data5;
	FILE *fp;
	FILE *fp2;
	
	design_file = argv[1];
	fault_file = argv[2];

	if (argc != 3) {
	        printf("Error: Please input a gate design file and fault description file\n");
		exit(1);
	}
	
	if (!(fp = fopen(design_file,"r"))) {
		perror("Error opening file");
		exit(1);
	}

	if (!(fp2 = fopen(fault_file,"r"))) {
	        perror("Error opening file");
		exit(1);
	}
	
	while (fgets(line, sizeof(line), fp) != NULL) {

	        line2 = line;
		if (strstr(line, "INPUT(") != NULL) {
		        data1 = strsep(&line2,"(");
			data1 = strsep(&line2,")");
			input_array[input_counter] = atoi(data1);
			input_counter++;
		}

		else if (strstr(line, "OUTPUT(") != NULL) {
		        data1 = strsep(&line2,"(");
			data1 = strsep(&line2,")");
			output_array[output_counter] = atoi(data1);
			output_counter++;
		}

		else if (strstr(line, "= DFF") != NULL) {
		        data1 = strsep(&line2, " ");
			data2 = strsep(&line2, "(");
			data2 = strsep(&line2, ",");
			data3 = strsep(&line2, " ");
			data3 = strsep(&line2, ",");
			data4 = strsep(&line2, " ");
			data4 = strsep(&line2, ",");
			data5 = strsep(&line2, " ");
			data5 = strsep(&line2, ")");
			flipflop_array[flipflop_counter][0] = atoi(data5);
			flipflop_array[flipflop_counter][1] = atoi(data2);
			flipflop_array[flipflop_counter][2] = atoi(data3);
			flipflop_array[flipflop_counter][3] = atoi(data4);
			flipflop_array[flipflop_counter][4] = atoi(data1);
			flipflop_counter++;
		}
		
		else if (strstr(line, "= BUFF") != NULL) {
		        data1 = strsep(&line2," ");
			data2 = strsep(&line2, "(");
			data2 = strsep(&line2, ")");
			buff_array[buff_counter][0] = atoi(data2);
			buff_array[buff_counter][1] = atoi(data1);
			buff_counter++;
		}

		else if (strstr(line, "= NOT") != NULL) {
		        data1 = strsep(&line2," ");
			data2 = strsep(&line2, "(");
			data2 = strsep(&line2, ")");
			not_array[not_counter][0] = atoi(data2);
			not_array[not_counter][1] = atoi(data1);
			not_counter++;
		}
		
		else if (strstr(line, "= AND") != NULL) {
		        data1 = strsep(&line2," ");
			data2 = strsep(&line2, "(");
			data2 = strsep(&line2, ", ");
			data3 = strsep(&line2, " ");
			data3 = strsep(&line2, ")");
			and_array[and_counter][0] = atoi(data2);
			and_array[and_counter][1] = atoi(data3);
			and_array[and_counter][2] = atoi(data1);
			and_counter++;
		}

                else if (strstr(line, "= NAND") != NULL) {
		        data1 = strsep(&line2," ");
			data2 = strsep(&line2, "(");
			data2 = strsep(&line2, ", ");
			data3 = strsep(&line2, " ");
			data3 = strsep(&line2, ")");
			nand_array[nand_counter][0] = atoi(data2);
			nand_array[nand_counter][1] = atoi(data3);
			nand_array[nand_counter][2] = atoi(data1);
			nand_counter++;
		}

		else if (strstr(line, "= OR") != NULL) {
		        data1 = strsep(&line2," ");
			data2 = strsep(&line2, "(");
			data2 = strsep(&line2, ", ");
			data3 = strsep(&line2, " ");
			data3 = strsep(&line2, ")");
			or_array[or_counter][0] = atoi(data2);
			or_array[or_counter][1] = atoi(data3);
			or_array[or_counter][2] = atoi(data1);
			or_counter++;
		}

                else if (strstr(line, "= NOR") != NULL) {
		        data1 = strsep(&line2," ");
			data2 = strsep(&line2, "(");
			data2 = strsep(&line2, ", ");
			data3 = strsep(&line2, " ");
			data3 = strsep(&line2, ")");
			nor_array[nor_counter][0] = atoi(data2);
			nor_array[nor_counter][1] = atoi(data3);
			nor_array[nor_counter][2] = atoi(data1);
			nor_counter++;
		}
				
                else if (strstr(line, "= XOR") != NULL) {
		        data1 = strsep(&line2," ");
			data2 = strsep(&line2, "(");
			data2 = strsep(&line2, ", ");
			data3 = strsep(&line2, " ");
			data3 = strsep(&line2, ")");
			xor_array[xor_counter][0] = atoi(data2);
			xor_array[xor_counter][1] = atoi(data3);
			xor_array[xor_counter][2] = atoi(data1);
			xor_counter++;  
		}

		else if (strstr(line, "= NXOR") != NULL) {
		        data1 = strsep(&line2," ");
			data2 = strsep(&line2, "(");
			data2 = strsep(&line2, ", ");
			data3 = strsep(&line2, " ");
			data3 = strsep(&line2, ")");
			nxor_array[nxor_counter][0] = atoi(data2);
			nxor_array[nxor_counter][1] = atoi(data3);
			nxor_array[nxor_counter][2] = atoi(data1);
			nxor_counter++;
		}

		else {
		  
		}

	}

        while (fgets(line, sizeof(line), fp2) != NULL) {

	        line2 = line;
		data1 = strtok(line2,"\t");
                data2 = strtok(NULL,"\t");
		data3 = strtok(NULL,"\t");
				
		fault_array2[fault_counter][0] = data1;
		fault_array2[fault_counter][1] = data2;
		fault_array2[fault_counter][2] = data3;

		if (strstr(data3, "SA0") != NULL) {
		  fault_array[fault_counter][2] = "SA0";
		} else if (strstr(data3, "SA1") != NULL) {
		  fault_array[fault_counter][2] = "SA1";
		} else if (strstr(data3, "NEG") != NULL) {
		  fault_array[fault_counter][2] = "NEG";
		} else if (strstr(data3, "RDOB_AND") != NULL) {
		  fault_array[fault_counter][2] = "RDOB_AND";
		} else if (strstr(data3, "RDOB_NAND") != NULL) {
		  fault_array[fault_counter][2] = "RDOB_NAND";
		} else if (strstr(data3, "RDOB_OR") != NULL) {
		  fault_array[fault_counter][2] = "RDOB_OR";
		} else if (strstr(data3, "RDOB_NOR") != NULL) {
		  fault_array[fault_counter][2] = "RDOB_NOR";
		} else if (strstr(data3, "RDOB_XOR") != NULL) {
		  fault_array[fault_counter][2] = "RDOB_XOR";
		} else if (strstr(data3, "RDOB_NXOR") != NULL) {
		  fault_array[fault_counter][2] = "RDOB_NXOR";
		} else if (strstr(data3, "RDOB_NOT") != NULL) {
		  fault_array[fault_counter][2] = "RDOB_NOT";
		} else if (strstr(data3, "RDOB_BUFF") != NULL) {
		  fault_array[fault_counter][2] = "RDOB_BUFF";
		} else {
		}

		fault_array[fault_counter][0] = malloc(sizeof(char) * strlen(fault_array2[fault_counter][0]));
		strncpy(fault_array[fault_counter][0],fault_array2[fault_counter][0],strlen(fault_array2[fault_counter][0]));
		
		fault_array[fault_counter][1] = malloc(sizeof(char) * strlen(fault_array2[fault_counter][1]));
		strncpy(fault_array[fault_counter][1],fault_array2[fault_counter][1],strlen(fault_array2[fault_counter][1]));

		fault_counter++;

	}

	/* Prints out the parsed information */

	printf("\nList of INPUT PORTS:\n");
	for (int i = 0; i<input_counter; i++) {
	        printf("%d\n",input_array[i]);
	}

        printf("\nList of OUTPUT PORTS:\n");
	for (int i = 0; i<output_counter; i++) {
	        printf("%d\n",output_array[i]);
	}

        printf("\nList of DFFS:\n");
	for (int i = 0; i<flipflop_counter; i++) {
	        printf("Input Signal:    %d    ",flipflop_array[i][0]);
		printf("    Clock Signal:    %d    ",flipflop_array[i][1]);
		printf("    Reset Signal:    %d    ",flipflop_array[i][2]);
		printf("    Enable Signal:    %d    ",flipflop_array[i][3]);
		printf("    Output Signal:    %d\n",flipflop_array[i][4]);
	}
	
        printf("\nList of BUFFS:\n");
	for (int i = 0; i<buff_counter; i++) {
	        printf("Input Signal:    %d    ",buff_array[i][0]);
		printf("    Output Signal:    %d\n",buff_array[i][1]);
	}
	
	printf("\nList of NOTS:\n");
	for (int i = 0; i<not_counter; i++) {
	        printf("Input Signal:    %d    ",not_array[i][0]);
	        printf("    Output Signal:    %d\n",not_array[i][1]);
	}

	printf("\nList of ANDS:\n");
	for (int i = 0; i<and_counter; i++) {
	        printf("Input Signal 1:    %d    ",and_array[i][0]);
	        printf("    Input Signal 2:    %d    ",and_array[i][1]);
		printf("    Output Signal:    %d\n",and_array[i][2]);
	}
	
        printf("\nList of NANDS:\n");
	for (int i = 0; i<nand_counter; i++) {
	        printf("Input Signal 1:    %d    ",nand_array[i][0]);
		printf("    Input Signal 2:    %d    ",nand_array[i][1]);
		printf("    Output Signal:    %d\n",nand_array[i][2]);
	}
	
        printf("\nList of ORS:\n");
	for (int i = 0; i<or_counter; i++) {
	        printf("Input Signal 1:    %d    ",or_array[i][0]);
		printf("    Input Signal 2:    %d    ",or_array[i][1]);
		printf("    Output Signal:    %d\n",or_array[i][2]);
	}

	printf("\nList of NORS:\n");
	for (int i = 0; i<nor_counter; i++) {
	        printf("Input Signal 1:    %d    ",nor_array[i][0]);
	        printf("    Input Signal 2:    %d    ",nor_array[i][1]);
	        printf("    Output Signal:    %d\n",nor_array[i][2]);
	}

	printf("\nList of XORS:\n");
	for (int i = 0; i<xor_counter; i++) {
	        printf("Input Signal 1:    %d    ",xor_array[i][0]);
		printf("    Input Signal 2:    %d    ",xor_array[i][1]);
		printf("    Output Signal:    %d\n",xor_array[i][2]);
	}

	printf("\nList of NXORS:\n");
	for (int i = 0; i<nxor_counter; i++) {
	        printf("Input Signal 1:    %d    ",nxor_array[i][0]);
		printf("    Input Signal 2:    %d    ",nxor_array[i][1]);
		printf("    Output Signal:    %d\n",nxor_array[i][2]);
	}
       
	printf("\nList of Faults:\n");
	for (int i = 0; i<fault_counter; i++) {
	        printf("Fault Identifier:    %s    ",fault_array[i][0]);
		printf("Signal Injected:    %s    ",fault_array[i][1]);
		printf("Fault Type:    %s\n",fault_array[i][2]);
	}
	
	fclose(fp);
	fclose(fp2);
	
}
