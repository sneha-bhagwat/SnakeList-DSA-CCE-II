// SnakeList - Snake game using Linked Lists (Unit III)
// Snake = Doubly Linked List | Power-ups = Queue (linked) | Undo = Stack (linked)
// Memory: malloc / calloc / free | Controls: W A S D move, E power-up, U undo 3 moves, Q quit
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// ---- keyboard/screen helpers (platform specific, no need to explain) ----
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
char key()          { return _kbhit() ? _getch() : 0; }
void wait(int ms)   { Sleep(ms); }
void cls()          { system("cls"); }
void rawMode(bool)  {}
#else
#include <termios.h>
#include <unistd.h>
termios old;
char key()          { char c; return read(0, &c, 1) == 1 ? c : 0; }
void wait(int ms)   { usleep(ms * 1000); }
void cls()          { cout << "\033[H\033[2J"; }
void rawMode(bool on) {
    if (on) { tcgetattr(0, &old); termios t = old; t.c_lflag &= ~(ICANON | ECHO);
              t.c_cc[VMIN] = 0; t.c_cc[VTIME] = 0; tcsetattr(0, TCSANOW, &t); }
    else tcsetattr(0, TCSANOW, &old);
}
#endif

const int W = 30, H = 15;

// ---- nodes: data + pointer(s) ----
struct Seg { int x, y; Seg *prev, *next; };            // snake (doubly)
struct Pow { int type; Pow *next; };                   // queue node
struct Mov { int tx, ty, grew, dx, dy; Mov *next; };   // stack node

Seg *head = 0, *tail = 0;      // snake first/last
Pow *qf = 0, *qr = 0;          // queue front/rear
Mov *top = 0;                  // stack top
int len = 0, qn = 0, sn = 0, alive = 0;   // alive = nodes in memory
const char *pname[] = {"SLOW", "SHRINK", "2X"};

// ---- Doubly Linked List (snake) ----
Seg *mk(int x, int y, Seg *p, Seg *n) {                // malloc one node
    Seg *s = (Seg*)malloc(sizeof(Seg)); s->x = x; s->y = y; s->prev = p; s->next = n;
    len++; alive++; return s;
}
void addHead(int x, int y) { Seg *s = mk(x, y, 0, head); if (head) head->prev = s; else tail = s; head = s; }
void addTail(int x, int y) { Seg *s = mk(x, y, tail, 0); if (tail) tail->next = s; else head = s; tail = s; }
void delTail() { Seg *t = tail; tail = t->prev; if (tail) tail->next = 0; else head = 0; free(t); len--; alive--; }
void delHead() { Seg *h = head; head = h->next; if (head) head->prev = 0; else tail = 0; free(h); len--; alive--; }
bool hit(int x, int y, bool skipTail) {                // search: is (x,y) on the snake?
    for (Seg *p = head; p; p = p->next)
        if (!(skipTail && p == tail) && p->x == x && p->y == y) return true;
    return false;
}

// ---- Queue using linked list (FIFO): insert at rear, delete from front ----
void enqueue(int t) {
    Pow *n = (Pow*)calloc(1, sizeof(Pow)); n->type = t;   // calloc: memory set to 0
    if (qr) qr->next = n; else qf = n;
    qr = n; qn++; alive++;
}
int dequeue() {
    Pow *n = qf; int t = n->type; qf = n->next;
    if (!qf) qr = 0;
    free(n); qn--; alive--; return t;
}

// ---- Stack using linked list (LIFO): insert/delete at top ----
void push(int tx, int ty, int grew, int dx, int dy) {
    Mov *m = (Mov*)malloc(sizeof(Mov));
    m->tx = tx; m->ty = ty; m->grew = grew; m->dx = dx; m->dy = dy;
    m->next = top; top = m; sn++; alive++;
}
Mov pop() { Mov *n = top, copy = *n; top = n->next; free(n); sn--; alive--; return copy; }

void draw(int fx, int fy, int score, int undos) {
    string g[H], bar(W, '-');
    for (int i = 0; i < H; i++) g[i] = string(W, ' ');
    for (Seg *p = head; p; p = p->next) g[p->y][p->x] = (p == head) ? 'O' : 'o';
    g[fy][fx] = '*';
    cls();
    cout << "+" << bar << "+\n";
    for (int i = 0; i < H; i++) cout << "|" << g[i] << "|\n";
    cout << "+" << bar << "+\n";
    cout << "Score:" << score << "  Length:" << len << "  Undo left:" << undos << "\n";
    cout << "Power-up queue: "; for (Pow *p = qf; p; p = p->next) cout << pname[p->type] << " ";
    cout << "\nStack depth:" << sn << "  Nodes alive:" << alive << "      \n";
}

int main() {
    srand(time(0)); rawMode(true);
    addHead(15, 7); addTail(14, 7); addTail(13, 7);       // starting snake: 3 nodes
    int dx = 1, dy = 0, ldx = 1, ldy = 0;                 // direction, last moved direction
    int score = 0, foods = 0, undos = 3, slow = 0, dbl = 0, fx, fy;
    const char *msg = "You quit";
    do { fx = rand() % W; fy = rand() % H; } while (hit(fx, fy, false));

    while (true) {
        draw(fx, fy, score, undos);
        bool quit = false;
        for (int t = 0; t < (slow ? 180 : 100); t += 10) {   // read keys during one tick
            char k = key();
            if (k >= 'A' && k <= 'Z') k += 32;
            if (k == 'w' && ldy != 1)  { dx = 0;  dy = -1; }
            if (k == 's' && ldy != -1) { dx = 0;  dy = 1; }
            if (k == 'a' && ldx != 1)  { dx = -1; dy = 0; }
            if (k == 'd' && ldx != -1) { dx = 1;  dy = 0; }
            if (k == 'q') quit = true;
            if (k == 'u' && undos > 0 && sn > 0) {            // UNDO: pop 3 moves
                for (int i = 0; i < 3 && top; i++) {
                    Mov m = pop();
                    delHead();                                // step head back
                    if (!m.grew) addTail(m.tx, m.ty);         // give tail back
                    dx = ldx = m.dx; dy = ldy = m.dy;
                }
                undos--;
            }
            if (k == 'e' && qn > 0) {                         // power-up: dequeue
                int p = dequeue();
                if (p == 0) slow = 40;
                else if (p == 1) { for (int i = 0; i < 2 && len > 3; i++) delTail(); }
                else dbl = 1;
            }
            wait(10);
        }
        if (quit) break;
        if (slow) slow--;

        int nx = head->x + dx, ny = head->y + dy;
        if (nx < 0 || nx >= W || ny < 0 || ny >= H) { msg = "You hit the wall!"; break; }
        bool eat = (nx == fx && ny == fy);
        if (hit(nx, ny, !eat)) { msg = "You bit yourself!"; break; }

        push(tail->x, tail->y, eat, dx, dy);                  // save move on stack
        addHead(nx, ny); ldx = dx; ldy = dy;                  // grow at head
        if (eat) {
            score += dbl ? 20 : 10; dbl = 0; foods++;
            if (foods % 3 == 0 && qn < 5) enqueue(rand() % 3);  // reward power-up
            do { fx = rand() % W; fy = rand() % H; } while (hit(fx, fy, false));
        } else delTail();                                     // not eaten: remove tail
    }

    rawMode(false);
    cout << "\nGAME OVER: " << msg << "  Score: " << score << "\n";
    while (head) delHead();                                   // free() everything
    while (qf) dequeue();
    while (top) pop();
    cout << "Nodes still in memory: " << alive << (alive == 0 ? "  (no leak)\n" : "  (LEAK!)\n");
    return 0;
}
