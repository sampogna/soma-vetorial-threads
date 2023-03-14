//Aluno: Rafael Walace Sampogna
//Matricula: 20161BSI0233
//Disciplina: Fundamentos de Programação Paralela e Distribuída
//Professor: Flávio Lamas

#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#define NUM_THREADS 10
#define ARR_LENGTH 100000

#include <semaphore.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t  mutex;

typedef struct arrObj {
	int			currentPosition;
	long long	totalSum;
	int			currentThread;
	int			eachArrSum[NUM_THREADS];
	int			realArr[ARR_LENGTH];
} ArrObj;



void* SumArr(void* arg) {
	ArrObj* obj = (ArrObj*) arg;

	while (obj->currentPosition < ARR_LENGTH) {
		pthread_mutex_lock(&mutex);
		if (obj->currentPosition < ARR_LENGTH) {
			(long long)obj->totalSum += obj->realArr[(int)obj->currentPosition];
			(int)obj->eachArrSum[(int)obj->currentThread]++;
			obj->currentPosition++;
		}
		pthread_mutex_unlock(&mutex);
	};
	return 0;
}

int main() {

	pthread_t threads[NUM_THREADS];
	int rc, t, i, c;
	ArrObj obj;
	

	int arr[ARR_LENGTH];
	int counter = 1;
	for (i = 0; i < ARR_LENGTH; i++) {
		obj.realArr[i] = counter;
		counter++;
	}
	obj.currentPosition = 0;
	obj.totalSum = 0;

	//Initializing mutex
	pthread_mutex_init(&mutex, NULL);

	for (t = 0; t < NUM_THREADS; t++) {
		//Assigning id for current thred being created
		obj.currentThread = t;
		obj.eachArrSum[t] = 0; //Thread work number starts with zero
		rc = pthread_create(&threads[t], NULL, (void*)SumArr, &obj);

	}
	//Esperando as threads terminarem
	for (t = 0; t < NUM_THREADS; t++) {
		rc = pthread_join(threads[t], NULL);

	}

	for (t = 0; t < NUM_THREADS; t++)
		printf("\nO trabalho da thread #%d foi de %d somas [%.2f%%]", t, obj.eachArrSum[t], ( ((float) obj.eachArrSum[t] * 100)/ ((float) ARR_LENGTH * 100) * 100));

	printf("\n\nA soma total eh: %lld", obj.totalSum);

	return 0;
}