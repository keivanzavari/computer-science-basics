#include <iostream>

class Foo {
public:
    explicit Foo(int a, int b) : m_a(a), m_b(b) {
        std::cout << "construct "  << m_a << ", " << m_b << std::endl;
    }
    void echo() const {
        std::cout << "echo: " << m_a << ", " << m_b << std::endl;
    }
    Foo(const Foo &w) : m_a(w.m_a), m_b(w.m_b) {
        std::cout << "copy construct " << m_a << ", " << m_b << std::endl;
    }

    Foo(Foo &&w) : m_a(w.m_a), m_b(w.m_b) {
        std::cout << "move construct " <<  m_a << ", " << m_b << std::endl;
    }
    ~Foo() {
        std::cout << "destruct" << std::endl;
    }
    Foo &operator=(const Foo &w) = default;
    Foo &operator=(Foo &&w) = default;


private:
    const int m_a;
    int m_b;
};

Foo func_a(int a) {
    if (a < -3) {
        // causes a construct call
        return Foo(a, -1);
    } else if (a >= -3 || a <= 3) {
        // causes a copy construct call
        const Foo w(a, 0);
        return w;
    } else {
        // causes a move construct call
        Foo w2(a, 1);
        return w2;
    }
}

Foo func_b(int a) {
    const Foo w(a, 1);
    return w;
}

Foo func_c(int a) {
    Foo w(a, 1);
    return w;
}
int main(int argc, char **argv) {

    // only construct call, no destruct call
    const Foo w1 = func_b(1);
    w1.echo();

    std::cout << "-------------------" << std::endl;

    // only construct call, no destruct call
    const Foo w2 = func_c(2);
    w2.echo();

    std::cout << "-------------------" << std::endl;

    // construct and copy construct call, then a destruct call right before 
    // returning from the function 
    Foo w3 = func_a(3);
    w3.echo();

    std::cout << "-------------------" << std::endl;

    // only construct call
    const Foo w4 = func_a(-4);
    w4.echo();

    std::cout << "-------------------" << std::endl;


    // construct and move construct call, then a destruct call right before 
    // returning from the function 
    const Foo w5 = func_a(5);
    w5.echo();

    std::cout << "-------------------" << std::endl;

    // destruct all objects
    return 0;
}