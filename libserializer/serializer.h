#pragma once
#include<vector>
#include<string>
#include<list>
#include<map>
#include<sstream>
#ifdef DEBUG_SERIALIZER
    #include<cassert>
#else
    #include<stdexcept>
#endif
#include<type_traits>

#include <libserializer/endian_detector.h>
#include <libserializer/numeric_detector.h>
using namespace std;

inline void WRITABLE_REQUIRED(const ostream *out){
#ifndef NO_EXCEPTION
    #ifdef DEBUG_SERIALIZER
        assert(out!=nullptr);
    #else
        if(out==nullptr) throw invalid_argument("A writable stream is required.");
    #endif
#endif
}

inline void READABLE_REQUIRED(const istream *in){
#ifndef NO_EXCEPTION
    #ifdef DEBUG_SERIALIZER
        assert(in!=nullptr);
    #else
        if(in==nullptr) throw invalid_argument("A readable stream is required.");
    #endif
#endif
}

/*!
  The basis of Serializer.
  @warning This is not Serializer. This class is only the basis of that.
 */
#if defined(_WIN32)||defined(_WIN64)
class __declspec(dllexport) serializer_interface{
#else
class serializer_interface{
#endif
    public:
        /*!
          Constructs serializer_interface with the specified istream.
          @param istream istream you want to use.
          @see serializer_interface(ostream &out);
          @see serializer_interface(iostream &io);
         */
        serializer_interface(istream &);
        /*!
          Constructs serializer_interface with the specified ostream.
          @param ostream ostream you want to use.
          @see serializer_interface(istream &in);
          @see serializer_interface(iostream &io);
         */
        serializer_interface(ostream &);
        /*!
          Constructs serializer_interface with the specified iostream.
          @param iostream iostream you want to use.
          @throw bad_cast This exception may be thrown when casting is failed.\n
                          It is depend on your environment whether the exception is thrown or not.
          @see serializer_interface(istream &in);
          @see serializer_interface(ostream &out);
         */
        serializer_interface(iostream &);
        /*!
          Removes relationship between this class and specified stream.
          @warning This class removes the relationship only; This sets this->_in and this->_out to nullptr.
          @return True if this class removed the relationship properly. Otherwise, false.
         */
        bool close();
        /*!
          Changes stream.
          @param istream istream to make new relationship with this class.
          @see stream(ostream &)
          @see stream(iostream &)
         */
        void stream(istream &);
        /*!
          Changes stream.
          @param ostream ostream to make new relationship with this class.
          @see stream(istream &)
          @see stream(iostream &)
         */
        void stream(ostream &);
        /*!
          Changes stream.
          @param iostream iostream to make new relationship with this class.
          @throw bad_cast This exception may be thrown when casting is failed.\n
                          It is depend on your environment whether the exception is thrown or not.
          @see stream(istream &)
          @see stream(ostream &)
         */
        void stream(iostream &);
    protected:
        /*!
          This enum is used for specifying seeking mode.
         */
        enum seek_mode{SEEK_IN=1,SEEK_OUT=2};
        /*!
          Pointer to hold relationship the specified stream.
         */
        istream *_in;
        /*!
          Pointer to hold relationship the specified stream.
         */
        ostream *_out;
        /*!
          Returns the istream's size.
          @return Size of istream related to this class.
          @throw logic_error throws this exception if this->_in is nullptr.
        */
        size_t size();
        /*!
          Sets the current position to the offset.
          @param streamoff where to seek.
          @param seek_mode stream to set the position. If SEEK_IN is specified, the seeking is applied to input only. 
                 If SEEK_OUT is specified, the seeking is applied to output only. By default, the seeking is applied to both streams.
         */
        void seek(const streamoff,const int=SEEK_IN|SEEK_OUT);
        /*!
         * Gets the size of the available buffer in _in.
         * \return the size of the available buffer in _in
         */
        streamsize in_avail();
    private:
        void setSize();
        size_t _size;
};
/*!
  You can serialize various types by using this class.
  @note Serializer is a alias to serializer. Thus, you can also use serializer.
  @bug Deserializing data is very slow. This problem will be sloved in the future.\n
       Unfortunately, to solve this problem, I need to rewrite the code, so please be patient.
*/
#if defined(_WIN32)||defined(_WIN64)
class __declspec(dllexport) serializer:virtual public serializer_interface{
#else
class serializer:virtual public serializer_interface{
#endif
    public:
        /*!
          Constructs Serializer with the specified stream.
          @param istream istream that has the data to deserialize.
          @see serializer(ostream &);
          @see serializer(iostream &);
         */
        serializer(istream &);
        /*!
          Constructs Serializer with the specified stream.
          @param ostream ostream to write the serialized data.
          @see serializer(istream &);
          @see serializer(iostream &);
         */
        serializer(ostream &);
        /*!
          Constructs Serializer with the specified stream.
          
          @warning This constructor calls the constructor of serializer_interface.\n
                   Therefore, the exceptions of serializer_interface may be thrown. \n
                   For details, look at serializer_interface::serializer_interface(iostream &);
          @param iostream iostream to write the serialized data/that has the data to deserialize.
          @see serializer(istream &)
          @see serializer(ostream &)
         */
        serializer(iostream &);
        /*!
          Destructs serializer.
         */
        ~serializer();
        /*!
          Serializes string.
          @param "const string" String to serialize.
          @warning Don't include \\0 in the string, or deserializing will not work properly. \n
          @return (*this) after serializing.
          @see operator<<(const T[])
          @see operator>>(string &)
         */
        serializer& operator<<(const string &);
        /*!
          Serializes string. \n
          This operator reads the data while the read data is 0x00 or EOF.
          @param string String to put the deserialized data.
          @return (*this) after deserializing.
          @throw invalid_argument This exception will be thrown when the type of the data is invalid.
          @see operator<<(const string &)
         */
        serializer& operator>>(string &);
        /*!
          Serializes primitive type.
          This operator supports the following types:
          
            bool\n
            float\n
            doule\n
            long double\n
            char\n
            short\n
            int\n
            long\n
            long long\n
            unsigned char\n
            unsigned short\n
            unsigned int\n
            unsigned long\n
            unsigned long long
            
            If you want to serialize class made by your hand, you can overload operator<< and operator>>
            @param "typename T" The type of T.
            @param "const T" The primitive type variable that you want to serialize.
            @return (*this) after serializing.
            @throw out_of_range This exception will be thrown when the size of the value is too large to cast from size_t to streamsize, or the value is too large/small for streamsize. \n
                                However, this exception will not be thrown in the almost all situation, because sizeof(size_t)==sizeof(streamsize) in the most situation.
            @throw logic_error This exception will be thrown when the endian of the computer using this library is PPD (aka. middle endian). \n
                               However, this exception will not be thrown in the most case neither, because I've never seen a computer using PPD endian since I was born.
            @throw invalid_argument This exception will be thrown when the type of the variable you want to deserialize is not valid.
            @see operator>>(T &)
         */
        template<typename T> serializer& operator<<(const T&);
        /*!
          Deserializes the data to primivive type.
          @param "typename T" The type of T.
          @param T& The variable to store the deserialized data.
          @return (*this) after serializing.
          @see operator<<(const T&)
         */
        template<typename T> serializer& operator>>(T &);
        /*!
          Serializes the input array.
          This member function serializes "Static Array". i.e. T[].
          @param "typename T" The type of ref
          @param "ref" The reference of array to be serialized.
          @return (*this) after serializing.
          @see operator<<(const T&)
          @see operator<<(const list<T> &lst)
          @see operator<<(const vectort<T> &lst)
         */
        template<typename T> serializer& operator<<(const T ref[]){
            this->writeArray(ref,sizeof(ref)/sizeof(ref[0]));
            return (*this);
        }
        /*!
          Serializes STL list.
          This member function consists of a foreach loop that calls operator<<(const T).\n
          This means, if you want to serialize list<MyClass>, operator<<(const MyClass) or operator(const MyClass &) must be implemented.
          @param "class T" Type of the class.
          @param "lst" The list that has (a) element(s) of which type is "class T".
          @return (*this) after serializing.
          @see operator<<(const T&)
          @see operator>>(list<T> &lst)
        */
    template<class T> serializer& operator<<(const list<T> &lst){
            this->writeArray(lst,lst.size());
            return (*this);
        }
        /*!
          Serializes STL vector.
          This member function consists of a foreach loop that calls operator<<(const T).\n
          This means, if you want to serialize vector<MyClass>, operator<<(const MyClass) or operator(const MyClass &) must be implemented.
          @param "class T" Type of the class.
          @param "v" The vector that has (a) element(s) of which type is "class T".
          @return (*this) after serializing.
          @see operator<<(const T&)
          @see operator>>(vector<T> &lst)
         */
        template<class T> serializer& operator<<(const vector<T> &v){
            this->writeArray(v,v.size());
            return (*this);
        }
        /*!
          Serializes STL pair.
          This member function just calls operator<<(const T) twice.\n
          This means, if you want to pair<classA,classB>, operator<<(const classA) and operator<<(const classB), or operator<<(const classA &) and operator<<(const classB &) must be implemented.
          @param "class S" Key type of the pair.
          @param "class T" Value type of the pair.
          @param "p" The pair to serialize.
          @return (*this) after serializing.
          @see operator<<(const T&)
          @see operator>>(pair<S,T> &p)
         */
        template<class S,class T> serializer& operator<<(const pair<S,T> &p){return (*this)<<p.first<<p.second;}
        /*!
          Serializes STL map.
          This member function consists of a foreach loop that calls operator<<(const pair<S,T> &p).\n
          For details, please look at operator<<(const pair<S,T> &p).
          @param "class S" Key type of the map.
          @param "class T" Value type of the map.
          @param "m" The map.
          @return (*this) after serializing.
          @see operator<<(const pair<S,T> &p)
          @see operator>>(map<S,T> &m)
         */
        template<class S,class T> serializer& operator<<(const map<S,T> &m){
            this->writeArray(m,m.size());
            return (*this);
        }
        /*!
          Deserializes the input array.
          This member function calls operator>>(T &) multiple times, using for-loop.
          Therefore, if you want to deserialize the data into array of which type is MyClass, operator>>(MyClass &) must be inplemented.
          @param array The array into which the deserialized data are input.
          @param "class T" Type of array
          @see operator<<(const T [])
          @see operator>>(T &)
         */
        template <class T> serializer& operator>>(const T array[]){
            this->readArray(array);
            return (*this);
        }
        /*!
          Deserializes STL list.
          This member function consists of a for loop that calls operator>>(T &);\n
          If you want to deserialize the data to list<MyClass>, operator>>(MyClass &) must be implemented.
          @param "class T" The type of the value.
          @param "lst" The list.
          @return (*this) after deserializing
          @see operator>>(T &)
          @see operator<<(const list<T> &lst)
         */
        template<class T> serializer& operator>>(list<T> &lst){
            this->readArray(lst);
            return (*this);
        }
        /*!
          Deserializes STL vector.
          This member function consists of a for loop that calls operator>>(T &);\n
          If you want to deserialize the data to vector<MyClass>, operator>>(MyClass &) must be implemented.
          @param "class T" The type of the value.
          @param "v" The vector.
          @return (*this) after deserializing.
          @see operator>>(T &)
          @see operator<<(const vector<T> &v)
         */
        template<class T> serializer& operator>>(vector<T> &v){
            this->readArray(v);
            return (*this);
        }
        /*!
          Deserializes STL pair.
          This member function just calls operator>>(T &) twice.\n
          If you want to deserialize the data to pair<classA,classB>, operator>>(classA &) and operator>>(class B &) must be implemented.
          @param "class S" The key type.
          @param "class T" The value type.
          @param "p" pair<S,T>.
          @return (*this) after deserializing.
          @see operator>>(T &)
          @see operator<<(const pair<S,T> &p)
         */
        template<class S,class T> serializer& operator>>(pair<S,T> &p){return (*this)>>p.first>>p.second;}
        /*!
          Deserializes STL map.
          This member function consists of a for loop that calls operator>>(pair<S,T> &p).
          For details, please look at operator>>(pair<S,T> &p).
          @param "class S" The key type.
          @param "class T" The value type.
          @return (*this) after deserializing.
          @see operator>>(pair<S,T> &p)
          @see operator<<(const map<S,T> &m)
         */
        template<class S,class T> serializer& operator>>(map<S,T> &m){
            this->readMap(m);
            return (*this);
        }
    private:
        Endian endian;
        size_t buffer_size;
        char *buffer;
        void init();
        template<class S,class T> void writeArray(const T &array,const S &size){
            (*this)<<size;
            for(auto value:array) (*this)<<value;
        }
        template<class T> typename enable_if<is_array<T>::value,void>::type readArray(T &array){
            size_t size;
            (*this)>>size;
            for(size_t counter=0;counter<size;counter++) (*this)>>array[counter];
        }

        template<class T> typename enable_if<is_class<T>::value,void>::type readArray(T &array){
            size_t size;
            (*this)>>size;
            for(size_t counter=0;counter<size;counter++){
                typename T::value_type value;
                (*this)>>value;
                array.insert(array.end(),value);
            }
        }
        template <class S,class T> void readMap(map<S,T> &ref){
            size_t size;
            (*this)>>size;
            for(size_t counter=0;counter<size;counter++){
                pair<S,T> value;
                (*this)>>value;
                ref.insert(value);
            }
        }
};
#ifndef typedef_serializer
#define typedef_serializer
    typedef class serializer Serializer;
#endif
