//Aluno: Rafael Walace Sampogna
//Matricula: 20161BSI0233
//Disciplina: Fundamentos de Programação Paralela e Distribuída
//Professor: Flávio Lamas

#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#define NUM_THREADS 10
#define ARR_LENGTH 100

#include <semaphore.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t  mutex;

typedef struct arrObj {
	int*  currentPosition;
	int*  eachArrSum;
	int*  totalSum;
	int*  currentThread;
	int*  realArr;
} ArrObj;



void* SumArr(void* arg, int* id_thread) {
	ArrObj* obj = (ArrObj *) arg;
	printf("current thread: %d\n", obj->currentThread);


	while (obj->currentPosition <= ARR_LENGTH) {
		
	}


	////int* id = (int *) id_thread;

	//pthread_mutex_lock(&mutex);
	////Somar ao total
	//obj->totalSum += obj->realArr[obj->currentPosition];

	////Incrementar posicao
	//obj->currentPosition += 1;

	////Incrementar numero de operacoes da thread
	//obj->eachArrSum[obj->currentThread] += 1;
	//pthread_mutex_unlock(&mutex);

	return 0;
}

void printArr(int* arr, int length) {
	int i;
	printf("\n");
	for (i = 0; i < length; i++)
		printf("%d, ", arr[i]);
}

int main(int argc, char* argv[]) {

	pthread_t threads[NUM_THREADS];
	int rc, t, i, c;

	int arr[ARR_LENGTH];
	int counter = 1;
	for (i = 0; i < ARR_LENGTH; i++) {
		arr[i] = counter;
		counter++;
	}

	//printArr(arr, ARR_LENGTH);

	ArrObj obj;
	//obj.currentPosition = -1; //Posi
	obj.eachArrSum = malloc(NUM_THREADS * sizeof(int));
	obj.totalSum = (int *)0;
	obj.realArr = arr;

	//Mutex section
	pthread_mutex_init(&mutex, NULL);

	for (t = 0; t < NUM_THREADS; t++) {
		//Assigning id for current thred being created
		obj.currentThread = t;
		obj.eachArrSum[t] = 0; //Zerando contador de cada thread
		rc = pthread_create(&threads[t], NULL, SumArr, &obj, &t);

	}
	//Esperando as threads terminarem
	for (t = 0; t < NUM_THREADS; t++) {
		rc = pthread_join(threads[t], NULL);

	}

	//printf("\nTotal sum is: %d", obj.currentPosition);

	printArr(obj.eachArrSum, NUM_THREADS);


	//for (t = 0; t < NUM_THREADS; t++)
	//	pthread_join(threads[i], NULL);

	return 0;
}