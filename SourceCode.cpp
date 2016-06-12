#include<iostream>
#include<math.h>
#include<string>
//nclude<stdint.h>
using namespace std;

int prime(int data)
{
	int value = data , count=0;
	for(int i=value ; i>1 ;--i)
	{
		for(int j=1; j<=i ; ++j)
			if(i % j ==0 )
				++count;

		if(count == 2)                      // 2 | 2           
		{
			data = i;	
			break;
		}
		else
			count = 0;
	}
	return data;
}

string binary_value(unsigned char val)
{
	unsigned int num = val;
	string binary = "";
	for(int i=7 ; i>=0 ; --i)
	{
		if(num != 0)
		{
			if(num % 2 == 1)
				binary.append("1");
			else
				binary.append("0");
			num /= 2;
		}
		else
			binary.append("0");
	}
	char real[8];

	int j=0;
	for(i=0 , j=7 ; i<8 && j >=0 ; ++i , --j)
		real[i] = binary[j];

	binary = "";
	for(i=0 ; i<8 ; ++i)
	{
		if(real[i] == '0')
			binary.append("0");
		else
			binary.append("1");
	}

	return binary;
}

char character_converting(char *value1)
{
	int result=0;
	char character;
	for(int i=0 , j=7 ; i<8 ; ++i , --j)
	{
		if(value1[i] == '1')
			result += pow(2,j); 
	}
		
	character = result;
	return character;
}

int binary_to_decimal(string value)
{
	int num=0 , i=0;
	for(i=0 ; i<= 7 ; ++i)
	{
		if(value[i] == 1)
			num += pow(2 , i);
	}
	return num;
}

void main()
{
	bool status = true;
	char str[50];
	cout<<"Enter string: ";
	cin.getline(str , 50 , '\n');

	int size=0 ,i=0;
	for(i=0 ; str[i] != NULL ; ++i)
		++size;

	if(size % 2 != 0)
	{
		++size;
		status = false;
	}
	else if(size == 0)
	{
		size =2;
		str[0] = NULL;
		status = false;
	}

	int *array_of_ascii = new int[size];
	char *array_of_result = new char[size/2];

	for(i=0; i<size ; ++i)
	{
		array_of_ascii[i] = str[i];
		array_of_ascii[i] = prime(array_of_ascii[i]);
	}
	if(status == false)
	{
		array_of_ascii[size-1] = 'A';
		array_of_ascii[size-1] = prime(array_of_ascii[size-1]);
	}

	unsigned char num_1=0 , num_2=0 ,A=0 , B=0, temp_num=0;
	string Num_1 , Num_2 ;
	char temp[8];
	int count=0 ;
	
	int res_size = size/2;
	if(res_size % 2 != 0)
		++res_size;

	do
	{
		for(int p=0 ; p<size && size >=2 ;)
		{
			num_1 = array_of_ascii[p];
			num_2 = array_of_ascii[p+1];

			// round1
			A = num_1 , B = num_2;
			num_1 = ((A & B) | ( ~(A) & B));
			num_2 = ((A & B) | ( A & ~(B)));

			// round2
			A = num_1 , B = num_2;
			num_1 = ((A & B) | ( A & ~(B)));
			num_2 = ((A & B) | ( ~(A) & B));

			// round3
			A = num_1 , B = num_2;
			num_1 = A ^ B;
			num_2 = A ^ (A | ~(B));

			Num_1 = binary_value(num_1);
			Num_2 = binary_value(num_2);

			for(i=0 ; i<4 ; ++i)
				temp[i] = Num_1[i];
			for(i=4 ; i<8 ; ++i)
				temp[i] = Num_2[i];

			array_of_result[count] = character_converting(temp);
			++count;
			p+=2;
		}
		array_of_ascii = new int[res_size];
		
		if((size/2) % 2 != 0)
		{
			for(i=0 ; i<res_size-1 ; ++i)
				array_of_ascii[i] = array_of_result[i];

			//if(size % 2 != 0)
				array_of_ascii[i] = 'A'; 
				array_of_result[i] = 'A';
		}
		else
		{
			for(i=0 ; i<res_size ; ++i)
				array_of_ascii[i] = array_of_result[i];
		}

		for(i=0; i<res_size ; ++i)
		{
			array_of_ascii[i] = prime(array_of_ascii[i]);
		}

		size = res_size;
		res_size /= 2;
		if(res_size % 2 != 0)
			++res_size;

		count=0;
	}
	while(size > 2);

	cout<<"Message digest:";
	
	int m=0;
	while( m < 2 )
	{
		if(int(array_of_result[m]) == 32)
			cout<<"Space";
		else if(int(array_of_result[m]) == 0)
			cout<<"NULL";
		else
			cout<<array_of_result[m];
		
		if(m == 0)
			cout<<",";
		else 
			cout<<"\n";

		++m;
	}

	m=0;
	for(; m<2 ; ++m)
	{
		if(int(array_of_result[m]) == 32)
			cout<<"Space = ";
		else if(int(array_of_result[m]) == 0)
			cout<<"NULL = ";
		else
			cout<<array_of_result[m]<<" = ";
		
		cout<<unsigned int(array_of_result[m]);
		
		if(m==0)
			cout<<" , ";
		else
			cout<<"\n";
	}
}



