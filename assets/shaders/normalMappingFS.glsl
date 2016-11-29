#version 410

out vec4 FragColor;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;
in vec3 lightDirectionOut;
in vec4 vertexColoursOut;

uniform sampler2D normalSampler;

struct DirectionalLight
{
	vec3 direction;

	vec4 ambientColour;
	vec4 diffuseColour;
	vec4 specularColour;
};

uniform DirectionalLight directionLight;



uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform vec4 diffuseMaterialColour=vec4(0.8f,0.0f,0.0f,1.0f);
uniform vec4 specularMaterialColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform float specularPower=25.0f;
uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;




void main()
{
	vec3 bumpNormals = texture(normalSampler, vertexTextureCoordsOut).xyz;
	bumpNormals = normalize((bumpNormals*2.0f) - 1.0f);

	
	vec3 lightDir=normalize(-directionLight.direction);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	//float diffuseTerm = dot(vertexNormalOut, lightDir);
	//float specularTerm = pow(dot(vertexNormalOut, halfWayVec), specularPower);
	
	float diffuseTerm = dot(bumpNormals, lightDir);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), specularPower);
	

	vec4 textureColour = texture(diffuseSampler, vertexTextureCoordsOut);
	vec4 specColour = texture(specularSampler, vertexTextureCoordsOut);

	
	//FragColor = vec4 ( halfWayVec, 1.0f);
	
	FragColor = (ambientMaterialColour*directionLight.ambientColour) + (textureColour*directionLight.diffuseColour*diffuseTerm) + (specColour*directionLight.specularColour*specularTerm);
}
