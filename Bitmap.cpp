#include "Bitmap.h"
#include <stdlib.h>

#define BYTE_SIZE sizeof(unsigned char)
#define BIGGEST_BYTE 0xff


Bitmap::Bitmap(int size)
{
    this->bytes = (unsigned char*) malloc(calculate_byte_size(size));
}

Bitmap::~Bitmap()
{
    free(this->bytes);
}

int Bitmap::calculate_byte_size(int size) const
{
    int res = size / BYTE_SIZE;
    if ((size % BYTE_SIZE) != 0)
        res++;
    return res;
}

bool Bitmap::get_value(int index) const
{
    int byte_index = get_byte_index(index);
    int bit_index = get_bit_index(index);
    return get_bit_value(byte_index, bit_index);
}

void Bitmap::set_value(int index, bool value)
{
    int byte_index = get_byte_index(index);
    int bit_index = get_bit_index(index);
    set_bit_value(byte_index, bit_index, value);
}

bool Bitmap::get_bit_value(int byte_index, int bit_index)const
{
    return 1 & (this->bytes[byte_index] >> bit_index); 
}

void Bitmap::set_bit_value(int byte_index, int bit_index, bool value)
{
    if (value)
        this->bytes[byte_index] |= 1 << bit_index;
    else
        this->bytes[byte_index] &= BIGGEST_BYTE ^ (1 << bit_index);
}

int Bitmap::get_byte_index(int index) const
{
    return index / BYTE_SIZE;
}

int Bitmap::get_bit_index(int index) const
{
    return index % BYTE_SIZE;
}