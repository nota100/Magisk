#pragma once

#include <string>
#include <map>

#include <system_properties.h>

#define PERSISTENT_PROPERTY_DIR  "/data/property"

struct prop_cb {
    virtual void exec(const char *name, const char *value) = 0;
};

using prop_list = std::map<std::string, std::string>;

struct prop_collector : prop_cb {
    explicit prop_collector(prop_list &list) : list(list) {}
    void exec(const char *name, const char *value) override {
        list.insert_or_assign(name, value);
    }
private:
    prop_list &list;
};

std::string persist_getprop(const char *name);
void persist_getprops(prop_cb *prop_cb);
bool persist_deleteprop(const char *name);
