//Sequence.cpp

#include "Sequence.h"


//Constructor
Sequence::Sequence(){
	//initialize the m_head pointer to the address of the dummy
	//leave m_dummy's m_data uninitialized
	m_head = &m_dummy;

	//dummy has pointers to itself
	m_dummy.m_next = &m_dummy;
	m_dummy.m_prev = &m_dummy;
	
	//set m_size to 0 since m_dummy does not count as a node with data in the sequence
	m_size = 0;
	
}

//destructor
Sequence:: ~Sequence(){

	//set the pointer to m_dummy's m_next
	Node* p = m_head->m_next;
	//for each node in the list, erase it (deallocating the memory)
	for (int i = 0; i < m_size; i++){
		p = p->m_next;
		erase(i);
	}
	//then delete the object the m_head points to, leaving m_head uninitialied
	//delete m_head;
}

//copy constructor
Sequence::Sequence(const Sequence& other){
	//copy the sizes
	this->m_size = other.m_size;
	//copy the dummy values from other into this
	this->m_dummy = other.m_dummy;
	//assign the m_head pointer to m_dummy
	this->m_head = &m_dummy;
	//use a pointer to move along the other linked list
	Node*p = other.m_head->m_next;

	//for each m_data value, add a new node to this 
	for (int i = 0; i < size(); i++){
		p = p->m_next;
		insert(i, p->m_data);
	}
}
//assignment operator
Sequence& Sequence::operator=(const Sequence& rhs){
	//accounts for aliasing
	if (this != &rhs){
		Sequence temp(rhs);//use copy constructor, if can't copy into temp, don't delete anything
		swap(temp);
	}
	return *this;
}

// Return true if the sequence is empty, otherwise false.
bool Sequence::empty() const{
	if (m_size == 0){
		return true;
	}
	return false;
}

// Return the number of items in the sequence.
int Sequence::size() const{
	return m_size;
}

// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return true if 0 <= pos <= size() and the value could be
// inserted.    Otherwise,leave the sequence unchanged and return false. 
// Notice that if pos is equal to size(), the value is inserted at the end.
bool Sequence::insert(int pos, const ItemType& value){
	if (pos < 0 || pos > size()){
		return false;
	}
	Node* p = m_head->m_next;
	//find the position you want to insert in
	for (int i = 0; i < pos; i++){
		p = p->m_next;
	}
	//set up a new pointer that points to the node to be added
	Node* newPtr = new Node;
	newPtr->m_data = value;

	//set links between new Node and the old previous
	p->m_prev->m_next = newPtr;
	newPtr->m_prev = p->m_prev;

	//set links between new node and p which was pushed up one count
	p->m_prev = newPtr;
	newPtr->m_next = p;

	m_size++;
	return true;

}

// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return true if the value
// was actually inserted.  Return false if the value was not inserted.
//(Should always be inserted since the Sequence is not of fixed size.)
bool Sequence::insert(const ItemType& value){

	Node* p = m_head->m_next;
	for (int i = 0; i < size(); i++){
		if (value <= p->m_data || m_size == 0){
			insert(i, value);
			return true;
		}
	}
	//no smaller value found
	insert(m_size, value);
	return true;
}

// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed this item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
bool Sequence::erase(int pos){
	if (pos < 0 || pos >=size()){
		return false;
	}
	Node* p = m_head->m_next;
	for (int i = 0; i < pos; i++){
		p = p->m_next;
	}
	 //skip over p when reseting the pointers
	 p->m_prev->m_next = p->m_next;
	 p->m_next->m_prev = p->m_prev;
	 //delete the object pointed to by p, p points to undefined value
	 delete p;
	 m_size--;
	 return true;
}

// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
int Sequence::remove(const ItemType& value){
	int count = 0;
	Node* p = m_head->m_next;
	for (int i = 0; i < size(); i++){
		p = p->m_next;
		if (p->m_data == value){
			erase(i);
			count++;
		}
	}
	return count;
}

// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.
bool Sequence::get(int pos, ItemType& value) const{
	if (pos < 0 || pos >= size()){
		return false;
	}
	Node* p = m_head->m_next;
	for (int i = 0; i < pos; i++){
		p = p->m_next;
	}
	value = p->m_data;
	return true;
}

// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
bool Sequence::set(int pos, const ItemType& value){
	if (pos < 0 || pos >= size()){
		return false;
	}
	Node* p = m_head->m_next;
	for (int i = 0; i < pos; i++){
		p = p->m_next;
	}
	p->m_data = value;
	return true;
}

// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.
int Sequence::find(const ItemType& value) const{
	//tracking pointer
	Node*p = m_head->m_next;
	int count = 0;
	while (p->m_data != value && p != m_head){
		p = p->m_next;
		count++;
	}
	if (p->m_data == value){
		return count;
	}
	return -1;

}

// Exchange the contents of this sequence with the other one.
void Sequence::swap(Sequence& other){
	//swap the m_sizes
	int temp_size = other.m_size;
	other.m_size = m_size;
	m_size = temp_size;

	//swap by switching the m_head pointers 
	Node* temp = other.m_head;
	other.m_head = this->m_head;
	this->m_head = temp;

}

int subsequence(const Sequence& seq1, const Sequence& seq2){
	ItemType value2;
	ItemType value1;
	for (int i = 0; i < seq1.size()-seq2.size(); i++){
		//count number of consecutive matches
		int count = 0;
		for (int j = 0; j < seq2.size(); j++){
			seq2.get(j, value2);
			seq1.get(i+j, value1);
			if (value1 == value2){
				count++;
			}
		}
		if (count == seq2.size())
			return i;
	}
	return -1;
}

//lace the two Sequences together
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result){
	//make sure result is empty before adding anything
	for (int i = 0; i < result.size(); i++){
		result.erase(i);
	}

	//initialize count and value variables 
	int count1 = 0;
	int count2 = 0;
	ItemType value1;
	ItemType value2;
	
	//while they both have valid values, get the value at each position
	while (count1 < seq1.size() && count2 < seq2.size()){
		seq1.get(count1, value1);
		seq2.get(count2, value2);
		//increment the position
		count1++;
		count2++;
		//add the gotten value to end of result, with seq1 going first
		result.insert(result.size(),value1);
		result.insert(result.size(),value2);
	}
	//if one of them is longer, add on the rest of the values
	if (seq1.size() > seq2.size()){
		for (int i = count1; i < seq1.size(); i++){
			seq1.get(count1, value1);
			result.insert(result.size(),value1);
		}
	}
	//else do it for the other one
	else{
		for (int i = count2; i < seq2.size(); i++){
			seq1.get(count2, value2);
			result.insert(result.size(), value2);
		}
	}
}

