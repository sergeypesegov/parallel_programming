#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
 
//Pesegov Sergey Aleksandrovich. 7*6*13
 
/*const int B1 = 7;
	const int B2 = 8;
	const int B3 = 6;
	const int B4 = 7; */
 
 
const int A = 7 * 6 * 13; //546
 
int generate_variant_1(int A) {
	const int B1 = 7;
	const int variant_task_1 = 1 + ((A % 47) % B1);
	return variant_task_1;
}
 
int generate_variant_2(int A) {
	const int B2 = 8;
	const int variant_task_2 = 1 + ((A % 47) % B2);
	return variant_task_2;
}
 
int generate_variant_3(int A) {
	const int B3 = 6;
	const int variant_task_3 = 1 + ((A % 47) % B3);
	return variant_task_3;
}
 
 
void generate_arrays(double* M1, double* M2, int n, unsigned* seed) {
 
	for (int i = 0; i < n; i++) {
		M1[i] = 1 + rand_r(seed) % A; // from 1 to A
	}
 
	for (int i = 0; i < n/2; i++) {
		M2[i] = A + rand_r(seed) % (10 * A); // from A to 10 * A
	}
}
 
void map(double* M1, double* M2, int n) {
	for (int i = 0; i < n; i++) {
		M1[i] = cbrt(M1[i] / M_E);
	}
 
	for (int i = 0; i < n/2 - 1; i++) {
		M2[i] = pow(log10(M2[i+1] + M2[i]), M_E);
	}
}
 
void merge(double* M1, double* M2, int n) {
	for (int i = 0; i < n/2; i++) {
		M2[i] = abs(M1[i] - M2[i]);
	}
}
 
 
int get_next_gap(int gap) {
	gap = gap / 1.3;
	if (gap < 1) {
		return 1;
	}
	return gap;
}
 
 
void comb_sort(double* new_array, int n){
	int temp = 0;
	int gap = n;
	bool swapped = true;
	while (gap != 1 || swapped == true) {
		gap = get_next_gap(gap); // the value 1.3 has been received empirically
		swapped = false;
 
		for (int i = 0; i < n-gap; i++) {
			if (new_array[i] > new_array[i+gap]) {
 
				//swap 2 elements
				temp = new_array[i];
				new_array[i] = new_array[i+gap];
				new_array[i+gap] = temp;
				//set the flag of swapping
				swapped = true;
			}
		}
	}
	//for (int i = 0; i < n; i++) {
	//	printf("%f",new_array[i]);
	//}
}
 
 
 double min_element(double* array, int n) { //works only for positive numbers
 	double min = array[0];
	for (int i = 1; i < n; i++)
		if (array[i] < min)
			min = array[i];
 
	return min;
 }
 
 
void reduce(double * M2, int n) {
	double sum = 0;
	double min;
	min = min_element(M2, n);
	double mod_element;
	for (int i = 0; i < n; i++) {
		mod_element = M2[i] / min;
		int mod_element_int = (int)floor(mod_element);
		if (mod_element_int % 2 == 0) 
			sum += sin(M2[i]);
	}
	//printf("%f\n", sum);
}
 
 
int main(int argc, char* argv[]) {
	//printf("Variant for task 1: %d\n",generate_variant_1(A)); //2
	//printf("Variant for task 2: %d\n",generate_variant_2(A)); //6
	//printf("Variant for task 3: %d\n",generate_variant_3(A)); //6
	//printf("Variant for task 4: %d\n",generate_variant_1(A)); //2
 
 
 	struct timeval T1, T2;
 	long delta_ms;
 	int const N = atoi(argv[1]); /* N равен первому параметру командной строки */
 	printf("%d\n", N);
 	gettimeofday(&T1, NULL);
 
	for (int i = 0; i < 50; i++) {  
		unsigned seed = i;
 
		double M1[N];
		double M2[N/2];
 
		generate_arrays(M1, M2, N, &seed);
		map(M1, M2, N);
		merge(M1, M2, N);
		comb_sort(M2, N / 2);
		reduce(M2, N / 2);
	}
 
	gettimeofday(&T2, NULL);   /* запомнить текущее время T2 */
	delta_ms =  1000*(T2.tv_sec - T1.tv_sec) + (T2.tv_usec - T1.tv_usec)/1000;
	printf("\nN=%d. Milliseconds passed: %ld\n", N, delta_ms); /* T2 -T1 */
	return 0;
}