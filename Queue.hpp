#include <iostream>
#include <mutex>
#include <random>
#include <vector>
#include <thread>	

using namespace std;

template <class T>
struct nodeQueue {                //A diferencia del ya mostrado, este nodo sera utilizado para crear pilas y colas
	T value;
	nodeQueue<T>* nextQueue;
	int stade;                   //Este estado se usara para saber cuanda se sacara un elemento, dependiendo de como se le usara mas adelante
	nodeQueue(T x, nodeQueue<T>* n) {
		value = x;
		nextQueue= n;
		stade = 0;
	}
};

template <class T>
struct Queue {                          //Aqui encontraremos la estructura de la cola
	nodeQueue<T>* h_queue;
	Queue() { h_queue = nullptr; }
    bool find (T x) {
        nodeQueue<T>** p;
        for (p = &h_queue; *p && (*p)->value != x; p = &((*p)->nextQueue)) {}//Recorre la cola hasta que el puntero apunte a nulo, o se encuentre el valor
		return !!*p;
    } 
	bool push(T x) {
		nodeQueue<T>** p = &h_queue;
		for (; *p ; p = &((*p)->nextQueue)) {}
		*p = new nodeQueue<T>(x, *p);
		return true; 
	}
	bool pop() { nodeQueue<T>* p = h_queue; h_queue = h_queue->nextQueue; delete p; return true; }
};