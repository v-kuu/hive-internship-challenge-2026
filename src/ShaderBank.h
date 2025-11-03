#pragma once
#include <string_view>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

class ShaderBank
{
	public:
		ShaderBank() = delete;
		static void init(sf::RenderWindow &window);

		static std::map<std::string, sf::Shader> shaders;
};
