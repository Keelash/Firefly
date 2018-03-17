#ifndef FACTORY_H
#define FACTORY_H

#include <map>

template<class Key, class A_Item>
class Factory {
public:

    typedef A_Item* (*CreateItem)(void);
    typedef std::map<Key, CreateItem> FactoryMap;

    static Factory *getInstance() {
        static Factory instance;
        return &instance;
    }

    void registerItem(const Key &key, CreateItem fCreate) {
        this->getFactoryMap()[key] = fCreate;
    }

    A_Item *createItem(const Key &key) {
        typename FactoryMap::iterator it = this->getFactoryMap().find(key);

        if(it != this->getFactoryMap().end()) {
            return it->second();
        }

        return nullptr;
    }

    typename FactoryMap::iterator begin() { return this->getFactoryMap().begin(); }
    typename FactoryMap::iterator end() { return this->getFactoryMap().end(); }

protected:

    FactoryMap& getFactoryMap() {
        static FactoryMap factoryMap;
        return factoryMap;
    }

    Factory() {  }
    Factory(const Factory& ) {  }
    Factory &operator=(const Factory&) { return *this; }

    virtual ~Factory() {  }
};

#define REGISTER_FACTORY_ITEM(factory_klass, a_item_klass, klass, name) \
    class klass##Factory { \
    public: \
        klass##Factory() \
        { \
            factory_klass::getInstance()->registerItem(name, create); \
        } \
    \
        static a_item_klass* create() { \
            return new klass(); \
        } \
    }; \
    static klass##Factory global_##klass##Factory;

#endif//FACTORY_H
