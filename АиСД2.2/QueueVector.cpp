#include "QueueVector.h"

template <class T>
QueueVector<T>::QueueVector() :

	currentSize(initialSize),
	first(0),
	last(0),
	counter(0)
{
	try { data = new T[initialSize]; }
	catch (std::bad_alloc er) {
		std::cerr << "error: " << er.what() << '\n';
	}
};

template <class T>
void QueueVector<T>::resize(){
	try {
		bool flag = false;
		int newCurrentSize = (this->currentSize) * 2;
		T* newData = new T[newCurrentSize];
		int i, j;
		j = 0;
		i = this->first;
		if (i == 0) {
			flag = true;
		}
		while (i < this->counter) {
			newData[j] = this->data[i];
			i++;
			j++;
		}
		i = 0;
		if (flag == false) {
			while (i < this->last) {
				newData[j] = this->data[i];
				i++;
				j++;
			}
		}

		delete[] this->data;
		this->data = newData;
		this->currentSize = newCurrentSize;
		this->first = 0;
		this->last = this->counter;
	}
	catch (std::bad_alloc er) {
		std::cerr << "error: " << er.what() << '\n';
	}
}
template <class T>
void QueueVector<T>::enQueue(const T& data) {
	try {
		if (this->counter < 0) {
			throw UnexpectedError("Ungodly crap");
		}
		if (this->counter == currentSize) {
			if (this->currentSize == maxSize) {
				throw QueueOverflow("Queue overflow");
			}
			this->resize();
		}
		this->data[last] = data;
		if (this->last == ((this->currentSize) - 1)) {
			this->last = 0;
		}
		else {
			this->last += 1;
		}
		this->counter++;

	}
	catch (UnexpectedError er) {
		std::cerr << "error: " << er.what() << '\n';
		std::cerr << "How????????????" << '\n';
	}
	catch (QueueOverflow er) {
		std::cerr << "error: " << er.what() << '\n';
	}

}

template <class T>
T QueueVector<T>::deQueue() {
	try {
		if (this->isEmpty()) {
			throw QueueUnderflow("Queue underflow");
		}
		T temp = this->data[first];
		if (this->first == ((this->currentSize) - 1)) {
			this->first = 0;
		}
		else {
			this->first += 1;
		}
		this->counter--;
		return temp;
	}
	catch (QueueUnderflow er) {
		std::cerr << "error: " << er.what() << '\n';
		return T{};
	}
}

template <class T>
void QueueVector<T>::print() {
	try {
		
		if (this->isEmpty()) {
			throw QueueUnderflow("Queue underflow");
		}
		bool flag = false;
		
		std::cout << "[";
		for (int i = 0; i < this->currentSize; i++) {
			if (this->counter == this->currentSize) {
				flag = false;
			}
			if (((i % 10) == 0) && (i != this->currentSize) && (i != 0)) {
				std::cout << '\n';
			}
			switch (flag) {
			case true:
				if (i < this->first) {
					std::cout << '-' << ' ';
				}
				else {
					if ((i + 1) == this->currentSize) {
						std::cout << this->data[i];
					}
					else {
						std::cout << this->data[i] << ' ';
					}
				}
				break;
			case false:
				if (this->counter == this->currentSize) {
					if ((i + 1) == this->currentSize) {
						std::cout << this->data[i];
					}
					else {
						std::cout << this->data[i] << ' ';
					}
				}
				else {
					if (((this->last) < (this->first)) && flag == false) {
						if (((i + 1) == this->last)) {
							flag = true;
							std::cout << this->data[i] << ' ';
						}
						else if (((i == 0) && (this->last == 0))) {
							flag = true;
							std::cout << '-' << ' ';
						}
						else {
							std::cout << this->data[i] << ' ';
						}
					}
					else if (((this->last) > (this->first)) && ((i < this->last)) && (i >= this->first)) {
						std::cout << this->data[i] << ' ';
					}
					else {
						if ((i + 1) == this->currentSize) {
							std::cout << '-';
						}
						else {
							std::cout << '-' << ' ';
						}
					}
				}
				break;
			}
		}

		std::cout << "]" << '	' << "Current size: " << this->currentSize << '\n';
	}
	catch (QueueUnderflow er) {
		std::cerr << "error: " << er.what() << '\n';
	}
}

template class QueueVector<int>;