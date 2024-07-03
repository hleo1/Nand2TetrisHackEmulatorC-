#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>

//    std::cout << "Press any key to see it displayed. Press 'Esc' to exit." << std::endl;
    
//     while (true) {
//         // Check if a key is pressed
//         if (_kbhit()) {
//             // Get the key code of the pressed key
//             char ch = _getch();

//             // Display the pressed key
//             std::cout << "Key pressed: " << ch << std::endl;

//             // Exit the loop if 'Esc' key is pressed
//             if (ch == 27) { // 27 is the ASCII code for 'Esc'
//                 break;
//             }
//         }

//         // Wait for 1 second
//         // std::th/ int main()
// is_thread::sleep_for(std::chrono::seconds(1));
//     }

//     return 0;
// }

using namespace std;

struct Vector {
    double* elem;
    int sz;
};


void vector_init(Vector& v, int s) {
    v.elem = new double[s];
    v.sz = s;
}

void read_in_vector(Vector& v) {
    for(int i = 0; i != v.sz; i++) {
        cin >> v.elem[i];
    }
}

void print_vector(Vector& v) {
    for(int i = 0; i != v.sz; i++) {
        cout << v.elem[i];
    }
}

int main() {
    Vector v;
    vector_init(v, 3);
    read_in_vector(v);
    print_vector(v);
    return 0;
}

#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;
class RAM {
    public :
    RAM(int size) : elem{new double[size]}, sz{size} {}
    double& operator[](int i) {return elem[i];}
    int size() {return sz;}

    private:
    double* elem;
    int sz;

};


int main() {
    RAM vector(3);
    cin >> vector[0];
}