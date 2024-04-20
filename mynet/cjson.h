#ifndef CJSON_H
#define CJSON_H
#include"json.h"
#include <vector>

class CJson
{
public:
    CJson(){
        m_str = json_object_new_object();
    }

    CJson( const char* str){
        m_str = json_tokener_parse(str);
    }
    ~CJson(){
        json_object_put(m_str);
    }

    void json_add_value( const char * key,  const char * value){
        json_object_object_add(m_str,key, json_object_new_string(value));
    }
    void json_add_value( const char * key,  int value){
        json_object_object_add(m_str,key, json_object_new_int(value));
    }

    void json_add_value( const char * key,  std::vector<int>& value){
        json_object *jarray = json_object_new_array();
        for (const int& x: value) {
            json_object_array_add(jarray, json_object_new_int(x));
        }
        json_object_object_add(m_str,key, json_object_get(jarray));

        // 回收空间
        json_object_put(jarray);
    }

    const char * json_to_string(){
        return json_object_to_json_string(m_str);
    }

    int json_get_int( const char * key)
    {
        return  json_object_get_int(  json_object_object_get(m_str,key) );
    }
    const char *  json_get_string(const char * key)
    {
        return  json_object_get_string(  json_object_object_get(m_str,key) );
    }

    std::vector<int> json_get_int_list(const char* key)
    {
        json_object *jarray = json_object_object_get(m_str,key);
        int array_len = json_object_array_length(jarray);
        std::vector<int> res;

        for (int i = 0; i < array_len; i++) {
            json_object *element = json_object_array_get_idx(jarray, i);
            res.emplace_back(json_object_get_int(element));
        }
        return res;
    }

private:
    struct json_object *m_str;
};

#endif // CJSON_H
