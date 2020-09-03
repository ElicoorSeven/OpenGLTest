#version 330

in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

struct Light 
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

struct PointLight 
{
	Light base;
	vec3 position;
	float attenuationConstant;
	float attenuationLinear;
	float attenuationExponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specularIntensity;
	float specularPower;
};

uniform sampler2D theTexture;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_POINT_LIGHTS];
uniform Material material;
uniform int pointLightCount;
uniform int spotLightCount;
uniform vec3 eyePosition;


vec4 CalcLightByDirection(Light light, vec3 direction)
{
	vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;
	
	float diffuseFactor = dot(normalize(Normal), normalize(direction));
	vec4 diffuseColor = vec4(light.color, 1.0f) * light.diffuseIntensity * diffuseFactor;

	vec4 specularColor = vec4(0,0,0,0);
	if (diffuseFactor > 0.0f) {
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
		float specularFactor = dot(fragToEye, reflectedVertex);
		if (specularFactor > 0.0f) {
			specularFactor = pow(specularFactor, material.specularPower);
			specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
		}
	}

    return (diffuseColor + ambientColor + specularColor);
}

vec4 CalcPointLight(PointLight light)
{
	vec3 direction = FragPos - light.position;
	float distance = length(direction);
	direction = normalize(direction);
	vec4 color = CalcLightByDirection(light.base, direction);
	float attenuation = light.attenuationExponent * distance * distance +
		light.attenuationLinear * distance +
		light.attenuationConstant;
	return (color / attenuation);
}

vec4 CalcSpotLight(SpotLight light) {
	vec3 rayDirection = normalize(FragPos - light.base.position);
	float slFactor = dot(rayDirection, light.direction);
	if(slFactor > light.edge) {
		vec4 color = CalcPointLight(light.base);
		return color * (1.0f - (1.0f - slFactor)*(1.0f/(1.0f - light.edge)));
	} else {
		return vec4(0,0,0,0);
	}
}

vec4 CalcDirectionalLight()
{
	return CalcLightByDirection(directionalLight.base, directionalLight.direction);
}

vec4 CalcPointLights() {
	vec4 totalColor = vec4(0,0,0,0);
	for (int i = 0; i < pointLightCount; i++) {
		totalColor += CalcPointLight(pointLights[i]);
	}
	return totalColor;
}
vec4 CalcSpotLights() {
	vec4 totalColor = vec4(0,0,0,0);
	for (int i = 0; i < spotLightCount; i++) {
		totalColor += CalcSpotLight(spotLights[i]);
	}
	return totalColor;
}

void main()
{
	vec4 finalColor = CalcDirectionalLight();
	finalColor += CalcPointLights();
	finalColor += CalcSpotLights();
	color = texture(theTexture, TexCoord) * finalColor;
}