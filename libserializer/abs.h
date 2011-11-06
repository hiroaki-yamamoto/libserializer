#pragma once
#include<ostream>
namespace converter{
    class Abs{
    public:
        Abs(const unsigned long long);
        Abs(const long double);
        Abs();
        unsigned long long int_value() const;
        double dbl_value() const;
        bool is_dblMode() const;
        bool operator==(const Abs &);
        bool operator>(const Abs &);
        bool operator<(const Abs &);
        bool operator!=(const Abs &);
        bool operator>=(const Abs &);
        bool operator<=(const Abs &);
        template <typename S> operator S(){return (this->_dbl_mode)?(S)this->_dbl_value:(S)this->_int_value;}
        friend std::ostream& operator<<(std::ostream &,const converter::Abs&);
    private:
        unsigned long long _int_value;
        long double _dbl_value;
        bool _dbl_mode;
    };
    std::ostream& operator<<(std::ostream &,const converter::Abs&);
}
