#version 330 core

uniform vec2 uResolution;
uniform float time;

out vec4 outColor;


void main() {
	vec2 uv = gl_FragCoord.xy/800;
	vec4 color = vec4(abs(uv.x * cos(time)), 0, abs(uv.y*sin(time)), 1.0);
   outColor = vec4(color);
} 