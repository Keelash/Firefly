#include <map>
#include <string>

class DataBase {
public:
    class DataElement {
    public :
        DataElement(DataBase* owner);
        ~DataElement();

        static std::string type() = 0;

    protected:
        void update();

    private:
        unsigned int key_;
        DataBase* owner_;
    };


    DataBase();
    ~DataBase();

    template<Type T>
    T getElement(unsigned int pos);

private:
    std::multimap<unsigned int, DataElement> data_;
};
