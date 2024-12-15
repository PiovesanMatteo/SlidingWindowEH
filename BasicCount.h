class BasicCount {
private:
    struct node {
        int value;
        int exp;
        node* next;
        node* prev;
    };
    int k, k_half, max_exponent, time, sum, window_size;
    node** array_last;
    node* start;
    node* stop;
    int* array_count;
public:
    BasicCount(float e, int n);
    ~BasicCount();
    void insert(int value);
    int eval();
    int nbucket();
private:
    void push(int exp, int value);
    int pop(int exp);
    void update();
};
