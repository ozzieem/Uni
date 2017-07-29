#version 400
in vec3 np;
out vec4 frag_colour;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xyz + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.zzz, 1.0, 1.0), c.y);
}

void main () {
    /* resulting color from position will be greyscale
        using the above function unnecessary */
	frag_colour = vec4(-np.zzz, 0.0);
}
