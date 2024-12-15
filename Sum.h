class Sum {
private:
    struct node {
        int timest;
        int size;
        bool merged;
        node* next;
        node* prev;
    };
    int time, somma, window_size,lenght;
    float k;
    node* start;
    node* stop;

public:
    Sum(float e, int n);
    ~Sum();
    void insert(int value);
    int eval();
    int nbucket() { return lenght; }
private:
    node* push(int size, int value, node* insert, bool merged);
    int pop(node* buck);
    void update();
};
