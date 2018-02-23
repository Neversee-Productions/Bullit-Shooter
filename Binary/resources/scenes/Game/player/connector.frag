#ifdef GL_ES
precision lowp float;
#endif

uniform float time;
uniform vec2 resolution;


float Hash( vec2 p)
{
    vec3 p2 = vec3(p.xy,1.0);
    return fract(sin(dot(p2,vec3(37.1,61.7, 12.4)))*3758.5453123);
}

float noise(in vec2 p)
{
    vec2 i = floor(p);
    vec2 f = fract(p);
    f *= f * (3.0-2.0*f);

    return mix(mix(Hash(i + vec2(0.,0.)), Hash(i + vec2(1.,0.)),f.x),
               mix(Hash(i + vec2(0.,1.)), Hash(i + vec2(1.,1.)),f.x),
               f.y);
}

float fbm(vec2 p)
{
     float v = 0.0;
     v += noise(p*1.)*.5;
     v += noise(p*2.)*.25;
     v += noise(p*4.)*.125;
     v += noise(p*8.)*.0625;
     return v;
}

float reduceColor(float color)
{
	const float COLOR_REDUCTION = 0.05;
	if (color <= COLOR_REDUCTION)
	{
		return 0.0;
	}
	return color - COLOR_REDUCTION;
}

float determineAlpha(vec3 rgb)
{
	float alpha = 0.0;
	alpha = max(max(rgb.x, rgb.y), rgb.z);
	return alpha;
}

void main( void ) 
{

	//vec2 uv = ( gl_FragCoord.xy / resolution.xy ) - 1.0;
	vec2 uv = (gl_FragCoord.xy / resolution.xy) - 0.85;
	//uv.x *= resolution.x/resolution.y;
		
	vec3 finalColor = vec3( 0.0 );
	for( int i=1; i < 8; ++i )
	{
		float t = abs(1.0 / ((uv.x + fbm( uv + time/float(i)))*75.));
		finalColor +=  t * vec3( float(i) * 0.1 +0.1, 0.5, 2.0 );
	}
	
	finalColor.x = reduceColor(finalColor.x);
	finalColor.y = reduceColor(finalColor.y);
	finalColor.z = reduceColor(finalColor.z);
	
	gl_FragColor = vec4( finalColor, determineAlpha(finalColor) );

}