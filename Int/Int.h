#include "head.h"

#ifndef __Int_H__
#define __Int_H__


class Int
{
private:
	//Int�� λ�ṹ
	typedef struct strInt
	{
		//Int�� λ�ţ�1~...��
		unsigned int no;
		//��ֵ��1~999,999,999��
		unsigned int num;
		//��һλ ��ַ
		strInt* prior;
		//��һλ ��ַ
		strInt* next;
	}strInt;


private:
	//Int 1��λ ��ַ
	strInt* no1;
	//Int ���λ ��ַ
	strInt* noHead;
	//Int λ����
	unsigned int noNum;
	//����λ��0���� 1����
	bool sign;


private:
	/* set get���� */
	void set_no1_(strInt* no1);
	strInt* get_no1_();

	void set_noHead_(strInt* noHead);
	strInt* get_noHead_();

	void set_noNum_(const unsigned int& noNum);
	unsigned int get_noNum_();

	void set_sign_(const bool& sign);
	bool get_sign_();


public:
	/* ���� ���� */
	Int();
	Int(const Int& obj);
	Int(const int& x);
	~Int();


public:
	/* ��ʼ�� */
	//��ʼ��Ϊ0
	int init_();//��������
	//������ʼ��
	int init_(const Int& obj);//��������
	//int��ʼ��
	int init_(const int& x);//��������


public:
	/* ��ϵ���� */
	/* ���� == */
	//��this�������� ����1�� ���򷵻�0
	bool equal_(const Int& obj);//��������
	bool equal_(const int& x);

	/* ������ != */
	//��this���������� ����1�� ���򷵻�0
	bool not_equal_(const Int& obj);
	bool not_equal_(const int& x);

	/* ���� > */
	//��this���ڲ��� ����1�� ���򷵻�0
	bool greater_(const Int& obj);//��������
	bool greater_(const int& x);

	/* ���ڵ��� >= */
	//��this���ڻ���ڲ��� ����1�� ���򷵻�0
	bool greater_or_equal_(const Int& obj);
	bool greater_or_equal_(const int& x);

	/* С�� < */
	//��thisС�ڲ��� ����1�� ���򷵻�0
	bool less_(const Int& obj);//��������
	bool less_(const int& x);

	/* С�ڵ��� <= */
	//��thisС�ڻ���ڲ��� ����1�� ���򷵻�0
	bool less_or_equal_(const Int& obj);
	bool less_or_equal_(const int& x);


public:
	/* �������� */
	/* �� + */
	//obj = objA + objB
	static int add_(Int& obj, const Int& objA, const Int& objB);
	static int add_(Int& obj, const Int& objA, const int& b);
	static int add_(Int& obj, const int& a, const Int& objB);
	static int add_(Int& obj, const int& a, const int& b);
	//�ӵ��� +=
	int add_(const Int& obj);
	int add_(const int& x);

	/* �� - */
	//obj = objA - objB
	static int sub_(Int& obj, const Int& objA, const Int& objB);
	static int sub_(Int& obj, const Int& objA, const int& b);
	static int sub_(Int& obj, const int& a, const Int& objB);
	static int sub_(Int& obj, const int& a, const int& b);
	//������ -=
	int sub_(const Int& obj);
	int sub_(const int& x);

	/* �� * */
	//obj = objA * objB
	static int mul_(Int& obj, const Int& objA, const Int& objB);
	static int mul_(Int& obj, const Int& objA, const int& b);
	static int mul_(Int& obj, const int& a, const Int& objB);
	static int mul_(Int& obj, const int& a, const int& b);
	//�˵��� *=
	int mul_(const Int& obj);
	int mul_(const int& x);

	/* ���� / */
	//obj = objA / objB  �����0ȡ��
	static int div_(Int& obj, const Int& objA, const Int& objB);
	static int div_(Int& obj, const Int& objA, const int& b);
	static int div_(Int& obj, const int& a, const Int& objB);
	static int div_(Int& obj, const int& a, const int& b);
	//�������� /=
	int div_(const Int& obj);
	int div_(const int& x);



	////////////////////////////////////////
	//��ģ mod ����ʵ�֣�
	// /////////////////////////////////////
	//ȡ�� rem ����ʵ�֣�
	////////////////////////////////////////



	/* �������� */
	//��ӡ
	void print_();



};//Int



#endif //#ifndef __Int_H__