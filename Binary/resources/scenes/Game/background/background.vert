void main(void) 
{
	//position the shader
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	
	// transform the texture coordinates
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	
	// forward the vertex colour
	gl_FrontColor = gl_Color;
}