#include "ObjectType.h"

bool ObjectType::Validate(std::vector<RawProperty> req, std::vector<RawProperty> nreq, std::vector<PropertyBase*>& reqOut, std::vector<PropertyBase*>& nreqOut)
{
    auto checkMatch = [](const std::vector<RawProperty>& inputVector,
        const std::vector<PropertyType>& schemaVector,
        std::vector<PropertyBase*>& outList)
        {
            for (const auto& raw : inputVector) {
                int match_count = 0;

                for (const auto& schema : schemaVector) {
                    if (schema.Validate(raw)) {
                        match_count++;
                        outList.push_back(PropertyBase::CreateProperty(schema, raw.value));
                    }
                }

                if (match_count != 1) {
                    return false;
                }
            }
            return true;
        };

    return checkMatch(req, this->req, reqOut) && checkMatch(nreq, this->nreq, nreqOut);
}

std::string ObjectType::ToString() const
{
    std::string text = name + "\n";
    for (PropertyType p : req) text += p.ToString() + "\n";
    for (PropertyType p : nreq) text += p.ToString() + "\n";
    return text;
}