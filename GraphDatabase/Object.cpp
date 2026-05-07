#include "Object.h"

long int Object::GetId()
{
    return id;
}

std::string Object::ToString() const
{
    std::string text = std::to_string(id) + "\n";
    for (PropertyBase* p : req) text += p->ToString() + "\n";
    for (PropertyBase* p : nreq) text += p->ToString() + "\n";
    return text;
}
