#pragma once
#include <string>

class PropertyType;

class PairBase
{
public:
	virtual std::string ToString() const = 0;
	virtual ~PairBase() = default;

	static PairBase* CreatePair(const PropertyType& propertytype, const std::string& rawvalue);
};

template <typename T> class Pair : public PairBase
{
public:
	std::string key;
	T value;
	Pair(std::string key, T value) : key(key), value(value) {}
public:
	std::string ToString() const override
	{
		if constexpr (std::is_same_v < T, std::string>)
		{
			return key + ": " + value;
		}
		else
		{
			return key + ": " + std::to_string(value);
		}
	}
};

