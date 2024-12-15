#include "Sum.h"
Sum::Sum(float e, int n) {
    k = 1 / (2 * e);
    start = new node;
    stop = new node;

    //viene usata una lista concatenata come struttuta di supporto
    start->next = stop;
    start->prev = nullptr;
    stop->next = nullptr;
    stop->prev = start;
    start->merged = false;
    stop->merged = false;

    time = 0;
    somma = 0;
    window_size = n;
}
Sum::~Sum() {
    node* iter = start->next;
    while (iter != stop) {
        node* del = iter;
        iter = iter->next;
        delete del;
    }
    delete stop;
    delete start;
}
Sum::node* Sum::push(int size, int timest, node* insert, bool merged) {
    node* ins = new node;
    lenght++;
    ins->size = size;
    ins->timest = timest;
    ins->merged = merged;

    ins->next = insert->next;
    ins->prev = insert;
    insert->next->prev = ins;
    insert->next = ins;

    somma += size;
    return ins;

}
int Sum::pop(node* buck) {
    buck->prev->next = buck->next;
    buck->next->prev = buck->prev;
    somma -= buck->size;
    int ret = buck->timest;
    delete buck;
    lenght--;
    return ret;
}
void Sum::insert(int value) {
    if (value != 0) push(value, time, start, false);
    //wrap-around counter (dal momento che parte da 0, viene resettato quando raggiunge window_size)
    time++;
    if (time == window_size)time = 0;
    update();
}
void Sum::update() {
    //Merge phase
    node* iter = start->next;
    int i = 1;
    //Si porta il puntatore iter al terzo elemento
    while (iter != stop && i < 3) {
        iter = iter->next;
        i++;
    }
    //Early return se ci sono meno di 3 elementi
    if (iter == stop)return;
    int iter_sum = start->next->size;
    while (iter != stop) {
        if (k * (iter->size + iter->prev->size) <= iter_sum) {
            node* ins = iter->prev->prev;
            int newval = iter->size + iter->prev->size;
            //L'elemento a sinistra è sicuramente più antico
            int a = pop(iter->prev);
            pop(iter);
            iter = push(newval, a, ins, true);
        }
        else iter_sum += iter->prev->size;
        iter = iter->next;
    }
    //Scarto dell'ultimo bucket se uscito dalla finestra
    if (stop->prev->timest == time) pop(stop->prev);
}
int Sum::eval() {
    //Viene tenuta la somma attuale di tutti i bucket attuali e poi sottratta la metà dell'ultimo
    //Se l'ultimo bucket non è frutto di un merge non si fa approssimazione
    if (!stop->prev->merged) return somma;
    return somma - ((stop->prev->size) / 2);
}
