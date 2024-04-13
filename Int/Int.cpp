#include "Int.h"

/* set get����*/
void Int::set_no1_(strInt* no1)
{
	this->no1 = no1;
}//set_no1_(strInt* no1)
Int::strInt* Int::get_no1_()
{
	return this->no1;
}//get_no1_()

void Int::set_noHead_(strInt* noHead)
{
	this->noHead = noHead;
}//set_noHead_(strInt* noHead)
Int::strInt* Int::get_noHead_()
{
	return this->noHead;
}//get_noHead_

void Int::set_noNum_(const unsigned int& noNum)
{
	this->noNum = noNum;
}//set_noNum_(const unsigned int& noNum)
unsigned int Int::get_noNum_()
{
	return this->noNum;
}//get_noNum_()

void Int::set_sign_(const bool& sign)
{
	this->sign = sign;
}//set_sign_(const bool& sign)
bool Int::get_sign_()
{
	return this->sign;
}//get_sign_()


/* ���� ���� */
Int::Int()
{
	this->init_();
}//Int()
Int::Int(const Int& obj)
{
	this->init_(obj);
}//Int(const Int& obj)
Int::Int(const int& x)
{
	this->init_(x);
}//Int(const int& x)
Int::~Int()
{
	int e = this->init_();
	//if (e) { cout << e << endl; }
}//~Int()


/* ��ʼ�� */
//��ʼ��Ϊ0
int Int::init_()
/*����ֵ < 0��ʾ�д���
**����ֵ >= 0��ʾ����*/
{
	if (this->no1 == NULL && this->noNum == 0) {
		return 1;//�������أ���Ϊ0�������ʼ��
	}
	else if (this->no1 && this->noNum) {
		if (this->noHead->no != this->noNum) {
			return -1;//����
		}

		strInt* curr = this->no1;

		for (unsigned int i = 1; i <= this->noNum; i++) {
			this->set_no1_(curr->next);
			delete curr;//�ͷ��ڴ�
			curr = this->no1;
		}
		this->set_no1_(NULL);
		this->set_noHead_(NULL);
		this->set_noNum_(0);
		this->set_sign_(0);
		return 0;//��������
	}
	else {
		return -2;//����
	}
}//init_()
//������ʼ��
int Int::init_(const Int& obj)
{
	int e = this->init_();
	if (e < 0) {
		return e;
	}

	//����Ϊ0 ֱ�ӷ���
	if (obj.noNum == 0) {
		return 0;
	}

	this->set_no1_(new(strInt));
	strInt* curr = this->no1;
	strInt* front = curr;
	strInt* objCurr = obj.no1;

	curr->no = objCurr->no;
	curr->num = objCurr->num;
	curr->prior = NULL;

	for (unsigned int i = 2; i <= obj.noNum; i++) {
		curr = new(strInt);
		objCurr = objCurr->next;
		curr->no = objCurr->no;
		curr->num = objCurr->num;
		curr->prior = front;
		front->next = curr;
		front = curr;
	}
	curr->next = NULL;
	this->set_noHead_(curr);
	this->set_noNum_(obj.noNum);
	this->set_sign_(obj.sign);

	return 0;
}//init_(const Int& obj)
//����int��ʼ��
int Int::init_(const int& x)
{
	int e = this->init_();
	if (e < 0) {
		return e;
	}

	unsigned int u_x = x;
	if (x == 0) {
		return 0;
	}
	else if (x < 0) {
		this->set_sign_(1);
		u_x = abs(x);
	}
	else {
		this->set_sign_(0);
	}

	this->set_noNum_(1);
	this->set_no1_(new(strInt));
	this->no1->no = 1;
	this->no1->num = u_x % (unsigned int)pow(10, 9);
	this->no1->prior = NULL;
	this->no1->next = NULL;
	this->set_noHead_(this->no1);

	if (u_x / (unsigned int)pow(10, 9)) {
		this->set_noNum_(2);
		strInt* temp = new(strInt);
		temp->no = 2;
		temp->num = u_x / (unsigned int)pow(10, 9);
		this->no1->next = temp;
		temp->prior = this->no1;
		temp->next = NULL;
		this->set_noHead_(temp);
	}

	return 0;
}//init_(const int& x)


/* ��ϵ���� */
/* ���� == */
//��this�������� ����1�� ���򷵻�0
bool Int::equal_(const Int& obj)
{
	if (this->noNum != obj.noNum) {
		return 0;
	}
	if (this->noNum == 0) {
		return 1;
	}
	if (this->sign != obj.sign) {
		return 0;
	}

	strInt* curr = this->no1;
	strInt* objCurr = obj.no1;

	for (unsigned int i = 1; i <= this->noNum; i++) {

		if (curr->num != objCurr->num) {
			return 0;
		}

		curr = curr->next;
		objCurr = objCurr->next;
	}

	return 1;
}//equal_(const Int& obj)
bool Int::equal_(const int& x)
{
	Int obj(x);//��������

	bool e = this->equal_(obj);

	obj.init_();//�ͷſռ�

	return e;
}//equal_(const int& x)

/* ������ != */
//��this���������� ����1�� ���򷵻�0
bool Int::not_equal_(const Int& obj)
{
	if (this->equal_(obj)) {
		return 0;
	}
	else {
		return 1;
	}
}//not_equal_(const Int& obj)
bool Int::not_equal_(const int& x)
{
	if (this->equal_(x)) {
		return 0;
	}
	else {
		return 1;
	}
}//not_equal_(const int& x)

/* ���� > */
//��this���ڲ��� ����1�� ���򷵻�0
bool Int::greater_(const Int& obj)
{
	if ((obj.sign == 0 && this->sign == 1) || (this->noNum == 0 && obj.noNum == 0)) {
		return 0;
	}
	else if (this->sign == 0 && obj.sign == 1) {
		return 1;
	}
	else if (this->noNum == obj.noNum) {

		strInt* curr = this->noHead;
		strInt* objCurr = obj.noHead;

		if (this->sign == 0) {
			for (unsigned int i = this->noNum; i >= 1; i--) {
				if (curr->num > objCurr->num) {
					return 1;
				}
			}
		}
		else {//this->sign == 1
			for (unsigned int i = this->noNum; i >= 1; i--) {
				if (curr->num < objCurr->num) {
					return 1;
				}
			}
		}

		return 0;
	}
	else {
		if (this->sign == 0) {
			return this->noNum > obj.noNum ? 1 : 0;
		}
		else {//this->sign == 1
			return this->noNum < obj.noNum ? 1 : 0;
		}
	}
}//greater_(const Int& obj)
bool Int::greater_(const int& x)
{
	Int obj(x);//��������

	bool e = this->greater_(obj);

	obj.init_();//�ͷſռ�

	return e;
}//greater_(const int& x)

/* ���ڵ��� >= */
//��this���ڻ���ڲ��� ����1�� ���򷵻�0
bool Int::greater_or_equal_(const Int& obj)
{
	if (this->less_(obj)) {
		return 0;
	}
	else {
		return 1;
	}
}//greater_or_equal_(const Int& obj)
bool Int::greater_or_equal_(const int& x)
{
	if (this->less_(x)) {
		return 0;
	}
	else {
		return 1;
	}
}//greater_or_equal_(const int& x)

/* С�� < */
//��thisС�ڲ��� ����1�� ���򷵻�0
bool Int::less_(const Int& obj)
{
	if ((this->sign == 0 && obj.sign == 1) || (this->noNum == 0 && obj.noNum == 0)) {
		return 0;
	}
	else if (obj.sign == 0 && this->sign == 1) {
		return 1;
	}
	else if (this->noNum == obj.noNum) {

		strInt* curr = this->noHead;
		strInt* objCurr = obj.noHead;

		if (this->sign == 0) {
			for (unsigned int i = this->noNum; i >= 1; i--) {
				if (curr->num < objCurr->num) {
					return 1;
				}
			}
		}
		else {//this->sign == 1
			for (unsigned int i = this->noNum; i >= 1; i--) {
				if (curr->num > objCurr->num) {
					return 1;
				}
			}
		}

		return 0;
	}
	else {
		if (this->sign == 0) {
			return this->noNum < obj.noNum ? 1 : 0;
		}
		else {//this->sign == 1
			return this->noNum > obj.noNum ? 1 : 0;
		}
	}
}//less_(const Int& obj)
bool Int::less_(const int& x)
{
	Int obj(x);//��������

	bool e = this->less_(obj);

	obj.init_();//�ͷſռ�

	return e;
}//less_(const int& x)

/* С�ڵ��� <= */
//��thisС�ڻ���ڲ��� ����1�� ���򷵻�0
bool Int::less_or_equal_(const Int& obj)
{
	if (this->greater_(obj)) {
		return 0;
	}
	else {
		return 1;
	}
}//less_or_equal_(const Int& obj)
bool Int::less_or_equal_(const int& x)
{
	if (this->greater_(x)) {
		return 0;
	}
	else {
		return 1;
	}
}//less_or_equal_(const int& x)


/* �������� */
/* �� + */
//obj = objA + objB
int Int::add_(Int& obj, const Int& objA, const Int& objB)//��������
{
	//������ʱ����
	Int objBackA(objA);
	Int objBackB(objB);

	//obj��ʼ��
	obj.init_();

	unsigned int carry = 0;//��λ
	strInt* curr = obj.no1;//��ǰλ
	strInt* currA = objBackA.no1;//
	strInt* currB = objBackB.no1;//
	strInt* front = curr;//ǰһλ
	strInt* frontA = currA;//
	strInt* frontB = currB;//

	//ȡ�������� λ����� λ��
	unsigned int maxNum = objBackA.noNum > objBackB.noNum ? objBackA.noNum : objBackB.noNum;

	//����
	//����������ͬ
	if (objBackA.sign == objBackB.sign) {

		//�������
		obj.set_sign_(objBackA.sign);

		//��ǰ����i��λ����ӣ�
		for (unsigned int i = 1; i <= maxNum || carry; i++) {

			curr = new(strInt);
			curr->no = i;
			curr->num = 0;//��ǰλ��� ��������
			curr->prior = front;
			if (front) { front->next = curr; }
			curr->next = NULL;

			if (i == 1) { obj.set_no1_(curr); }
			obj.set_noHead_(curr);
			obj.set_noNum_(i);


			unsigned int temp = (currA ? currA->num : 0) + (currB ? currB->num : 0) + carry;//����
			curr->num = temp % (unsigned int)pow(10, 9);
			carry = temp / (unsigned int)pow(10, 9);


			front = curr;
			curr = curr->next;
			if (currA) {
				frontA = currA;
				currA = currA->next;
			}
			if (currB) {
				frontB = currB;
				currB = currB->next;
			}
		}
	}
	//�������Ų�ͬ
	else {

		//�������
		if (objBackA.noNum > objBackB.noNum || (objBackA.noNum == objBackB.noNum && objBackA.noHead->num > objBackB.noHead->num)) {
			obj.set_sign_(objBackA.sign);
		}
		else {
			obj.set_sign_(objBackB.sign);
		}


		//ȡ����ֵ
		objBackA.set_sign_(0);
		objBackB.set_sign_(0);

		if (objBackA.greater_(objBackB)) {
			//��ǰ����i��λ�������
			for (unsigned int i = 1; i <= maxNum || carry; i++) {

				curr = new(strInt);
				curr->no = i;
				curr->num = 0;//��ǰλ��� ��������
				curr->prior = front;
				if (front) { front->next = curr; }
				curr->next = NULL;

				if (i == 1) { obj.set_no1_(curr); }
				obj.set_noHead_(curr);
				obj.set_noNum_(i);


				int temp = currA->num - carry - (currB ? currB->num : 0);//����
				if (temp < 0) {
					carry = 1;
					curr->num = temp + (int)pow(10, 9);
				}
				else {
					carry = 0;
					curr->num = temp;
				}


				front = curr;
				curr = curr->next;
				frontA = currA;
				currA = currA->next;
				if (currB) {
					frontB = currB;
					currB = currB->next;
				}
			}
		}
		else {//objBackA С�ڵ��� objBackB
			//��ǰ����i��λ�������
			for (unsigned int i = 1; i <= maxNum || carry; i++) {

				curr = new(strInt);
				curr->no = i;
				curr->num = 0;//��ǰλ��� ��������
				curr->prior = front;
				if (front) { front->next = curr; }
				curr->next = NULL;

				if (i == 1) { obj.set_no1_(curr); }
				obj.set_noHead_(curr);
				obj.set_noNum_(i);


				int temp = currB->num - carry - (currA ? currA->num : 0);//����
				if (temp < 0) {
					carry = 1;
					curr->num = temp + (int)pow(10, 9);
				}
				else {
					carry = 0;
					curr->num = temp;
				}


				front = curr;
				curr = curr->next;
				if (currA) {
					frontA = currA;
					currA = currA->next;
				}
				frontB = currB;
				currB = currB->next;
			}
		}


		//�������Ų�ͬ��������ɾ��ǰ��Ŀ�λ
		for (unsigned int i = obj.noNum; i >= 1; i--) {
			if (obj.noHead->num == 0) {
				if (i == 1) {
					obj.init_();
					break;
				}

				curr = obj.noHead;
				obj.set_noHead_(curr->prior);
				delete curr;
				obj.noHead->next = NULL;

				obj.set_noNum_(obj.noNum - 1);
			}
			else {
				break;
			}
		}
	}

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return 0;
}//add_(Int& obj, const Int& objA, const Int& objB)
int Int::add_(Int& obj, const Int& objA, const int& b)
{
	//������ʱ����
	Int objBackA(objA);
	Int objBackB(b);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::add_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//add_(Int& obj, const Int& objA, const int& b)
int Int::add_(Int& obj, const int& a, const Int& objB)
{
	//������ʱ����
	Int objBackA(a);
	Int objBackB(objB);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::add_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//add_(Int& obj, const int& a, const Int& objB)
int Int::add_(Int& obj, const int& a, const int& b)
{
	//������ʱ����
	Int objBackA(a);
	Int objBackB(b);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::add_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//add_(Int& obj, const int& a, const int& b)
//�ӵ��� +=
int Int::add_(const Int& obj)
{
	return Int::add_(*this, *this, obj);
}//add_(const Int& obj)
int Int::add_(const int& x)
{
	return Int::add_(*this, *this, x);
}//add_(const int& x)

/* �� - */
//obj = objA - objB
int Int::sub_(Int& obj, const Int& objA, const Int& objB)
{
	//������ʱ���󣨼���ȡ�෴����
	Int objBackA(objA);
	Int objBackB(objB);
	objBackB.set_sign_(!objBackB.sign);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::add_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//sub_(Int& obj, const Int& objA, const Int& objB)
int Int::sub_(Int& obj, const Int& objA, const int& b)
{
	//������ʱ���󣨼���ȡ�෴����
	Int objBackA(objA);
	Int objBackB(b);
	objBackB.set_sign_(!objBackB.sign);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::add_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//int sub_(Int& obj, const Int& objA, const int& b)
int Int::sub_(Int& obj, const int& a, const Int& objB)
{
	//������ʱ���󣨼���ȡ�෴����
	Int objBackA(a);
	Int objBackB(objB);
	objBackB.set_sign_(!objBackB.sign);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::add_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//sub_(Int& obj, const int& a, const Int& objB)
int Int::sub_(Int& obj, const int& a, const int& b)
{
	//������ʱ���󣨼���ȡ�෴����
	Int objBackA(a);
	Int objBackB(b);
	objBackB.set_sign_(!objBackB.sign);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::add_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//sub_(Int& obj, const int& a, const int& b)
//������ -=
int Int::sub_(const Int& obj)
{
	return Int::sub_(*this, *this, obj);
}//sub_(const Int& obj)
int Int::sub_(const int& x)
{
	return Int::sub_(*this, *this, x);
}//sub_(const int& x)

/* �� * */
//obj = objA * objB
int Int::mul_(Int& obj, const Int& objA, const Int& objB)
{
	//������ʱ����
	Int i(1);//��������
	Int objBackA(objA);
	Int objBackB(objB);
	objBackA.set_sign_(0);
	objBackB.set_sign_(0);

	//obj��ʼ��
	obj.init_();

	//�������
	if (objA.sign == objB.sign) {
		obj.set_sign_(0);
	}
	else {
		obj.set_sign_(1);
	}

	//����
	if (objBackA.not_equal_(0)) {
		for (; i.less_or_equal_(objBackB); i.add_(1)) {
			obj.add_(objBackA);
		}
	}

	//�ͷſռ�
	i.init_();
	objBackA.init_();
	objBackB.init_();

	return 0;
}//mul_(Int& obj, const Int& objA, const Int& objB)
int Int::mul_(Int& obj, const Int& objA, const int& b)
{
	//������ʱ����
	Int objBackA(objA);
	Int objBackB(b);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::mul_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//mul_(Int& obj, const Int& objA, const int& b)
int Int::mul_(Int& obj, const int& a, const Int& objB)
{
	//������ʱ����
	Int objBackA(a);
	Int objBackB(objB);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::mul_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//mul_(Int& obj, const int& a, const Int& objB)
int Int::mul_(Int& obj, const int& a, const int& b)
{
	//������ʱ����
	Int objBackA(a);
	Int objBackB(b);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::mul_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//mul_(Int& obj, const int& a, const int& b)
//�˵��� *=
int Int::mul_(const Int& obj)
{
	return Int::mul_(*this, *this, obj);
}//mul_(const Int& obj)
int Int::mul_(const int& x)
{
	return Int::mul_(*this, *this, x);
}//mul_(const int& x)

/* ���� / */
//obj = objA / objB  �����0ȡ��
int Int::div_(Int& obj, const Int& objA, const Int& objB)
{
	//������ʱ����
	Int objBackA(objA);
	Int objBackB(objB);
	objBackA.set_sign_(0);
	objBackB.set_sign_(0);

	//obj��ʼ��
	obj.init_();

	//�������
	if (objA.sign == objB.sign) {
		obj.set_sign_(0);
	}
	else {
		obj.set_sign_(1);
	}

	//����
	for (; objBackA.greater_or_equal_(objBackB); obj.add_(1)) {
		objBackA.sub_(objBackB);
	}

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return 0;
}//div_(Int& obj, const Int& objA, const Int& objB)
int Int::div_(Int& obj, const Int& objA, const int& b)
{
	//������ʱ����
	Int objBackA(objA);
	Int objBackB(b);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::div_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//div_(Int& obj, const Int& objA, const int& b)
int Int::div_(Int& obj, const int& a, const Int& objB)
{
	//������ʱ����
	Int objBackA(a);
	Int objBackB(objB);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::div_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//div_(Int& obj, const int& a, const Int& objB)
int Int::div_(Int& obj, const int& a, const int& b)
{
	//������ʱ����
	Int objBackA(a);
	Int objBackB(b);

	//obj��ʼ��
	obj.init_();

	//����
	int e = Int::div_(obj, objBackA, objBackB);

	//�ͷſռ�
	objBackA.init_();
	objBackB.init_();

	return e;
}//div_(Int& obj, const int& a, const int& b)
//�������� /=
int Int::div_(const Int& obj)
{
	return Int::div_(*this, *this, obj);
}//div_(const Int& obj)
int Int::div_(const int& x)
{
	return Int::div_(*this, *this, x);
}//div_(const int& x)


/* �������� */
//��ӡ
void Int::print_()
{
	if (this->sign) {
		cout << "-";
	}

	strInt* curr = this->noHead;

	for (unsigned int i = this->noNum; i >= 1; i--) {
		if (i == this->noNum) {
			cout << curr->num << ",";////////////////���ſ���ȥ��
		}
		else {
			printf("%09u,", curr->num);///////////////���ſ���ȥ��
		}
		curr = curr->prior;
	}
}
