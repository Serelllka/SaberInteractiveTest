#include <iostream>
#include <string>

template<typename T>
void out_binary(T a)
{
    typedef unsigned char* uc_ptr;
    bool f = false;

    if (!std::is_signed<T>() || !std::is_integral<T>())
    {
        std::cerr << "Type must be signed and integral" << std::endl;
        return;
    }

    size_t size = sizeof(T);
    uc_ptr ptr = (uc_ptr)&a + size - 1;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (*ptr & (128 >> j))
            {
                std::cout << 1;
                f = true;
            }
            else
            {
                if (f)
                {
                    std::cout << 0;
                }
            }
        }
        ptr -= 1;
    }
    std::cout << std::endl;
}

int main()
{
    out_binary<float>(-4);
    out_binary<int>(-4);
    out_binary<long long>(1024);
    out_binary<unsigned int>(200);

}
