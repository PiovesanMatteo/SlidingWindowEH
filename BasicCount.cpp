#include "BasicCount.h"
#include<cmath>
BasicCount::BasicCount(float e, int n) {
    k = ceil(1 / e);
    k_half = ceil((float)k / 2);
    max_exponent = ceil(log2(n / k_half)) + 1;
    array_count = new int[max_exponent + 1];
    array_last = new node * [max_exponent + 1];
    start = new node;
    stop = new node;

    start->next = stop;
    start->prev = nullptr;
    stop->next = nullptr;
    stop->prev = start;

    start->exp = -1;
    stop->exp = -1;
    time = 0;
    sum = 0;
    window_size = n;
    for (int i = 0;i < max_exponent + 1;i++) {
        array_count[i] = 0;
        array_last[i] = nullptr;
    }
}
BasicCount::~BasicCount() {

    node* iter = start->next;
    while (iter != stop) {
        node* temp = iter->next;
        delete iter;
        iter = temp;
    }
    delete start;
    delete stop;
    delete[] array_count;
    delete[] array_last;*/
}
void BasicCount::push(int exp, int value) {
    node* temp;
    //se exp è maggiore di 0, implica che esista almeno un bucket di (exp-1)
    //il merge si attiva quando il numero di  bucket per  una size raggiunge (k/2)+2
    //(k/2)+2-2=0 -> k/2=0 -> k=0, il che  è impossibile
    if (exp == 0) temp = start;
    else temp = array_last[exp - 1];
    node* ins = new node;

    ins->exp = exp;
    ins->value = value;

    ins->next = temp->next;
    ins->prev = temp;
    temp->next->prev = ins;
    temp->next = ins;


    if (array_last[exp] == nullptr)array_last[exp] = ins;
    array_count[exp]++;
    sum += pow(2, exp);
}
int BasicCount::pop(int exp) {
    array_last[exp]->next->prev = array_last[exp]->prev;
    array_last[exp]->prev->next = array_last[exp]->next;

    int ret = array_last[exp]->value;

    sum -= pow(2, exp);
    array_count[exp]--;
    node* temp = array_last[exp];
    if (array_count[exp] == 0)array_last[exp] = nullptr;
    else array_last[exp] = array_last[exp]->prev;

    delete temp;
    return ret;
}
void BasicCount::insert(int value) {
    if (value != 0) push(0, time);
    time++;
    if (time >= window_size) time = 0;
    update();
}
void BasicCount::update() {
    //Merge phase
    if (array_count[0] > k + 1) {
        //L'elemento a sinistra contiene sicuramente l'elemento più antico
        pop(0);
        int a = pop(0);
        push(1, a);
    }
    for (int i = 1;i <= max_exponent;i++) {
        if (array_count[i] > k_half + 1) {
            pop(i);
            int a = pop(i);
            push(i + 1, a);
        }
    }
    if (stop->prev->value == time) pop(stop->prev->exp);
}
int BasicCount::eval() {
    return sum - pow(2, (stop->prev->exp) - 1);
    //(2^x)/2=2^(x-1)
}
int BasicCount::nbucket() {
    int ret = 0;
    for (int i = 0;i <= max_exponent;i++) ret += array_count[i];
    return ret;
}
