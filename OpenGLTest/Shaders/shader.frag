#version 330

in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;

out vec4 color;

struct DirectionalLight 
{
	vec3 color;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColor = vec4(directionalLight.color, 1.0f) * directionalLight.ambientIntensity;
	
	float diffuseFactor = dot(normalize(Normal), normalize(directionalLight.direction));
	vec4 diffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;

    color = texture(theTexture, TexCoord) * (diffuseColor * ambientColor);
}