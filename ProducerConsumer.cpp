//============================================================================
// Name        : ProducerConsumer.cpp
// Author      : Jay Nathani
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>

using namespace std;

//The producer will enter 15 items in the queue to check if the producer sleeps after entering 10 values

class Producer{
	int item;
	int item_count;
public:
	Producer(){
		item = 0;
		item_count = 0;
	}
	int create_item(){
		item_count++;
		item = item_count;
		return item;
	}
	void enter_item_in_queue(queue<int>& q){
		for(int i=0;i<15;i++){
			int updated_item;
			updated_item = create_item();
			if(q.size() == 10){
				cout<<"Producer goes to sleep"<<endl;
				//sleep
			}
			q.push(item);
			cout<<"Item pushed by producer: "<<q.back();
			cout<<"\tQueue size is: "<<q.size()<<endl;
		}
	}
	void operator()(){

	}
};

/*The consumer will be in sleep for at least 10 values so that the procedure doesn't go into a process
where in one cycle the producer enters an item in the queue and the consumer consumes the item from the
queue in the next cycle.*/

class Consumer{
	int item;
	vector<int> consumer_vector;
public:
	void extract_and_remove_item_from_queue(queue<int>& q){
/*		int flag = 1;
		if(q.size() == 0){
			//sleep
	//		cout<<"The size of the queue is: "<<q.size()<<endl;
			cout<<"Consumer goes to sleep";
		}
		else{

			if(q.size() == 10 && flag == 1){
				flag = 0;
				item = q.front();
				consumer_vector.push_back(item);	//Saving values from the queue
				q.pop();
				cout<<"Item extracted by consumer: "<<item;
			}
			else if(flag == 0){
				item = q.front();
				consumer_vector.push_back(item);	//Saving values from the queue
				q.pop();
				cout<<"Item extracted by consumer: "<<item;
			}
		}*/
	}
	void operator()(queue<int>& q){
		int flag = 1;
				if(q.size() == 0){
					//sleep
			//		cout<<"The size of the queue is: "<<q.size()<<endl;
					cout<<"Consumer goes to sleep";
				}
				else{

					if(q.size() == 10 && flag == 1){
						flag = 0;
						item = q.front();
						consumer_vector.push_back(item);	//Saving values from the queue
						q.pop();
						cout<<"Item extracted by consumer: "<<item;
					}
					else if(flag == 0){
						item = q.front();
						consumer_vector.push_back(item);	//Saving values from the queue
						q.pop();
						cout<<"Item extracted by consumer: "<<item;
					}
				}
	}

};


int main() {
	int size = 10; //Restricting queue size to 10
	queue<int> myqueue;
	Producer p1;	//Producer one
	Consumer c1;	//Consumer one
	int queue_size = myqueue.size();
	thread t1(p1);
	thread t2((c1), myqueue);

	p1.enter_item_in_queue(myqueue);

//	cout<<"The size of the queue is: "<<myqueue.size()<<endl;
	c1.extract_and_remove_item_from_queue(myqueue);



	t1.join();
	t2.join();
	return 0;
}
