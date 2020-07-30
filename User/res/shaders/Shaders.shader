

float4 VShader(float3 position : POSITION) : SV_POSITION
{
	return position;
}

float PShader() : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}