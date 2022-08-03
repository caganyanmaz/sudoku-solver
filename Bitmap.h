#ifndef _BITMAP_H_
#define _BITMAP_H_

class Bitmap
{
    unsigned char *bytes;
public:
    Bitmap(int size);
    ~Bitmap();
    bool get_value(int index)const;
    void set_value(int index, bool value);
private:
    int calculate_byte_size(int size)const;
    
    bool get_bit_value(int byte_index, int bit_index)const;
    void set_bit_value(int byte_index, int bit_index, bool value);
    
    int get_byte_index(int index)const;
    int get_bit_index(int index)const;
};

#endif