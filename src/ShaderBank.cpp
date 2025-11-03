#include "ShaderBank.h"

constexpr std::string_view fragInvert = R"(
uniform sampler2D texture;

void main()
{
	vec4 color = texture2D(texture, gl_TexCoord[0].xy);
	gl_FragColor = vec4(1.0 - color.rgb, color.a);
}
)";

std::map<std::string, sf::Shader> ShaderBank::shaders = {};

void ShaderBank::init(sf::RenderWindow &window)
{
	(void)window;
	sf::Shader shader;
	if (!shader.loadFromMemory(fragInvert, sf::Shader::Type::Fragment))
		std::cerr << "Failed to load shader from memory" << std::endl;
	shader.setUniform("texture", sf::Shader::CurrentTexture);
	shaders["Invert"] = std::move(shader);
}
