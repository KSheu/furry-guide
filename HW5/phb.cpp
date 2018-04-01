//
// CS31 Winter 2015
// File: HW #5 – Get to the Point!
// Author: Katherine Sheu (katherinesheu@ucla.edu)
// SID: 304150980
// Date: 2015-03-09
// Version: 1.0
// Description: A demonstration of manipulating arrays through pointers only to appease the PHB
//


#include<cstdlib>
#include<ctime>
#include<iostream>
#include<cassert>
using namespace std;

const int PHB_LIST_LENGTH = 1000;
const int PHB_LIST_MAX_VAL = 100;
const int PHB_LIST_MAGIC_NUM = 31;
enum PHB_LIST_ORDER {
	PHB_LIST_ORDER_INC,
	PHB_LIST_ORDER_DEC
};

bool PHB_list_check(const int *in_list, const int *in_len, int *out_list);
bool PHB_list_delete_duplicates(int *in_list, const int *len);
bool PHB_list_fill_up(int *list, const int *len);
bool PHB_list_reverse(int *list, const int *len);
bool PHB_list_sort(int *list, const int *len, const PHB_LIST_ORDER *ord);
bool PHB_list_sum_31(const int *in_list, const int *in_len, int *out_list, int *out_len);

int main(){
	/*
	//checking function test
	int phb[4] = { 3, 5, -6, 211 };
	int *ptr_phb = phb;
	int *ptr_out= new int[];
	int length = 4;
	int *ptr_len = &length;
	bool test = PHB_list_check(ptr_phb, ptr_len, ptr_out);
	cout << test << endl;
	for (int i = 0; i < 2; i++){
	cout << *(ptr_out+i);
	}
	*/
	//sorting function
	PHB_LIST_ORDER myOrd = PHB_LIST_ORDER_INC;
	int len = 8;
	int list[8] = { 3, 87, 3, 2, 1, 6, 2, 4 };
	int *list_ptr = list;
	PHB_list_sort(list_ptr, &len, &myOrd);
	for (int i = 0; i < 8; i++){
		cout << *(list_ptr + i) << endl;
	}
	

	//fill up function test
	int mylen = 8;
	int myList[8];
	int* myList_ptr = myList;
	PHB_list_fill_up(myList_ptr, &mylen);
	for (int i = 0; i < 8; i++){
		cout << *(myList_ptr + i) << endl;
	}
	/*
	//reverse function
	const int len = 7;
	int list[len] = {  3, 3, 2, 1, 6, 2, 40 };
	int *list_ptr = list;
	PHB_list_reverse(list_ptr, &len);
	for (int i = 0; i < len; i++){
		cout << *(list_ptr+i) << endl;
	}
	*/

	

	//delete duplicate function test
	int phb[9] = { 34,2,1,3,2,1,3,2,1 };
	int *ptr_phb = phb;
	int length = 9;
	int *ptr_len = &length;
	PHB_list_delete_duplicates(ptr_phb, ptr_len);
	
	for (int i = 0; i < 9; i++){
		cout << *(ptr_phb + i) << endl;
	}

	const int LEN = 8;
	int last_list[LEN] = { 9, 5, 16, 22, 1, 37, 26, 7 };
	int *ptr_last_list = last_list;
	int last_len = LEN;
	int out_list[LEN];
	int *ptr_out_list = out_list;
	int out_len = LEN;
	bool sum_test = PHB_list_sum_31(ptr_last_list, &last_len, ptr_out_list, &out_len);
	for (int i = 0; i < out_len; i++){
		cout << *(out_list+i) << endl;
	}
	cout << "out length is " << out_len << endl;
	cout << sum_test<< endl;
	
}


bool PHB_list_check(const int *in_list, const int *in_len, int *out_list){
	assert(*in_len <= PHB_LIST_LENGTH);
	bool check = true;
	//used to keep track of how many invalid elements have been seen
	int out_list_count = 0;
	//out_list = new int[];
	//for each element 
	for (int i = 0; i < *in_len; i++){
		//if it i between 1 and 100 set return var to false
		if (*(in_list+i) < 1 || *(in_list+i) > PHB_LIST_MAX_VAL){
			check = false;
			//add that index to the out_list array
			*(out_list + out_list_count) = i;
			out_list_count ++;
		}
	}
	return check;
}
bool PHB_list_delete_duplicates(int *in_list, const int *len){
	assert(*len <= PHB_LIST_LENGTH);
	int end = *len;
	//for each element, move down the rest of the list and remove duplicates by shifting everything else down
	for (int i = 0; i < end; i++){
		for (int j = i+1; j < end; j++){
			//check to see if any elements down the list are duplicates
			if (*(in_list + i) == *(in_list + j)){
				//move everything down one address, doesn't matter what is in the vacated spot at the end
				for (int k = j; k < *len - 1; k++){
					*(in_list + k) = *(in_list + k + 1);
				}
				//each time array is shifted left the end of array decreases
				end--;
				//each time array is  shifted, j must be decremented to check the new value in the vacated index
				j--;
			}
			
		}	
	}
	return true;
}

bool PHB_list_fill_up(int *list, const int *len){
	assert(*len <= PHB_LIST_LENGTH);
	//seed the rand with time the program is being run
	srand(time(0));

	//fill with random values
	for (int i = 0; i < *len; i++){
		*(list+i) = (rand()%100) +1;
	}
	return true;
}

//swap function for use in list_reverse and insertion_sort
void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

bool PHB_list_reverse(int *list, const int *len){
	assert(*len <= PHB_LIST_LENGTH);
	//divide the array in half
	for (int i = 0; i < *len/2; i++){
		//cout << "swapping " << *(list + i) << *(list + *len-1 - i) << endl;
		//swap the first and last elements until the center is reached
		swap((list + i), (list + *len-1 - i));
	}
	return true;
}

void inc_insertion_sort(int *a,  int len){
	//for every element of array
	for (int i = 1; i < len; i++){
		int j = i;
		//while the number to the left of it is larger (or unil the element becomes the first element), swap the two
		while (j > 0 && *(a+j - 1) > *(a+j)){
			swap(*(a+j), *(a+j - 1));
			//tracks the location of the element in question as comparisons are made
			j--;
		}
	}
}

void dec_insertion_sort(int *a, int len){
	for (int i = 1; i < len; i++){
		int j = i;
		//while the number to the left of it is smaller (or unil the element becomes the first element), swap the two
		while (j > 0 && *(a + j - 1) < *(a + j)){
			swap(*(a + j), *(a + j - 1));
			j--;
		}
	}
}
bool PHB_list_sort(int *list, const int *len, const PHB_LIST_ORDER *ord){
	assert(*len <= PHB_LIST_LENGTH);
	if (*ord == PHB_LIST_ORDER_INC){
		//insertion sort
		inc_insertion_sort(list, *len);
	}
	if (*ord == PHB_LIST_ORDER_DEC){
		//insertion sort
		dec_insertion_sort(list, *len);
	}
	return true;
}
bool PHB_list_sum_31(const int *in_list, const int *in_len, int *out_list, int *out_len){
	assert(*in_len <= PHB_LIST_LENGTH);
	int sum;
	//deals with lists that are smaller than or equal to 5 elements since we can look at every subset
	if (*in_len <= 5){
		//sets the first element to be inspected
		for (int k = 0; k < *in_len; k++){
			//iterate through the possibilities of 1 element being the correct sum
			for (int i = k; i < *in_len; i++){
				sum = 0;
				sum = *(in_list + i);
				//cout << "sum of 1 is " << sum << endl;
				//store appropriate values if sum is correct
				if (sum == PHB_LIST_MAGIC_NUM){
					*(out_list + 0) = i;
					*out_len = 1;
					return true;
				}
				//if the array is larger than size 1, check possibilities of 2 numbers adding to make the sum
				if (*in_len > 1){
					for (int j = i + 1; j < *in_len; j++){
						sum = 0;
						//take the sum of two numbers
						sum = *(in_list + i) + *(in_list + j);
						//cout << "sum of 2 is " << sum << endl;
						//store the indices of the two numbers if the sum is right
						if (sum == PHB_LIST_MAGIC_NUM){
							*(out_list + 0) = i;
							*(out_list + 1) = j;
							//set the out_len to 2 since two numbers were added
							*out_len = 2;
							return true;
						}
						//if the array is larger than size 2, check possibilities of 3 numbers adding to make the sum
						//logic is same as above 
						if (*in_len > 2){
							for (int l = j + 1; l < *in_len; l++){
								sum = 0;
								sum = *(in_list + i) + *(in_list + j) + *(in_list + l);
								//cout << "sum of 3 is " << sum << endl;
								if (sum == PHB_LIST_MAGIC_NUM){
									*(out_list + 0) = i;
									*(out_list + 1) = j;
									*(out_list + 2) = l;
									*out_len = 3;
									return true;
								}
								//if the array is larger than size 3, check possibilities of 4 numbers adding to make the sum
								if (*in_len > 3){
									for (int m = l + 1; m < *in_len; m++){
										sum = 0;
										sum = *(in_list + i) + *(in_list + j) + *(in_list + l) + *(in_list + m);
										//cout << "sum of 4 is " << sum << endl;
										if (sum == PHB_LIST_MAGIC_NUM){
											*(out_list + 0) = i;
											*(out_list + 1) = j;
											*(out_list + 2) = l;
											*(out_list + 3) = m;
											*out_len = 4;
											return true;
										}
										//if the array is larger than size 4, check possibilities of 5 numbers adding to make the sum
										if (*in_len > 4){
											for (int n = m + 1; n < *in_len; n++){
												sum = 0;
												sum = *(in_list + i) + *(in_list + j) + *(in_list + l) + *(in_list + m) + *(in_list + n);
												//cout << "sum of 5 is " << sum << endl;
												if (sum == PHB_LIST_MAGIC_NUM){
													*(out_list + 0) = i;
													*(out_list + 1) = j;
													*(out_list + 2) = l;
													*(out_list + 3) = m;
													*(out_list + 4) = n;
													*out_len = 5;
													return true;
												}

											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	//a brute force algorithm 
	*out_len = 0;
	if (*in_len > 5){
		//this limits each subset looked at to 5 consequtive numbers
		//the rest of the code follows the same algorithm as described above
		for (int k = 0; k < *in_len-5+1; k++){
			for (int i = k; i < k+5; i++){
				sum = 0;
				sum = *(in_list + i);
				//cout << "sum of 1 is " << sum << endl;
				if (sum == PHB_LIST_MAGIC_NUM){
					*(out_list + 0) = i;
					*out_len = 1;
					return true;
				}
				for (int j = i + 1; j < k + 5; j++){
					sum = 0;
					sum = *(in_list + i) + *(in_list + j);
					//cout << "sum of 2 is " << sum << endl;
					if (sum == PHB_LIST_MAGIC_NUM){
						*(out_list + 0) = i;
						*(out_list + 1) = j;
						*out_len = 2;
						return true;
					}
					for (int l = j + 1; l < k + 5; l++){
						sum = 0;
						sum = *(in_list + i) + *(in_list + j) + *(in_list + l);
						//cout << "sum of 3 is " << sum << endl;
						if (sum == PHB_LIST_MAGIC_NUM){
							*(out_list + 0) = i;
							*(out_list + 1) = j;
							*(out_list + 2) = l;
							*out_len = 3;
							return true;
						}
						for (int m = l + 1; m < k + 5; m++){
							sum = 0;
							sum = *(in_list + i) + *(in_list + j) + *(in_list + l) + *(in_list + m);
							//cout << "sum of 4 is " << sum << endl;
							if (sum == PHB_LIST_MAGIC_NUM){
								*(out_list + 0) = i;
								*(out_list + 1) = j;
								*(out_list + 2) = l;
								*(out_list + 3) = m;
								*out_len = 4;
								return true;
							}
							for (int n = m + 1; n < k + 5; n++){
								sum = 0;
								sum = *(in_list + i) + *(in_list + j) + *(in_list + l) + *(in_list + m) + *(in_list + n);
								//cout << "sum of 5 is " << sum << endl;
								if (sum == PHB_LIST_MAGIC_NUM){
									*(out_list + 0) = i;
									*(out_list + 1) = j;
									*(out_list + 2) = l;
									*(out_list + 3) = m;
									*(out_list + 4) = n;
									*out_len = 5;
									return true;
								}
							}
						}
					}
				}
			}
		}
	}

	//if all possible combinations are run through and none match the wanted sum, return false
	if (sum != PHB_LIST_MAGIC_NUM){
		return false;
	}
	
}




