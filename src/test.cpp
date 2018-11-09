#include "bigint.hpp"

using namespace ecs;

template <typename F>
bool throws(F& lambda)
{
    try{lambda();}
    catch(int e){return true;}
    return false;
}

template <typename F>
bool throws(F&& lambda)
{
    return throws((F&) lambda);
}

template <typename T>
void print(T val)
{
    cout << val << endl;
}

template <typename T>
void tprint(string name, T actual, T expected)
{
    print("");
    if (actual == expected)
    {
        cout << "Passed: " << name << endl;
    }
    else
    {
        cout << "Failed: " << name << endl;
        cout << "Actual = " << actual << endl;
        cout << "Expected = " << expected << endl;
    }
}

void tprint(string name, string actual, string expected)
{
    return tprint<string>(name, actual, expected);
}

int main()
{
    print("Testando bigint:" );

    // Instanciacao:
    auto v1 = bigint(1);
    tprint("Instanciacao int",
        v1.show(), "000000001"
    );

    auto v2 = bigint("12");
    tprint("Instanciacao string",
        v2.show(), "000000012"
    );

    auto v3 = bigint("1000000000");
    tprint("Instanciacao big int",
        v3.show(), "000000001000000000"
    );

    tprint("Big int tem tamanho correto",
        v3.bsize(), 2
    );

    tprint("Inteiro muito grande gera excecao",
        throws([]{return bigint(4000000000);}), true
    );

    tprint("Negativo gera excecao (int)",
        throws([]{return bigint(-1);}), true
    );

    tprint("Negativo gera excecao (string)",
        throws([]{return bigint("-1");}), true
    );

    // Soma:
    tprint("Soma",
        (v1 + v2).show(), "000000013"
    );

    tprint("Soma com carry",
        (v3 + bigint("999999999") + v1).show(), "000000002000000000"
    );

    tprint("Numeros bem grandes 1",
        (bigint("9999999999999999999999999999999999") + v1).show(),
        "010000000000000000000000000000000000"
    );

    tprint("Numeros bem grandes 2",
        (
            bigint("9000000000000000000000000000000000") +
            bigint("1000000000000000000000000000000000")
        ).show(),
        "010000000000000000000000000000000000"
    );

    // Operator ++
    tprint("Pre incremento ",
        (++bigint("9999999999999999999999999999999999")).show(),
        "010000000000000000000000000000000000"
    );

    tprint("Pos incremento retorna o valor anterior",
        (bigint("9999999999999999999999999999999999")++).show(),
        "009999999999999999999999999999999999"
    );

    v1++;
    tprint("Pos incremento realmente incrementa",
        v1.show(),
        "000000002"
    );
}
