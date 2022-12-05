#include <iostream>
#include <mutex>
#include <random>
#include <vector>
#include <thread>	

using namespace std;

int get_random(int low, int high) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distribution(low, high);
  return distribution(gen);
}

template <class T>
struct Node {
	mutex node_mutex;
	T value;
	bool checked;
	Node<T>* next;
	Node (T a, Node<T>* p) {
		checked = false;
		value = a;
		next = p;
	}
	void lock_n () {
		node_mutex.lock();
	}
	void unlock_n () {
		node_mutex.unlock();
	}
};

template <class T>
class List {
	Node<T>* head;
    Node<T>* tail;
public:
	List () {
		tail = new Node<T>(numeric_limits<T>::max(), nullptr);
		head = new Node<T>(numeric_limits<T>::max(), tail);
	}
	bool validation(Node<T>* q, Node<T>* p) {	
    	return !q->checked && !p->marked && q->next == p;
	}
	bool find (Node<T>*& p, Node<T>*& q, T a) {
		for (; p->value < a; q = p, p = p->next) {}
		return p->value == a;
	}
	bool add (T a) {
		bool rpta = false;
		bool search;
		while (true) {
			Node<T> *q = &head;
			Node<T> *p = head->next;
			search = find(p, q, a);
			
			q->lock_n();  
        	p->lock_n();  
			
			if (validation(q,p)) {
				if (search) { rpta = false; }
				else {
					Node<T>* n = new Node<T>(a, p);
					q->next = n;
					rpta = true;
				}
				q->unlock_n();  
        		p->unlock_n();
				return rpta;
			}
			q->unlock_n();  
    		p->unlock_n();
		}
	}
	bool remove (T a) {
		bool rpta = false;
		bool search;
		while (true) {
			Node<T> *q = &head;
			Node<T> *p = head->next;
			search = find(p, q, a);
			
			q->lock_n();  
        	p->lock_n();  
			
			if (validation(q,p)) {
				if (!search) { rpta = false; }
				else {
					p->checked = true;
					q->next = p->next;
					rpta = true;	
				}
				q->unlock_n();
        		p->unlock_n();
				return rpta;
			}
			q->unlock_n();  
    		p->unlock_n();
		}
	}
	void print () {
		cout << "Head -> ";
    	for (Node<T>* a = head->next; a != tail; a = a->next) {
        	cout << a->value << " -> ";
		}
    	cout << "null\n";
	}
};

/*struct Add{
  int min_;
  int max_;
  List<int> *ptr_;
  
  Add(int min,int max,List<int> *ptr):min_(min),max_(max),ptr_(ptr){}
  
  void operator()(int operaciones){
    for(int i=0;i<operaciones;i++){
      ptr_->add(get_random(min_,max_));
    }
  }
};*/