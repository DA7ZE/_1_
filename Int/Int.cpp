#include "Int.h"

/* set get方法*/
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


/* 构造 析构 */
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


/* 初始化 */
//初始化为0
int Int::init_()
/*返回值 < 0表示有错误
**返回值 >= 0表示正常*/
{
	if (this->no1 == NULL && this->noNum == 0) {
		return 1;//正常返回：已为0，无需初始化
	}
	else if (this->no1 && this->noNum) {
		if (this->noHead->no != this->noNum) {
			return -1;//错误
		}

		strInt* curr = this->no1;

		for (unsigned int i = 1; i <= this->noNum; i++) {
			this->set_no1_(curr->next);
			delete curr;//释放内存
			curr = this->no1;
		}
		this->set_no1_(NULL);
		this->set_noHead_(NULL);
		this->set_noNum_(0);
		this->set_sign_(0);
		return 0;//正常返回
	}
	else {
		return -2;//错误
	}
}//init_()
//拷贝初始化
int Int::init_(const Int& obj)
{
	int e = this->init_();
	if (e < 0) {
		return e;
	}

	//参数为0 直接返回
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
//参数int初始化
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


/* 关系运算 */
/* 等于 == */
//若this与参数相等 返回1， 否则返回0
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
	Int obj(x);//创建对象

	bool e = this->equal_(obj);

	obj.init_();//释放空间

	return e;
}//equal_(const int& x)

/* 不等于 != */
//若this与参数不相等 返回1， 否则返回0
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

/* 大于 > */
//若this大于参数 返回1， 否则返回0
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
	Int obj(x);//创建对象

	bool e = this->greater_(obj);

	obj.init_();//释放空间

	return e;
}//greater_(const int& x)

/* 大于等于 >= */
//若this大于或等于参数 返回1， 否则返回0
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

/* 小于 < */
//若this小于参数 返回1， 否则返回0
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
	Int obj(x);//创建对象

	bool e = this->less_(obj);

	obj.init_();//释放空间

	return e;
}//less_(const int& x)

/* 小于等于 <= */
//若this小于或等于参数 返回1， 否则返回0
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


/* 算术运算 */
/* 加 + */
//obj = objA + objB
int Int::add_(Int& obj, const Int& objA, const Int& objB)//基础方法
{
	//创建临时对象
	Int objBackA(objA);
	Int objBackB(objB);

	//obj初始化
	obj.init_();

	unsigned int carry = 0;//进位
	strInt* curr = obj.no1;//当前位
	strInt* currA = objBackA.no1;//
	strInt* currB = objBackB.no1;//
	strInt* front = curr;//前一位
	strInt* frontA = currA;//
	strInt* frontB = currB;//

	//取两加数中 位数大的 位数
	unsigned int maxNum = objBackA.noNum > objBackB.noNum ? objBackA.noNum : objBackB.noNum;

	//计算
	//两数符号相同
	if (objBackA.sign == objBackB.sign) {

		//计算符号
		obj.set_sign_(objBackA.sign);

		//当前计算i号位（相加）
		for (unsigned int i = 1; i <= maxNum || carry; i++) {

			curr = new(strInt);
			curr->no = i;
			curr->num = 0;//当前位结果 即将计算
			curr->prior = front;
			if (front) { front->next = curr; }
			curr->next = NULL;

			if (i == 1) { obj.set_no1_(curr); }
			obj.set_noHead_(curr);
			obj.set_noNum_(i);


			unsigned int temp = (currA ? currA->num : 0) + (currB ? currB->num : 0) + carry;//计算
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
	//两数符号不同
	else {

		//计算符号
		if (objBackA.noNum > objBackB.noNum || (objBackA.noNum == objBackB.noNum && objBackA.noHead->num > objBackB.noHead->num)) {
			obj.set_sign_(objBackA.sign);
		}
		else {
			obj.set_sign_(objBackB.sign);
		}


		//取绝对值
		objBackA.set_sign_(0);
		objBackB.set_sign_(0);

		if (objBackA.greater_(objBackB)) {
			//当前计算i号位（相减）
			for (unsigned int i = 1; i <= maxNum || carry; i++) {

				curr = new(strInt);
				curr->no = i;
				curr->num = 0;//当前位结果 即将计算
				curr->prior = front;
				if (front) { front->next = curr; }
				curr->next = NULL;

				if (i == 1) { obj.set_no1_(curr); }
				obj.set_noHead_(curr);
				obj.set_noNum_(i);


				int temp = currA->num - carry - (currB ? currB->num : 0);//计算
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
		else {//objBackA 小于等于 objBackB
			//当前计算i号位（相减）
			for (unsigned int i = 1; i <= maxNum || carry; i++) {

				curr = new(strInt);
				curr->no = i;
				curr->num = 0;//当前位结果 即将计算
				curr->prior = front;
				if (front) { front->next = curr; }
				curr->next = NULL;

				if (i == 1) { obj.set_no1_(curr); }
				obj.set_noHead_(curr);
				obj.set_noNum_(i);


				int temp = currB->num - carry - (currA ? currA->num : 0);//计算
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


		//两数符号不同，计算结果删除前面的空位
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

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return 0;
}//add_(Int& obj, const Int& objA, const Int& objB)
int Int::add_(Int& obj, const Int& objA, const int& b)
{
	//创建临时对象
	Int objBackA(objA);
	Int objBackB(b);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::add_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//add_(Int& obj, const Int& objA, const int& b)
int Int::add_(Int& obj, const int& a, const Int& objB)
{
	//创建临时对象
	Int objBackA(a);
	Int objBackB(objB);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::add_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//add_(Int& obj, const int& a, const Int& objB)
int Int::add_(Int& obj, const int& a, const int& b)
{
	//创建临时对象
	Int objBackA(a);
	Int objBackB(b);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::add_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//add_(Int& obj, const int& a, const int& b)
//加等于 +=
int Int::add_(const Int& obj)
{
	return Int::add_(*this, *this, obj);
}//add_(const Int& obj)
int Int::add_(const int& x)
{
	return Int::add_(*this, *this, x);
}//add_(const int& x)

/* 减 - */
//obj = objA - objB
int Int::sub_(Int& obj, const Int& objA, const Int& objB)
{
	//创建临时对象（减数取相反数）
	Int objBackA(objA);
	Int objBackB(objB);
	objBackB.set_sign_(!objBackB.sign);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::add_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//sub_(Int& obj, const Int& objA, const Int& objB)
int Int::sub_(Int& obj, const Int& objA, const int& b)
{
	//创建临时对象（减数取相反数）
	Int objBackA(objA);
	Int objBackB(b);
	objBackB.set_sign_(!objBackB.sign);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::add_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//int sub_(Int& obj, const Int& objA, const int& b)
int Int::sub_(Int& obj, const int& a, const Int& objB)
{
	//创建临时对象（减数取相反数）
	Int objBackA(a);
	Int objBackB(objB);
	objBackB.set_sign_(!objBackB.sign);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::add_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//sub_(Int& obj, const int& a, const Int& objB)
int Int::sub_(Int& obj, const int& a, const int& b)
{
	//创建临时对象（减数取相反数）
	Int objBackA(a);
	Int objBackB(b);
	objBackB.set_sign_(!objBackB.sign);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::add_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//sub_(Int& obj, const int& a, const int& b)
//减等于 -=
int Int::sub_(const Int& obj)
{
	return Int::sub_(*this, *this, obj);
}//sub_(const Int& obj)
int Int::sub_(const int& x)
{
	return Int::sub_(*this, *this, x);
}//sub_(const int& x)

/* 乘 * */
//obj = objA * objB
int Int::mul_(Int& obj, const Int& objA, const Int& objB)
{
	//创建临时对象
	Int i(1);//索引变量
	Int objBackA(objA);
	Int objBackB(objB);
	objBackA.set_sign_(0);
	objBackB.set_sign_(0);

	//obj初始化
	obj.init_();

	//计算符号
	if (objA.sign == objB.sign) {
		obj.set_sign_(0);
	}
	else {
		obj.set_sign_(1);
	}

	//计算
	if (objBackA.not_equal_(0)) {
		for (; i.less_or_equal_(objBackB); i.add_(1)) {
			obj.add_(objBackA);
		}
	}

	//释放空间
	i.init_();
	objBackA.init_();
	objBackB.init_();

	return 0;
}//mul_(Int& obj, const Int& objA, const Int& objB)
int Int::mul_(Int& obj, const Int& objA, const int& b)
{
	//创建临时对象
	Int objBackA(objA);
	Int objBackB(b);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::mul_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//mul_(Int& obj, const Int& objA, const int& b)
int Int::mul_(Int& obj, const int& a, const Int& objB)
{
	//创建临时对象
	Int objBackA(a);
	Int objBackB(objB);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::mul_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//mul_(Int& obj, const int& a, const Int& objB)
int Int::mul_(Int& obj, const int& a, const int& b)
{
	//创建临时对象
	Int objBackA(a);
	Int objBackB(b);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::mul_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//mul_(Int& obj, const int& a, const int& b)
//乘等于 *=
int Int::mul_(const Int& obj)
{
	return Int::mul_(*this, *this, obj);
}//mul_(const Int& obj)
int Int::mul_(const int& x)
{
	return Int::mul_(*this, *this, x);
}//mul_(const int& x)

/* 整除 / */
//obj = objA / objB  结果向0取整
int Int::div_(Int& obj, const Int& objA, const Int& objB)
{
	//创建临时对象
	Int objBackA(objA);
	Int objBackB(objB);
	objBackA.set_sign_(0);
	objBackB.set_sign_(0);

	//obj初始化
	obj.init_();

	//计算符号
	if (objA.sign == objB.sign) {
		obj.set_sign_(0);
	}
	else {
		obj.set_sign_(1);
	}

	//计算
	for (; objBackA.greater_or_equal_(objBackB); obj.add_(1)) {
		objBackA.sub_(objBackB);
	}

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return 0;
}//div_(Int& obj, const Int& objA, const Int& objB)
int Int::div_(Int& obj, const Int& objA, const int& b)
{
	//创建临时对象
	Int objBackA(objA);
	Int objBackB(b);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::div_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//div_(Int& obj, const Int& objA, const int& b)
int Int::div_(Int& obj, const int& a, const Int& objB)
{
	//创建临时对象
	Int objBackA(a);
	Int objBackB(objB);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::div_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//div_(Int& obj, const int& a, const Int& objB)
int Int::div_(Int& obj, const int& a, const int& b)
{
	//创建临时对象
	Int objBackA(a);
	Int objBackB(b);

	//obj初始化
	obj.init_();

	//计算
	int e = Int::div_(obj, objBackA, objBackB);

	//释放空间
	objBackA.init_();
	objBackB.init_();

	return e;
}//div_(Int& obj, const int& a, const int& b)
//整除等于 /=
int Int::div_(const Int& obj)
{
	return Int::div_(*this, *this, obj);
}//div_(const Int& obj)
int Int::div_(const int& x)
{
	return Int::div_(*this, *this, x);
}//div_(const int& x)


/* 其它方法 */
//打印
void Int::print_()
{
	if (this->sign) {
		cout << "-";
	}

	strInt* curr = this->noHead;

	for (unsigned int i = this->noNum; i >= 1; i--) {
		if (i == this->noNum) {
			cout << curr->num << ",";////////////////逗号可以去掉
		}
		else {
			printf("%09u,", curr->num);///////////////逗号可以去掉
		}
		curr = curr->prior;
	}
}
