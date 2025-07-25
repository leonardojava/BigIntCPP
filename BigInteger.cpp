#include <string>
#include <cmath>
#include <iostream>
#include <cassert>
struct ListNode{
    long val;
    ListNode* next ;
    ListNode* prev; 
}; 

class BigInteger{
    private:
        ListNode* head;
        ListNode* tail;
        std::string origin;
        int length;
        int sign;
        int p = 3;
        int max_powa = pow(10,p);
        BigInteger(ListNode* head, ListNode* tail, int sign){
            this->head = head;
            this->tail = tail;
            this->sign = sign;
        }
        BigInteger copy(const BigInteger& N) const{
            int sign = N.sign;
            ListNode* dummy = new ListNode();
            ListNode* head = dummy;
            ListNode* curr = N.tail;
            while(curr != nullptr){
                ListNode* new_node = new ListNode();
                new_node->val = curr->val;
                new_node->next = head;
                head->prev = new_node;
                head = new_node;
                curr = curr->prev;
            }
            ListNode* real_tail = dummy->prev;
            real_tail->next = nullptr;
            dummy->prev = nullptr;
            delete dummy;
            BigInteger res = BigInteger(head, real_tail, sign);
            res.origin = N.origin;
            res.length = N.length;
            return res;
        }
    public:
        BigInteger(std::string s){
            // Initialize pointers
            
            this->origin = s;
            this->head = nullptr;
            this->tail = nullptr;  
            this->length = 0;
            if(s == "0"){
                ListNode* zero = new ListNode();
                zero->val = 0;
                this->head = zero;
                this->tail = zero;
                this->sign = 1;
                return;
            }
            int start_idx = 0;
            char first = s[0];
            if(first == '-' || first == '+'){
                this->sign = first == '-' ? -1 : 1;
                start_idx = 1;
            } else {
                this->sign = 1;
            }
            
            long curr = 0;
            int curr_pow = 1;
            for(int i = s.length() - 1; i >= start_idx; i--){
                curr += (s[i] - '0') * curr_pow;
                curr_pow *= 10;
                if(curr_pow == this->max_powa){
                    ListNode* new_node = new ListNode();
                    this->length++;
                    new_node->val = curr;
                    new_node->next = nullptr;
                    new_node->prev = nullptr;
                    curr = 0;
                    curr_pow = 1;
                    if(head == nullptr){
                        this->head = new_node;
                        this->tail = new_node;
                    }
                    else{
                        this->head->prev = new_node;
                        new_node->next = this->head;
                        this->head = new_node;
                    }
                }
                
            }
            if(curr != 0){
                
                ListNode* new_node = new ListNode();
                this->length++;
                new_node->val = curr;
                new_node->next = nullptr;
                new_node->prev = nullptr;
                
                if(head == nullptr){
                    this->head = new_node;
                    this->tail = new_node;
                }
                else{
                    this->head->prev = new_node;
                    new_node->next = this->head;
                    this->head = new_node;
                }
            }

        }
        bool absLesser(const BigInteger& other) const {
            if(this->length != other.length) return this->origin.length() < other.origin.length();
            //if both are same length then same # nodes probably
            ListNode* l1 = this->head;
            ListNode* l2 = other.head;
            while(l1 != nullptr && l2 != nullptr){
                if(l1->val != l2->val) return l1->val < l2->val;
                l1 = l1->next;
                l2 = l2->next;
            }
            return false;
        }
        BigInteger subtract(const BigInteger &N) const{
            bool this_is_lesser = this->absLesser(N);
            ListNode* lesser = this_is_lesser ? this->tail : N.tail;
            ListNode* greater= this_is_lesser? N.tail : this->tail;

            int sign = this_is_lesser ? (-N.sign) : this->sign;
            int sign1 = this->sign;
            int sign2 = N.sign;
            
            long remainder = 0;
            ListNode* dummy = new ListNode();
            ListNode* res = dummy;
            while(greater != nullptr && lesser != nullptr){
                long diff = greater->val - lesser->val;
                diff += remainder;
                remainder = 0;
                if(diff < 0){
                    diff += this->max_powa;
                    remainder = -1;
                }

                ListNode* new_node = new ListNode();
                new_node-> val = diff;
                res->prev = new_node;
                new_node->next = res;
                res = res->prev;

                greater = greater->prev;
                lesser = lesser->prev;
            }
            while(greater != nullptr){
                long diff = greater->val + remainder;
                remainder = 0;
                if(diff < 0){
                    diff += this-> max_powa;
                    remainder = -1;
                }
                ListNode* new_node = new ListNode();
                new_node-> val = diff;
                res->prev = new_node;
                new_node->next = res;
                res = res->prev;

                greater = greater->prev;

            }
            while(res->val == 0){
                ListNode* to_delete = res;
                ListNode* next = res->next;
                res->next = nullptr;
                next->prev = nullptr;
                res = next;
                delete to_delete;
                
            }
            ListNode* real_tail = dummy->prev;
            real_tail->next = nullptr;
            dummy->prev = nullptr; //is allat necessary can I just delete dummy? who knows mane
            delete dummy;
            
            
            return BigInteger(res,real_tail,sign);
        }
        BigInteger add(const BigInteger &N) const{
            //on second thought I think if we had them in reverse order it would've been easier but who caresssss x3333
            ListNode* curr1 = this->tail;
            ListNode* curr2 = N.tail;
            int sign1 = this->sign;
            int sign2 = N.sign;
            if(sign1 == -1 && sign2 == 1){
                BigInteger copied = copy(*this);
                copied.sign = 1;
                return N.subtract(copied);
            }
            if(sign1 == 1 && sign2 == -1){
                BigInteger copied = copy(N);
                copied.sign = 1;
                return this->subtract(copied);
            }
            ListNode* dummy = new ListNode();
            ListNode* res = dummy;
            long remainder = 0;
            while(curr1 != nullptr && curr2 != nullptr){
                long sum = curr1->val + curr2->val;
                sum += remainder;
                remainder = 0;
                if(sum >= this->max_powa){
                    sum -= this->max_powa;
                    remainder = 1;
                }
                ListNode* new_node = new ListNode();
                new_node-> val = sum;
                res->prev = new_node;
                new_node->next = res;
                res = res->prev;

                curr1 = curr1->prev;
                curr2 = curr2->prev;
            }
            if(curr1 != nullptr){
                while(curr1 != nullptr){
                    long sum = curr1->val;
                    if(remainder == 1){
                        sum += remainder;
                        remainder = 0;
                    }
                    if(sum >= this->max_powa){
                        sum -= this->max_powa;
                        remainder = 1;
                    }
                    
                    ListNode* new_node = new ListNode();
                    new_node-> val = sum;
                    res->prev = new_node;
                    new_node->next = res;
                    res = res->prev;
                    curr1 = curr1->prev;
                }
            }
            else if(curr2 != nullptr){
                if(curr2 != nullptr){
                    while(curr2 != nullptr){
                        long sum = curr2->val;
                        if(remainder == 1){
                            sum += remainder;
                            remainder = 0;
                        }
                        
                        if(sum >= this->max_powa){
                            sum -= this->max_powa;
                            remainder = 1;
                        }
                        
                        ListNode* new_node = new ListNode();
                        new_node-> val = sum;
                        res->prev = new_node;
                        new_node->next = res;
                        res = res->prev;
                        curr2 = curr2->prev;
                    }
                }
            }
            if(remainder == 1){
                ListNode* new_node = new ListNode();
                new_node->val = 1;
                res->prev = new_node;
                new_node->next = res;
                res = res->prev;
            }
            ListNode* real_tail = dummy->prev;
            real_tail->next = nullptr;
            dummy->prev = nullptr; //is allat necessary can I just delete dummy? who knows mane
            delete dummy;
            return BigInteger(res,real_tail,sign1);
        }
        //Destructor
        ~BigInteger(){
            ListNode* curr = this->head;
            while(curr != nullptr){
                ListNode* next = curr->next;
                delete curr;
                curr = next;
            }
            this->head = nullptr;
            this->tail = nullptr;
        }
        
        std::string toString(){
            std::string res = "";
            if(this->sign == -1){
                res += "-";
            }
            ListNode* curr = this->head;
            res += std::to_string(curr->val); // First group, no leading zeros
            curr = curr->next;
            while(curr != nullptr){
                std::string group = std::to_string(curr->val);
                while(group.length() < this->p){
                    group = "0" + group;
                }
                res += group;
                curr = curr->next;
            }
            return res;
        }

};

int main() {
    
    assert((BigInteger("123").add(BigInteger("456"))).toString() == "579");
    assert((BigInteger("999").add(BigInteger("1"))).toString() == "1000");
    assert((BigInteger("1000").subtract(BigInteger("1"))).toString() == "999");

    assert((BigInteger("-123").add(BigInteger("-456"))).toString() == "-579");
    assert((BigInteger("-999").add(BigInteger("-1"))).toString() == "-1000");
    assert((BigInteger("-1000").subtract(BigInteger("-1"))).toString() == "-999");

    assert((BigInteger("1000").subtract(BigInteger("999"))).toString() == "1");
    assert((BigInteger("999").subtract(BigInteger("1000"))).toString() == "-1");
    assert((BigInteger("-999").add(BigInteger("1000"))).toString() == "1");
    assert((BigInteger("999").add(BigInteger("-1000"))).toString() == "-1");
    std::cout<<"All these tests pass yiay";
    
    

    return 0;
}