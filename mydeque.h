// mydeque.h
template <typename T>
class MyDeque {
    T* tab;
    int msize; // największa możliwa liczba elementów plus jeden
    int head; // pierwszy do pobrania
    int tail; // pierwsza wolna pozycja
public:
    MyDeque(int s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert( tab != nullptr );
    } // default constructor
    ~MyDeque() { delete [] tab; }
    MyDeque(const MyDeque& other)
    {
        tab = new T[other.msize];
        msize = other.msize;
        head = other.head;
        tail = other.tail;
        for(int i = 0; i < other.msize; i++){
            tab[i] = other.tab[i];
        }
    } // copy constructor
    MyDeque(MyDeque&& other)
    {
        tab = new T[other.msize];
        msize = other.msize;
        head = other.head;
        tail = other.tail;
        other.msize = 0;
        other.head = 0;
        other.tail = 0;
        for(int i = 0; i < other.msize; i++){
            tab[i] = other.tab[i];
            other.tab[i] = 0;
        }
        delete [] other.tab;
    } // move constructor
    MyDeque& operator=(const MyDeque& other)
    {
        tab = new T[other.msize];
        msize = other.msize;
        head = other.head;
        tail = other.tail;
        for(int i = 0; i < other.msize; i++){
            tab[i] = other.tab[i];
        }
        delete [] other.tab;
        return *this;
    } // copy assignment operator, return *this
    MyDeque& operator=(MyDeque&& other)
    {
        tab = new T[other.msize];
        msize = other.msize;
        head = other.head;
        tail = other.tail;
        other.msize = 0;
        other.head = 0;
        other.tail = 0;
        for(int i = 0; i < other.msize; i++){
            tab[i] = other.tab[i];
            other.tab[i] = 0;
        }
        delete [] other.tab;
        return *this;
    } // move assignment operator, return *this
    bool empty() const { return head == tail; }
    bool full() const { return (tail + 1) % msize == head; }
    int size() const { return (tail - head + msize) % msize; }
    int max_size() const { return msize-1; }
    void push_front(const T& item);
     // dodanie na początek O(1)
    void push_front(T&& item)
    {
        head = std::move((head + msize -1) % msize);
        tab[head] = std::move(item);
    } // dodanie na początek O(1)
    void push_back(const T& item);
     // dodanie na koniec O(1)
    void push_back(T&& item)
    {
        tab[tail] = std::move(item);
        tail = std::move((tail + 1) % msize);
    } // dodanie na koniec O(1)
    T& front() { return tab[head]; } // zwraca poczatek
    T& back() { return tab[(tail + msize -1) % msize]; } // zwraca koniec
    void pop_front()
    {
        assert(!empty());
        if (head == tail){
            head = 0;
            tail = 0;
        }
        else{
            if(head == msize - 1){
                head = 0;
            }
            else{
                head = head+1;
            }
        }
    } // usuwa początek kolejki O(1)
    void pop_back()
    {
        assert(!empty());
        if (head == tail){
            head = 0;
            tail = 0;
        }
        else if(tail == 0){
            tail = size() - 1;
        }
        else{
            tail = tail - 1;
        }
    } // usuwa koniec kolejki O(1)
    void clear()
    {
        for (int i = head; i != tail; i=(i+1) % msize) {
            tab[i] = 0;
        }
        delete [] tab;
    } // czyszczenie listy z elementow
    void display();
    // Operacje z indeksami.
    T& operator[](int pos)
    {
        if(pos > msize || pos < 0){
            std::cout<<"Nieprawidlowa pozycja\n";
            return tab[-1];
        }
        return tab[pos];
    } // podstawienie L[pos]=item, odczyt L[pos]
    const T& operator[](int pos) const
    {
        if(pos > msize || pos < 0){
            std::cout<<"Nieprawidlowa pozycja\n";
            return tab[-1];
        }
        return tab[pos];
    } // dostęp do obiektu const
    void erase(int pos)
    {
        if(pos > msize || pos < 0){
            std::cout<<"Nieprawidlowa pozycja\n";
            return;
        }
        if(pos == head){
            pop_front();
            return;
        }
        if(pos == tail){
            pop_back();
            return;
        }
        for(int i = pos; i != tail; i=(i+1) % msize){
            int j = (i+1) % msize;
            tab[i] = tab[j];
        }
        tail--;
    }
    int index(const T& item)
    {
        int i = head;
        bool sem = 0;
        for(; i != tail; i=(i+1) % msize){
            if(tab[i] == item){
                sem = 1;
                break;
            }
        }
        if (sem){
            return i;
        }
        else{
            return -1;
        }
    } // jaki index na liscie (-1 gdy nie ma)
    void insert(int pos, const T& item)
    {
        if(size() > msize - 2){
            std::cout << "Za malo miejsca by wstawic nowy element\n";
            return;
        }
        if(pos < 0 || pos > msize - 1){
            std::cout << "Nieprawidlowa pozycja\n";
            return;
        }
        int pom[msize], k = 0;
        for(int i = pos; i != tail; i =(i+1) % msize){
            pom[k] = tab[i];
            k++;
        }
        tab[pos] = item;
        pos = (pos+1) % msize;
        k = 0;
        tail++;
        for(int i = pos; i != tail; i =(i+1) % msize){
            tab[i] = tab[k];
            k++;
        }
    } // inserts item before pos
    void insert(int pos, T&& item)
    {
        if(size() > msize - 2){
            std::cout << "Za malo miejsca by wstawic nowy element\n";
            return;
        }
        if(pos < 0 || pos > msize - 1){
            std::cout << "Nieprawidlowa pozycja\n";
            return;
        }
        int pom[msize], k = 0;
        for(int i = pos; i != tail; i =(i+1) % msize){
            pom[k] = tab[i];
            k++;
        }
        tab[pos] = std::move(item);
        pos = (pos+1) % msize;
        k = 0;
        tail++;
        for(int i = pos; i != tail; i =(i+1) % msize){
            tab[i] = pom[k];
            k++;
        }
    } // inserts item before pos
    int retHead(){return head;}
    int retTail(){return tail;}
};
template <typename T>
void MyDeque<T>::push_front(const T& item) {
    head = (head + msize -1) % msize;
    tab[head] = item;
}
template <typename T>
void MyDeque<T>::push_back(const T& item) {
    tab[tail] = item;
    tail = (tail + 1) % msize;
}
template <typename T>
void MyDeque<T>::display() {
    for (int i = head; i != tail; i=(i+1) % msize) {
        std::cout << tab[i] << " ";
    }
    std::cout << std::endl;
}
