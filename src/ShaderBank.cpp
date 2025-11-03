#include "ShaderBank.h"

constexpr std::string_view fragInvert = R"(
uniform sampler2D texture;

void main()
{
	vec4 color = texture2D(texture, gl_TexCoord[0].xy);
	gl_FragColor = vec4(1.0 - color.rgb, color.a);
}
)";

// Snatched from a previous project of mine
constexpr std::string_view fragCRT = R"(
#define M_PI 3.1415926535897932384626433832795

uniform sampler2D texture;
uniform vec2 resolution;

vec2 curve(vec2 uv)
{
	uv = (uv - 0.5) * 2.0;
	uv *= 1.1;	
	uv.x *= 1.0 + pow((abs(uv.y) / 5.0), 2.0);
	uv.y *= 1.0 + pow((abs(uv.x) / 4.0), 2.0);
	uv  = (uv / 2.0) + 0.5;
	uv =  uv *0.92 + 0.04;
	return uv;
}

vec4 scanline(vec2 uv)
{
    float line_count = 150.0;
    float s = sin(uv.y * line_count * M_PI * 2.0);
	float brightness = 0.9;
	float min_darkness = 0.5;
	s = (s * 0.5 + 0.5) * brightness + min_darkness;
	return vec4(vec3(pow(s, 0.25)), 1.0);
}

void main()
{
    vec2 uv = gl_FragCoord.xy/resolution.xy;
    uv = curve(uv);

    vec3 color = texture2D(texture, uv).rgb;
    if (uv.x < 0.0 || uv.y < 0.0 || uv.x > 1.0 || uv.y > 1.0)
        gl_FragColor = vec4(0, 0, 0, 1);
    else
        gl_FragColor = vec4(color, 1);
        
    gl_FragColor *= scanline(uv);
}
)";

std::map<std::string, sf::Shader> ShaderBank::shaders = {};

void ShaderBank::init(sf::RenderWindow &window)
{
	sf::Shader shader;
	if (!shader.loadFromMemory(fragInvert, sf::Shader::Type::Fragment))
		std::cerr << "Failed to load shader from memory" << std::endl;
	shader.setUniform("texture", sf::Shader::CurrentTexture);
	shaders["Invert"] = std::move(shader);

	if (!shader.loadFromMemory(fragCRT, sf::Shader::Type::Fragment))
		std::cerr << "Failed to load shader from memory" << std::endl;
	shader.setUniform("texture", sf::Shader::CurrentTexture);
	shader.setUniform("resolution", sf::Vector2f(window.getSize()));
	shaders["CRT"] = std::move(shader);
}
