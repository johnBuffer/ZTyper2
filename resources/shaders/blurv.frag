uniform sampler2D image;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
void main()
{
	vec2 TexCoords = gl_TexCoord[0].xy; vec2 tex_offset = 1.0 / textureSize(image, 0);
	vec3 result = texture(image, TexCoords).rgb * weight[0]; for(int i = 1; i < 5; ++i)
	{
		result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
		result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
	}
	
	gl_FragColor = vec4(result, 1.0);
}