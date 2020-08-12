cbuffer view
{
	float4x4 viewMatrix;
};

struct VOut
{
	float4 color : COLOR;
	float2 texcoords : TEXCOORDS;
	float TextureIndex : TEXINDEX;
	float4 position : SV_POSITION;
};

VOut main(float4 position : POSITION, float4 color : COLOR, float2 texcoords : TEXCOORDS, float texindex : TEXINDEX)
{
	VOut output;
	
	output.position = mul(viewMatrix, position);
	output.color = color;
	output.texcoords = texcoords;
	output.TextureIndex = texindex;

	return output;
}