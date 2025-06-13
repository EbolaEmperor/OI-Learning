/***************************************************************
 *
 * 这是一个利用高精度分数运算库
 * 运算效率较低，但能保证绝对精确的运算，可用于理论研究
 * 依赖于：bigint.h
 * 
 * copyright © 2022 Wenchong Huang, All rights reserved.
 *
 **************************************************************/

#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <iostream>
#include <cstring>
#include "bigint.h"

class fraction{
private:
	bigint a,b;
public:
	fraction(){a=0;b=1;}
	fraction(const int &_a){a=_a;b=1;}
	fraction(const int &_a, const int &_b){a=_a;b=_b;}
	fraction(const bigint &_a){a=_a;b=1;}
	fraction(const bigint &_a, const bigint &_b){a=_a;b=_b;}
	fraction(const fraction &rhs){a=rhs.a; b=rhs.b;}
	void simp(){
		if(b==0) {
			std::cerr << "fractional Eror!" << std::endl;
			exit(-1);
		}
		bigint g = gcd(a.abs(),b);
		a = a / g;
		b = b / g;
	}
    fraction & operator = (const fraction & rhs){
        fraction copy(rhs);
        std::swap(*this, copy);
        return *this;
    }
    fraction & operator = (fraction && rhs){
        std::swap(a, rhs.a);
		std::swap(b, rhs.b);
        return *this;
    }
	friend std::istream & operator >> (std::istream &in, fraction &x) {
        std::string s;
        in >> s;
        int i = s.find('/');
        x.a = bigint(s.substr(0,i));
        x.b = bigint(s.substr(i+1));
        return in;
	}
	friend std::ostream & operator << (std::ostream &out, const fraction &x) {
		if(x.b==1) out<<x.a;
		else out<<x.a<<'/'<<x.b;
		return out;
	}
    double to_double(){
        return a.todouble()/b.todouble();
    }
	bool operator == (const fraction &y) const{
		return ((*this)-y).a==0;
	}
	bool operator != (const fraction &y) const{
		return !(*this==y);
	}
	bool operator < (const fraction &y) const{
		return a*y.b<y.a*b;
	}
	bool operator > (const fraction &y) const{
		return a*y.b>y.a*b;
	}
	bool operator <= (const fraction &y) const{
		return !((*this)>y);
	}
	bool operator >= (const fraction &y) const{
		return !((*this)<y);
	}
	fraction operator * (const fraction &y) const{
		fraction c(a*y.a,b*y.b);
		c.simp();
		return c;
	}
	fraction operator / (const fraction &y) const{
		fraction c(a*y.b,b*y.a);
		c.simp();
		return c;
	}
	fraction operator + (const fraction &y) const{
		fraction c(a*y.b+y.a*b,b*y.b);
		c.simp();
		return c;
	}
	fraction operator - (const fraction &y) const{
		fraction c(a*y.b-y.a*b,b*y.b);
		c.simp();
		return c;
	}
	fraction operator - () const{
		return fraction(-a,b);
	}
	fraction operator *= (const fraction &y){
		return (*this)=(*this)*y;
	}
	fraction operator /= (const fraction &y){
		return (*this)=(*this)/y;
	}
	fraction operator += (const fraction &y){
		return (*this)=(*this)+y;
	}
	fraction operator -= (const fraction &y){
		return (*this)=(*this)-y;
	}
};

#endif