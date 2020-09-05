#version 330

in vec4 vertexColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 DirectionalLightSpacePos;

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
uniform sampler2D directionalShadowMap;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_POINT_LIGHTS];

uniform Material material;

uniform int pointLightCount;
uniform int spotLightCount;

uniform vec3 eyePosition;

float CalcDirectionalShadowFactor(DirectionalLight dLight) {
	vec3 projectCoords = DirectionalLightSpacePos.xyz / DirectionalLightSpacePos.w;
	projectCoords  = (projectCoords * .5) + .5;
	float currentDepth = projectCoords.z;

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(dLight.direction);

	float bias = max(0.05 *(1 - dot(normal, lightDir)), 0.005f);

	float shadow = 0.0;

	vec2 texelSize = 1.0/textureSize(directionalShadowMap, 0);
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			float pcfDepth = texture(directionalShadowMap, projectCoords.xy + vec2(i,j) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}

	shadow /= 9.0f;

	if (projectCoords.z > 1.0) {
		shadow = 0.0;
	}

	return shadow;
}

vec4 CalcLightByDirection(Light light, vec3 direction, float shadowFactor)
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

    return (ambientColor + (1.0 - shadowFactor) * (diffuseColor + specularColor));
}

vec4 CalcPointLight(PointLight pLight)
{
	vec3 direction = FragPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);
	vec4 color = CalcLightByDirection(pLight.base, direction, 0.0f);
	float attenuation = pLight.attenuationExponent * distance * distance +
		pLight.attenuationLinear * distance +
		pLight.attenuationConstant;
	return (color / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight) {
	vec3 rayDirection = normalize(FragPos - sLight.base.position);
	float slFactor = dot(rayDirection, sLight.direction);
	if(slFactor > sLight.edge) {
		vec4 color = CalcPointLight(sLight.base);
		return color * (1.0f - (1.0f - slFactor)*(1.0f/(1.0f - sLight.edge)));
	} else {
		return vec4(0,0,0,0);
	}
}

vec4 CalcDirectionalLight()
{
	float shadowFactor = CalcDirectionalShadowFactor(directionalLight);
	return CalcLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
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