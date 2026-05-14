#include "ObjectType.h"

bool ObjectType::Validate(std::vector<RawProperty> req, std::vector<RawProperty> nreq, std::vector<PropertyBase*>& reqOut, std::vector<PropertyBase*>& nreqOut)
{
    for (const auto& schema : this->req) {
        bool found = false;
        for (const auto& raw : req) {
            if (schema.Validate(raw)) {
                reqOut.push_back(PropertyBase::CreateProperty(schema, raw.value));
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    for (const auto& raw : nreq) {
        bool matched = false;
        for (const auto& schema : this->nreq) {
            if (schema.Validate(raw)) {
                nreqOut.push_back(PropertyBase::CreateProperty(schema, raw.value));
                matched = true;
                break;
            }
        }
        if (!matched) return false;
    }

    return true;
}

void ObjectType::SetId(long int id)
{
    this->id = id;
}

std::string ObjectType::ToString() const
{
    std::string text = name + "\n\n";
    for (PropertyType p : req) text += p.ToString() + "\n";
    text += "\n";
    for (PropertyType p : nreq) text += p.ToString() + "\n";
    return text;
}