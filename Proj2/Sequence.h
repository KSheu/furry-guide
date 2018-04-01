//Sequence.h

#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include<string>
using namespace std;

typedef std::string ItemType;

class Sequence
{
public:
	Sequence();
	~Sequence();
	Sequence(const Sequence& other);
	Sequence& operator=(const Sequence& rhs);
	bool empty() const;
	int size() const;
	bool insert(int pos, const ItemType& value);
	bool insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
private:
	struct Node
	{
		ItemType m_data;
		Node* m_next;
		Node* m_prev;
	};
	int m_size;
	Node* m_head;
	Node m_dummy;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif //SEQUENCE_INCLUDED