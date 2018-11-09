#ifndef __BIGINT_HPP__
#define __BIGINT_HPP__

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

namespace ecs
{

using namespace std;

// Máximo inteiro com 32 bits (unsigned): 4294967295

const int BASE = 1000000000; // Base decimal para facilitar na exibição.
const int PART_LEN = 9;

string padleft(string str, int len, char padChar = ' ')
{
    auto ret = str;
    while (ret.size() < len) ret = padChar + ret;
    return ret;
}

class bigint
{
    private:
        typedef vector<unsigned int> TBuffer;
        TBuffer buffer;

    public:

        // Estou implementando apenas para facilitar input de inteiros pequenos
        // O construtor baseado em strings permite qualquer valor.
        bigint(unsigned int val)
        {
            // TODO: Implementar a inicializacao completa para inteiros.
            // Por enquanto, apenas impedir que se possa usar um número negativo ou maior que BASE
            if (val >= BASE || val < 0) throw 1;
            buffer.push_back(val);
        }

        bigint(const bigint& other)
        {
            buffer = other.buffer;
        }

        // Este é o construtor que realmente interessa. Usuários podem inserir qualquer valor através deste construtor
        bigint(string val)
        {
            for (int i = val.size(); i > 0; i -= PART_LEN )
            {
                string part = val.substr(max(i - PART_LEN, 0), min(i, PART_LEN));
                auto p = stoi(part);
                if (p < 0) throw 1;
                buffer.push_back(p);
            }
        }

        // Tenho tudo o que preciso para operator+, então porque não?
        bigint operator+(const bigint& other) const
        {
            auto ret = bigint(0);
            bufferSum(&ret.buffer, this->buffer, other.buffer);
            return ret;
        }

        bigint operator++(int)
        {
            auto ret = *this;
            ++(*this);
            return ret;
        }

        bigint& operator++()
        {
            bufferSum(&this->buffer, this->buffer, bigint(1).buffer);
            return *this;
        }

        TBuffer* bufferSum(TBuffer *res, const TBuffer& b1, const TBuffer& b2) const
        {
            auto n = max(b1.size(), b2.size());
            *res = b1;
            auto temp = b2;

            res->resize(n, 0);
            temp.resize(n, 0);

            int carry = 0;
            for (auto i = 0; i < n; ++i)
            {
                int p = (*res)[i] + temp[i] + carry;
                carry = 0;
                if (p >= BASE)
                {
                    carry = 1;
                    p = p - BASE;
                }
                (*res)[i] = p;
            }
            if (carry > 0) res->push_back(carry);
            return res;
        }

        // Só estou usando essa função para debug.
        void print() const
        {
            for (auto i = 0; i< buffer.size(); ++i)
            {
                cout << buffer[i] << " ";
            }
            cout << endl;
        }

        string show() const
        {
            int i = 0;
            string ret = "";
            string part;
            bool shallPrint = false;
            for (TBuffer::const_reverse_iterator it = buffer.rbegin(); it != buffer.rend(); ++it)
            {
                if (*it != 0) shallPrint = true;
                if (shallPrint)
                {
                    char p[10];
                    sprintf(p, "%i", *it);
                    part = padleft(p, PART_LEN, '0');
                    ret += part;
                }
            }

            return ret;
        }

        friend ostream& operator<< (ostream& stream, const bigint& num);

        int bsize() const
        {
            return buffer.size();
        }
};

ostream& operator<< (ostream& stream, const bigint& num)
{
    stream << num.show();
    return stream;
}

} /** namespace ecs **/

#endif /** __BIGINT_HPP__ **/
