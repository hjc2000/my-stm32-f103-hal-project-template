#pragma once
#include<bsp-interface/ToString.h>
#include<nlohmann/json.hpp>
#include<string>

namespace bsp
{
	using Json = nlohmann::json;
	using JsonTypeError = Json::type_error;

	class IJsonSerializable :public ICanToString
	{
	public:
		~IJsonSerializable() {}

	public:
		std::string ToString() override
		{
			return ToJson().dump(4);
		}

		virtual Json ToJson() = 0;
	};
}
