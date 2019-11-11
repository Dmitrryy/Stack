
using namespace std;

struct StPoint {
    void* ptr;
    size_t page;
};

struct StPoint* fixations (void* st, size_t n_page, bool mod);

void terminate (int signum) {

    if (signum == 11) {
        cout << "an unauthorized attempt to change the contents of Stack was recorded" << endl;
        cout << "Interrupt signal (" << signum << ") received.\n" << endl;
    }

    StPoint* del = NULL;
    for (int i = 0; (del = fixations(NULL, 0, false)) != NULL; i++) {

    }

    exit(signum);
}

int my_realloc (StPoint** arr, size_t elem) {

    StPoint* tmp = new StPoint[elem + 10];
    memcpy(tmp, *arr, elem * sizeof(StPoint));
    delete [] (*arr);
    *arr = tmp;
}

struct StPoint* fixations (void* st, size_t n_page, bool mod) {

    static struct StPoint* add = new StPoint[10];
    static int i = 0;

    if (mod == true) {
        if (i % 10 == 9)
            my_realloc(&add, i);

        add[i].page = n_page;
        add[i++].ptr = st;
    } else {
        if (i <= 0)
            return NULL;
        return &(add[i]);
    }
}