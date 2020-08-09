cbuffer view
{
	float4x4 viewMatrix;
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VOut main(float4 position : POSITION, float4 color : COLOR)
{
	VOut output;
	
	output.position = mul(viewMatrix, position);
	output.color = color;

	return output;
}