#ifndef CJSON_H
#define CJSON_H
#include"json.h"

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

private:
    struct json_object *m_str;
};

#endif // CJSON_H
