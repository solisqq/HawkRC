#ifndef CONVERTER_H
#define CONVERTER_H

class Converter {
public:
    template<typename Type>
    static Type mapper(Type low_src, Type high_src, Type low_rslt, Type high_rslt, Type val) {
        return ((high_rslt-low_rslt)/(high_src-low_src))*val;
    }
};

#endif