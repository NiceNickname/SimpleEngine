Texture2D Texture0;
Texture2D Texture1;
Texture2D Texture2;
Texture2D Texture3;
Texture2D Texture4;
Texture2D Texture5;
Texture2D Texture6;
Texture2D Texture7;
Texture2D Texture8;
Texture2D Texture9;
Texture2D Texture10;
Texture2D Texture11;
Texture2D Texture12;
Texture2D Texture13;
Texture2D Texture14;
Texture2D Texture15;
Texture2D Texture16;
Texture2D Texture17;
Texture2D Texture18;
Texture2D Texture19;
Texture2D Texture20;
Texture2D Texture21;
Texture2D Texture22;
Texture2D Texture23;
Texture2D Texture24;
Texture2D Texture25;
Texture2D Texture26;
Texture2D Texture27;
Texture2D Texture28;
Texture2D Texture29;
Texture2D Texture30;
Texture2D Texture31;



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
	if (texindex == 4)
		return color * Texture4.Sample(ss, texcoords);
	if (texindex == 5)
		return color * Texture5.Sample(ss, texcoords);
	if (texindex == 6)
		return color * Texture6.Sample(ss, texcoords);
	if (texindex == 7)
		return color * Texture7.Sample(ss, texcoords);
	if (texindex == 8)
		return color * Texture8.Sample(ss, texcoords);
	if (texindex == 9)
		return color * Texture9.Sample(ss, texcoords);
	if (texindex == 10)
		return color * Texture10.Sample(ss, texcoords);
	if (texindex == 11)
		return color * Texture11.Sample(ss, texcoords);
	if (texindex == 12)
		return color * Texture12.Sample(ss, texcoords);
	if (texindex == 13)
		return color * Texture13.Sample(ss, texcoords);
	if (texindex == 14)
		return color * Texture14.Sample(ss, texcoords);
	if (texindex == 15)
		return color * Texture15.Sample(ss, texcoords);
	if (texindex == 16)
		return color * Texture16.Sample(ss, texcoords);
	if (texindex == 17)
		return color * Texture17.Sample(ss, texcoords);
	if (texindex == 18)
		return color * Texture18.Sample(ss, texcoords);
	if (texindex == 19)
		return color * Texture19.Sample(ss, texcoords);
	if (texindex == 20)
		return color * Texture20.Sample(ss, texcoords);
	if (texindex == 21)
		return color * Texture21.Sample(ss, texcoords);
	if (texindex == 22)
		return color * Texture22.Sample(ss, texcoords);
	if (texindex == 23)
		return color * Texture23.Sample(ss, texcoords);
	if (texindex == 24)
		return color * Texture24.Sample(ss, texcoords);
	if (texindex == 25)
		return color * Texture25.Sample(ss, texcoords);
	if (texindex == 26)
		return color * Texture26.Sample(ss, texcoords);
	if (texindex == 27)
		return color * Texture27.Sample(ss, texcoords);
	if (texindex == 28)
		return color * Texture28.Sample(ss, texcoords);
	if (texindex == 29)
		return color * Texture29.Sample(ss, texcoords);
	if (texindex == 30)
		return color * Texture30.Sample(ss, texcoords);

	return color * Texture31.Sample(ss, texcoords);
}