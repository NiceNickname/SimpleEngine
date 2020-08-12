Texture2D Texture0 : register(t0);
Texture2D Texture1 : register(t1);
Texture2D Texture2 : register(t2);
Texture2D Texture3 : register(t3);
Texture2D Texture4 : register(t4);

SamplerState ss;

float4 main(float4 color : COLOR, float2 texcoords : TEXCOORDS, float texindex : TEXINDEX) : SV_TARGET
{
	if (texindex == 0)
		return color * Texture0.Sample(ss, texcoords);
	if (texindex == 1)
		return color * Texture1.Sample(ss, texcoords);
	if (texindex == 2)
		return color * Texture2.Sample(ss, texcoords);
	if (texindex == 3)
		return color * Texture3.Sample(ss, texcoords);
	
	return color * Texture4.Sample(ss, texcoords);
}