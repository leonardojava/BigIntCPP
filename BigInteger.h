#include <string>
#include <iostream>

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

struct ListNode{
    long long val;
    ListNode* next;
    ListNode* prev; 
}; 

class BigInteger{
    private:
        ListNode* head;
        ListNode* tail;
        std::string origin;
        int length;
        int sign;
        BigInteger(ListNode* head, ListNode* tail, int sign);
        BigInteger copy(const BigInteger& N) const;
        bool absLesser(const BigInteger& other) const;
    
    public:
        BigInteger(std::string s);
        BigInteger add(const BigInteger& N) const;
        BigInteger subtract(const BigInteger& N) const;
        BigInteger multiply(const BigInteger& N) const;
        std::string to_string();
        ~BigInteger();
};

#endif