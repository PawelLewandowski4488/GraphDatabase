#pragma once
#include <string>

class PropertyType;

class PropertyBase
{
public:
	virtual std::string ToString() const = 0;
	virtual ~PropertyBase() = default;

	static PropertyBase* CreateProperty(const PropertyType& propertytype, const std::string& rawvalue);
};

template <typename T> class Property : public PropertyBase
{
public:
	std::string name;
	T value;
	Property(std::string name, T value) : name(name), value(value) {}
public:
	std::string ToString() const override
	{
		if constexpr (std::is_same_v < T, std::string>)
		{
			return name + ": " + value;
		}
		else
		{
			return name + ": " + std::to_string(value);
		}
	}
};

