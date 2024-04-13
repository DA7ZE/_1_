#include "head.h"

#ifndef __Int_H__
#define __Int_H__


class Int
{
private:
	//Int类 位结构
	typedef struct strInt
	{
		//Int类 位号（1~...）
		unsigned int no;
		//数值（1~999,999,999）
		unsigned int num;
		//上一位 地址
		strInt* prior;
		//下一位 地址
		strInt* next;
	}strInt;


private:
	//Int 1号位 地址
	strInt* no1;
	//Int 最高位 地址
	strInt* noHead;
	//Int 位数量
	unsigned int noNum;
	//正负位（0正， 1负）
	bool sign;


private:
	/* set get方法 */
	void set_no1_(strInt* no1);
	strInt* get_no1_();

	void set_noHead_(strInt* noHead);
	strInt* get_noHead_();

	void set_noNum_(const unsigned int& noNum);
	unsigned int get_noNum_();

	void set_sign_(const bool& sign);
	bool get_sign_();


public:
	/* 构造 析构 */
	Int();
	Int(const Int& obj);
	Int(const int& x);
	~Int();


public:
	/* 初始化 */
	//初始化为0
	int init_();//基础方法
	//拷贝初始化
	int init_(const Int& obj);//基础方法
	//int初始化
	int init_(const int& x);//基础方法


public:
	/* 关系运算 */
	/* 等于 == */
	//若this与参数相等 返回1， 否则返回0
	bool equal_(const Int& obj);//基础方法
	bool equal_(const int& x);

	/* 不等于 != */
	//若this与参数不相等 返回1， 否则返回0
	bool not_equal_(const Int& obj);
	bool not_equal_(const int& x);

	/* 大于 > */
	//若this大于参数 返回1， 否则返回0
	bool greater_(const Int& obj);//基础方法
	bool greater_(const int& x);

	/* 大于等于 >= */
	//若this大于或等于参数 返回1， 否则返回0
	bool greater_or_equal_(const Int& obj);
	bool greater_or_equal_(const int& x);

	/* 小于 < */
	//若this小于参数 返回1， 否则返回0
	bool less_(const Int& obj);//基础方法
	bool less_(const int& x);

	/* 小于等于 <= */
	//若this小于或等于参数 返回1， 否则返回0
	bool less_or_equal_(const Int& obj);
	bool less_or_equal_(const int& x);


public:
	/* 算术运算 */
	/* 加 + */
	//obj = objA + objB
	static int add_(Int& obj, const Int& objA, const Int& objB);
	static int add_(Int& obj, const Int& objA, const int& b);
	static int add_(Int& obj, const int& a, const Int& objB);
	static int add_(Int& obj, const int& a, const int& b);
	//加等于 +=
	int add_(const Int& obj);
	int add_(const int& x);

	/* 减 - */
	//obj = objA - objB
	static int sub_(Int& obj, const Int& objA, const Int& objB);
	static int sub_(Int& obj, const Int& objA, const int& b);
	static int sub_(Int& obj, const int& a, const Int& objB);
	static int sub_(Int& obj, const int& a, const int& b);
	//减等于 -=
	int sub_(const Int& obj);
	int sub_(const int& x);

	/* 乘 * */
	//obj = objA * objB
	static int mul_(Int& obj, const Int& objA, const Int& objB);
	static int mul_(Int& obj, const Int& objA, const int& b);
	static int mul_(Int& obj, const int& a, const Int& objB);
	static int mul_(Int& obj, const int& a, const int& b);
	//乘等于 *=
	int mul_(const Int& obj);
	int mul_(const int& x);

	/* 整除 / */
	//obj = objA / objB  结果向0取整
	static int div_(Int& obj, const Int& objA, const Int& objB);
	static int div_(Int& obj, const Int& objA, const int& b);
	static int div_(Int& obj, const int& a, const Int& objB);
	static int div_(Int& obj, const int& a, const int& b);
	//整除等于 /=
	int div_(const Int& obj);
	int div_(const int& x);



	////////////////////////////////////////
	//求模 mod （待实现）
	// /////////////////////////////////////
	//取余 rem （待实现）
	////////////////////////////////////////



	/* 其它方法 */
	//打印
	void print_();



};//Int



#endif //#ifndef __Int_H__